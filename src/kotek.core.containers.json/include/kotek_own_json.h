#pragma once

// KOTEK_JSON_LIBRARY=KOTEK_OWN (task K4): kotek's own dependency-free json
// backend. This header is the DOM half: value/object/array/string plus the
// pmr-style storage (storage_ptr/static_resource/monotonic_resource) that
// ktkJson's embedded memory layouts construct with, the boost-shaped
// value_from/value_to tag_invoke customization point, and parse/serialize
// built on the streaming half (kotek_own_json_stream.h).
//
// The API mirrors the subset of boost::json the codebase actually uses, so
// call sites compile unchanged; the alias header maps the `json` namespace
// to this implementation when KOTEK_JSON_LIBRARY=KOTEK_OWN is selected.
//
// Rules honored here: no third-party includes (C/C++ standard headers
// only), no exceptions anywhere (parse errors are error_code values,
// resource exhaustion is a graceful failed-flag on the resource, type
// mismatches are KOTEK_ASSERT in debug and a safe fallback in release).
// All DOM storage lives in the pmr-style resources — no std containers
// hold document data (same design as boost::json).
//
// Semantics notes (matching boost where it matters):
//  - every value/object/array/string carries its own storage_ptr, so
//    mixed-resource trees stay consistent; deallocation always goes
//    through the owning resource's virtuals (module-safe: the resource
//    vtable dispatches into the module that created the resource);
//  - copy construction propagates the SOURCE storage, copy assignment
//    keeps the TARGET's storage (sticky), move pilfers;
//  - object preserves insertion order (serialize is stable across
//    parse/serialize round trips, which the zircon command journal
//    relies on for byte-identical state checks);
//  - doubles always serialize with a fraction or exponent marker, so a
//    round trip preserves kind (1.0 stays a double, 1 stays an integer).

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>
#include <kotek.core.defines_dependent.message/include/kotek_core_defines_dependent_message.h>

#include "kotek_own_json_stream.h"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <initializer_list>
#include <new>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

#if defined(KOTEK_USE_JSON_LIBRARY_KOTEK_OWN)

/// initial element capacity of a freshly grown array/object body
/// (small: embedded callers size their buffers tightly and growth
/// doubles from here)
#define KOTEK_DEF_OWN_JSON_INITIAL_CONTAINER_CAPACITY 2

/// scratch buffer the serializer feeds through its stream_writer
#define KOTEK_DEF_OWN_JSON_SERIALIZER_SCRATCH_SIZE 256

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

namespace json
{
	class value;
	class object;
	class array;
	class string;
	class key_value_pair;
	class object_iterator;
	class object_const_iterator;
	class array_iterator;
	class array_const_iterator;

	enum class kind : unsigned char
	{
		null = 0,
		bool_,
		int64,
		uint64,
		double_,
		string,
		array,
		object
	};

	// ------------------------------------------------------------------
	// pmr-style storage
	// ------------------------------------------------------------------

	class memory_resource
	{
	public:
		memory_resource(void) : m_failed(false) {}
		virtual ~memory_resource(void) {}

		memory_resource(const memory_resource&) = delete;
		memory_resource& operator=(const memory_resource&) = delete;

		void* allocate(size_t bytes, size_t alignment)
		{
			return this->do_allocate(bytes, alignment);
		}

		void deallocate(void* p, size_t bytes, size_t alignment)
		{
			if (p == nullptr)
				return;

			this->do_deallocate(p, bytes, alignment);
		}

		bool is_equal(const memory_resource& other) const
		{
			return this == &other;
		}

		/// sticky exhaustion flag: once an allocation failed every
		/// later DOM operation degrades gracefully instead of
		/// crashing; parsers map this to error::resource_exhausted
		bool failed(void) const { return this->m_failed; }

	protected:
		void set_failed(void)
		{
			if (this->m_failed == false)
			{
				this->m_failed = true;

				// exhaustion is an expected runtime condition in the
				// embedded configuration (tight static_resource), not
				// a logic error — warn once, degrade gracefully
				KOTEK_MESSAGE_WARNING(
					"json memory resource exhausted");
			}
		}

	private:
		virtual void* do_allocate(size_t bytes, size_t alignment) = 0;
		virtual void do_deallocate(
			void* p, size_t bytes, size_t alignment) = 0;

		bool m_failed;
	};

	namespace detail
	{
		class heap_memory_resource : public memory_resource
		{
		public:
			heap_memory_resource(void) : memory_resource() {}

		private:
			void* do_allocate(size_t bytes, size_t alignment) override
			{
				// the DOM never requests alignment above 16
				KOTEK_ASSERT(
					alignment <= 16,
					"unsupported alignment for the default json "
					"heap resource");

				if (alignment > 16)
				{
					this->set_failed();
					return nullptr;
				}

				void* p = std::malloc(bytes == 0 ? 1 : bytes);

				if (p == nullptr)
					this->set_failed();

				return p;
			}

			void do_deallocate(
				void* p, size_t bytes, size_t alignment) override
			{
				(void)bytes;
				(void)alignment;
				std::free(p);
			}
		};

		/// per-module default resource (null storage_ptr resolves
		/// here). Access is always through memory_resource virtuals,
		/// so a block allocated in one module is freed by the same
		/// module's code even when the value travels across module
		/// boundaries — the ktkI* discipline applied to storage.
		inline memory_resource* default_resource(void)
		{
			static heap_memory_resource instance;
			return &instance;
		}
	} // namespace detail

	class storage_ptr
	{
	public:
		storage_ptr(void) : m_p_resource(nullptr) {}
		storage_ptr(std::nullptr_t) : m_p_resource(nullptr) {}
		storage_ptr(memory_resource* p_resource) :
			m_p_resource(p_resource)
		{
		}

		/// resolves the default resource for null pointers
		memory_resource* get(void) const
		{
			return this->m_p_resource ? this->m_p_resource
			                          : detail::default_resource();
		}

		/// the raw pointer without default resolution
		memory_resource* get_raw(void) const
		{
			return this->m_p_resource;
		}

		explicit operator bool(void) const
		{
			return this->m_p_resource != nullptr;
		}

	private:
		memory_resource* m_p_resource;
	};

	/// fixed-buffer resource: never reallocates, exhaustion sets the
	/// failed flag and every later allocation returns nullptr (the DOM
	/// degrades to empty/partial values — never a crash)
	class static_resource : public memory_resource
	{
	public:
		static_resource(unsigned char* p_buffer, size_t size) :
			memory_resource(),
			m_p_begin(p_buffer),
			m_capacity(size),
			m_used(0)
		{
		}

		template <size_t _Size>
		explicit static_resource(unsigned char (&buffer)[_Size]) :
			static_resource(buffer, _Size)
		{
		}

		size_t used(void) const { return this->m_used; }

		size_t remaining(void) const
		{
			return this->m_capacity - this->m_used;
		}

	private:
		void* do_allocate(size_t bytes, size_t alignment) override
		{
			if (alignment == 0)
				alignment = 1;

			if (alignment > 16)
				alignment = 16;

			const size_t aligned =
				(this->m_used + (alignment - 1)) & ~(alignment - 1);

			if (aligned + bytes > this->m_capacity)
			{
				this->set_failed();
				return nullptr;
			}

			void* p = this->m_p_begin + aligned;
			this->m_used = aligned + bytes;
			return p;
		}

		void do_deallocate(
			void* p, size_t bytes, size_t alignment) override
		{
			(void)alignment;

			// lifo pop only, everything else is a no-op (same
			// contract as boost's static_resource)
			if (static_cast<unsigned char*>(p) + bytes ==
			    this->m_p_begin + this->m_used)
			{
				this->m_used -= bytes;
			}
		}

		unsigned char* m_p_begin;
		size_t m_capacity;
		size_t m_used;
	};

	/// buffer-first resource that may grow: allocates from the caller's
	/// initial buffer, then chains malloc'd blocks (freed all at once at
	/// destruction); individual deallocations are no-ops
	class monotonic_resource : public memory_resource
	{
	public:
		monotonic_resource(unsigned char* p_buffer, size_t size) :
			memory_resource(),
			m_p_head(nullptr),
			m_p_current(nullptr),
			m_current_used(0),
			m_current_size(0),
			m_external_size(size),
			m_external_used(0),
			m_p_external(p_buffer)
		{
		}

		template <size_t _Size>
		explicit monotonic_resource(unsigned char (&buffer)[_Size]) :
			monotonic_resource(buffer, _Size)
		{
		}

		~monotonic_resource(void) override
		{
			block_header* p = this->m_p_head;
			while (p)
			{
				block_header* p_next = p->p_next;
				std::free(p);
				p = p_next;
			}
		}

	private:
		struct block_header
		{
			block_header* p_next;
			size_t size;
		};

		void* bump_alloc(
			unsigned char* p_base, size_t& used, size_t limit,
			size_t bytes, size_t alignment)
		{
			const size_t aligned =
				(used + (alignment - 1)) & ~(alignment - 1);

			if (aligned + bytes > limit)
				return nullptr;

			void* p = p_base + aligned;
			used = aligned + bytes;
			return p;
		}

