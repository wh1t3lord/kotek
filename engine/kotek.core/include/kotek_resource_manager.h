#pragma once

#include "kotek_std.h"
#include "kotek_interface_resource_loader_manager.h"

namespace Kotek
{
	namespace Core
	{
		enum class eResourceLoadingPolicy : ktk::enum_base_t
		{
			kAsync,
			kSync
		};

		enum class eResourceCachingPolicy : ktk::enum_base_t
		{
			// Returns constructed object
			kCache,

			// Using temporary instances that resource manager has
			kWithoutCache
		};

		class ktkLoadingRequest
		{
		public:
			ktkLoadingRequest(eResourceLoadingPolicy type_loading,
				eResourceCachingPolicy type_policy_caching,
				eResourceLoadingType type_of_loading_resource,
				const ktk::string& resource_path) :
				m_policy_loading{type_loading},
				m_policy_caching{type_policy_caching},
				m_resource_type{type_of_loading_resource}, m_resource_path{
															   resource_path}
			{
			}

			ktkLoadingRequest(void) :
				m_policy_caching{},
				m_policy_loading{eResourceLoadingPolicy::kAsync},
				m_resource_type{eResourceLoadingType::kAutoDetect}
			{
			}

			~ktkLoadingRequest() = default;

			ktkLoadingRequest& SetLoadingPolicy(
				eResourceLoadingPolicy policy) noexcept;
			eResourceLoadingPolicy GetLoadingPolicy(void) const noexcept;

			ktkLoadingRequest& SetCachingPolicy(
				eResourceCachingPolicy policy) noexcept;
			eResourceCachingPolicy GetCachingPolicy(void) const noexcept;

			ktkLoadingRequest& SetResourceType(
				eResourceLoadingType type) noexcept;
			eResourceLoadingType GetResourceType() const noexcept;

			ktkLoadingRequest& SetResourcePath(
				const ktk::string& path) noexcept;
			const ktk::string& GetResourcePath(void) const noexcept;

		private:
			eResourceLoadingPolicy m_policy_loading;
			eResourceCachingPolicy m_policy_caching;
			eResourceLoadingType m_resource_type;
			ktk::string m_resource_path;
		};

		class ktkIResourceManager
		{
		public:
			virtual ~ktkIResourceManager(void) {}

			template <typename ResourceType>
			ktk::shared_ptr<ResourceType> Load(
				const ktkLoadingRequest& request) noexcept
			{
				return any_cast<ktk::shared_ptr<ResourceType>>(
					this->LoadResource(request));
			}

		protected:
			virtual ktk::any LoadResource(const ktkLoadingRequest& request) = 0;
		};
	} // namespace Core
} // namespace Kotek
