#pragma once

/// \file kotek_render_geometry_handle_table.h
/// \~english the opaque-handle table behind ktkIRenderGeometryManager
/// (task K11 phase 3 / zircon Z24 B3b). Deliberately free of NRI types — it
/// bookkeeps OPAQUE void* slots — so the handle semantics (generation-tagged
/// indices, stale/foreign guards, the capacity contract) are provable
/// headlessly in kotek.core's tests without a GPU. The manager maps the
/// slots onto nri::Buffer*/nri::Pipeline*; both fit the object+aux pair
/// (buffer+memory, pipeline+pipeline-layout).
///
/// Handle encoding: (generation << 16) | (index + 1) — index+1 in the low
/// 16 bits so the all-zero low half never aliases a live slot (0 is not a
/// valid handle); the generation in the high half makes a stale handle
/// (slot freed and re-created) detectable instead of silently re-binding
/// whatever now occupies the slot. Capacities stay below 65535 by the
/// KOTEK_DEF_RENDER_NRI_GEOMETRY_MAX_* defines.

#include "kotek_render_nri.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_NRI

/// \~english the slot payload: the two opaque backend objects plus the
/// bookkeeping the guards need (a 16-bit generation per slot, the byte size
/// for the upload-range validation)
struct ktkRenderGeometrySlot
{
	void* m_p_object{};
	void* m_p_aux{};
	kun_ktk uint64_t m_size_bytes{};
	kun_ktk uint16_t m_generation{};
	bool m_is_alive{};
};

/// \~english the fixed-capacity handle table (a member of the geometry
/// manager — no static storage, rule 1a)
template <kun_ktk size_t Capacity>
class ktkRenderGeometryHandleTable
{
public:
	ktkRenderGeometryHandleTable(void) = default;
	~ktkRenderGeometryHandleTable(void) = default;

	ktkRenderGeometryHandleTable(const ktkRenderGeometryHandleTable&) =
		delete;
	ktkRenderGeometryHandleTable& operator=(
		const ktkRenderGeometryHandleTable&) = delete;

	/// \~english stores the pair, returning the fresh handle; the invalid
	/// sentinel when the table is full (the caller logs — a capacity error
	/// is loud, never silent)
	kun_ktk uint32_t allocate(void* p_object, void* p_aux,
		kun_ktk uint64_t size_bytes) noexcept
	{
		for (kun_ktk uint32_t index = 0; index < Capacity; ++index)
		{
			if (this->m_slots[index].m_is_alive == false)
			{
				ktkRenderGeometrySlot& slot = this->m_slots[index];

				slot.m_p_object = p_object;
				slot.m_p_aux = p_aux;
				slot.m_size_bytes = size_bytes;
				slot.m_is_alive = true;

				return this->encode(
					index, slot.m_generation);
			}
		}

		return 0u; // the all-zero pattern — never a live handle
	}

	/// \~english frees the slot the handle names (bumping its generation so
	/// every outstanding copy of the handle goes stale); false on an
	/// invalid/stale/foreign handle — a loud no-op, never a crash
	bool free(kun_ktk uint32_t handle) noexcept
	{
		ktkRenderGeometrySlot* p_slot = this->resolve(handle);

		if (p_slot == nullptr)
			return false;

		p_slot->m_p_object = nullptr;
		p_slot->m_p_aux = nullptr;
		p_slot->m_size_bytes = 0;
		p_slot->m_is_alive = false;
		++p_slot->m_generation; // the stale-maker (16-bit wrap is fine —
								// the live handle must only survive one
								// free/re-create cycle)

		return true;
	}

	/// \~english the slot for a VALID handle, nullptr for an invalid /
	/// stale / foreign / out-of-range one (the callers guard loudly)
	ktkRenderGeometrySlot* resolve(kun_ktk uint32_t handle) noexcept
	{
		const kun_ktk uint32_t index = this->index_of(handle);

		if (index >= Capacity)
			return nullptr;

		ktkRenderGeometrySlot& slot = this->m_slots[index];

		if (slot.m_is_alive == false)
			return nullptr;

		if (slot.m_generation != this->generation_of(handle))
			return nullptr;

		return &slot;
	}

	const ktkRenderGeometrySlot* resolve(
		kun_ktk uint32_t handle) const noexcept
	{
		return const_cast<ktkRenderGeometryHandleTable*>(this)->resolve(
			handle);
	}

	/// \~english the upload-range guard: the handle is live AND
	/// offset + size fits the stored size
	bool is_range_valid(kun_ktk uint32_t handle,
		kun_ktk uint64_t offset_bytes,
		kun_ktk uint64_t size_bytes) const noexcept
	{
		const ktkRenderGeometrySlot* p_slot = this->resolve(handle);

		if (p_slot == nullptr)
			return false;

		return (offset_bytes <= p_slot->m_size_bytes) &&
			(size_bytes <= p_slot->m_size_bytes - offset_bytes);
	}

	kun_ktk uint32_t get_live_count(void) const noexcept
	{
		kun_ktk uint32_t count = 0;

		for (kun_ktk uint32_t index = 0; index < Capacity; ++index)
		{
			if (this->m_slots[index].m_is_alive)
				++count;
		}

		return count;
	}

	/// \~english the capacity the KOTEK_DEF_RENDER_NRI_GEOMETRY_MAX_*
	/// defines size — the tests build a small instantiation to prove the
	/// overflow contract without allocating the real table
	static constexpr kun_ktk uint32_t get_capacity(void) noexcept
	{
		return static_cast<kun_ktk uint32_t>(Capacity);
	}