		void* do_allocate(size_t bytes, size_t alignment) override
		{
			if (alignment == 0)
				alignment = 1;

			if (alignment > 16)
				alignment = 16;

			if (this->m_p_external)
			{
				void* p = this->bump_alloc(
					this->m_p_external,
					this->m_external_used,
					this->m_external_size,
					bytes,
					alignment);

				if (p)
					return p;

				// the external buffer is spent exactly once
				this->m_p_external = nullptr;
			}

			void* p = this->bump_alloc(
				reinterpret_cast<unsigned char*>(this->m_p_current),
				this->m_current_used,
				this->m_current_size,
				bytes,
				alignment);

			if (p)
				return p;

			// grow: every new block doubles, with a floor that
			// keeps small documents on few blocks
			size_t new_size = this->m_current_size * 2;
			const size_t floor = 1024;
			if (new_size < floor)
				new_size = floor;

			const size_t needed = bytes + sizeof(block_header) + 16;
			if (new_size < needed)
				new_size = needed;

			block_header* p_block = static_cast<block_header*>(
				std::malloc(new_size));

			if (p_block == nullptr)
			{
				this->set_failed();
				return nullptr;
			}

			p_block->p_next = this->m_p_head;
			p_block->size = new_size - sizeof(block_header);
			this->m_p_head = p_block;
			this->m_p_current = p_block + 1;
			this->m_current_used = 0;
			this->m_current_size = p_block->size;

			return this->bump_alloc(
				reinterpret_cast<unsigned char*>(this->m_p_current),
				this->m_current_used,
				this->m_current_size,
				bytes,
				alignment);
		}

		void do_deallocate(
			void* p, size_t bytes, size_t alignment) override
		{
			(void)p;
			(void)bytes;
			(void)alignment;
			// monotonic: freed all at once at destruction
		}

		block_header* m_p_head;
		void* m_p_current;
		size_t m_current_used;
		size_t m_current_size;
		size_t m_external_size;
		size_t m_external_used;
		unsigned char* m_p_external;
	};

	namespace detail
	{
		struct string_body
		{
			// single allocation: the character storage (size + 1
			// bytes, always NUL-terminated) follows this header.
			// capacity always equals size — growth reallocates
			// exactly, which is what lets the DOM fit the tight
			// embedded parser budgets (string churn here is small)
			std::uint32_t size;
		};

		struct array_body;

		struct object_body;

		inline void* resource_allocate(
			storage_ptr sp, size_t bytes, size_t alignment)
		{
			return sp.get()->allocate(bytes, alignment);
		}

		inline void resource_deallocate(
			storage_ptr sp, void* p, size_t bytes, size_t alignment)
		{
			sp.get()->deallocate(p, bytes, alignment);
		}

		template <typename Type, typename... Arguments>
		Type* resource_new(storage_ptr sp, Arguments&&... arguments)
		{
			void* p_memory =
				resource_allocate(sp, sizeof(Type), alignof(Type));

			if (p_memory == nullptr)
				return nullptr;

			return new (p_memory)
				Type(std::forward<Arguments>(arguments)...);
		}

		template <typename Type>
		void resource_delete(storage_ptr sp, Type* p_instance)
		{
			if (p_instance == nullptr)
				return;

			p_instance->~Type();
			resource_deallocate(
				sp, p_instance, sizeof(Type), alignof(Type));
		}
	} // namespace detail

	// ------------------------------------------------------------------
	// string
	// ------------------------------------------------------------------

	class string
	{
	public:
		string(void) : m_sp(), m_p_body(nullptr) {}

		explicit string(storage_ptr sp) : m_sp(sp), m_p_body(nullptr) {}

		string(string_view view, storage_ptr sp = {}) :
			m_sp(sp),
			m_p_body(nullptr)
		{
			this->assign(view);
		}

		string(const char* p_text, storage_ptr sp = {}) :
			string(p_text ? string_view(p_text) : string_view(), sp)
		{
		}

		/// copy: propagates the source storage
		string(const string& other) :
			m_sp(other.m_sp),
			m_p_body(nullptr)
		{
			if (other.m_p_body)
				this->assign(string_view(other.data(), other.size()));
		}

		/// copy into an explicit storage (ktkJson's embedded layout
		/// constructs its members through this form)
		string(const string& other, storage_ptr sp) :
			m_sp(sp),
			m_p_body(nullptr)
		{
			if (other.m_p_body)
				this->assign(string_view(other.data(), other.size()));
		}

		string(string&& other) noexcept :
			m_sp(other.m_sp),
			m_p_body(other.m_p_body)
		{
			other.m_p_body = nullptr;
		}

		~string(void) { this->destroy(); }

		/// sticky storage: the copy allocates from this string's
		/// resource, not the source's
		string& operator=(const string& other)
		{
			if (this != &other)
				this->assign(string_view(other.data(), other.size()));

			return *this;
		}

		string& operator=(string&& other) noexcept
		{
			if (this != &other)
			{
				this->destroy();
				this->m_sp = other.m_sp;
				this->m_p_body = other.m_p_body;
				other.m_p_body = nullptr;
			}

			return *this;
		}

		string& operator=(const char* p_text)
		{
			this->assign(
				p_text ? string_view(p_text) : string_view());
			return *this;
		}

		string& operator=(string_view view)
		{
			this->assign(view);
			return *this;
		}

		void append(string_view view)
		{
			if (view.empty())
				return;

			const size_t old_size = this->size();
			const size_t new_size = old_size + view.size();

			if (this->reserve(new_size + 1) == false)
				return;

			std::memcpy(
				this->chars() + old_size, view.data(), view.size());

			this->m_p_body->size =
				static_cast<std::uint32_t>(new_size);
			this->chars()[new_size] = '\0';
		}

		/// grows the character storage to hold at least the given
		/// byte count (content length + NUL)
		bool reserve(size_t capacity)
		{
			const size_t old_size = this->size();

			if (this->m_p_body && capacity <= old_size + 1)
				return true;

			detail::string_body* p_new =
				static_cast<detail::string_body*>(
					detail::resource_allocate(
						this->m_sp,
						sizeof(detail::string_body) + capacity,
						alignof(detail::string_body)));

			if (p_new == nullptr)
				return false;

			if (this->m_p_body)
			{
				std::memcpy(p_new + 1, this->chars(), old_size);

				detail::resource_deallocate(
					this->m_sp,
					this->m_p_body,
					sizeof(detail::string_body) + old_size + 1,
					alignof(detail::string_body));
			}

			this->m_p_body = p_new;
			this->m_p_body->size =
				static_cast<std::uint32_t>(old_size);
			this->chars()[old_size] = '\0';
			return true;
		}

		const char* c_str(void) const
		{
			return this->m_p_body
				? reinterpret_cast<const char*>(this->m_p_body + 1)
				: "";
		}

		const char* data(void) const { return this->c_str(); }

		size_t size(void) const
		{
			return this->m_p_body ? this->m_p_body->size : 0;
		}

		bool empty(void) const { return this->size() == 0; }

		const char* begin(void) const { return this->c_str(); }

		const char* end(void) const
		{
			return this->c_str() + this->size();
		}

		char operator[](size_t index) const
		{
			KOTEK_ASSERT(index < this->size(), "out of bounds");
			return this->c_str()[index];
		}

		storage_ptr storage(void) const { return this->m_sp; }

		operator string_view(void) const
		{
			return string_view(this->data(), this->size());
		}

		/// lets `ktk cstring result; result = json::serialize(x);`
		/// compile against any string-like target constructible from
		/// an iterator pair (std::basic_string, etl strings, ...)
		template <
			typename StringType,
			typename = std::enable_if_t<
				std::is_constructible_v<
					StringType,
					const char*,
					const char*> &&
				!std::is_same_v<StringType, string>>>
		operator StringType(void) const
		{
			return StringType(this->begin(), this->end());
		}

	private:
		char* chars(void)
		{
			return reinterpret_cast<char*>(this->m_p_body + 1);
		}

		void assign(string_view view)
		{
			if (view.empty())
			{
				this->destroy();
				return;
			}

			if (this->reserve(view.size() + 1) == false)
			{
				// exhausted resource: degrade to empty, the
				// failed flag on the resource reports it
				return;
			}

			std::memcpy(this->chars(), view.data(), view.size());

			this->m_p_body->size =
				static_cast<std::uint32_t>(view.size());
			this->chars()[view.size()] = '\0';
		}

		void destroy(void)
		{
			if (this->m_p_body)
			{
				detail::resource_deallocate(
					this->m_sp,
					this->m_p_body,
					sizeof(detail::string_body) +
						this->m_p_body->size + 1,
					alignof(detail::string_body));

				this->m_p_body = nullptr;
			}
		}

		storage_ptr m_sp;
		detail::string_body* m_p_body;
	};

	inline bool operator==(const string& left, const string& right)
	{
		if (left.size() != right.size())
			return false;

		if (left.size() == 0)
			return true;

		return std::memcmp(left.data(), right.data(), left.size()) == 0;
	}

	inline bool operator!=(const string& left, const string& right)
	{
		return (left == right) == false;
	}

	inline bool operator==(const string& left, const char* p_right)
	{
		return string_view(left.data(), left.size()) ==
			string_view(p_right ? p_right : "");
	}

	inline bool operator==(const char* p_left, const string& right)
	{
		return right == p_left;
	}

	inline bool operator!=(const string& left, const char* p_right)
	{
		return (left == p_right) == false;
	}

	inline bool operator!=(const char* p_left, const string& right)
	{
		return (right == p_left) == false;
	}

	// ------------------------------------------------------------------
	// object / array (member function definitions follow value — the
	// element type must be complete first)
	// ------------------------------------------------------------------

	class object
	{
	public:
		using iterator = object_iterator;
		using const_iterator = object_const_iterator;

		object(void);
		explicit object(storage_ptr sp);
		object(const object& other);
		object(const object& other, storage_ptr sp);
		object(object&& other) noexcept;
		~object(void);

		object& operator=(const object& other);
		object& operator=(object&& other) noexcept;

