#pragma once

// KOTEK_JSON_LIBRARY=KOTEK_OWN (task K4): kotek's own dependency-free json
// backend. This header is the streaming half: a SAX-style incremental
// reader (chunk-safe — a token may split across feed() boundaries at any
// byte) and a SAX-style writer (emits into a caller buffer and hands
// completed chunks to a flush callback). The DOM half (value/object/array
// plus the pmr-style resources) lives in kotek_own_json.h; its parse() and
// parser are built on top of stream_reader, and its serializer drives a
// stream_writer.
//
// Rules honored here: no third-party includes (C/C++ standard headers
// only), no exceptions (every failure is an error_code), fixed internal
// buffers only — every capacity is a named preprocessor constant below,
// never a magic number. No per-token heap allocation: the reader delivers
// string_view slices of the caller's chunk when a string token lies
// entirely inside one feed() call and falls back to a fixed assembly
// buffer only when the token spans chunks or contains escapes.
//
// The whole header compiles to nothing unless the own backend is selected:
// under the boost backend `json` is an alias to boost::json and a real
// namespace with these names would collide with it.

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>
#include <kotek.core.defines_dependent.message/include/kotek_core_defines_dependent_message.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <string_view>

#if defined(KOTEK_USE_JSON_LIBRARY_KOTEK_OWN)

// capacities (house rule: sizes are preprocessor constants, never magic
// numbers)

/// maximum nesting depth of array/object the reader tracks and the writer
/// accepts; deeper documents fail gracefully with error::depth_exceeded
#define KOTEK_DEF_OWN_JSON_STREAM_MAX_DEPTH 64

/// assembly buffer for one string token (key or value) that spans chunk
/// boundaries or contains escapes; longer strings fail gracefully with
/// error::token_too_long
#define KOTEK_DEF_OWN_JSON_STREAM_TOKEN_BUFFER_SIZE 512

/// assembly buffer for one number token (the longest round-trippable
/// double is ~24 characters, 64 leaves headroom)
#define KOTEK_DEF_OWN_JSON_STREAM_NUMBER_BUFFER_SIZE 64

/// minimum caller buffer the writer accepts (the longest indivisible
/// emission is a 32-bit number ~20 chars or a "XXXX" escape = 6)
#define KOTEK_DEF_OWN_JSON_STREAM_WRITER_MIN_BUFFER 32

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

namespace json
{
	using string_view = std::string_view;

	/// parse/stream failure codes; error_code below carries them and is
	/// what the boost-shaped call sites inspect (`if (code)`,
	/// `code.message()`)
	enum class error : unsigned char
	{
		none = 0,
		expected_value,
		expected_key,
		expected_colon,
		expected_comma_or_end,
		unexpected_character,
		trailing_content,
		depth_exceeded,
		token_too_long,
		invalid_number,
		invalid_escape,
		invalid_literal,
		invalid_unicode_escape,
		unexpected_end_of_input,
		handler_aborted,
		resource_exhausted,
		writer_misuse,
		buffer_overflow
	};

	class error_code
	{
	public:
		error_code(void) : m_value(error::none) {}
		error_code(error value) : m_value(value) {}

		explicit operator bool(void) const
		{
			return this->m_value != error::none;
		}

		error value(void) const { return this->m_value; }

		void clear(void) { this->m_value = error::none; }

		void assign(error value) { this->m_value = value; }

		const char* message(void) const
		{
			switch (this->m_value)
			{
			case error::none:
				return "no error";
			case error::expected_value:
				return "expected a json value";
			case error::expected_key:
				return "expected an object key";
			case error::expected_colon:
				return "expected ':' after an object key";
			case error::expected_comma_or_end:
				return "expected ',' or the end of a container";
			case error::unexpected_character:
				return "unexpected character";
			case error::trailing_content:
				return "trailing content after the root value";
			case error::depth_exceeded:
				return "maximum nesting depth exceeded";
			case error::token_too_long:
				return "a string token exceeds the fixed token "
				       "buffer";
			case error::invalid_number:
				return "invalid number";
			case error::invalid_escape:
				return "invalid string escape";
			case error::invalid_literal:
				return "invalid literal (expected true/false/null)";
			case error::invalid_unicode_escape:
				return "invalid \\u escape";
			case error::unexpected_end_of_input:
				return "unexpected end of input";
			case error::handler_aborted:
				return "the stream handler aborted the parse";
			case error::resource_exhausted:
				return "the json memory resource is exhausted";
			case error::writer_misuse:
				return "stream_writer contract violation";
			case error::buffer_overflow:
				return "stream_writer buffer overflow";
			default:
				return "unknown json error";
			}
		}

	private:
		error m_value;
	};

	struct parse_options
	{
		/// allow /* ... *&#47; and // ... comments outside of strings
		bool allow_comments = false;
		/// allow a comma directly before '}' or ']'
		bool allow_trailing_commas = false;
		/// accepted for boost interface parity; the reader never
		/// validates utf-8 so invalid sequences already pass through
		bool allow_invalid_utf8 = false;
		/// 0 means the default cap (KOTEK_DEF_OWN_JSON_STREAM_MAX_DEPTH)
		unsigned char max_depth = 0;
	};

