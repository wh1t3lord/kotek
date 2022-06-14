#ifdef KOTEK_DEBUG
	#include "../include/kotek_render_device.h"
	#include <boost/test/unit_test.hpp>

namespace Kotek
{
	namespace Render
	{
		void registerTests_Device_ForModule_Render_VK(void)
		{
			KOTEK_MESSAGE("registered!");
		}

		/* TODO: перенести тесты в отдельное приложение, остальное тестировать
		   динамически BOOST_AUTO_TEST_CASE(ctor_dtor_render_device)
		        {
		            vk::kotek_render_device instance;
		        }

		        BOOST_AUTO_TEST_CASE(initialize_shutdown_device)
		        {
		            Core::ktkMainManager main_manager(0, nullptr);

		            vk::kotek_render_device instance;
		            instance.initialize(main_manager);
		            instance.shutdown();
		        }

		        BOOST_AUTO_TEST_CASE(
		            getting_allocator_which_is_initialize_in_initialize_function_device)
		        {
		            Core::ktkMainManager main_manager(0, nullptr);
		            vk::kotek_render_device instance;

		            instance.initialize(main_manager);

		            BOOST_CHECK(instance.getAllocator() != nullptr);

		            instance.shutdown();
		        }

		        BOOST_AUTO_TEST_CASE(
		            getting_current_physical_device_which_is_always_initialized_device)
		        {
		            Core::ktkMainManager main_manager(0, nullptr);

		            vk::kotek_render_device instance;
		            instance.initialize(main_manager);

		            BOOST_CHECK(instance.getCurrentPhysicalDevice() != nullptr);

		            instance.shutdown();
		        }

		        BOOST_AUTO_TEST_CASE(
		            getting_instance_which_is_always_initialized_device)
		        {
		            Core::ktkMainManager main_manager(0, nullptr);

		            vk::kotek_render_device instance;
		            instance.initialize(main_manager);

		            BOOST_CHECK(instance.getInstance() != nullptr);

		            instance.shutdown();
		        }

		        BOOST_AUTO_TEST_CASE(
		            getting_logical_device_which_is_always_initialized_device)
		        {
		            Core::ktkMainManager main_manager(0, nullptr);

		            vk::kotek_render_device instance;
		            instance.initialize(main_manager);

		            BOOST_CHECK(instance.getDevice() != nullptr);

		            instance.shutdown();
		        }

		        BOOST_AUTO_TEST_CASE(getting_surface_which_is_always_initialized_device)
		        {
		            Core::ktkMainManager main_manager(0, nullptr);

		            vk::kotek_render_device instance;
		            instance.initialize(main_manager);

		            BOOST_CHECK(instance.getSurface() != nullptr);

		            instance.shutdown();
		        }*/

	} // namespace Render
} // namespace Kotek
#endif