		value& operator[](string_view key);
		value& at(string_view key);
		const value& at(string_view key) const;

		iterator find(string_view key);
		const_iterator find(string_view key) const;

		iterator begin(void);
		iterator end(void);
		const_iterator begin(void) const;
		const_iterator end(void) const;

		bool empty(void) const;
		size_t size(void) const;

		storage_ptr storage(void) const { return this->m_sp; }

	private:
		detail::object_body* m_p_body;
		storage_ptr m_sp;
	};

	class array
	{
	public:
		using iterator = array_iterator;
		using const_iterator = array_const_iterator;

		array(void);
		explicit array(storage_ptr sp);
		array(const array& other);
		array(const array& other, storage_ptr sp);
		array(array&& other) noexcept;
		array(std::initializer_list<value> elements, storage_ptr sp = {});
		template <
			typename Iterator,
			typename = std::enable_if_t<
				!std::is_integral_v<Iterator>>>
		array(Iterator first, Iterator last, storage_ptr sp = {});
		~array(void);

		array& operator=(const array& other);
		array& operator=(array&& other) noexcept;
		array& operator=(std::initializer_list<value> elements);

		void push_back(const value& element);
		void push_back(value&& element);

		template <typename... Arguments>
		value& emplace_back(Arguments&&... arguments);

		value& operator[](size_t index);
		const value& operator[](size_t index) const;

		iterator begin(void);
		iterator end(void);
		const_iterator begin(void) const;
		const_iterator end(void) const;

		bool empty(void) const;
		size_t size(void) const;

		storage_ptr storage(void) const { return this->m_sp; }

	private:
		detail::array_body* m_p_body;
		storage_ptr m_sp;
	};

	// ------------------------------------------------------------------
	// value
	// ------------------------------------------------------------------

	class value
	{
	public:
		value(void) : m_kind(kind::null)
		{
			this->m_payload.scalar.data.p = nullptr;
		}

		explicit value(storage_ptr sp) : m_kind(kind::null)
		{
			this->m_payload.scalar.sp = sp;
			this->m_payload.scalar.data.p = nullptr;
		}

		value(std::nullptr_t, storage_ptr sp = {}) : m_kind(kind::null)
		{
			this->m_payload.scalar.sp = sp;
			this->m_payload.scalar.data.p = nullptr;
		}

		template <
			typename Type,
			typename = std::enable_if_t<std::is_same_v<Type, bool>>>
		value(Type data, storage_ptr sp = {}) : m_kind(kind::bool_)
		{
			this->m_payload.scalar.sp = sp;
			this->m_payload.scalar.data.b = data;
		}

		template <
			typename Type,
			typename = std::enable_if_t<
				std::is_integral_v<Type> &&
				!std::is_same_v<Type, bool>>,
			typename = void>
		value(Type data, storage_ptr sp = {})
		{
			this->m_payload.scalar.sp = sp;

			if constexpr (std::is_signed_v<Type>)
			{
				this->m_kind = kind::int64;
				this->m_payload.scalar.data.i =
					static_cast<std::int64_t>(data);
			}
			else
			{
				this->m_kind = kind::uint64;
				this->m_payload.scalar.data.u =
					static_cast<std::uint64_t>(data);
			}
		}

		template <
			typename Type,
			typename = std::enable_if_t<std::is_floating_point_v<Type>>,
			typename = void,
			typename = void>
		value(Type data, storage_ptr sp = {}) : m_kind(kind::double_)
		{
			this->m_payload.scalar.sp = sp;
			this->m_payload.scalar.data.d = static_cast<double>(data);
		}

		value(const char* p_text, storage_ptr sp = {}) :
			m_kind(kind::string)
		{
			new (&this->m_payload.s) string(
				p_text ? string_view(p_text) : string_view(), sp);
		}

		value(string_view view, storage_ptr sp = {}) :
			m_kind(kind::string)
		{
			new (&this->m_payload.s) string(view, sp);
		}

		value(const string& data, storage_ptr sp = {}) :
			m_kind(kind::string)
		{
			new (&this->m_payload.s)
				string(data, sp.get_raw() ? sp : data.storage());
		}

		value(string&& data, storage_ptr sp = {}) : m_kind(kind::string)
		{
			if (sp.get_raw())
				new (&this->m_payload.s) string(data, sp);
			else
				new (&this->m_payload.s) string(std::move(data));
		}

		value(const object& data, storage_ptr sp = {});
		value(object&& data, storage_ptr sp = {});
		value(const array& data, storage_ptr sp = {});
		value(array&& data, storage_ptr sp = {});

		/// deep copy, propagates the source storage
		value(const value& other)
		{
			this->copy_payload(other, other.current_sp());
		}

		/// deep copy into an explicit storage
		value(const value& other, storage_ptr sp)
		{
			this->copy_payload(other, sp);
		}

		value(value&& other) noexcept
		{
			this->pilfer(other);
		}

		~value(void) { this->destroy_payload(); }

		/// sticky: the copy lands in this value's storage
		value& operator=(const value& other)
		{
			if (this != &other)
			{
				const storage_ptr target = this->current_sp();
				this->destroy_payload();
				this->copy_payload(other, target);
			}

			return *this;
		}

		/// pilfers: this value takes over the source's storage and
		/// payload, the source becomes null
		value& operator=(value&& other) noexcept
		{
			if (this != &other)
			{
				this->destroy_payload();
				this->pilfer(other);
			}

			return *this;
		}

		value& operator=(const object& data);
		value& operator=(object&& data) noexcept;
		value& operator=(const array& data);
		value& operator=(array&& data) noexcept;

		value& operator=(const string& data)
		{
			const storage_ptr target = this->current_sp();
			this->destroy_payload();
			this->m_kind = kind::string;
			new (&this->m_payload.s) string(data, target);
			return *this;
		}

		value& operator=(string&& data) noexcept
		{
			this->destroy_payload();
			this->m_kind = kind::string;
			new (&this->m_payload.s) string(std::move(data));
			return *this;
		}

		value& operator=(const char* p_text)
		{
			const storage_ptr target = this->current_sp();
			this->destroy_payload();
			this->m_kind = kind::string;
			new (&this->m_payload.s) string(
				p_text ? string_view(p_text) : string_view(), target);
			return *this;
		}

		value& operator=(string_view view)
		{
			const storage_ptr target = this->current_sp();
			this->destroy_payload();
			this->m_kind = kind::string;
			new (&this->m_payload.s) string(view, target);
			return *this;
		}

		value& operator=(bool data)
		{
			const storage_ptr target = this->current_sp();
			this->destroy_payload();
			this->m_kind = kind::bool_;
			this->m_payload.scalar.sp = target;
			this->m_payload.scalar.data.b = data;
			return *this;
		}

		template <
			typename Type,
			typename = std::enable_if_t<
				std::is_integral_v<Type> &&
				!std::is_same_v<Type, bool>>>
		value& operator=(Type data)
		{
			const storage_ptr target = this->current_sp();
			this->destroy_payload();

			this->m_payload.scalar.sp = target;

			if constexpr (std::is_signed_v<Type>)
			{
				this->m_kind = kind::int64;
				this->m_payload.scalar.data.i =
					static_cast<std::int64_t>(data);
			}
			else
			{
				this->m_kind = kind::uint64;
				this->m_payload.scalar.data.u =
					static_cast<std::uint64_t>(data);
			}

			return *this;
		}

		template <
			typename Type,
			typename = std::enable_if_t<std::is_floating_point_v<Type>>,
			typename = void>
		value& operator=(Type data)
		{
			const storage_ptr target = this->current_sp();
			this->destroy_payload();
			this->m_kind = kind::double_;
			this->m_payload.scalar.sp = target;
			this->m_payload.scalar.data.d = static_cast<double>(data);
			return *this;
		}

		kind get_kind(void) const { return this->m_kind; }

		bool is_null(void) const { return this->m_kind == kind::null; }
		bool is_bool(void) const { return this->m_kind == kind::bool_; }
		bool is_int64(void) const
		{
			return this->m_kind == kind::int64;
		}
		bool is_uint64(void) const
		{
			return this->m_kind == kind::uint64;
		}
		bool is_double(void) const
		{
			return this->m_kind == kind::double_;
		}
		bool is_string(void) const
		{
			return this->m_kind == kind::string;
		}
		bool is_array(void) const
		{
			return this->m_kind == kind::array;
		}
		bool is_object(void) const
		{
			return this->m_kind == kind::object;
		}

		bool as_bool(void) const
		{
			if (this->m_kind != kind::bool_)
			{
				KOTEK_ASSERT(false, "as_bool on a non-bool json value");
				return false;
			}

			return this->m_payload.scalar.data.b;
		}

		std::int64_t as_int64(void) const
		{
			if (this->m_kind == kind::int64)
				return this->m_payload.scalar.data.i;

			if (this->m_kind == kind::uint64 &&
			    this->m_payload.scalar.data.u <=
			        static_cast<std::uint64_t>(INT64_MAX))
			{
				return static_cast<std::int64_t>(
					this->m_payload.scalar.data.u);
			}

			KOTEK_ASSERT(false, "as_int64 on a non-int64 json value");
			return 0;
		}

		std::uint64_t as_uint64(void) const
		{
			if (this->m_kind == kind::uint64)
				return this->m_payload.scalar.data.u;

			if (this->m_kind == kind::int64 &&
			    this->m_payload.scalar.data.i >= 0)
			{
				return static_cast<std::uint64_t>(
					this->m_payload.scalar.data.i);
			}

			KOTEK_ASSERT(false, "as_uint64 on a non-uint64 json value");
			return 0;
		}