	/// SAX handler driven by stream_reader. Every callback returns false
	/// to abort the parse gracefully (reader reports
	/// error::handler_aborted). Delivered string_views are only valid
	/// until the next feed() call — copy them if they must outlive it
	/// (the DOM builder does exactly that, into its memory resource).
	class stream_handler
	{
	public:
		virtual ~stream_handler(void) {}

		virtual bool on_object_begin() = 0;
		virtual bool on_object_end() = 0;
		virtual bool on_array_begin() = 0;
		virtual bool on_array_end() = 0;
		virtual bool on_key(string_view key) = 0;
		virtual bool on_string(string_view data) = 0;
		virtual bool on_null() = 0;
		virtual bool on_bool(bool data) = 0;
		virtual bool on_int64(std::int64_t data) = 0;
		virtual bool on_uint64(std::uint64_t data) = 0;
		virtual bool on_double(double data) = 0;
	};

	namespace detail
	{
		/// shortest round-trip double formatting: tries 15..17
		/// significant digits until strtod reproduces the bits, then
		/// guarantees the text re-parses as a double (appends ".0" when
		/// the %g form has no fraction/exponent marker). nan/inf are
		/// not representable in json — they serialize as null.
		/// Returns the number of chars written (0 on buffer failure).
		inline size_t format_double(char* p_out, size_t capacity, double data)
		{
			if (data != data)
			{
				// nan
				if (capacity < 5)
					return 0;
				std::memcpy(p_out, "null", 5);
				return 4;
			}

			if (data == data * 0.5 && data != 0.0)
			{
				// +-inf (inf * 0.5 == inf, everything else shrinks)
				if (capacity < 5)
					return 0;
				std::memcpy(p_out, "null", 5);
				return 4;
			}

			int written = 0;
			for (int precision = 15; precision <= 17; ++precision)
			{
				written = std::snprintf(
					p_out, capacity, "%.*g", precision, data);

				if (written <= 0 || static_cast<size_t>(written) >= capacity)
					return 0;

				char* p_end = nullptr;
				errno = 0;
				const double round_trip = std::strtod(p_out, &p_end);

				if (p_end == p_out + written && round_trip == data)
					break;
			}

			bool has_double_marker = false;
			for (int i = 0; i < written; ++i)
			{
				const char c = p_out[i];
				if (c == '.' || c == 'e' || c == 'E')
				{
					has_double_marker = true;
					break;
				}
			}

			if (has_double_marker == false)
			{
				if (static_cast<size_t>(written) + 2 >= capacity)
					return 0;
				p_out[written++] = '.';
				p_out[written++] = '0';
				p_out[written] = '\0';
			}

			return static_cast<size_t>(written);
		}

		inline size_t format_int64(
			char* p_out, size_t capacity, std::int64_t data)
		{
			const int written =
				std::snprintf(p_out, capacity, "%lld", data);

			if (written <= 0 || static_cast<size_t>(written) >= capacity)
				return 0;

			return static_cast<size_t>(written);
		}

		inline size_t format_uint64(
			char* p_out, size_t capacity, std::uint64_t data)
		{
			const int written =
				std::snprintf(p_out, capacity, "%llu", data);

			if (written <= 0 || static_cast<size_t>(written) >= capacity)
				return 0;

			return static_cast<size_t>(written);
		}

		enum class number_class : unsigned char
		{
			invalid = 0,
			is_integer,
			is_double
		};

		/// validates the strict json number grammar:
		/// '-'? ('0' | [1-9][0-9]*) ('.' [0-9]+)? ([eE] [-+]? [0-9]+)?
		inline number_class classify_number(const char* p_text, size_t size)
		{
			if (size == 0)
				return number_class::invalid;

			size_t i = 0;
			number_class result = number_class::is_integer;

			if (p_text[i] == '-')
			{
				++i;
				if (i == size)
					return number_class::invalid;
			}

			if (p_text[i] == '0')
			{
				++i;
				// a leading zero must stand alone
				if (i < size && p_text[i] >= '0' && p_text[i] <= '9')
					return number_class::invalid;
			}
			else if (p_text[i] >= '1' && p_text[i] <= '9')
			{
				while (i < size && p_text[i] >= '0' && p_text[i] <= '9')
					++i;
			}
			else
			{
				return number_class::invalid;
			}

			if (i < size && p_text[i] == '.')
			{
				result = number_class::is_double;
				++i;
				const size_t fraction_begin = i;
				while (i < size && p_text[i] >= '0' && p_text[i] <= '9')
					++i;
				if (i == fraction_begin)
					return number_class::invalid;
			}

			if (i < size && (p_text[i] == 'e' || p_text[i] == 'E'))
			{
				result = number_class::is_double;
				++i;
				if (i < size && (p_text[i] == '+' || p_text[i] == '-'))
					++i;
				const size_t exponent_begin = i;
				while (i < size && p_text[i] >= '0' && p_text[i] <= '9')
					++i;
				if (i == exponent_begin)
					return number_class::invalid;
			}

			if (i != size)
				return number_class::invalid;

			return result;
		}

		inline bool is_hex_digit(char c, unsigned char* p_value)
		{
			if (c >= '0' && c <= '9')
			{
				*p_value = static_cast<unsigned char>(c - '0');
				return true;
			}
			if (c >= 'a' && c <= 'f')
			{
				*p_value = static_cast<unsigned char>(c - 'a' + 10);
				return true;
			}
			if (c >= 'A' && c <= 'F')
			{
				*p_value = static_cast<unsigned char>(c - 'A' + 10);
				return true;
			}
			return false;
		}
	} // namespace detail

