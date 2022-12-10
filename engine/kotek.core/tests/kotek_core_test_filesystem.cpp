#include "../include/kotek_core.h"
#include <boost/test/unit_test.hpp>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#ifdef KOTEK_USE_TESTS
	#ifdef KOTEK_DEBUG
void test_filesystem_check_folder_tests_for_existance()
{
	ktkFileSystem instance;

	instance.Initialize();

	bool status = instance.IsValidPath(
		instance.GetFolderByEnum(eFolderIndex::kFolderIndex_UserTests));

	BOOST_REQUIRE(status);

	instance.Shutdown();
}

void test_file_create_pretty_output()
{
	ktkFileSystem filesystem;

	filesystem.Initialize();

	ktkFileText instance("pretty");

	auto path =
		filesystem.GetFolderByEnum(eFolderIndex::kFolderIndex_UserTests);

	ktk::string test(KOTEK_TEXT("いくつか"));

	instance.Write("test_field1", "data");
	instance.Write("test_field2", "data2");
	instance.Write<const ktk::string&>("ktk::string", test);

		#ifdef KOTEK_USE_UNICODE
	instance.Write<const ktk::string&>("KOTEK_TEXT", KOTEK_TEXT("いくつか"));
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

void RegisterTests_Filesystem_ForModule_Core(void)
{
#ifdef KOTEK_USE_TESTS

	boost::unit_test::test_suite* p_suite =
		BOOST_TEST_SUITE("Core::FileSystem");
	
	p_suite->add(
		BOOST_TEST_CASE(&test_filesystem_check_folder_tests_for_existance));
	p_suite->add(BOOST_TEST_CASE(&test_file_create_pretty_output));

	boost::unit_test::framework::master_test_suite().add(p_suite);



	KOTEK_MESSAGE("registered!");
#endif
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