		double as_double(void) const
		{
			if (this->m_kind != kind::double_)
			{
				KOTEK_ASSERT(
					false, "as_double on a non-double json value");
				return 0.0;
			}

			return this->m_payload.scalar.data.d;
		}

		const string& as_string(void) const;
		const object& as_object(void) const;
		const array& as_array(void) const;

		object& as_object(void);
		array& as_array(void);

		/// numeric conversion tolerant to any numeric kind (int64,
		/// uint64 and double all convert), like boost's to_number
		template <typename Type>
		Type to_number(void) const
		{
			switch (this->m_kind)
			{
			case kind::int64:
				return static_cast<Type>(this->m_payload.scalar.data.i);
			case kind::uint64:
				return static_cast<Type>(this->m_payload.scalar.data.u);
			case kind::double_:
				return static_cast<Type>(this->m_payload.scalar.data.d);
			default:
				KOTEK_ASSERT(
					false, "to_number on a non-numeric json value");
				return Type{};
			}
		}

		storage_ptr storage(void) const { return this->current_sp(); }

	private:
		/// every payload member keeps its storage pointer in the same
		/// leading position — scalars through the scalar storage,
		/// containers through their wrapper class
		storage_ptr current_sp(void) const
		{
			switch (this->m_kind)
			{
			case kind::string:
				return this->m_payload.s.storage();
			case kind::array:
				return this->m_payload.a.storage();
			case kind::object:
				return this->m_payload.o.storage();
			default:
				return this->m_payload.scalar.sp;
			}
		}

		void destroy_payload(void)
		{
			switch (this->m_kind)
			{
			case kind::string:
				this->m_payload.s.~string();
				break;
			case kind::array:
				this->m_payload.a.~array();
				break;
			case kind::object:
				this->m_payload.o.~object();
				break;
			default:
				break;
			}

			this->m_kind = kind::null;
			this->m_payload.scalar.sp = storage_ptr();
			this->m_payload.scalar.data.p = nullptr;
		}

		/// this value must be freshly constructed or destroyed first
		void copy_payload(const value& other, storage_ptr target)
		{
			this->m_kind = other.m_kind;

			switch (other.m_kind)
			{
			case kind::bool_:
			case kind::int64:
			case kind::uint64:
			case kind::double_:
				this->m_payload.scalar.sp = target;
				this->m_payload.scalar.data = other.m_payload.scalar.data;
				break;
			case kind::string:
				new (&this->m_payload.s)
					string(other.m_payload.s, target);
				break;
			case kind::array:
				new (&this->m_payload.a)
					array(other.m_payload.a, target);
				break;
			case kind::object:
				new (&this->m_payload.o)
					object(other.m_payload.o, target);
				break;
			default:
				this->m_payload.scalar.sp = target;
				this->m_payload.scalar.data.p = nullptr;
				break;
			}
		}

		void pilfer(value& other)
		{
			this->m_kind = other.m_kind;

			switch (other.m_kind)
			{
			case kind::string:
				new (&this->m_payload.s)
					string(std::move(other.m_payload.s));
				other.m_payload.s.~string();
				break;
			case kind::array:
				new (&this->m_payload.a)
					array(std::move(other.m_payload.a));
				other.m_payload.a.~array();
				break;
			case kind::object:
				new (&this->m_payload.o)
					object(std::move(other.m_payload.o));
				other.m_payload.o.~object();
				break;
			default:
				this->m_payload.scalar = other.m_payload.scalar;
				break;
			}

			other.m_kind = kind::null;
			other.m_payload.scalar.sp = storage_ptr();
			other.m_payload.scalar.data.p = nullptr;
		}

		struct scalar_storage
		{
			scalar_storage(void) : sp(), data() {}

			storage_ptr sp;

			union data_union
			{
				data_union(void) : p(nullptr) {}
				~data_union(void) {}

				bool b;
				std::int64_t i;
				std::uint64_t u;
				double d;
				void* p;
			} data;
		};

		union payload_union
		{
			payload_union(void) : scalar() {}
			~payload_union(void) {}

			scalar_storage scalar;
			string s;
			array a;
			object o;
		};

		kind m_kind;
		payload_union m_payload;
	};

	namespace detail
	{
		/// returned by fallible accessors when the resource is
		/// exhausted or the key is missing; the KOTEK_ASSERT on the
		/// path catches the logic error in debug, release degrades to
		/// writes into a scratch null value (boost throws here)
		inline value& fallback_value(void)
		{
			static value instance;
			return instance;
		}

		inline const object& fallback_object(void)
		{
			static const object instance{};
			return instance;
		}

		inline const array& fallback_array(void)
		{
			static const array instance{};
			return instance;
		}

		inline const string& fallback_string(void)
		{
			static const string instance{};
			return instance;
		}

		inline object& fallback_object_mutable(void)
		{
			static object instance{};
			return instance;
		}

		inline array& fallback_array_mutable(void)
		{
			static array instance{};
			return instance;
		}
	} // namespace detail

	inline const string& value::as_string(void) const
	{
		if (this->m_kind != kind::string)
		{
			KOTEK_ASSERT(false, "as_string on a non-string json value");
			return detail::fallback_string();
		}

		return this->m_payload.s;
	}

	inline const object& value::as_object(void) const
	{
		if (this->m_kind != kind::object)
		{
			KOTEK_ASSERT(false, "as_object on a non-object json value");
			return detail::fallback_object();
		}

		return this->m_payload.o;
	}

	inline const array& value::as_array(void) const
	{
		if (this->m_kind != kind::array)
		{
			KOTEK_ASSERT(false, "as_array on a non-array json value");
			return detail::fallback_array();
		}

		return this->m_payload.a;
	}

	inline object& value::as_object(void)
	{
		if (this->m_kind != kind::object)
		{
			KOTEK_ASSERT(false, "as_object on a non-object json value");
			return detail::fallback_object_mutable();
		}

		return this->m_payload.o;
	}

	inline array& value::as_array(void)
	{
		if (this->m_kind != kind::array)
		{
			KOTEK_ASSERT(false, "as_array on a non-array json value");
			return detail::fallback_array_mutable();
		}

		return this->m_payload.a;
	}

	// ------------------------------------------------------------------
	// object / array storage bodies
	// ------------------------------------------------------------------

	namespace detail
	{
		struct object_slot
		{
			// keys are NUL-terminated (compared with a length
			// check + memcmp), so a slot is exactly key pointer +
			// value — the leanest layout that keeps insertion order
			char* p_key;
			value entry;
		};

		struct object_body
		{
			// single allocation: the slot array (capacity entries)
			// follows this header
			std::uint32_t size;
			std::uint32_t capacity;
		};

		struct array_body
		{
			// single allocation: the value array follows this header
			std::uint32_t size;
			std::uint32_t capacity;
		};

		inline object_slot* object_slots(object_body* p_body)
		{
			return reinterpret_cast<object_slot*>(p_body + 1);
		}

		inline const object_slot* object_slots(const object_body* p_body)
		{
			return reinterpret_cast<const object_slot*>(p_body + 1);
		}

		inline value* array_items(array_body* p_body)
		{
			return reinterpret_cast<value*>(p_body + 1);
		}

		inline const value* array_items(const array_body* p_body)
		{
			return reinterpret_cast<const value*>(p_body + 1);
		}

		inline bool object_key_equals(const char* p_key, string_view key)
		{
			const size_t stored_length = std::strlen(p_key);

			if (stored_length != key.size())
				return false;

			if (stored_length == 0)
				return true;

			return std::memcmp(p_key, key.data(), stored_length) == 0;
		}
	} // namespace detail

	// ------------------------------------------------------------------
	// key_value_pair — the proxy object iteration yields (same shape as
	// boost: key_c_str()/value() over storage owned by the object)
	// ------------------------------------------------------------------

	class key_value_pair
	{
	public:
		key_value_pair(const char* p_key, json::value* p_entry)
			:
			m_p_key(p_key),
			m_p_entry(p_entry)
		{
		}

		string_view key(void) const
		{
			return string_view(this->m_p_key);
		}

		const char* key_c_str(void) const { return this->m_p_key; }

		// qualified json::value everywhere: the member function's own
		// name hides the type inside this class (same rule that makes
		// boost spell these qualified)
		json::value& value(void) { return *this->m_p_entry; }

		const json::value& value(void) const { return *this->m_p_entry; }

	private:
		const char* m_p_key;
		json::value* m_p_entry;
	};

	class object_iterator
	{
	public:
		object_iterator(void) : m_p_slot(nullptr) {}
		explicit object_iterator(detail::object_slot* p_slot) :
			m_p_slot(p_slot)
		{
		}

		key_value_pair operator*(void) const
		{
			return key_value_pair(
				this->m_p_slot->p_key, &this->m_p_slot->entry);
		}

		object_iterator& operator++(void)
		{
			++this->m_p_slot;
			return *this;
		}

		object_iterator operator++(int)
		{
			object_iterator copy = *this;
			++this->m_p_slot;
			return copy;
		}

		bool operator==(const object_iterator& other) const
		{
			return this->m_p_slot == other.m_p_slot;
		}

		bool operator!=(const object_iterator& other) const
		{
			return this->m_p_slot != other.m_p_slot;
		}

	private:
		detail::object_slot* m_p_slot;
	};

	class object_const_iterator
	{
	public:
		object_const_iterator(void) : m_p_slot(nullptr) {}
		explicit object_const_iterator(const detail::object_slot* p_slot)
			:
			m_p_slot(p_slot)
		{
		}

