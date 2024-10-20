#pragma once

#include <kotek.core.api/include/kotek_api.h>
#include <kotek.core.containers.vector/include/kotek_core_containers_vector.h>
#include <kotek.core.containers.unordered_map/include/kotek_core_containers_unordered_map.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

template <typename ComponentType, std::size_t array_size>
class ktkComponentAllocator : public ktkIComponentAllocator
{
public:
	ktkComponentAllocator(void) :
		m_hashed_type(typeid(ComponentType).hash_code()), m_current_index{}
	{
		KOTEK_ASSERT(array_size > 0,
			"you must create allocator with array_size > 0! {}",
			this->GetDebugName().get_as_is());

		// TODO: Use deffered initialization for that case
		this->m_storage.resize(array_size);
		this->m_storage_entity_indicies.reserve(array_size);
	}

	~ktkComponentAllocator(void) {}

	// TODO: it's better to remove because you have GetComponentName
    ktk::cstring GetDebugName(void) const noexcept override
	{
        return typeid(ComponentType).name();
	}

	bool Create(ktk::uint32_t id) noexcept override
	{
		if (this->m_storage_entity_indicies.find(id) !=
			this->m_storage_entity_indicies.end())
		{
			KOTEK_ASSERT(
				false, "you have already existed component in storage: {}", id);

			return false;
		}

		if (this->m_current_index + 1 > array_size)
		{
			KOTEK_ASSERT(this->m_current_index == array_size,
				"Overflow! You need to set size bigger than: {}, [{}]",
				array_size, this->GetDebugName().get_as_is());

			return false;
		}

		this->m_storage_entity_indicies[id] = this->m_current_index;

		++this->m_current_index;

		return true;
	}

	bool Remove(ktk::uint32_t id) noexcept override
	{
		if (this->m_storage_entity_indicies.find(id) ==
			this->m_storage_entity_indicies.end())
		{
			return false;
		}

		auto index = this->m_storage_entity_indicies.at(id);

		this->m_storage.at(index).Clear();

		this->m_storage_entity_indicies.erase(id);

		--this->m_current_index;

		return true;
	}

	void* Get(ktk::uint32_t id) noexcept override
	{
		if (this->m_storage_entity_indicies.find(id) ==
			this->m_storage_entity_indicies.end())
		{
			return nullptr;
		}

		auto index = this->m_storage_entity_indicies.at(id);

		KOTEK_ASSERT(index < this->m_storage.size(),
			"Overflow or index is invalid, debug your code");

		return static_cast<void*>(&this->m_storage.at(index));
	}

	ktk::size_t GetHashedValueOfComponentType(void) const noexcept
	{
		return this->m_hashed_type;
	}

	ktk::ustring GetComponentName(void) const noexcept override
	{
		return ComponentType::GetComponentName();
	}

	void DrawImGui(Kotek::Core::ktkMainManager* main_manager,
		ktk::uint32_t entity_id) noexcept override
	{
		ComponentType* p_component =
			static_cast<ComponentType*>(this->Get(entity_id));

		if (p_component)
		{
			p_component->DrawImGui(main_manager);
		}
	}

	ktk::size_t GetCurrentSize(void) const noexcept
	{
		return this->m_current_index;
	}

	const ktk::vector<ComponentType>& GetComponents(void) const noexcept
	{
		return this->m_storage;
	}

private:
	ktk::size_t m_hashed_type;
	ktk::size_t m_current_index;
	ktk::vector<ComponentType> m_storage;
	ktk::unordered_map<ktk::uint32_t, ktk::size_t> m_storage_entity_indicies;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