	/// Incremental SAX reader. Feed arbitrary string_view chunks — token
	/// boundaries are not respected and may split at any byte — then call
	/// finish() once at end of input. All state lives in this object;
	/// the only buffers are the fixed ones below.
	class stream_reader
	{
	public:
		stream_reader(stream_handler& handler)
			: stream_reader(handler, parse_options{})
		{
		}

		stream_reader(stream_handler& handler, const parse_options& options)
			: m_p_handler(&handler),
			  m_options(options),
			  m_state(state::root),
			  m_depth(0),
			  m_token(token::none),
			  m_buffer_length(0),
			  m_buffer_used(false),
			  m_string_escape(false),
			  m_string_is_key(false),
			  m_unicode_remaining(0),
			  m_unicode_value(0),
			  m_unicode_high_surrogate(0),
			  m_unicode_expect_low(0),
			  m_number_length(0),
			  m_literal_position(0),
			  m_comment_closing(false),
			  m_error()
		{
		}

		void reset(stream_handler& handler, const parse_options& options)
		{
			this->m_p_handler = &handler;
			this->m_options = options;
			this->m_state = state::root;
			this->m_depth = 0;
			this->m_token = token::none;
			this->m_buffer_length = 0;
			this->m_buffer_used = false;
			this->m_string_escape = false;
			this->m_string_is_key = false;
			this->m_unicode_remaining = 0;
			this->m_unicode_value = 0;
			this->m_unicode_high_surrogate = 0;
			this->m_unicode_expect_low = 0;
			this->m_number_length = 0;
			this->m_literal_position = 0;
			this->m_comment_closing = false;
			this->m_error.clear();
		}

		/// consumes the whole chunk; returns false (sticky) on error
		bool feed(string_view chunk)
		{
			if (this->m_error)
				return false;

			size_t i = 0;
			const size_t n = chunk.size();

			while (i < n && this->m_error.value() == error::none)
			{
				const char c = chunk[i];

				switch (this->m_token)
				{
				case token::string_token:
				{
					this->step_string(chunk, i);
					continue;
				}
				case token::number_token:
				{
					if (this->is_number_character(c))
					{
						if (this->m_number_length + 1 >=
						    KOTEK_DEF_OWN_JSON_STREAM_NUMBER_BUFFER_SIZE)
						{
							this->fail(error::token_too_long);
							break;
						}

						this->m_number_buffer[this->m_number_length++] = c;
						++i;
					}
					else
					{
						// the delimiter is not consumed here —
						// the structural half sees it next
						this->finish_number();
					}
					continue;
				}
				case token::literal_true:
				case token::literal_false:
				case token::literal_null:
				{
					const char* p_word =
						this->m_token == token::literal_true
						? "true"
						: (this->m_token == token::literal_false
						          ? "false"
						          : "null");

					const size_t word_length =
						this->m_token == token::literal_true
						? 4
						: (this->m_token == token::literal_false ? 5 : 4);

					if (c != p_word[this->m_literal_position])
					{
						this->fail(error::invalid_literal);
						break;
					}

					++this->m_literal_position;
					++i;

					if (this->m_literal_position == word_length)
					{
						this->m_token = token::none;

						bool status = false;
						if (p_word[0] == 't')
							status = this->m_p_handler->on_bool(true);
						else if (p_word[0] == 'f')
							status = this->m_p_handler->on_bool(false);
						else
							status = this->m_p_handler->on_null();

						if (status == false)
							this->fail(error::handler_aborted);
						else
							this->after_value();
					}
					continue;
				}
				case token::comment_line:
				{
					if (c == '\n')
						this->m_token = token::none;
					++i;
					continue;
				}
				case token::comment_block:
				{
					if (this->m_comment_closing && c == '/')
					{
						this->m_token = token::none;
						this->m_comment_closing = false;
					}
					else
					{
						this->m_comment_closing = (c == '*');
					}
					++i;
					continue;
				}
				case token::slash_pending:
				{
					// a '/' ended the previous chunk; only a
					// comment can legally follow
					if (c == '/')
						this->m_token = token::comment_line;
					else if (c == '*')
					{
						this->m_token = token::comment_block;
						this->m_comment_closing = false;
					}
					else
					{
						this->fail(error::unexpected_character);
					}
					++i;
					continue;
				}
				case token::none:
				default:
					break;
				}

				if (this->m_error)
					break;

				if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
				{
					++i;
					continue;
				}

				if (c == '/' && this->m_options.allow_comments)
				{
					if (i + 1 == n)
					{
						// decision deferred to the next chunk
						this->m_token = token::slash_pending;
						++i;
						continue;
					}

					const char next = chunk[i + 1];
					if (next == '/')
					{
						this->m_token = token::comment_line;
						i += 2;
						continue;
					}
					if (next == '*')
					{
						this->m_token = token::comment_block;
						this->m_comment_closing = false;
						i += 2;
						continue;
					}

					this->fail(error::unexpected_character);
					break;
				}

				switch (this->m_state)
				{
				case state::root:
				case state::object_value:
				case state::array_first:
				case state::array_value:
				{
					this->start_value(chunk, i);
					break;
				}
				case state::object_first:
				{
					if (c == '}')
					{
						this->close_object();
						++i;
					}
					else if (c == '"')
					{
						this->begin_string(true, i);
						++i;
					}
					else
					{
						this->fail(error::expected_key);
					}
					break;
				}
				case state::object_key:
				{
					if (c == '"')
					{
						this->begin_string(true, i);
						++i;
					}
					else if (
						c == '}' &&
					    this->m_options.allow_trailing_commas)
					{
						this->close_object();
						++i;
					}
					else
					{
						this->fail(error::expected_key);
					}
					break;
				}
				case state::object_colon:
				{
					if (c == ':')
					{
						this->m_state = state::object_value;
						++i;
					}
					else
					{
						this->fail(error::expected_colon);
					}
					break;
				}
				case state::object_next:
				{
					if (c == ',')
					{
						this->m_state = state::object_key;
						++i;
					}
					else if (c == '}')
					{
						this->close_object();
						++i;
					}
					else
					{
						this->fail(error::expected_comma_or_end);
					}
					break;
				}
				case state::array_next:
				{
					if (c == ',')
					{
						this->m_state = state::array_value;
						++i;
					}
					else if (c == ']')
					{
						this->close_array();
						++i;
					}
					else
					{
						this->fail(error::expected_comma_or_end);
					}
					break;
				}
				case state::done:
				default:
				{
					this->fail(error::trailing_content);
					break;
				}
				}
			}

			// the chunk ended: keep the raw prefix of an open string
			// token for the next feed() (covers both a string split
			// mid-content and an opening quote as the chunk's last
			// byte — materialize is a no-op once engaged)
			if (this->m_error.value() == error::none &&
			    this->m_token == token::string_token &&
			    this->m_buffer_used == false)
			{
				this->materialize_string_prefix(chunk, n);
			}

			return this->m_error.value() == error::none;
		}
		bool finish(void)
		{
			if (this->m_error)
				return false;

			if (this->m_token == token::number_token)
				this->finish_number();

			if (this->m_error)
				return false;

			if (this->m_token == token::comment_line)
				this->m_token = token::none;

			if (this->m_token != token::none)
			{
				this->fail(error::unexpected_end_of_input);
				return false;
			}

			if (this->m_state != state::done)
			{
				this->fail(error::unexpected_end_of_input);
				return false;
			}

			return true;
		}

