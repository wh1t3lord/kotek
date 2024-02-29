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

void test_container_filesystem_static_path_has_extension()
{
	ktk_filesystem_path test("/");
	ktk_filesystem_path test2("\\");
	ktk_filesystem_path test3("/ab/test.txt");
	ktk_filesystem_path test4("/ab/.");
	ktk_filesystem_path test5("/ab/..");
	ktk_filesystem_path test6("/ab/.1");
	ktk_filesystem_path test7("/ab/..1");
	ktk_filesystem_path test8("/ab/1.1");
	ktk_filesystem_path test9("/ab/1.");
	ktk_filesystem_path test10("/ab/...");
	ktk_filesystem_path test11("/ab/.1.");
	ktk_filesystem_path test12("/ab\\..1");
	ktk_filesystem_path test13("/ab/1.1");
	ktk_filesystem_path test14("\\ab/1.");
	ktk_filesystem_path test15("\\ab\\...");
	ktk_filesystem_path test16("/ab\\.1.");

	std::filesystem::path std_test("/");
	std::filesystem::path std_test2("\\");
	std::filesystem::path std_test3("/ab/test.txt");
	std::filesystem::path std_test4("/ab/.");
	std::filesystem::path std_test5("/ab/..");
	std::filesystem::path std_test6("/ab/.1");
	std::filesystem::path std_test7("/ab/..1");
	std::filesystem::path std_test8("/ab/1.1");
	std::filesystem::path std_test9("/ab/1.");
	std::filesystem::path std_test10("/ab/...");
	std::filesystem::path std_test11("/ab/.1.");
	std::filesystem::path std_test12("/ab\\..1");
	std::filesystem::path std_test13("/ab/1.1");
	std::filesystem::path std_test14("\\ab/1.");
	std::filesystem::path std_test15("\\ab\\...");
	std::filesystem::path std_test16("/ab\\.1.");

	BOOST_REQUIRE(test.has_extension() == std_test.has_extension());
	BOOST_REQUIRE(test2.has_extension() == std_test2.has_extension());
	BOOST_REQUIRE(test3.has_extension() == std_test3.has_extension());
	BOOST_REQUIRE(test4.has_extension() == std_test4.has_extension());
	BOOST_REQUIRE(test5.has_extension() == std_test5.has_extension());
	BOOST_REQUIRE(test6.has_extension() == std_test6.has_extension());
	BOOST_REQUIRE(test7.has_extension() == std_test7.has_extension());
	BOOST_REQUIRE(test8.has_extension() == std_test8.has_extension());
	BOOST_REQUIRE(test9.has_extension() == std_test9.has_extension());
	BOOST_REQUIRE(test10.has_extension() == std_test10.has_extension());
	BOOST_REQUIRE(test11.has_extension() == std_test11.has_extension());
	BOOST_REQUIRE(test12.has_filename() == std_test12.has_filename());
	BOOST_REQUIRE(test13.has_filename() == std_test13.has_filename());
	BOOST_REQUIRE(test14.has_filename() == std_test14.has_filename());
	BOOST_REQUIRE(test15.has_filename() == std_test15.has_filename());
	BOOST_REQUIRE(test16.has_filename() == std_test16.has_filename());
}

