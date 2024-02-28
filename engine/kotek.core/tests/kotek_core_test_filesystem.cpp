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
		instance.GetFolderByEnum(eFolderIndex::kFolderIndex_UserData_Tests));

	BOOST_REQUIRE(status);

	instance.Shutdown();
}

void test_file_create_pretty_output()
{
	ktkMainManager main_manager;
	ktkFileSystem filesystem;

	filesystem.Initialize();

	main_manager.Set_FileSystem(&filesystem);

	ktkFileText instance("pretty");

	auto path =
		filesystem.GetFolderByEnum(eFolderIndex::kFolderIndex_UserData_Tests);

	path /= instance.Get_FileName().c_str();

		#ifdef KOTEK_USE_UNICODE
	ktk::ustring test(KOTEK_TEXTU("いくつか"));
		#else
	ktk::ustring test("いくつか");
		#endif

	instance.Write("test_field1", "data");
	instance.Write("test_field2", "data2");
	instance.Write<ktk::ustring>("ktk::ustring", test);

		#ifdef KOTEK_USE_UNICODE
	instance.Write<ktk::ustring>("KOTEK_TEXT", KOTEK_TEXTU("いくつか"));
	instance.Write<ktk::wstring>("wchar_t", L"いくつか");
	instance.Write<ktk::u8string>("char8_t", u8"いくつか");
	instance.Write<ktk::u16string>("char16_t", u"いくつか");
	instance.Write<ktk::u32string>("char32_t", U"いくつか");
		#endif

	ktkResourceSaverManager saver_instance;
	saver_instance.Initialize(&filesystem, &main_manager);

	bool status = saver_instance.Save(path, &instance);

	BOOST_REQUIRE(status);

	filesystem.Shutdown();
	saver_instance.Shutdown();
	main_manager.Shutdown();
}

void test_container_filesystem_static_path_constructor()
{
	ktk_filesystem_path test1;
}

void test_container_filesystem_static_path_make_preferred()
{
	ktk_filesystem_path test1("a/b/c");
		#ifdef KOTEK_USE_PLATFORM_WINDOWS
	BOOST_REQUIRE(test1.make_preferred().native() == "a\\b\\c");
		#elif defined(KOTEK_USE_PLATFORM_LINUX)
			#error implement
		#elif defined(KOTEK_USE_PLATFORM_MACOS)
			#error implement
		#endif
}

void test_container_filesystem_static_path_remove_filename()
{
	ktk_filesystem_path test("/");
	ktk_filesystem_path test1("\\");
	ktk_filesystem_path test2;
	ktk_filesystem_path test3("");
	ktk_filesystem_path test4("foo/bar");
	ktk_filesystem_path test5("foo/");
	ktk_filesystem_path test6("/foo");

	BOOST_REQUIRE(test.remove_filename().native() == "/");
	BOOST_REQUIRE(test1.remove_filename().native() == "\\");
	BOOST_REQUIRE(test2.remove_filename().native() == "");
	BOOST_REQUIRE(test3.remove_filename().native() == "");
	BOOST_REQUIRE(test4.remove_filename().native() == "foo/");
	BOOST_REQUIRE(test5.remove_filename().native() == "foo/");
	BOOST_REQUIRE(test6.remove_filename().native() == "/");
}

void test_container_filesystem_static_path_remove_filename2()
{
	ktk_filesystem_path test("/");
	ktk_filesystem_path test1("\\");
	ktk_filesystem_path test2;
	ktk_filesystem_path test3("");

	BOOST_REQUIRE(test.remove_filename().native() == "/");
	BOOST_REQUIRE(test1.remove_filename().native() == "\\");
	BOOST_REQUIRE(test2.remove_filename().native() == "");
	BOOST_REQUIRE(test3.remove_filename().native() == "");
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
	p_suite->add(
		BOOST_TEST_CASE(&test_container_filesystem_static_path_constructor));
	p_suite->add(BOOST_TEST_CASE(
		&test_container_filesystem_static_path_remove_filename));
	p_suite->add(
		BOOST_TEST_CASE(&test_container_filesystem_static_path_make_preferred));
	p_suite->add(BOOST_TEST_CASE(
		&test_container_filesystem_static_path_remove_filename2));
	boost::unit_test::framework::master_test_suite().add(p_suite);

	KOTEK_MESSAGE("registered!");
#endif
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