		/// the root value completed (possibly before finish() when the
		/// document ends exactly at its closing token); a trailing
		/// comment still in progress counts as complete — finish()
		/// stays strict and only tolerates a line comment
		bool document_complete(void) const
		{
			return this->m_state == state::done &&
				(this->m_token == token::none ||
			     this->m_token == token::comment_line ||
			     this->m_token == token::comment_block);
		}

		error_code get_error(void) const { return this->m_error; }

	private:
		enum class state : unsigned char
		{
			root = 0,
			object_first,
			object_key,
			object_colon,
			object_value,
			object_next,
			array_first,
			array_value,
			array_next,
			done
		};

		enum class token : unsigned char
		{
			none = 0,
			string_token,
			number_token,
			literal_true,
			literal_false,
			literal_null,
			comment_line,
			comment_block,
			slash_pending
		};

		void fail(error value)
		{
			if (this->m_error.value() == error::none)
				this->m_error.assign(value);
		}

		size_t depth_limit(void) const
		{
			return this->m_options.max_depth != 0
				? static_cast<size_t>(this->m_options.max_depth)
				: static_cast<size_t>(
					  KOTEK_DEF_OWN_JSON_STREAM_MAX_DEPTH);
		}

		static bool is_number_character(char c)
		{
			return (c >= '0' && c <= '9') || c == '-' || c == '+' ||
				c == '.' || c == 'e' || c == 'E';
		}

		/// a value (scalar or closed container) completed — compute the
		/// state that follows it from the enclosing container
		void after_value(void)
		{
			if (this->m_depth == 0)
			{
				this->m_state = state::done;
			}
			else if (this->m_stack[this->m_depth - 1] == 'o')
			{
				this->m_state = state::object_next;
			}
			else
			{
				this->m_state = state::array_next;
			}
		}

		void start_value(string_view chunk, size_t& i)
		{
			const char c = chunk[i];

			switch (c)
			{
			case '{':
			{
				if (this->m_depth >= this->depth_limit())
				{
					this->fail(error::depth_exceeded);
					return;
				}

				this->m_stack[this->m_depth++] = 'o';

				if (this->m_p_handler->on_object_begin() == false)
				{
					this->fail(error::handler_aborted);
					return;
				}

				this->m_state = state::object_first;
				++i;
				break;
			}
			case '[':
			{
				if (this->m_depth >= this->depth_limit())
				{
					this->fail(error::depth_exceeded);
					return;
				}

				this->m_stack[this->m_depth++] = 'a';

				if (this->m_p_handler->on_array_begin() == false)
				{
					this->fail(error::handler_aborted);
					return;
				}

				this->m_state = state::array_first;
				++i;
				break;
			}
			case '"':
			{
				this->begin_string(false, i);
				++i;
				break;
			}
			case ']':
			{
				if (this->m_state == state::array_first ||
				    (this->m_state == state::array_value &&
				     this->m_options.allow_trailing_commas))
				{
					this->close_array();
					++i;
				}
				else
				{
					this->fail(error::expected_value);
				}
				break;
			}
			case 't':
			{
				this->m_token = token::literal_true;
				this->m_literal_position = 1;
				++i;
				break;
			}
			case 'f':
			{
				this->m_token = token::literal_false;
				this->m_literal_position = 1;
				++i;
				break;
			}
			case 'n':
			{
				this->m_token = token::literal_null;
				this->m_literal_position = 1;
				++i;
				break;
			}
			default:
			{
				if (c == '-' || (c >= '0' && c <= '9'))
				{
					this->m_token = token::number_token;
					this->m_number_length = 0;
					this->m_number_buffer[this->m_number_length++] = c;
					++i;
				}
				else
				{
					this->fail(error::expected_value);
				}
				break;
			}
			}
		}