		key_value_pair operator*(void) const
		{
			return key_value_pair(
				this->m_p_slot->p_key,
				const_cast<value*>(&this->m_p_slot->entry));
		}

		object_const_iterator& operator++(void)
		{
			++this->m_p_slot;
			return *this;
		}

		object_const_iterator operator++(int)
		{
			object_const_iterator copy = *this;
			++this->m_p_slot;
			return copy;
		}

		bool operator==(const object_const_iterator& other) const
		{
			return this->m_p_slot == other.m_p_slot;
		}

		bool operator!=(const object_const_iterator& other) const
		{
			return this->m_p_slot != other.m_p_slot;
		}

	private:
		const detail::object_slot* m_p_slot;
	};

	class array_iterator
	{
	public:
		array_iterator(void) : m_p_item(nullptr) {}
		explicit array_iterator(value* p_item) : m_p_item(p_item) {}

		value& operator*(void) const { return *this->m_p_item; }

		array_iterator& operator++(void)
		{
			++this->m_p_item;
			return *this;
		}

		array_iterator operator++(int)
		{
			array_iterator copy = *this;
			++this->m_p_item;
			return copy;
		}

		bool operator==(const array_iterator& other) const
		{
			return this->m_p_item == other.m_p_item;
		}

		bool operator!=(const array_iterator& other) const
		{
			return this->m_p_item != other.m_p_item;
		}

	private:
		value* m_p_item;
	};

	class array_const_iterator
	{
	public:
		array_const_iterator(void) : m_p_item(nullptr) {}
		explicit array_const_iterator(const value* p_item) :
			m_p_item(p_item)
		{
		}

		const value& operator*(void) const { return *this->m_p_item; }

		array_const_iterator& operator++(void)
		{
			++this->m_p_item;
			return *this;
		}

		array_const_iterator operator++(int)
		{
			array_const_iterator copy = *this;
			++this->m_p_item;
			return copy;
		}

		bool operator==(const array_const_iterator& other) const
		{
			return this->m_p_item == other.m_p_item;
		}

		bool operator!=(const array_const_iterator& other) const
		{
			return this->m_p_item != other.m_p_item;
		}

	private:
		const value* m_p_item;
	};

	// ------------------------------------------------------------------
	// object implementation
	// ------------------------------------------------------------------

	namespace detail
	{
		inline void object_slot_destroy(storage_ptr sp, object_slot& slot)
		{
			if (slot.p_key)
			{
				resource_deallocate(
					sp, slot.p_key, std::strlen(slot.p_key) + 1, 1);
				slot.p_key = nullptr;
			}

			slot.entry.~value();
		}

		inline void object_body_destroy(storage_ptr sp, object_body* p_body)
		{
			if (p_body == nullptr)
				return;

			object_slot* p_slots = object_slots(p_body);

			for (std::uint32_t i = 0; i < p_body->size; ++i)
				object_slot_destroy(sp, p_slots[i]);

			resource_deallocate(
				sp,
				p_body,
				sizeof(object_body) +
					p_body->capacity * sizeof(object_slot),
				alignof(object_slot));
		}

		/// linear search over the slots (house rule: lookup table on
		/// a vector — object element counts are small and this stays
		/// cache-friendly)
		inline size_t object_find_index(
			const object_body* p_body, string_view key)
		{
			if (p_body == nullptr)
				return static_cast<size_t>(-1);

			const object_slot* p_slots = object_slots(p_body);

			for (std::uint32_t i = 0; i < p_body->size; ++i)
			{
				if (object_key_equals(p_slots[i].p_key, key))
					return i;
			}

			return static_cast<size_t>(-1);
		}

		/// (re)allocates the body — header and slots live in one
		/// block, so growth replaces the whole allocation
		inline bool object_grow(storage_ptr sp, object_body*& p_body)
		{
			const std::uint32_t new_capacity =
				p_body == nullptr
				? KOTEK_DEF_OWN_JSON_INITIAL_CONTAINER_CAPACITY
				: p_body->capacity * 2;

			object_body* p_new = static_cast<object_body*>(
				resource_allocate(
					sp,
					sizeof(object_body) +
						new_capacity * sizeof(object_slot),
					alignof(object_slot)));

			if (p_new == nullptr)
				return false;

			object_slot* p_new_slots = object_slots(p_new);

			const std::uint32_t old_size = p_body ? p_body->size : 0;

			if (p_body)
			{
				object_slot* p_old_slots = object_slots(p_body);

				for (std::uint32_t i = 0; i < old_size; ++i)
				{
					new (&p_new_slots[i]) object_slot{
						p_old_slots[i].p_key,
						std::move(p_old_slots[i].entry)};

					p_old_slots[i].p_key = nullptr;
					p_old_slots[i].entry.~value();
				}

				resource_deallocate(
					sp,
					p_body,
					sizeof(object_body) +
						p_body->capacity * sizeof(object_slot),
					alignof(object_slot));
			}

			p_new->size = old_size;
			p_new->capacity = new_capacity;
			p_body = p_new;
			return true;
		}

		/// deep copy of other's content into sp preserving order
		inline bool object_copy_into(
			object_body*& p_target,
			storage_ptr target_sp,
			const object_body* p_source)
		{
			if (p_source == nullptr)
				return true;

			const object_slot* p_source_slots = object_slots(p_source);

			for (std::uint32_t i = 0; i < p_source->size; ++i)
			{
				const object_slot& source_slot = p_source_slots[i];

				if ((p_target == nullptr ||
				     p_target->size == p_target->capacity) &&
				    object_grow(target_sp, p_target) == false)
				{
					return false;
				}

				object_slot* p_slot =
					&object_slots(p_target)[p_target->size];

				const size_t key_length = std::strlen(source_slot.p_key);

				char* p_key = static_cast<char*>(resource_allocate(
					target_sp, key_length + 1, 1));

				if (p_key == nullptr)
					return false;

				std::memcpy(p_key, source_slot.p_key, key_length);
				p_key[key_length] = '\0';

				new (p_slot) object_slot{
					p_key, value(source_slot.entry, target_sp)};

				++p_target->size;
			}

			return true;
		}

		inline void array_body_destroy(storage_ptr sp, array_body* p_body)
		{
			if (p_body == nullptr)
				return;

			value* p_items = array_items(p_body);

			for (std::uint32_t i = 0; i < p_body->size; ++i)
				p_items[i].~value();

			resource_deallocate(
				sp,
				p_body,
				sizeof(array_body) + p_body->capacity * sizeof(value),
				alignof(value));
		}

		inline bool array_grow(storage_ptr sp, array_body*& p_body)
		{
			const std::uint32_t new_capacity =
				p_body == nullptr
				? KOTEK_DEF_OWN_JSON_INITIAL_CONTAINER_CAPACITY
				: p_body->capacity * 2;

			array_body* p_new = static_cast<array_body*>(
				resource_allocate(
					sp,
					sizeof(array_body) + new_capacity * sizeof(value),
					alignof(value)));

			if (p_new == nullptr)
				return false;

			value* p_new_items = array_items(p_new);

			const std::uint32_t old_size = p_body ? p_body->size : 0;

			if (p_body)
			{
				value* p_old_items = array_items(p_body);

				for (std::uint32_t i = 0; i < old_size; ++i)
				{
					new (&p_new_items[i])
						value(std::move(p_old_items[i]));
					p_old_items[i].~value();
				}

				resource_deallocate(
					sp,
					p_body,
					sizeof(array_body) +
						p_body->capacity * sizeof(value),
					alignof(value));
			}

			p_new->size = old_size;
			p_new->capacity = new_capacity;
			p_body = p_new;
			return true;
		}

		inline bool array_copy_into(
			array_body*& p_target,
			storage_ptr target_sp,
			const array_body* p_source)
		{
			if (p_source == nullptr)
				return true;

			const value* p_source_items = array_items(p_source);

			for (std::uint32_t i = 0; i < p_source->size; ++i)
			{
				if ((p_target == nullptr ||
				     p_target->size == p_target->capacity) &&
				    array_grow(target_sp, p_target) == false)
				{
					return false;
				}

				new (&array_items(p_target)[p_target->size])
					value(p_source_items[i], target_sp);

				++p_target->size;
			}

			return true;
		}
	} // namespace detail

	inline object::object(void) : m_p_body(nullptr), m_sp() {}

	inline object::object(storage_ptr sp) : m_p_body(nullptr), m_sp(sp) {}

	inline object::object(const object& other) :
		m_p_body(nullptr),
		m_sp(other.m_sp)
	{
		detail::object_copy_into(
			this->m_p_body, this->m_sp, other.m_p_body);
	}

	inline object::object(const object& other, storage_ptr sp) :
		m_p_body(nullptr),
		m_sp(sp)
	{
		detail::object_copy_into(
			this->m_p_body, this->m_sp, other.m_p_body);
	}

	inline object::object(object&& other) noexcept :
		m_p_body(other.m_p_body),
		m_sp(other.m_sp)
	{
		other.m_p_body = nullptr;
	}

	inline object::~object(void)
	{
		detail::object_body_destroy(this->m_sp, this->m_p_body);
	}

	inline object& object::operator=(const object& other)
	{
		if (this != &other)
		{
			detail::object_body_destroy(this->m_sp, this->m_p_body);
			this->m_p_body = nullptr;

			detail::object_copy_into(
				this->m_p_body, this->m_sp, other.m_p_body);
		}

		return *this;
	}

