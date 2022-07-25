#include "../include/kotek_core.h"
#include <boost/test/unit_test.hpp>

namespace Kotek
{
	namespace Core
	{
		void RegisterTests_Filesystem_ForModule_Core(void)
		{
#ifdef KOTEK_USE_TESTS
			KOTEK_MESSAGE("registered!");
#endif
		}

#ifdef KOTEK_USE_TESTS
	#ifdef KOTEK_DEBUG
		BOOST_AUTO_TEST_CASE(filesystem_check_folder_tests_for_existance)
		{
			ktkFileSystem instance;

			instance.Initialize();

			bool status = instance.IsValidPath(
				instance.GetFolderByEnum(eFolderIndex::kFolderIndex_UserTests));

			BOOST_REQUIRE(status);

			instance.Shutdown();
		}

		BOOST_AUTO_TEST_CASE(file_create_pretty_output)
		{
			ktkFileSystem filesystem;

			filesystem.Initialize();

			ktkFile instance("pretty");

			auto path = filesystem.GetFolderByEnum(
				eFolderIndex::kFolderIndex_UserTests);

			ktk::string test(KOTEK_TEXT("いくつか"));

			instance.Write("test_field1", "data");
			instance.Write("test_field2", "data2");
			instance.Write<const ktk::string&>("ktk::string", test);

		#ifdef KOTEK_USE_UNICODE
			instance.Write<const ktk::string&>(
				"KOTEK_TEXT", KOTEK_TEXT("いくつか"));
			instance.Write("wchar_t", L"いくつか");
			instance.Write("char8_t", u8"いくつか");
			instance.Write("char16_t", u"いくつか");
			instance.Write("char32_t", U"いくつか");
		#endif

			ktkResourceSaverManager saver_instance;
			saver_instance.Initialize(&filesystem);

			bool status = saver_instance.Save_Text_Formatted(path, &instance);

			BOOST_REQUIRE(status);

			filesystem.Shutdown();
		}
	#endif
#endif
	} // namespace Core
} // namespace Kotek