		void close_object(void)
		{
			if (this->m_depth == 0 ||
			    this->m_stack[this->m_depth - 1] != 'o')
			{
				this->fail(error::unexpected_character);
				return;
			}

			--this->m_depth;

			if (this->m_p_handler->on_object_end() == false)
			{
				this->fail(error::handler_aborted);
				return;
			}

			this->after_value();
		}

		void close_array(void)
		{
			if (this->m_depth == 0 ||
			    this->m_stack[this->m_depth - 1] != 'a')
			{
				this->fail(error::unexpected_character);
				return;
			}

			--this->m_depth;

			if (this->m_p_handler->on_array_end() == false)
			{
				this->fail(error::handler_aborted);
				return;
			}

			this->after_value();
		}

		void begin_string(bool is_key, size_t chunk_offset)
		{
			this->m_token = token::string_token;
			this->m_string_is_key = is_key;
			this->m_string_escape = false;
			this->m_buffer_used = false;
			this->m_buffer_length = 0;
			this->m_unicode_remaining = 0;
			this->m_unicode_value = 0;
			this->m_unicode_high_surrogate = 0;
			this->m_unicode_expect_low = 0;
			// chunk_offset points at the opening quote — the
			// deliverable content starts one char after it
			this->m_zero_copy_begin = chunk_offset + 1;
		}

		bool append_string_byte(char c)
		{
			if (this->m_buffer_length + 1 >=
			    KOTEK_DEF_OWN_JSON_STREAM_TOKEN_BUFFER_SIZE)
			{
				this->fail(error::token_too_long);
				return false;
			}

			this->m_buffer[this->m_buffer_length++] = c;
			return true;
		}

		/// moves the not-yet-delivered raw prefix of the current chunk
		/// into the assembly buffer (called when an escape appears or
		/// the chunk ends mid-string)
		bool materialize_string_prefix(string_view chunk, size_t end)
		{
			if (this->m_buffer_used)
				return true;

			for (size_t j = this->m_zero_copy_begin; j < end; ++j)
			{
				if (this->append_string_byte(chunk[j]) == false)
					return false;
			}

			this->m_buffer_used = true;
			return true;
		}

		bool append_unicode_codepoint(std::uint32_t codepoint)
		{
			if (codepoint < 0x80)
			{
				return this->append_string_byte(
					static_cast<char>(codepoint));
			}
			else if (codepoint < 0x800)
			{
				return this->append_string_byte(static_cast<char>(
					0xC0 | (codepoint >> 6))) &&
					this->append_string_byte(static_cast<char>(
						0x80 | (codepoint & 0x3F)));
			}
			else if (codepoint < 0x10000)
			{
				return this->append_string_byte(static_cast<char>(
					0xE0 | (codepoint >> 12))) &&
					this->append_string_byte(static_cast<char>(
						0x80 | ((codepoint >> 6) & 0x3F))) &&
					this->append_string_byte(static_cast<char>(
						0x80 | (codepoint & 0x3F)));
			}
			else
			{
				return this->append_string_byte(static_cast<char>(
					0xF0 | (codepoint >> 18))) &&
					this->append_string_byte(static_cast<char>(
						0x80 | ((codepoint >> 12) & 0x3F))) &&
					this->append_string_byte(static_cast<char>(
						0x80 | ((codepoint >> 6) & 0x3F))) &&
					this->append_string_byte(static_cast<char>(
						0x80 | (codepoint & 0x3F)));
			}
		}

