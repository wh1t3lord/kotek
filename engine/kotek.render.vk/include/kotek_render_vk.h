#pragma once

#include <kotek.core/include/kotek_std.h>

namespace Kotek
{
	namespace Render
	{
		bool InitializeModule_Render_VK(Core::ktkMainManager& main_manager);
		bool ShutdownModule_Render_VK(Core::ktkMainManager& main_manager);

#ifdef KOTEK_DEBUG

		/// <summary>
		/// Проблема заключается в том, что если пытаться выделять в отдельные
		/// файлы (тесты) в каждом проекте, то система (boost библиотека) не
		/// сможет нормально зарегистрировать тесты, поэтому мы должен создать
		/// контекст использование файла А для этого необходимо сделать хотя бы
		/// один вызов функции который располагается в соответствующем файле для
		/// тестов Таким образом, чтобы добавить тесты для того чтобы они
		/// исполнялись нужно:
		///		- Создать сам файл
		///		- Добавить тесты через BOOST_AUTO_TEST_CASE
		///		- Теперь чтобы их как бы зарегистрировать нужно сделать вызов
		///какой-то функции из этого файла в файл где инициализируется модуль
		///		- Таким образом мы получаем следующий стандарт определения и
		///регистрации тестов через функции которые определены там, где же и
		///определены инициализация и завершение модуля
		///		- Добавить вызов функции в registerAllTests, внимание данная
		///функция всегда определена и объявлена в main_название_модуля_dll.cpp,
		///таким образом она всегда приватная и не нужно беспокоиться о какой-то
		///коллизии, к примеру такая же функция есть во всех main_***_dll.cpp
		/// </summary>

		void registerTests_ShaderManager_ForModule_Render_VK();
		void registerTests_Device_ForModule_Render_VK();
		void registerTests_CommandListRing_ForModule_Render_VK();
		void registerTests_Swapchain_ForModule_Render_VK();
		void registerTests_ShaderCacheManager_ForModule_Render_VK();
#endif
	} // namespace Render
} // namespace Kotek
