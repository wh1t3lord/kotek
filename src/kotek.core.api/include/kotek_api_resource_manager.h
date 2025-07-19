#pragma once

#include <kotek.core.enum/include/kotek_core_enum.h>
#include <kotek.core.containers.filesystem.path\include\kotek_core_containers_filesystem_path.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkLoadingRequest
{
public:
	ktkLoadingRequest(eResourceThreadingPolicy type_threading,
		eResourceLoadingPolicy type_loading,
		eResourceCachingPolicy type_policy_caching,
		eResourceLoadingType type_of_loading_resource,
		const ktk_filesystem_path& resource_path) :
		m_policy_threading{type_threading}, m_policy_loading{type_loading},
		m_policy_caching{type_policy_caching},
		m_resource_type{type_of_loading_resource}, m_id{ktk::uint32_t(-1)},
		m_resource_path{resource_path}
	{
	}

	ktkLoadingRequest(eResourceThreadingPolicy type_threading,
		eResourceLoadingPolicy type_loading,
		eResourceCachingPolicy type_policy_caching,
		eResourceLoadingType type_of_loading_resource,
		const ktk_filesystem_path& resource_path, ktk::uint32_t id) :
		m_policy_threading{type_threading}, m_policy_loading{type_loading},
		m_policy_caching{type_policy_caching},
		m_resource_type{type_of_loading_resource}, m_id{id},
		m_resource_path{resource_path}
	{
	}

	ktkLoadingRequest(void) :
		m_policy_caching{},
		m_policy_threading{eResourceThreadingPolicy::kAsync},
		m_policy_loading{eResourceLoadingPolicy::kWhole},
		m_resource_type{eResourceLoadingType::kAutoDetect}, m_id{}
	{
	}

	~ktkLoadingRequest() = default;

	ktkLoadingRequest& Set_LoadingPolicy(eResourceLoadingPolicy policy) noexcept
	{
		this->m_policy_loading = policy;
		return *this;
	}

	eResourceThreadingPolicy Get_ThreadingPolicy(void) const noexcept
	{
		return this->m_policy_threading;
	}

	eResourceLoadingPolicy Get_LoadingPolicy(void) const noexcept
	{
		return this->m_policy_loading;
	}

	ktkLoadingRequest& Set_CachingPolicy(eResourceCachingPolicy policy) noexcept
	{
		this->m_policy_caching = policy;
		return *this;
	}

	eResourceCachingPolicy Get_CachingPolicy(void) const noexcept
	{
		return this->m_policy_caching;
	}

	ktkLoadingRequest& Set_ResourceType(eResourceLoadingType type) noexcept
	{
		this->m_resource_type = type;
		return *this;
	}

	eResourceLoadingType Get_ResourceType() const noexcept
	{
		return this->m_resource_type;
	}

	ktkLoadingRequest& Set_ResourcePath(
		const ktk_filesystem_path& path) noexcept
	{
		this->m_resource_path = path;
		return *this;
	}

	const ktk_filesystem_path& Get_ResourcePath(void) const noexcept
	{
		return this->m_resource_path;
	}

	bool Is_ForEntity(void) const noexcept
	{
		return this->m_id != ktk::uint32_t(-1);
	}

	ktk::uint32_t Get_EntityID(void) const noexcept { return this->m_id; }

private:
	eResourceThreadingPolicy m_policy_threading;
	eResourceLoadingPolicy m_policy_loading;
	eResourceCachingPolicy m_policy_caching;
	eResourceLoadingType m_resource_type;
	ktk::uint32_t m_id;
	ktk_filesystem_path m_resource_path;
};

/// @brief \~english request for loading or saving asset
struct ktkResourceAssetRequest
{
	ktkResourceAssetRequest(eResourceThreadingPolicy type_threading,
		eResourceLoadingPolicy type_loading,
		eResourceCachingPolicy type_policy_caching,
		eResourceLoadingType type_of_loading_resource,
		const ktk_filesystem_path& resource_path) :
		entity_id{kun_ktk uint32_t(-1)}, resource_path{resource_path}
	{
	}

	ktkResourceAssetRequest(eResourceThreadingPolicy type_threading,
		eResourceLoadingPolicy type_loading,
		eResourceCachingPolicy type_policy_caching,
		eResourceLoadingType type_of_loading_resource,
		const ktk_filesystem_path& resource_path, kun_ktk uint32_t id) :
		entity_id{id}, resource_path{resource_path}
	{
	}

	ktkResourceAssetRequest(void) : entity_id{} {}

	~ktkResourceAssetRequest() = default;