		void step_string(string_view chunk, size_t& i)
		{
			const size_t n = chunk.size();

			while (i < n && this->m_error.value() == error::none)
			{
				const char c = chunk[i];

				if (this->m_unicode_expect_low)
				{
					// after a high surrogate the input must
					// continue with "\uXXXX" — expect_low holds
					// how many of the two introducer chars are
					// still expected (2: "\u", 1: "u")
					const char expected =
						this->m_unicode_expect_low == 2 ? '\\' : 'u';

					if (c != expected)
					{
						this->fail(error::invalid_unicode_escape);
						return;
					}

					--this->m_unicode_expect_low;

					if (this->m_unicode_expect_low == 0)
					{
						this->m_unicode_remaining = 4;
						this->m_unicode_value = 0;
					}

					++i;
					continue;
				}

				if (this->m_unicode_remaining > 0)
				{
					unsigned char digit = 0;
					if (detail::is_hex_digit(c, &digit) == false)
					{
						this->fail(error::invalid_unicode_escape);
						return;
					}

					this->m_unicode_value =
						(this->m_unicode_value << 4) | digit;

					--this->m_unicode_remaining;
					++i;

					if (this->m_unicode_remaining == 0)
					{
						const std::uint32_t unit =
							this->m_unicode_value;

						if (this->m_unicode_high_surrogate)
						{
							if (unit < 0xDC00 || unit > 0xDFFF)
							{
								this->fail(
									error::invalid_unicode_escape);
								return;
							}

							const std::uint32_t codepoint =
								0x10000 +
								(((this->m_unicode_high_surrogate -
								     0xD800)
								     << 10) |
								 (unit - 0xDC00));

							this->m_unicode_high_surrogate = 0;

							if (this->append_unicode_codepoint(
									codepoint) == false)
								return;
						}
						else if (unit >= 0xD800 && unit <= 0xDBFF)
						{
							this->m_unicode_high_surrogate =
								static_cast<std::uint16_t>(unit);
							this->m_unicode_expect_low = 2;
						}
						else if (unit >= 0xDC00 && unit <= 0xDFFF)
						{
							this->fail(error::invalid_unicode_escape);
							return;
						}
						else
						{
							if (this->append_unicode_codepoint(
									unit) == false)
								return;
						}
					}

					continue;
				}

				if (this->m_string_escape)
				{
					this->m_string_escape = false;

					switch (c)
					{
					case '"':
					case '\\':
					case '/':
					{
						if (this->append_string_byte(c) == false)
							return;
						break;
					}
					case 'b':
					{
						if (this->append_string_byte('\b') == false)
							return;
						break;
					}
					case 'f':
					{
						if (this->append_string_byte('\f') == false)
							return;
						break;
					}
					case 'n':
					{
						if (this->append_string_byte('\n') == false)
							return;
						break;
					}
					case 'r':
					{
						if (this->append_string_byte('\r') == false)
							return;
						break;
					}
					case 't':
					{
						if (this->append_string_byte('\t') == false)
							return;
						break;
					}
					case 'u':
					{
						this->m_unicode_remaining = 4;
						this->m_unicode_value = 0;
						break;
					}
					default:
					{
						this->fail(error::invalid_escape);
						return;
					}
					}

					++i;
					continue;
				}

				if (c == '\\')
				{
					if (this->materialize_string_prefix(chunk, i) ==
					    false)
						return;

					this->m_string_escape = true;
					++i;
					continue;
				}

				if (c == '"')
				{
					string_view delivered;

					if (this->m_buffer_used)
					{
						delivered = string_view(
							this->m_buffer, this->m_buffer_length);
					}
					else
					{
						delivered = chunk.substr(
							this->m_zero_copy_begin,
							i - this->m_zero_copy_begin);
					}

					this->m_token = token::none;
					++i;

					if (this->m_string_is_key)
					{
						if (this->m_p_handler->on_key(delivered) ==
						    false)
						{
							this->fail(error::handler_aborted);
							return;
						}

						this->m_state = state::object_colon;
					}
					else
					{
						if (this->m_p_handler->on_string(delivered) ==
						    false)
						{
							this->fail(error::handler_aborted);
							return;
						}

						this->after_value();
					}

					return;
				}

				if (static_cast<unsigned char>(c) < 0x20)
				{
					this->fail(error::unexpected_character);
					return;
				}

				if (this->m_buffer_used)
				{
					if (this->append_string_byte(c) == false)
						return;
				}

				++i;
			}

			// the chunk ended mid-string: keep the raw prefix for
			// the next feed()
			if (this->m_error.value() == error::none &&
			    this->m_token == token::string_token &&
			    this->m_buffer_used == false)
			{
				this->materialize_string_prefix(chunk, n);
			}
		}

		void finish_number(void)
		{
			this->m_number_buffer[this->m_number_length] = '\0';

			const detail::number_class classification =
				detail::classify_number(
					this->m_number_buffer, this->m_number_length);

			if (classification == detail::number_class::invalid)
			{
				this->fail(error::invalid_number);
				return;
			}

			this->m_token = token::none;

			bool status = false;

			if (classification == detail::number_class::is_double)
			{
				status = this->m_p_handler->on_double(
					std::strtod(this->m_number_buffer, nullptr));
			}
			else if (this->m_number_buffer[0] == '-')
			{
				errno = 0;
				const long long parsed =
					std::strtoll(this->m_number_buffer, nullptr, 10);

				if (errno == ERANGE)
				{
					// negative integer below int64 — degrade to
					// double rather than failing
					status = this->m_p_handler->on_double(
						std::strtod(this->m_number_buffer, nullptr));
				}
				else
				{
					status = this->m_p_handler->on_int64(
						static_cast<std::int64_t>(parsed));
				}
			}
			else
			{
				errno = 0;
				const long long parsed =
					std::strtoll(this->m_number_buffer, nullptr, 10);

				if (errno == ERANGE)
				{
					errno = 0;
					const unsigned long long parsed_unsigned =
						std::strtoull(
							this->m_number_buffer, nullptr, 10);

					if (errno == ERANGE)
					{
						status = this->m_p_handler->on_double(
							std::strtod(
								this->m_number_buffer, nullptr));
					}
					else
					{
						status = this->m_p_handler->on_uint64(
							static_cast<std::uint64_t>(
								parsed_unsigned));
					}
				}
				else
				{
					status = this->m_p_handler->on_int64(
						static_cast<std::int64_t>(parsed));
				}
			}

			if (status == false)
			{
				this->fail(error::handler_aborted);
				return;
			}

			this->after_value();
		}

	private:
		stream_handler* m_p_handler;
		parse_options m_options;
		state m_state;
		size_t m_depth;
		token m_token;