void test_container_filesystem_static_path_has_filename()
{
	ktk_filesystem_path test("/");
	ktk_filesystem_path test2("\\");
	ktk_filesystem_path test3("/ab/test.txt");
	ktk_filesystem_path test4("/ab/.");
	ktk_filesystem_path test5("/ab/..");
	ktk_filesystem_path test6("/ab/.1");
	ktk_filesystem_path test7("/ab/..1");
	ktk_filesystem_path test8("/ab/1.1");
	ktk_filesystem_path test9("/ab/1.");
	ktk_filesystem_path test10("/ab/...");
	ktk_filesystem_path test11("/ab/.1.");
	ktk_filesystem_path test12("/ab\\..1");
	ktk_filesystem_path test13("/ab/1.1");
	ktk_filesystem_path test14("\\ab/1.");
	ktk_filesystem_path test15("\\ab\\...");
	ktk_filesystem_path test16("/ab\\.1.");

	std::filesystem::path std_test("/");
	std::filesystem::path std_test2("\\");
	std::filesystem::path std_test3("/ab/test.txt");
	std::filesystem::path std_test4("/ab/.");
	std::filesystem::path std_test5("/ab/..");
	std::filesystem::path std_test6("/ab/.1");
	std::filesystem::path std_test7("/ab/..1");
	std::filesystem::path std_test8("/ab/1.1");
	std::filesystem::path std_test9("/ab/1.");
	std::filesystem::path std_test10("/ab/...");
	std::filesystem::path std_test11("/ab/.1.");
	std::filesystem::path std_test12("/ab\\..1");
	std::filesystem::path std_test13("/ab/1.1");
	std::filesystem::path std_test14("\\ab/1.");
	std::filesystem::path std_test15("\\ab\\...");
	std::filesystem::path std_test16("/ab\\.1.");

	BOOST_REQUIRE(test.has_filename() == std_test.has_filename());
	BOOST_REQUIRE(test2.has_filename() == std_test2.has_filename());
	BOOST_REQUIRE(test3.has_filename() == std_test3.has_filename());
	BOOST_REQUIRE(test4.has_filename() == std_test4.has_filename());
	BOOST_REQUIRE(test5.has_filename() == std_test5.has_filename());
	BOOST_REQUIRE(test6.has_filename() == std_test6.has_filename());
	BOOST_REQUIRE(test7.has_filename() == std_test7.has_filename());
	BOOST_REQUIRE(test8.has_filename() == std_test8.has_filename());
	BOOST_REQUIRE(test9.has_filename() == std_test9.has_filename());
	BOOST_REQUIRE(test10.has_filename() == std_test10.has_filename());
	BOOST_REQUIRE(test11.has_filename() == std_test11.has_filename());
	BOOST_REQUIRE(test12.has_filename() == std_test12.has_filename());
	BOOST_REQUIRE(test13.has_filename() == std_test13.has_filename());
	BOOST_REQUIRE(test14.has_filename() == std_test14.has_filename());
	BOOST_REQUIRE(test15.has_filename() == std_test15.has_filename());
	BOOST_REQUIRE(test16.has_filename() == std_test16.has_filename());
}

void test_container_filesystem_static_path_replace_extension()
{
	ktk_filesystem_path test("/foo/bar.jpg");
	test.replace_extension(".png");

	ktk_filesystem_path test2("/foo/bar.jpg");
	test2.replace_extension("png");

	ktk_filesystem_path test3("/foo/bar.jpg");
	test3.replace_extension(".");

	ktk_filesystem_path test4("/foo/bar.jpg");
	test4.replace_extension("");

	ktk_filesystem_path test5("/foo/bar.");
	test5.replace_extension("png");

	ktk_filesystem_path test6("/foo/bar");
	test6.replace_extension(".png");

	ktk_filesystem_path test7("/foo/bar");
	test7.replace_extension("png");

	ktk_filesystem_path test8("/foo/bar");
	test8.replace_extension(".");

	ktk_filesystem_path test9("/foo/bar");
	test9.replace_extension("");

	ktk_filesystem_path test10("/foo/.");
	test10.replace_extension(".png");

	ktk_filesystem_path test11("/foo/.");
	test11.replace_extension("png");

	ktk_filesystem_path test12("/foo/.");
	test12.replace_extension(".");

	ktk_filesystem_path test13("/foo/.");
	test13.replace_extension("");

	ktk_filesystem_path test14("/foo/");
	test14.replace_extension(".png");

	ktk_filesystem_path test15("/foo/");
	test15.replace_extension("png");

	ktk_filesystem_path test16("/foo/bar.jpg");
	test16.replace_extension();
	
	BOOST_REQUIRE(test.native() == "/foo/bar.png");
	BOOST_REQUIRE(test2.native() == "/foo/bar.png");
	BOOST_REQUIRE(test3.native() == "/foo/bar.");
	BOOST_REQUIRE(test4.native() == "/foo/bar");
	BOOST_REQUIRE(test5.native() == "/foo/bar.png");
	BOOST_REQUIRE(test6.native() == "/foo/bar.png");
	BOOST_REQUIRE(test7.native() == "/foo/bar.png");
	BOOST_REQUIRE(test8.native() == "/foo/bar.");
	BOOST_REQUIRE(test9.native() == "/foo/bar");
	BOOST_REQUIRE(test10.native() == "/foo/..png");
	BOOST_REQUIRE(test11.native() == "/foo/..png");
	BOOST_REQUIRE(test12.native() == "/foo/..");
	BOOST_REQUIRE(test13.native() == "/foo/.");
	BOOST_REQUIRE(test14.native() == "/foo/.png");
	BOOST_REQUIRE(test15.native() == "/foo/.png");
	BOOST_REQUIRE(test16.native() == "/foo/bar");
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
	p_suite->add(
		BOOST_TEST_CASE(&test_container_filesystem_static_path_has_extension));
	p_suite->add(
		BOOST_TEST_CASE(&test_container_filesystem_static_path_has_filename));
	p_suite->add(BOOST_TEST_CASE(
		&test_container_filesystem_static_path_replace_extension));
	boost::unit_test::framework::master_test_suite().add(p_suite);

	KOTEK_MESSAGE("registered!");
#endif
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