	/// \~english the slot index a (valid-shaped) handle names — the
	/// compute-path side tables key off it (task K11 phase 4); no validity
	/// check (the caller resolved the handle already)
	static constexpr kun_ktk uint32_t slot_index(
		kun_ktk uint32_t handle) noexcept
	{
		return index_of(handle);
	}

	/// \~english the raw slot view (the manager's Shutdown walks every live
	/// slot directly — no handle indirection needed when tearing down)
	const ktkRenderGeometrySlot* get_slots(void) const noexcept
	{
		return this->m_slots;
	}

private:
	static constexpr kun_ktk uint32_t encode(
		kun_ktk uint32_t index, kun_ktk uint16_t generation) noexcept
	{
		return (static_cast<kun_ktk uint32_t>(generation) << 16u) |
			(index + 1u);
	}

	static constexpr kun_ktk uint32_t index_of(
		kun_ktk uint32_t handle) noexcept
	{
		return (handle & 0xFFFFu) - 1u; // 0 handle underflows to 0xFFFF
	}

	static constexpr kun_ktk uint16_t generation_of(
		kun_ktk uint32_t handle) noexcept
	{
		return static_cast<kun_ktk uint16_t>(handle >> 16u);
	}

private:
	/// \~english the slot storage: a plain fixed array (NOT a
	/// static_vector — etl::vector leaves its backing buffer
	/// unconstructed, and the slots must be zero-initialized from the
	/// first allocation; the in-class {} value-initializes every POD
	/// element deterministically)
	ktkRenderGeometrySlot m_slots[Capacity]{};
};

/// \~english the per-compute-pipeline storage-binding cache (task K11
/// phase 4 / zircon Z24 B3c): pure bookkeeping over opaque values — the
/// manager stores one per compute pipeline slot and the frame context asks
/// "did this binding change?" before recreating the backend view (a
/// Descriptor owns a descriptor handle on every backend, so per-frame
/// re-creation would leak; the pass re-declares the same bindings every
/// frame and the cache no-ops). Deliberately free of NRI types so the
/// change-detection contract is provable headlessly in kotek.core's tests
/// (the handle-table precedent)
template <kun_ktk size_t Capacity>
class ktkRenderGeometryComputeBindingCache
{
public:
	ktkRenderGeometryComputeBindingCache(void) = default;
	~ktkRenderGeometryComputeBindingCache(void) = default;

	ktkRenderGeometryComputeBindingCache(
		const ktkRenderGeometryComputeBindingCache&) = delete;
	ktkRenderGeometryComputeBindingCache& operator=(
		const ktkRenderGeometryComputeBindingCache&) = delete;

	/// \~english records the binding's current value; true when it CHANGED
	/// (or on first use) — the caller recreates the backend view; false =
	/// the cached view is still valid and nothing happens. An
	/// out-of-capacity binding is a loud assert (a programmer error — the
	/// pipeline was created with this many bindings)
	bool set(kun_ktk uint32_t binding_index,
		Core::ktkRenderGeometryBufferHandle buffer,
		kun_ktk uint64_t offset_bytes, kun_ktk uint64_t size_bytes) noexcept
	{
		if (binding_index >= Capacity)
		{
			KOTEK_ASSERT(false,
				"[nri] compute binding {} is outside the cache capacity "
				"{} — the pipeline declares fewer storage bindings",
				binding_index, Capacity);

			return false;
		}

		ktkRenderComputeBinding& binding = this->m_bindings[binding_index];

		if (binding.m_is_set && binding.m_buffer == buffer &&
			binding.m_offset_bytes == offset_bytes &&
			binding.m_size_bytes == size_bytes)
		{
			return false;
		}

		binding.m_buffer = buffer;
		binding.m_offset_bytes = offset_bytes;
		binding.m_size_bytes = size_bytes;
		binding.m_is_set = true;

		return true;
	}

	bool is_set(kun_ktk uint32_t binding_index) const noexcept
	{
		return binding_index < Capacity &&
			this->m_bindings[binding_index].m_is_set;
	}

	/// \~english the first binding_count bindings populated (the Dispatch
	/// guard: a kernel reading an unbound slot must never record). The
	/// capacity is the per-pipeline MAXIMUM — a pipeline declares its own
	/// binding count at creation, completeness is checked against THAT
	bool is_complete(kun_ktk uint32_t binding_count) const noexcept
	{
		if (binding_count > Capacity)
			return false;

		for (kun_ktk uint32_t index = 0; index < binding_count; ++index)
		{
			if (this->m_bindings[index].m_is_set == false)
				return false;
		}

		return true;
	}

	void clear(void) noexcept
	{
		for (kun_ktk size_t index = 0; index < Capacity; ++index)
		{
			this->m_bindings[index] = ktkRenderComputeBinding{};
		}
	}

private:
	struct ktkRenderComputeBinding
	{
		Core::ktkRenderGeometryBufferHandle m_buffer{
			Core::kInvalidRenderGeometryBufferHandle};
		kun_ktk uint64_t m_offset_bytes{};
		kun_ktk uint64_t m_size_bytes{};
		bool m_is_set{};
	};

	ktkRenderComputeBinding m_bindings[Capacity]{};
};

KOTEK_END_NAMESPACE_RENDER_NRI
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