		/// container stack: 'o' = object, 'a' = array
		char m_stack[KOTEK_DEF_OWN_JSON_STREAM_MAX_DEPTH];

		/// string token assembly (only engaged when the token spans
		/// chunks or contains escapes)
		char m_buffer[KOTEK_DEF_OWN_JSON_STREAM_TOKEN_BUFFER_SIZE];
		size_t m_buffer_length;
		bool m_buffer_used;
		size_t m_zero_copy_begin;
		bool m_string_escape;
		bool m_string_is_key;
		unsigned char m_unicode_remaining;
		std::uint32_t m_unicode_value;
		std::uint16_t m_unicode_high_surrogate;
		unsigned char m_unicode_expect_low;

		char m_number_buffer
			[KOTEK_DEF_OWN_JSON_STREAM_NUMBER_BUFFER_SIZE];
		size_t m_number_length;

		unsigned char m_literal_position;
		bool m_comment_closing;

		error_code m_error;
	};

	/// SAX writer — the mirror of stream_reader. Emits a well-formed
	/// json document into the caller's fixed buffer; whenever the buffer
	/// fills (and once at finish()) the completed chunk is handed to the
	/// flush callback. Contract violations (a key outside an object, a
	/// second root value, unclosed containers at finish()) set a sticky
	/// error instead of corrupting the output.
	class stream_writer
	{
	public:
		using flush_callback = void (*)(void* p_user, string_view chunk);

		stream_writer(
			char* p_buffer,
			size_t capacity,
			flush_callback p_callback,
			void* p_user)
			: m_p_buffer(p_buffer),
			  m_capacity(capacity),
			  m_position(0),
			  m_p_callback(p_callback),
			  m_p_user(p_user),
			  m_depth(0),
			  m_root_written(false),
			  m_error()
		{
			if (p_buffer == nullptr ||
			    capacity < KOTEK_DEF_OWN_JSON_STREAM_WRITER_MIN_BUFFER)
			{
				KOTEK_ASSERT(
					false,
					"stream_writer needs a buffer of at least "
					"KOTEK_DEF_OWN_JSON_STREAM_WRITER_MIN_BUFFER "
					"bytes");
				this->m_error.assign(error::buffer_overflow);
			}
		}

		bool on_object_begin(void)
		{
			if (this->prepare_value() == false)
				return false;

			if (this->m_depth >= KOTEK_DEF_OWN_JSON_STREAM_MAX_DEPTH)
			{
				this->fail(error::depth_exceeded);
				return false;
			}

			this->emit_raw('{');
			this->m_levels[this->m_depth++] = level::object_empty;
			return this->is_ok();
		}

		bool on_object_end(void)
		{
			if (this->m_depth == 0 ||
			    (this->m_levels[this->m_depth - 1] !=
			         level::object_empty &&
			     this->m_levels[this->m_depth - 1] !=
			         level::object_pairs))
			{
				this->fail(error::writer_misuse);
				return false;
			}

			--this->m_depth;
			this->emit_raw('}');
			this->commit_value();
			return this->is_ok();
		}

		bool on_array_begin(void)
		{
			if (this->prepare_value() == false)
				return false;

			if (this->m_depth >= KOTEK_DEF_OWN_JSON_STREAM_MAX_DEPTH)
			{
				this->fail(error::depth_exceeded);
				return false;
			}

			this->emit_raw('[');
			this->m_levels[this->m_depth++] = level::array_empty;
			return this->is_ok();
		}

		bool on_array_end(void)
		{
			if (this->m_depth == 0 ||
			    (this->m_levels[this->m_depth - 1] !=
			         level::array_empty &&
			     this->m_levels[this->m_depth - 1] !=
			         level::array_items))
			{
				this->fail(error::writer_misuse);
				return false;
			}

			--this->m_depth;
			this->emit_raw(']');
			this->commit_value();
			return this->is_ok();
		}

		bool on_key(string_view key)
		{
			if (this->m_depth == 0)
			{
				this->fail(error::writer_misuse);
				return false;
			}

			level& top = this->m_levels[this->m_depth - 1];

			if (top == level::object_pairs)
			{
				this->emit_raw(',');
			}
			else if (top != level::object_empty)
			{
				this->fail(error::writer_misuse);
				return false;
			}

			this->emit_escaped(key);
			this->emit_raw(':');
			top = level::object_after_key;
			return this->is_ok();
		}

		bool on_string(string_view data)
		{
			if (this->prepare_value() == false)
				return false;

			this->emit_escaped(data);
			this->commit_value();
			return this->is_ok();
		}

		bool on_null(void)
		{
			if (this->prepare_value() == false)
				return false;

			this->emit_raw("null", 4);
			this->commit_value();
			return this->is_ok();
		}

		bool on_bool(bool data)
		{
			if (this->prepare_value() == false)
				return false;

			if (data)
				this->emit_raw("true", 4);
			else
				this->emit_raw("false", 5);

			this->commit_value();
			return this->is_ok();
		}

		bool on_int64(std::int64_t data)
		{
			if (this->prepare_value() == false)
				return false;

			char text[24];
			const size_t length =
				detail::format_int64(text, sizeof(text), data);

			if (length == 0)
			{
				this->fail(error::buffer_overflow);
				return false;
			}

			this->emit_raw(text, length);
			this->commit_value();
			return this->is_ok();
		}