	inline object& object::operator=(object&& other) noexcept
	{
		if (this != &other)
		{
			detail::object_body_destroy(this->m_sp, this->m_p_body);
			this->m_p_body = other.m_p_body;
			this->m_sp = other.m_sp;
			other.m_p_body = nullptr;
		}

		return *this;
	}

	inline value& object::operator[](string_view key)
	{
		const size_t index =
			detail::object_find_index(this->m_p_body, key);

		if (index != static_cast<size_t>(-1))
			return detail::object_slots(this->m_p_body)[index].entry;

		if ((this->m_p_body == nullptr ||
		     this->m_p_body->size == this->m_p_body->capacity) &&
		    detail::object_grow(this->m_sp, this->m_p_body) == false)
		{
			// resource exhausted — the failed flag on the
			// resource reports it; degrade to a scratch value
			return detail::fallback_value();
		}

		detail::object_slot* p_slot =
			&detail::object_slots(this->m_p_body)[this->m_p_body->size];

		char* p_key = static_cast<char*>(detail::resource_allocate(
			this->m_sp, key.size() + 1, 1));

		if (p_key == nullptr)
		{
			// resource exhausted, same degradation
			return detail::fallback_value();
		}

		if (key.empty() == false)
			std::memcpy(p_key, key.data(), key.size());

		p_key[key.size()] = '\0';

		new (p_slot) detail::object_slot{p_key, value(this->m_sp)};

		++this->m_p_body->size;

		return p_slot->entry;
	}

	inline value& object::at(string_view key)
	{
		const size_t index =
			detail::object_find_index(this->m_p_body, key);

		if (index == static_cast<size_t>(-1))
		{
			KOTEK_ASSERT(false, "json object::at with a missing key");
			return detail::fallback_value();
		}

		return detail::object_slots(this->m_p_body)[index].entry;
	}

	inline const value& object::at(string_view key) const
	{
		const size_t index =
			detail::object_find_index(this->m_p_body, key);

		if (index == static_cast<size_t>(-1))
		{
			KOTEK_ASSERT(false, "json object::at with a missing key");
			return detail::fallback_value();
		}

		return detail::object_slots(this->m_p_body)[index].entry;
	}

	inline object::iterator object::find(string_view key)
	{
		const size_t index =
			detail::object_find_index(this->m_p_body, key);

		if (index == static_cast<size_t>(-1))
			return this->end();

		return iterator(&detail::object_slots(this->m_p_body)[index]);
	}

	inline object::const_iterator object::find(string_view key) const
	{
		const size_t index =
			detail::object_find_index(this->m_p_body, key);

		if (index == static_cast<size_t>(-1))
			return this->end();

		return const_iterator(&detail::object_slots(this->m_p_body)[index]);
	}

	inline object::iterator object::begin(void)
	{
		return iterator(
			this->m_p_body ? detail::object_slots(this->m_p_body)
			               : nullptr);
	}

	inline object::iterator object::end(void)
	{
		return iterator(
			this->m_p_body
				? detail::object_slots(this->m_p_body) +
			        this->m_p_body->size
				: nullptr);
	}

	inline object::const_iterator object::begin(void) const
	{
		return const_iterator(
			this->m_p_body ? detail::object_slots(this->m_p_body)
			               : nullptr);
	}

	inline object::const_iterator object::end(void) const
	{
		return const_iterator(
			this->m_p_body
				? detail::object_slots(this->m_p_body) +
			        this->m_p_body->size
				: nullptr);
	}

	inline bool object::empty(void) const
	{
		return this->m_p_body == nullptr || this->m_p_body->size == 0;
	}

	inline size_t object::size(void) const
	{
		return this->m_p_body ? this->m_p_body->size : 0;
	}

	// ------------------------------------------------------------------
	// array implementation
	// ------------------------------------------------------------------

	inline array::array(void) : m_p_body(nullptr), m_sp() {}

	inline array::array(storage_ptr sp) : m_p_body(nullptr), m_sp(sp) {}

	inline array::array(const array& other) :
		m_p_body(nullptr),
		m_sp(other.m_sp)
	{
		detail::array_copy_into(
			this->m_p_body, this->m_sp, other.m_p_body);
	}

	inline array::array(const array& other, storage_ptr sp) :
		m_p_body(nullptr),
		m_sp(sp)
	{
		detail::array_copy_into(
			this->m_p_body, this->m_sp, other.m_p_body);
	}

	inline array::array(array&& other) noexcept :
		m_p_body(other.m_p_body),
		m_sp(other.m_sp)
	{
		other.m_p_body = nullptr;
	}

	inline array::array(
		std::initializer_list<value> elements, storage_ptr sp) :
		m_p_body(nullptr),
		m_sp(sp)
	{
		for (const value& element : elements)
			this->push_back(element);
	}

	template <typename Iterator, typename>
	inline array::array(Iterator first, Iterator last, storage_ptr sp) :
		m_p_body(nullptr),
		m_sp(sp)
	{
		for (Iterator it = first; it != last; ++it)
			this->push_back(value(*it, this->m_sp));
	}

	inline array::~array(void)
	{
		detail::array_body_destroy(this->m_sp, this->m_p_body);
	}

	inline array& array::operator=(const array& other)
	{
		if (this != &other)
		{
			detail::array_body_destroy(this->m_sp, this->m_p_body);
			this->m_p_body = nullptr;

			detail::array_copy_into(
				this->m_p_body, this->m_sp, other.m_p_body);
		}

		return *this;
	}

	inline array& array::operator=(array&& other) noexcept
	{
		if (this != &other)
		{
			detail::array_body_destroy(this->m_sp, this->m_p_body);
			this->m_p_body = other.m_p_body;
			this->m_sp = other.m_sp;
			other.m_p_body = nullptr;
		}

		return *this;
	}

	inline array& array::operator=(std::initializer_list<value> elements)
	{
		detail::array_body_destroy(this->m_sp, this->m_p_body);
		this->m_p_body = nullptr;

		for (const value& element : elements)
			this->push_back(element);

		return *this;
	}

	inline void array::push_back(const value& element)
	{
		if ((this->m_p_body == nullptr ||
		     this->m_p_body->size == this->m_p_body->capacity) &&
		    detail::array_grow(this->m_sp, this->m_p_body) == false)
		{
			// resource exhausted — the failed flag reports it
			return;
		}

		new (&detail::array_items(this->m_p_body)[this->m_p_body->size])
			value(element, this->m_sp);

		++this->m_p_body->size;
	}

	inline void array::push_back(value&& element)
	{
		if ((this->m_p_body == nullptr ||
		     this->m_p_body->size == this->m_p_body->capacity) &&
		    detail::array_grow(this->m_sp, this->m_p_body) == false)
		{
			// resource exhausted — the failed flag reports it
			return;
		}

		new (&detail::array_items(this->m_p_body)[this->m_p_body->size])
			value(std::move(element));

		++this->m_p_body->size;
	}

	template <typename... Arguments>
	inline value& array::emplace_back(Arguments&&... arguments)
	{
		if ((this->m_p_body == nullptr ||
		     this->m_p_body->size == this->m_p_body->capacity) &&
		    detail::array_grow(this->m_sp, this->m_p_body) == false)
		{
			// resource exhausted — the failed flag reports it
			return detail::fallback_value();
		}

		value* p_slot =
			&detail::array_items(this->m_p_body)[this->m_p_body->size];

		new (p_slot)
			value(std::forward<Arguments>(arguments)..., this->m_sp);

		++this->m_p_body->size;

		return *p_slot;
	}

	inline value& array::operator[](size_t index)
	{
		if (this->m_p_body == nullptr || index >= this->m_p_body->size)
		{
			KOTEK_ASSERT(false, "json array index out of bounds");
			return detail::fallback_value();
		}

		return detail::array_items(this->m_p_body)[index];
	}

	inline const value& array::operator[](size_t index) const
	{
		if (this->m_p_body == nullptr || index >= this->m_p_body->size)
		{
			KOTEK_ASSERT(false, "json array index out of bounds");
			return detail::fallback_value();
		}

		return detail::array_items(this->m_p_body)[index];
	}

	inline array::iterator array::begin(void)
	{
		return iterator(
			this->m_p_body ? detail::array_items(this->m_p_body)
			               : nullptr);
	}

	inline array::iterator array::end(void)
	{
		return iterator(
			this->m_p_body
				? detail::array_items(this->m_p_body) +
			        this->m_p_body->size
				: nullptr);
	}

	inline array::const_iterator array::begin(void) const
	{
		return const_iterator(
			this->m_p_body ? detail::array_items(this->m_p_body)
			               : nullptr);
	}

	inline array::const_iterator array::end(void) const
	{
		return const_iterator(
			this->m_p_body
				? detail::array_items(this->m_p_body) +
			        this->m_p_body->size
				: nullptr);
	}

	inline bool array::empty(void) const
	{
		return this->m_p_body == nullptr || this->m_p_body->size == 0;
	}

	inline size_t array::size(void) const
	{
		return this->m_p_body ? this->m_p_body->size : 0;
	}

	// ------------------------------------------------------------------
	// value's container members (needed complete object/array)
	// ------------------------------------------------------------------

	inline value::value(const object& data, storage_ptr sp) :
		m_kind(kind::object)
	{
		new (&this->m_payload.o)
			object(data, sp.get_raw() ? sp : data.storage());
	}

	inline value::value(object&& data, storage_ptr sp) :
		m_kind(kind::object)
	{
		if (sp.get_raw())
			new (&this->m_payload.o) object(data, sp);
		else
			new (&this->m_payload.o) object(std::move(data));
	}

