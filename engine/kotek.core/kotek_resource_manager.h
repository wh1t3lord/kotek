#pragma once

#include "kotek_std.h"

namespace Kotek
{
	namespace Core
	{
		class ktkLoadingRequest;
	}
}

namespace Kotek
{
	namespace Core
	{
		class ktkIResourceManager
		{
		public:
			virtual ~ktkIResourceManager(void) {}

			template<typename ResourceType>
			ktk::shared_ptr<ResourceType> Load(
				const ktkLoadingRequest& request) noexcept
			{
				return any_cast<ktk::shared_ptr<ResourceType>>(this->LoadResource(request));
			}

		protected:
			virtual ktk::any LoadResource(
				const ktkLoadingRequest& request) = 0;
		};
	}
} // namespace Kotek