		bool on_uint64(std::uint64_t data)
		{
			if (this->prepare_value() == false)
				return false;

			char text[24];
			const size_t length =
				detail::format_uint64(text, sizeof(text), data);

			if (length == 0)
			{
				this->fail(error::buffer_overflow);
				return false;
			}

			this->emit_raw(text, length);
			this->commit_value();
			return this->is_ok();
		}

		bool on_double(double data)
		{
			if (this->prepare_value() == false)
				return false;

			char text[32];
			const size_t length =
				detail::format_double(text, sizeof(text), data);

			if (length == 0)
			{
				this->fail(error::buffer_overflow);
				return false;
			}

			this->emit_raw(text, length);
			this->commit_value();
			return this->is_ok();
		}

		/// hands the pending chunk to the callback without validating
		/// the document; finish() is what proves the document is whole
		void flush(void)
		{
			if (this->m_position > 0 && this->m_p_callback)
			{
				this->m_p_callback(
					this->m_p_user,
					string_view(this->m_p_buffer, this->m_position));
				this->m_position = 0;
			}
		}

		bool finish(void)
		{
			if (this->m_depth != 0 || this->m_root_written == false)
				this->fail(error::writer_misuse);

			this->flush();
			return this->is_ok();
		}

		bool is_ok(void) const
		{
			return this->m_error.value() == error::none;
		}

		error_code get_error(void) const { return this->m_error; }

	private:
		enum class level : unsigned char
		{
			object_empty = 0,
			object_pairs,
			object_after_key,
			array_empty,
			array_items
		};

		void fail(error value)
		{
			if (this->m_error.value() == error::none)
				this->m_error.assign(value);
		}

		/// emits the separators that must precede a value (',' in a
		/// non-empty array, nothing after a key) and validates the
		/// position
		bool prepare_value(void)
		{
			if (this->m_error)
				return false;

			if (this->m_depth == 0)
			{
				if (this->m_root_written)
				{
					this->fail(error::writer_misuse);
					return false;
				}

				return true;
			}

			const level top = this->m_levels[this->m_depth - 1];

			switch (top)
			{
			case level::object_after_key:
			{
				return true;
			}
			case level::array_empty:
			{
				return true;
			}
			case level::array_items:
			{
				this->emit_raw(',');
				return this->is_ok();
			}
			default:
			{
				this->fail(error::writer_misuse);
				return false;
			}
			}
		}

		/// bookkeeping after a value fully landed
		void commit_value(void)
		{
			if (this->m_depth == 0)
			{
				this->m_root_written = true;
				return;
			}

			level& top = this->m_levels[this->m_depth - 1];

			if (top == level::object_after_key)
				top = level::object_pairs;
			else if (top == level::array_empty)
				top = level::array_items;
		}

		void emit_raw(char c)
		{
			if (this->m_error)
				return;

			if (this->m_position == this->m_capacity)
			{
				this->flush();

				if (this->m_position == this->m_capacity)
				{
					// no callback (or it kept the data): the
					// single char itself does not fit
					this->fail(error::buffer_overflow);
					return;
				}
			}

			this->m_p_buffer[this->m_position++] = c;
		}

		void emit_raw(const char* p_text, size_t length)
		{
			while (length > 0 && this->m_error.value() == error::none)
			{
				if (this->m_position == this->m_capacity)
					this->flush();

				const size_t room =
					this->m_capacity - this->m_position;

				if (room == 0)
				{
					this->fail(error::buffer_overflow);
					return;
				}

				const size_t piece =
					length < room ? length : room;

				std::memcpy(
					this->m_p_buffer + this->m_position,
					p_text,
					piece);

				this->m_position += piece;
				p_text += piece;
				length -= piece;
			}
		}

		void emit_escaped(string_view data)
		{
			this->emit_raw('"');

			for (size_t i = 0; i < data.size(); ++i)
			{
				const char c = data[i];

				switch (c)
				{
				case '"':
					this->emit_raw("\\\"", 2);
					break;
				case '\\':
					this->emit_raw("\\\\", 2);
					break;
				case '\b':
					this->emit_raw("\\b", 2);
					break;
				case '\f':
					this->emit_raw("\\f", 2);
					break;
				case '\n':
					this->emit_raw("\\n", 2);
					break;
				case '\r':
					this->emit_raw("\\r", 2);
					break;
				case '\t':
					this->emit_raw("\\t", 2);
					break;
				default:
				{
					if (static_cast<unsigned char>(c) < 0x20)
					{
						char escape[6] = {'\\', 'u', '0', '0', '0', '0'};
						const unsigned char byte =
							static_cast<unsigned char>(c);
						escape[4] =
							"0123456789abcdef"[byte >> 4];
						escape[5] =
							"0123456789abcdef"[byte & 0x0F];
						this->emit_raw(escape, sizeof(escape));
					}
					else
					{
						this->emit_raw(c);
					}
					break;
				}
				}
			}

			this->emit_raw('"');
		}

	private:
		char* m_p_buffer;
		size_t m_capacity;
		size_t m_position;
		flush_callback m_p_callback;
		void* m_p_user;

		unsigned char m_depth;
		level m_levels[KOTEK_DEF_OWN_JSON_STREAM_MAX_DEPTH];
		bool m_root_written;

		error_code m_error;
	};

} // namespace json

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK

#endif