	inline value::value(const array& data, storage_ptr sp) :
		m_kind(kind::array)
	{
		new (&this->m_payload.a)
			array(data, sp.get_raw() ? sp : data.storage());
	}

	inline value::value(array&& data, storage_ptr sp) :
		m_kind(kind::array)
	{
		if (sp.get_raw())
			new (&this->m_payload.a) array(data, sp);
		else
			new (&this->m_payload.a) array(std::move(data));
	}

	inline value& value::operator=(const object& data)
	{
		const storage_ptr target = this->current_sp();
		this->destroy_payload();
		this->m_kind = kind::object;
		new (&this->m_payload.o) object(data, target);
		return *this;
	}

	inline value& value::operator=(object&& data) noexcept
	{
		this->destroy_payload();
		this->m_kind = kind::object;
		new (&this->m_payload.o) object(std::move(data));
		return *this;
	}

	inline value& value::operator=(const array& data)
	{
		const storage_ptr target = this->current_sp();
		this->destroy_payload();
		this->m_kind = kind::array;
		new (&this->m_payload.a) array(data, target);
		return *this;
	}

	inline value& value::operator=(array&& data) noexcept
	{
		this->destroy_payload();
		this->m_kind = kind::array;
		new (&this->m_payload.a) array(std::move(data));
		return *this;
	}

	// ------------------------------------------------------------------
	// structural equality (used by the test-suite; objects compare
	// order-insensitively like boost, arrays element-wise)
	// ------------------------------------------------------------------

	namespace detail
	{
		inline bool values_equal(const value& left, const value& right)
		{
			if (left.get_kind() != right.get_kind())
			{
				// int64/uint64 compare numerically across kinds
				if (left.is_int64() && right.is_uint64())
				{
					return left.as_int64() >= 0 &&
						static_cast<std::uint64_t>(
							left.as_int64()) == right.as_uint64();
				}

				if (left.is_uint64() && right.is_int64())
				{
					return right.as_int64() >= 0 &&
						left.as_uint64() ==
						static_cast<std::uint64_t>(
							right.as_int64());
				}

				return false;
			}

			switch (left.get_kind())
			{
			case kind::null:
				return true;
			case kind::bool_:
				return left.as_bool() == right.as_bool();
			case kind::int64:
				return left.as_int64() == right.as_int64();
			case kind::uint64:
				return left.as_uint64() == right.as_uint64();
			case kind::double_:
				return left.as_double() == right.as_double();
			case kind::string:
				return left.as_string() == right.as_string();
			case kind::array:
			{
				const array& left_array = left.as_array();
				const array& right_array = right.as_array();

				if (left_array.size() != right_array.size())
					return false;

				for (size_t i = 0; i < left_array.size(); ++i)
				{
					if (values_equal(
							left_array[i], right_array[i]) == false)
						return false;
				}

				return true;
			}
			case kind::object:
			{
				const object& left_object = left.as_object();
				const object& right_object = right.as_object();

				if (left_object.size() != right_object.size())
					return false;

				for (auto pair : left_object)
				{
					auto found = right_object.find(pair.key());

					if (found == right_object.end())
						return false;

					if (values_equal(pair.value(), (*found).value()) ==
					    false)
						return false;
				}

				return true;
			}
			default:
				return false;
			}
		}
	} // namespace detail

	inline bool operator==(const value& left, const value& right)
	{
		return detail::values_equal(left, right);
	}

	inline bool operator!=(const value& left, const value& right)
	{
		return (left == right) == false;
	}

	// ------------------------------------------------------------------
	// value_from / value_to with the boost-shaped tag_invoke ADL
	// customization point
	// ------------------------------------------------------------------

	struct value_from_tag
	{
	};

	template <typename Type>
	struct value_to_tag
	{
	};

	namespace detail
	{
		/// only char-based std strings convert built-in (boost parity:
		/// boost's own generic string conversion handles them and the
		/// user's tag_invoke overloads never get a chance); wchar and
		/// char8/16/32 strings fall through to the ADL overloads in
		/// kotek_json_casting_string.h (found through the ktk
		/// allocator's associated namespace)
		template <typename Type>
		struct is_std_basic_string : std::false_type
		{
		};

		template <typename Traits, typename Allocator>
		struct is_std_basic_string<std::basic_string<char, Traits, Allocator>>
			: std::true_type
		{
		};
	} // namespace detail

	/// dispatch order mirrors boost: json's own types and arithmetic/
	/// string-like types are converted built-in, everything else goes
	/// through the user's tag_invoke overloads found by ADL (the etl
	/// static-string, ktk math-type and zircon component overloads keep
	/// working unchanged)
	template <typename Type>
	value value_from(const Type& data, storage_ptr sp = {})
	{
		value result(sp);

		if constexpr (std::is_same_v<Type, value>)
		{
			result = data;
		}
		else if constexpr (std::is_same_v<Type, object>)
		{
			result = data;
		}
		else if constexpr (std::is_same_v<Type, array>)
		{
			result = data;
		}
		else if constexpr (std::is_same_v<Type, string>)
		{
			result = data;
		}
		else if constexpr (std::is_same_v<Type, bool>)
		{
			result = data;
		}
		else if constexpr (
			std::is_integral_v<Type> || std::is_floating_point_v<Type>)
		{
			result = data;
		}
		else if constexpr (
			std::is_same_v<Type, const char*> ||
		    std::is_same_v<Type, char*>)
		{
			result = string_view(data);
		}
		else if constexpr (
			std::is_array_v<Type> &&
		    std::is_same_v<std::remove_extent_t<Type>, char>)
		{
			result = string_view(data);
		}
		else if constexpr (std::is_same_v<Type, string_view>)
		{
			result = data;
		}
		else if constexpr (detail::is_std_basic_string<Type>::value)
		{
			result = string_view(data.data(), data.size());
		}
		else
		{
			tag_invoke(value_from_tag{}, result, data);
		}

		return result;
	}

	template <typename Type>
	Type value_to(const value& read_from)
	{
		if constexpr (std::is_same_v<Type, value>)
		{
			return read_from;
		}
		else if constexpr (std::is_same_v<Type, object>)
		{
			return read_from.as_object();
		}
		else if constexpr (std::is_same_v<Type, array>)
		{
			return read_from.as_array();
		}
		else if constexpr (std::is_same_v<Type, string>)
		{
			return read_from.as_string();
		}
		else if constexpr (std::is_same_v<Type, bool>)
		{
			return read_from.as_bool();
		}
		else if constexpr (
			std::is_integral_v<Type> || std::is_floating_point_v<Type>)
		{
			return read_from.to_number<Type>();
		}
		else if constexpr (detail::is_std_basic_string<Type>::value)
		{
			const string& data = read_from.as_string();
			return Type(data.begin(), data.end());
		}
		else
		{
			return tag_invoke(value_to_tag<Type>{}, read_from);
		}
	}

	// ------------------------------------------------------------------
	// parse (stream_reader + a DOM-building handler)
	// ------------------------------------------------------------------

	namespace detail
	{
		class dom_builder : public stream_handler
		{
		public:
			dom_builder(void) : m_sp(), m_root(), m_depth(0) {}

			explicit dom_builder(storage_ptr sp) :
				m_sp(sp),
				m_root(),
				m_depth(0)
			{
			}

			void reset(storage_ptr sp)
			{
				this->m_sp = sp;
				this->m_root = value();
				this->m_depth = 0;

				for (size_t i = 0;
				     i < KOTEK_DEF_OWN_JSON_STREAM_MAX_DEPTH;
				     ++i)
				{
					this->m_frames[i].entry = value();
					this->m_frames[i].p_pending = nullptr;
					this->m_frames[i].has_key = false;
				}
			}

			bool on_object_begin(void) override
			{
				if (this->m_depth >=
				    KOTEK_DEF_OWN_JSON_STREAM_MAX_DEPTH)
					return false;

				frame& current = this->m_frames[this->m_depth++];

				current.entry = value(object(this->m_sp));
				current.p_pending = nullptr;
				current.has_key = false;

				return this->resource_ok();
			}

			bool on_object_end(void) override
			{
				if (this->m_depth == 0)
					return false;

				--this->m_depth;

				return this->attach(
					std::move(this->m_frames[this->m_depth].entry));
			}

			bool on_array_begin(void) override
			{
				if (this->m_depth >=
				    KOTEK_DEF_OWN_JSON_STREAM_MAX_DEPTH)
					return false;

				frame& current = this->m_frames[this->m_depth++];

				current.entry = value(array(this->m_sp));
				current.p_pending = nullptr;
				current.has_key = false;

				return this->resource_ok();
			}

			bool on_array_end(void) override
			{
				if (this->m_depth == 0)
					return false;

				--this->m_depth;

				return this->attach(
					std::move(this->m_frames[this->m_depth].entry));
			}

			bool on_key(string_view key) override
			{
				if (this->m_depth == 0)
					return false;

				frame& current = this->m_frames[this->m_depth - 1];

				// the key goes straight into the object's slot
				// storage (one allocation, no pending key string);
				// the pending pointer stays valid until the value
				// arrives because the parent object receives no
				// insertions between a key and its value
				if (current.entry.is_object() == false)
					return false;

				object& target = current.entry.as_object();

				current.p_pending = &target[key];
				current.has_key = true;

				return this->resource_ok();
			}

			bool on_string(string_view data) override
			{
				return this->attach(value(data, this->m_sp));
			}

			bool on_null(void) override
			{
				return this->attach(value(this->m_sp));
			}

			bool on_bool(bool data) override
			{
				return this->attach(value(data, this->m_sp));
			}