	eResourceRequestThreadingPolicy policy_threading;
	eResourceRequestCachingPolicy policy_caching;
	eResourceRequestOperationType operation_type;
	eResourceRequestResourceType resource_type;

	kun_ktk uint32_t entity_id;
	ktk_filesystem_path resource_path;
};

/// @brief \~english provides I/O API for user
struct ktkResourceFileStreamRequest
{
	ktkResourceFileStreamRequest() :
		operation_type{eResourceRequestOperationType::kEndOfEnum},
		resource_type{eResourceRequestResourceType::kUnknown}
	{
	}

	~ktkResourceFileStreamRequest() = default;

	eResourceRequestOperationType operation_type;
	eResourceRequestResourceType resource_type;
	ktk_filesystem_path path_to_file;
};

class ktkResourceChunk
{
public:
	ktkResourceChunk() {}
	~ktkResourceChunk() {}

	kun_ktk uint32_t GetRemaningChunks() const
	{
		return this->total_chunks_count - this->current_chunk_index;
	}

	bool is_final;
	bool is_loaded;
	bool is_need_to_load_next_chunk;

	kun_ktk uint32_t current_chunk_index;
	kun_ktk uint32_t total_chunks_count;
};

class ktkResourceRequest
{
public:
	ktkResourceRequest(eResourceRequestOperationType type,
		const ktk_filesystem_path& path,
		eResourceRequestResourceType resource_type =
			eResourceRequestResourceType::kAutoDetect) :
		m_type{type}, m_resource_type{resource_type}, m_path_to_file{}
	{
	}

	ktkResourceRequest() :
		m_type{eResourceRequestOperationType::kLoad},
		m_resource_type{eResourceRequestResourceType::kAutoDetect},
		m_path_to_file{}
	{
	}

	~ktkResourceRequest() {}

private:
	eResourceRequestOperationType m_type;
	eResourceRequestResourceType m_resource_type;
	ktk_filesystem_path m_path_to_file;
};

struct ktkResourceLoadResponse
{
	friend class StreamingManager;

	ktkResourceLoadResponse() :
		m_ready{}, m_data{}, m_total_chunks{}, m_current_chunk{}
	{
	}
	~ktkResourceLoadResponse() {}

	bool is_ready(void) const noexcept
	{
		bool result{};
		if (!m_ready)
			return result;

		result = *m_ready;

		return result;
	}

	unsigned char* get_data(void) const { return m_data; }

	size_t get_total_chunks(void) const
	{
		if (!m_total_chunks)
			return 0;

		return *m_total_chunks;
	}

	size_t get_current_chunk(void) const
	{
		if (!m_current_chunk)
			return 0;

		return *m_current_chunk;
	}

private:
	bool* m_ready;           // Pointer to chunk readiness flag
	unsigned char* m_data;   // Pointer to chunk data
	size_t* m_total_chunks;  // Total chunks in the stream
	size_t* m_current_chunk; // Current chunk index (0-based)
};

struct ktkResourceSaveResponse
{
	friend class StreamingManager;

	ktkResourceSaveResponse() {}
	~ktkResourceSaveResponse() {}

private:
};

class ktkResourceReadingRequest
{
public:
	ktkResourceReadingRequest() :
		m_id{},
		m_resource_type{kun_kotek kun_core eResourceReadingType::kUnknown},
		m_policy{kun_kotek kun_core eResourceReadingPolicy::kSync}
	{
	}

	ktkResourceReadingRequest(kun_ktk uint32_t id, eResourceReadingType type,
		eResourceReadingPolicy policy, const ktk_filesystem_path& path) :
		m_id{id}, m_resource_type{type}, m_filepath_for_writing{path},
		m_policy{policy}
	{
	}
	~ktkResourceReadingRequest() = default;

	eResourceReadingType Get_ResourceType(void) const noexcept
	{
		return this->m_resource_type;
	}

	ktkResourceReadingRequest& Set_ResourceType(
		eResourceReadingType type) noexcept
	{
		this->m_resource_type = type;
		return *this;
	}

	kun_ktk uint32_t Get_ID(void) const noexcept { return this->m_id; }
	void Set_ID(kun_ktk uint32_t id) noexcept { this->m_id = id; }

	const ktk_filesystem_path& Get_Path(void) const noexcept
	{
		return this->m_filepath_for_writing;
	}

	ktkResourceReadingRequest& Set_Path(
		const ktk_filesystem_path& path) noexcept
	{
		this->m_filepath_for_writing = path;
		return *this;
	}

