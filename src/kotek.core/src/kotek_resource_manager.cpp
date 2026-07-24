#include "../include/kotek_resource_manager.h"

namespace Kotek
{
	namespace Core
	{
		ktkLoadingRequest& ktkLoadingRequest::SetLoadingPolicy(
			eResourceLoadingPolicy policy) noexcept
		{
			this->m_policy_loading = policy;
			return *this;
		}

		eResourceLoadingPolicy ktkLoadingRequest::GetLoadingPolicy(
			void) const noexcept
		{
			return this->m_policy_loading;
		}

		ktkLoadingRequest& ktkLoadingRequest::SetCachingPolicy(
			eResourceCachingPolicy policy) noexcept
		{
			this->m_policy_caching = policy;
			return *this;
		}

		eResourceCachingPolicy ktkLoadingRequest::GetCachingPolicy(
			void) const noexcept
		{
			return this->m_policy_caching;
		}

		ktkLoadingRequest& ktkLoadingRequest::SetResourceType(
			eResourceLoadingType type) noexcept
		{
			this->m_resource_type = type;
			return *this;
		}

		eResourceLoadingType ktkLoadingRequest::GetResourceType() const noexcept
		{
			return this->m_resource_type;
		}

		ktkLoadingRequest& ktkLoadingRequest::SetResourcePath(
			const ktk::string& path) noexcept
		{
			KOTEK_ASSERT(
				path.empty() == false, "you can't set an empty path here");

			this->m_resource_path = path;

			return *this;
		}

		const ktk::string& ktkLoadingRequest::GetResourcePath(
			void) const noexcept
		{
			return this->m_resource_path;
		}
	}
} // namespace Kotek