			bool on_int64(std::int64_t data) override
			{
				return this->attach(value(data, this->m_sp));
			}

			bool on_uint64(std::uint64_t data) override
			{
				return this->attach(value(data, this->m_sp));
			}

			bool on_double(double data) override
			{
				return this->attach(value(data, this->m_sp));
			}

			bool resource_failed(void) const
			{
				return this->m_sp.get()->failed();
			}

			value release_root(void)
			{
				return std::move(this->m_root);
			}

		private:
			bool resource_ok(void) const
			{
				return this->resource_failed() == false;
			}

			bool attach(value&& element)
			{
				if (this->m_depth == 0)
				{
					this->m_root = std::move(element);
					return this->resource_ok();
				}

				frame& current = this->m_frames[this->m_depth - 1];

				if (current.entry.is_object())
				{
					if (current.has_key == false ||
					    current.p_pending == nullptr)
					{
						return false;
					}

					*current.p_pending = std::move(element);

					current.p_pending = nullptr;
					current.has_key = false;
				}
				else
				{
					array& target = current.entry.as_array();
					target.push_back(std::move(element));
				}

				return this->resource_ok();
			}

			struct frame
			{
				value entry;
				value* p_pending = nullptr;
				bool has_key = false;
			};

			storage_ptr m_sp;
			value m_root;
			size_t m_depth;
			frame m_frames[KOTEK_DEF_OWN_JSON_STREAM_MAX_DEPTH];
		};
	} // namespace detail

	inline value parse(
		string_view text,
		error_code& ec,
		storage_ptr sp = {},
		const parse_options& options = {})
	{
		detail::dom_builder builder(sp);
		stream_reader reader(builder, options);

		bool status = reader.feed(text);

		if (status)
			status = reader.finish();

		if (status == false)
		{
			ec = reader.get_error();

			if (ec.value() == error::handler_aborted &&
			    builder.resource_failed())
			{
				ec.assign(error::resource_exhausted);
			}

			return value();
		}

		ec.clear();
		return builder.release_root();
	}

	/// incremental parser (the boost-shaped wrapper ktkResourceText
	/// drives): storage + options at construction, feed with write(),
	/// obtain the document with release()
	class parser
	{
	public:
		explicit parser(storage_ptr sp = {}) :
			parser(sp, parse_options{})
		{
		}

		parser(storage_ptr sp, const parse_options& options) :
			m_storage(sp),
			m_options(options),
			m_builder(sp),
			m_reader(m_builder, options)
		{
		}

		void reset(void)
		{
			this->m_builder.reset(this->m_storage);
			this->m_reader.reset(this->m_builder, this->m_options);
		}

		size_t write(const char* p_text, size_t size, error_code& ec)
		{
			if (this->m_reader.feed(string_view(p_text, size)) == false)
			{
				ec = this->m_reader.get_error();

				if (ec.value() == error::handler_aborted &&
				    this->m_builder.resource_failed())
				{
					ec.assign(error::resource_exhausted);
				}

				return 0;
			}

			ec.clear();
			return size;
		}

		size_t write(string_view text, error_code& ec)
		{
			return this->write(text.data(), text.size(), ec);
		}

		value release(void)
		{
			if (this->m_reader.document_complete() == false)
			{
				KOTEK_ASSERT(
					false,
					"parser::release before the document "
					"completed");
				return value();
			}

			return this->m_builder.release_root();
		}

		bool is_done(void) const
		{
			return this->m_reader.document_complete();
		}

	private:
		storage_ptr m_storage;
		parse_options m_options;
		detail::dom_builder m_builder;
		stream_reader m_reader;
	};

	// ------------------------------------------------------------------
	// serialize / serializer
	// ------------------------------------------------------------------

	namespace detail
	{
		inline void string_append_callback(void* p_user, string_view chunk)
		{
			static_cast<string*>(p_user)->append(chunk);
		}

		inline bool emit_value(stream_writer& writer, const value& data);

		inline bool emit_object(stream_writer& writer, const object& data)
		{
			if (writer.on_object_begin() == false)
				return false;

			for (auto pair : data)
			{
				if (writer.on_key(pair.key()) == false)
					return false;

				if (emit_value(writer, pair.value()) == false)
					return false;
			}

			return writer.on_object_end();
		}

		inline bool emit_array(stream_writer& writer, const array& data)
		{
			if (writer.on_array_begin() == false)
				return false;

			for (const value& element : data)
			{
				if (emit_value(writer, element) == false)
					return false;
			}

			return writer.on_array_end();
		}

		inline bool emit_string(stream_writer& writer, const string& data)
		{
			return writer.on_string(
				string_view(data.data(), data.size()));
		}

		/// recursive descent — depth is bounded by construction (the
		/// reader caps parsed documents at
		/// KOTEK_DEF_OWN_JSON_STREAM_MAX_DEPTH and hand-built DOMs in
		/// the codebase are a few levels deep)
		inline bool emit_value(stream_writer& writer, const value& data)
		{
			switch (data.get_kind())
			{
			case kind::null:
				return writer.on_null();
			case kind::bool_:
				return writer.on_bool(data.as_bool());
			case kind::int64:
				return writer.on_int64(data.as_int64());
			case kind::uint64:
				return writer.on_uint64(data.as_uint64());
			case kind::double_:
				return writer.on_double(data.as_double());
			case kind::string:
				return emit_string(writer, data.as_string());
			case kind::array:
				return emit_array(writer, data.as_array());
			case kind::object:
				return emit_object(writer, data.as_object());
			default:
				return false;
			}
		}

		template <typename JsonType>
		inline string serialize_impl(const JsonType& data);
	} // namespace detail

	inline string serialize(const value& data)
	{
		string result;

		char scratch[KOTEK_DEF_OWN_JSON_SERIALIZER_SCRATCH_SIZE];
		stream_writer writer(
			scratch,
			sizeof(scratch),
			&detail::string_append_callback,
			&result);

		if (detail::emit_value(writer, data))
			writer.finish();

		return result;
	}

	inline string serialize(const object& data)
	{
		string result;

		char scratch[KOTEK_DEF_OWN_JSON_SERIALIZER_SCRATCH_SIZE];
		stream_writer writer(
			scratch,
			sizeof(scratch),
			&detail::string_append_callback,
			&result);

		if (detail::emit_object(writer, data))
			writer.finish();

		return result;
	}

	inline string serialize(const array& data)
	{
		string result;

		char scratch[KOTEK_DEF_OWN_JSON_SERIALIZER_SCRATCH_SIZE];
		stream_writer writer(
			scratch,
			sizeof(scratch),
			&detail::string_append_callback,
			&result);

		if (detail::emit_array(writer, data))
			writer.finish();

		return result;
	}

	inline string serialize(const string& data)
	{
		string result;

		char scratch[KOTEK_DEF_OWN_JSON_SERIALIZER_SCRATCH_SIZE];
		stream_writer writer(
			scratch,
			sizeof(scratch),
			&detail::string_append_callback,
			&result);

		if (detail::emit_string(writer, data))
			writer.finish();

		return result;
	}

	/// pull-shaped serializer (the boost-shaped wrapper
	/// ktkResourceText::Serialize_ToString drives): reset() materializes
	/// the document into an internal buffer (the DOM is materialized
	/// anyway; the incremental byte-exact streaming path for big data
	/// is stream_writer), read() hands out slices of it
	class serializer
	{
	public:
		explicit serializer(storage_ptr sp = {}) : m_text(sp), m_position(0)
		{
		}

		void reset(const value* p_value)
		{
			this->m_text = string();
			this->m_position = 0;

			if (p_value == nullptr)
				return;

			char scratch[KOTEK_DEF_OWN_JSON_SERIALIZER_SCRATCH_SIZE];
			stream_writer writer(
				scratch,
				sizeof(scratch),
				&detail::string_append_callback,
				&this->m_text);

			if (detail::emit_value(writer, *p_value))
				writer.finish();
		}

		void reset(const object* p_object)
		{
			this->m_text = string();
			this->m_position = 0;

			if (p_object == nullptr)
				return;

			char scratch[KOTEK_DEF_OWN_JSON_SERIALIZER_SCRATCH_SIZE];
			stream_writer writer(
				scratch,
				sizeof(scratch),
				&detail::string_append_callback,
				&this->m_text);

			if (detail::emit_object(writer, *p_object))
				writer.finish();
		}

		void reset(const array* p_array)
		{
			this->m_text = string();
			this->m_position = 0;

			if (p_array == nullptr)
				return;

			char scratch[KOTEK_DEF_OWN_JSON_SERIALIZER_SCRATCH_SIZE];
			stream_writer writer(
				scratch,
				sizeof(scratch),
				&detail::string_append_callback,
				&this->m_text);

			if (detail::emit_array(writer, *p_array))
				writer.finish();
		}

		string_view read(char* p_dest, size_t size)
		{
			const size_t remaining =
				this->m_text.size() - this->m_position;

			const size_t piece = remaining < size ? remaining : size;

			if (piece > 0)
			{
				std::memcpy(
					p_dest,
					this->m_text.data() + this->m_position,
					piece);

				this->m_position += piece;
			}

			return string_view(p_dest, piece);
		}

		/// leaves room for the caller's terminating NUL
		template <size_t _Size>
		string_view read(char (&dest)[_Size])
		{
			static_assert(_Size > 1, "buffer too small");
			return this->read(dest, _Size - 1);
		}

		bool done(void) const
		{
			return this->m_position == this->m_text.size();
		}

	private:
		string m_text;
		size_t m_position;
	};

} // namespace json

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK

#endif