	eResourceReadingPolicy Get_Policy(void) const noexcept
	{
		return this->m_policy;
	}

private:
	kun_ktk uint32_t m_id;
	eResourceReadingType m_resource_type;
	eResourceReadingPolicy m_policy;
	ktk_filesystem_path m_filepath_for_writing;
};

class ktkResourceWritingRequest
{
public:
	ktkResourceWritingRequest() :
		m_id{},
		m_writing_mode{kun_kotek kun_core eResourceWritingMode::kNew_Trunc},
		m_resource_type{kun_kotek kun_core eResourceWritingType::kUnknown},
		m_policy{kun_kotek kun_core eResourceWritingPolicy::kSync}
	{
	}

	ktkResourceWritingRequest(kun_ktk uint32_t id, eResourceWritingMode mode,
		eResourceWritingType type, eResourceWritingPolicy policy,
		const ktk_filesystem_path& path) :
		m_id{id}, m_writing_mode{mode}, m_resource_type{type},
		m_filepath_for_writing{path}, m_policy{policy}
	{
	}
	~ktkResourceWritingRequest() = default;

	eResourceWritingType Get_ResourceType(void) const noexcept
	{
		return this->m_resource_type;
	}

	ktkResourceWritingRequest& Set_ResourceType(
		eResourceWritingType type) noexcept
	{
		this->m_resource_type = type;
		return *this;
	}

	eResourceWritingMode Get_WritingMode(void) const noexcept
	{
		return this->m_writing_mode;
	}

	ktkResourceWritingRequest& Set_WritingMode(
		eResourceWritingMode mode) noexcept
	{
		this->m_writing_mode = mode;
		return *this;
	}

	kun_ktk uint32_t Get_ID(void) const noexcept { return this->m_id; }
	void Set_ID(kun_ktk uint32_t id) noexcept { this->m_id = id; }

	const ktk_filesystem_path& Get_Path(void) const noexcept
	{
		return this->m_filepath_for_writing;
	}

	ktkResourceWritingRequest& Set_Path(
		const ktk_filesystem_path& path) noexcept
	{
		this->m_filepath_for_writing = path;
		return *this;
	}

	eResourceWritingPolicy Get_Policy(void) const noexcept
	{
		return this->m_policy;
	}

private:
	kun_ktk uint32_t m_id;
	eResourceWritingMode m_writing_mode;
	eResourceWritingType m_resource_type;
	eResourceWritingPolicy m_policy;
	ktk_filesystem_path m_filepath_for_writing;
};

class ktkResourceWritingStatus
{
public:
	ktkResourceWritingStatus() : m_can_be_closed{}, m_is_writing{} {}
	~ktkResourceWritingStatus() {}

	bool Is_Writing(void) const noexcept { return this->m_is_writing; }
	bool Is_CanBeClosed(void) const noexcept { return this->m_can_be_closed; }

	void Set_Writing(bool status) { this->m_is_writing = status; }
	void Set_CanBeClosed(bool status) { this->m_can_be_closed = status; }

private:
	bool m_can_be_closed;
	bool m_is_writing;
};

class ktkResourceHandle
{
public:
	ktkResourceHandle(void* p_allocated, bool is_allocated_on_stack = false
#ifdef KOTEK_DEBUG
		,
		const ktk_cstring_view& debug_type_name = "",
		const ktk_cstring_view& file_creation = "",
		const ktk_cstring_view& place_name = ""
#endif
		) :
		m_is_allocated_on_stack{is_allocated_on_stack},
		m_p_any_data_allocated{p_allocated}
#ifdef KOTEK_DEBUG
		,
		m_debug_type_name{debug_type_name.data()},
		m_file_name{file_creation.data()}, m_function_name{place_name.data()}
#endif
	{
	}

	ktkResourceHandle() = delete;
	~ktkResourceHandle()
	{
		if (!m_is_allocated_on_stack)
		{
			if (this->m_p_any_data_allocated)
			{
				delete this->m_p_any_data_allocated;
				this->m_p_any_data_allocated = nullptr;
			}
		}
	}

	bool Is_AllocatedOnStack(void) const noexcept
	{
		return this->m_is_allocated_on_stack;
	}

	void* Get_Resource(void) const noexcept
	{
		return this->m_p_any_data_allocated;
	}

private:
	bool m_is_allocated_on_stack;
	void* m_p_any_data_allocated;

#ifdef KOTEK_DEBUG
	ktk_cstring<128> m_debug_type_name;
	ktk_cstring<128> m_file_name;
	ktk_cstring<128> m_function_name;
#endif
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK