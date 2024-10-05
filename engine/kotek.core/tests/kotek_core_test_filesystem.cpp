#include "../include/kotek_core.h"
#include <catch2/catch_test_macros.hpp>

#ifdef KOTEK_USE_TESTS
	#ifdef KOTEK_DEBUG
		#include <filesystem>
		#include <vector>
	#endif
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#ifdef KOTEK_USE_TESTS
	#ifdef KOTEK_DEBUG
TEST_CASE("test_filesystem_check_folder_tests_for_existance()")
{
	ktkFileSystem instance;

	instance.Initialize();

	bool status = instance.IsValidPath(
		instance.GetFolderByEnum(eFolderIndex::kFolderIndex_UserData_Tests));

	REQUIRE(status);

	instance.Shutdown();
}

TEST_CASE(" test_file_create_pretty_output()")
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

	REQUIRE(status);

	filesystem.Shutdown();
	saver_instance.Shutdown();
	main_manager.Shutdown();
}

TEST_CASE(" test_container_filesystem_static_path_constructor()")
{
	ktk_filesystem_path test1;
}

TEST_CASE(" test_container_filesystem_static_path_make_preferred()")
{
	ktk_filesystem_path test1("a/b/c");
		#ifdef KOTEK_USE_PLATFORM_WINDOWS
	REQUIRE(test1.make_preferred().native() == "a\\b\\c");
		#elif defined(KOTEK_USE_PLATFORM_LINUX)
			#error implement
		#elif defined(KOTEK_USE_PLATFORM_MACOS)
			#error implement
		#endif
}

TEST_CASE(" test_container_filesystem_static_path_remove_filename()")
{
	ktk_filesystem_path test("/");
	ktk_filesystem_path test1("\\");
	ktk_filesystem_path test2;
	ktk_filesystem_path test3("");
	ktk_filesystem_path test4("foo/bar");
	ktk_filesystem_path test5("foo/");
	ktk_filesystem_path test6("/foo");

	REQUIRE(test.remove_filename().native() == "/");
	REQUIRE(test1.remove_filename().native() == "\\");
	REQUIRE(test2.remove_filename().native() == "");
	REQUIRE(test3.remove_filename().native() == "");
	REQUIRE(test4.remove_filename().native() == "foo/");
	REQUIRE(test5.remove_filename().native() == "foo/");
	REQUIRE(test6.remove_filename().native() == "/");
}

TEST_CASE(" test_container_filesystem_static_path_remove_filename2()")
{
	ktk_filesystem_path test("/");
	ktk_filesystem_path test1("\\");
	ktk_filesystem_path test2;
	ktk_filesystem_path test3("");

	REQUIRE(test.remove_filename().native() == "/");
	REQUIRE(test1.remove_filename().native() == "\\");
	REQUIRE(test2.remove_filename().native() == "");
	REQUIRE(test3.remove_filename().native() == "");
}

TEST_CASE(" test_container_filesystem_static_path_has_extension()")
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

	REQUIRE(test.has_extension() == std_test.has_extension());
	REQUIRE(test2.has_extension() == std_test2.has_extension());
	REQUIRE(test3.has_extension() == std_test3.has_extension());
	REQUIRE(test4.has_extension() == std_test4.has_extension());
	REQUIRE(test5.has_extension() == std_test5.has_extension());
	REQUIRE(test6.has_extension() == std_test6.has_extension());
	REQUIRE(test7.has_extension() == std_test7.has_extension());
	REQUIRE(test8.has_extension() == std_test8.has_extension());
	REQUIRE(test9.has_extension() == std_test9.has_extension());
	REQUIRE(test10.has_extension() == std_test10.has_extension());
	REQUIRE(test11.has_extension() == std_test11.has_extension());
}

TEST_CASE(" test_container_filesystem_static_path_has_filename()")
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

	REQUIRE(test.has_filename() == std_test.has_filename());
	REQUIRE(test2.has_filename() == std_test2.has_filename());
	REQUIRE(test3.has_filename() == std_test3.has_filename());
	REQUIRE(test4.has_filename() == std_test4.has_filename());
	REQUIRE(test5.has_filename() == std_test5.has_filename());
	REQUIRE(test6.has_filename() == std_test6.has_filename());
	REQUIRE(test7.has_filename() == std_test7.has_filename());
	REQUIRE(test8.has_filename() == std_test8.has_filename());
	REQUIRE(test9.has_filename() == std_test9.has_filename());
	REQUIRE(test10.has_filename() == std_test10.has_filename());
	REQUIRE(test11.has_filename() == std_test11.has_filename());
	REQUIRE(test12.has_filename() == std_test12.has_filename());
	REQUIRE(test13.has_filename() == std_test13.has_filename());
	REQUIRE(test14.has_filename() == std_test14.has_filename());
	REQUIRE(test15.has_filename() == std_test15.has_filename());
	REQUIRE(test16.has_filename() == std_test16.has_filename());
}

TEST_CASE(" test_container_filesystem_static_path_replace_extension()")
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

	REQUIRE(test.native() == "/foo/bar.png");
	REQUIRE(test2.native() == "/foo/bar.png");
	REQUIRE(test3.native() == "/foo/bar.");
	REQUIRE(test4.native() == "/foo/bar");
	REQUIRE(test5.native() == "/foo/bar.png");
	REQUIRE(test6.native() == "/foo/bar.png");
	REQUIRE(test7.native() == "/foo/bar.png");
	REQUIRE(test8.native() == "/foo/bar.");
	REQUIRE(test9.native() == "/foo/bar");
	REQUIRE(test10.native() == "/foo/..png");
	REQUIRE(test11.native() == "/foo/..png");
	REQUIRE(test12.native() == "/foo/..");
	REQUIRE(test13.native() == "/foo/.");
	REQUIRE(test14.native() == "/foo/.png");
	REQUIRE(test15.native() == "/foo/.png");
	REQUIRE(test16.native() == "/foo/bar");
}

TEST_CASE(" test_container_filesystem_static_path_swap()")
{
	ktk_filesystem_path test("C:/test");
	ktk_filesystem_path b("D:/kek");

	test.swap(b);

	REQUIRE(test.native() == "D:/kek");
	REQUIRE(b.native() == "C:/test");

	ktk_filesystem_path test2("D:\\Godot\\4.2.1\\GodotSharp\\Tools\\nupkgs");
	ktk_filesystem_path b2("C:\\Program Files (x86)\\Microsoft SQL "
						   "Server\\150\\LocalDB\\Binn\\Resources\\es-ES");

	test2.swap(b2);

	REQUIRE(test2.native() ==
		"C:\\Program Files (x86)\\Microsoft SQL "
		"Server\\150\\LocalDB\\Binn\\Resources\\es-ES");
	REQUIRE(b2.native() == "D:\\Godot\\4.2.1\\GodotSharp\\Tools\\nupkgs");

	ktk_filesystem_path test3("D:\\Godot\\4.2.1\\GodotSharp\\Tools\\nupkgs");
	ktk_filesystem_path b3("");

	test3.swap(b3);
	REQUIRE(test3.native() == "");
	REQUIRE(b3.native() == "D:\\Godot\\4.2.1\\GodotSharp\\Tools\\nupkgs");
}

TEST_CASE(" test_container_filesystem_static_path_compare()")
{
	ktk_filesystem_path a("/a/b/");
	ktk_filesystem_path b("/a/b/");

	ktk_filesystem_path a2("/a/b/");
	ktk_filesystem_path b2("/a/b/c");

	ktk_filesystem_path a3("/a/b/../b");
	ktk_filesystem_path b3("/a/b");

	ktk_filesystem_path a4("/a/b");
	ktk_filesystem_path b4("/a/b/.");

	ktk_filesystem_path a5("/a/b/");
	ktk_filesystem_path b5("a/c");

	REQUIRE(a.compare(b) == 0);
	REQUIRE(a2.compare(b2) < 0);
	REQUIRE(a3.compare(b3) > 0);
	REQUIRE(a4.compare(b4) < 0);
	REQUIRE(a5.compare(b5) > 0);

	a.compare("");
}

TEST_CASE(" test_container_filesystem_static_path_has_root_directory()")
{
	std::filesystem::path t("a/b");
	std::filesystem::path t1("C:/a/b");
	std::filesystem::path t2("C:\\a/b");
	std::filesystem::path t3("D:/a/b");
	std::filesystem::path t4("b");
	std::filesystem::path t5("/");
	std::filesystem::path t6("\\");
	std::filesystem::path t7("\\A\\B");
	std::filesystem::path t8("/A/b");
	std::filesystem::path t9("c\\d\\");
	std::filesystem::path t10(":/c\\d");

	ktk_filesystem_path _t("a/b");
	ktk_filesystem_path _t1("C:/a/b");
	ktk_filesystem_path _t2("C:\\a/b");
	ktk_filesystem_path _t3("D:/a/b");
	ktk_filesystem_path _t4("b");
	ktk_filesystem_path _t5("/");
	ktk_filesystem_path _t6("\\");
	ktk_filesystem_path _t7("\\A\\B");
	ktk_filesystem_path _t8("/A/b");
	ktk_filesystem_path _t9("c\\d\\");
	ktk_filesystem_path _t10(":/c\\d");

	REQUIRE(t.has_root_directory() == _t.has_root_directory());
	REQUIRE(t1.has_root_directory() == _t1.has_root_directory());
	REQUIRE(t2.has_root_directory() == _t2.has_root_directory());
	REQUIRE(t3.has_root_directory() == _t3.has_root_directory());
	REQUIRE(t4.has_root_directory() == _t4.has_root_directory());
	REQUIRE(t5.has_root_directory() == _t5.has_root_directory());
	REQUIRE(t6.has_root_directory() == _t6.has_root_directory());
	REQUIRE(t7.has_root_directory() == _t7.has_root_directory());
	REQUIRE(t8.has_root_directory() == _t8.has_root_directory());
	REQUIRE(t9.has_root_directory() == _t9.has_root_directory());
	REQUIRE(t10.has_root_directory() == _t10.has_root_directory());
}

TEST_CASE(" test_container_filesystem_static_path_is_absolute()")
{
	std::filesystem::path t("a/b");
	std::filesystem::path t1("C:/a/b");
	std::filesystem::path t2("C:\\a/b");
	std::filesystem::path t3("D:/a/b");
	std::filesystem::path t4("b");
	std::filesystem::path t5("/");
	std::filesystem::path t6("\\");
	std::filesystem::path t7("\\A\\B");
	std::filesystem::path t8("/A/b");
	std::filesystem::path t9("c\\d\\");
	std::filesystem::path t10("D:c\\d");
	std::filesystem::path t11("D:");
	std::filesystem::path t12("D:\\");

	ktk_filesystem_path _t("a/b");
	ktk_filesystem_path _t1("C:/a/b");
	ktk_filesystem_path _t2("C:\\a/b");
	ktk_filesystem_path _t3("D:/a/b");
	ktk_filesystem_path _t4("b");
	ktk_filesystem_path _t5("/");
	ktk_filesystem_path _t6("\\");
	ktk_filesystem_path _t7("\\A\\B");
	ktk_filesystem_path _t8("/A/b");
	ktk_filesystem_path _t9("c\\d\\");
	ktk_filesystem_path _t10("D:c\\d");
	ktk_filesystem_path _t11("D:");
	ktk_filesystem_path _t12("D:\\");

	REQUIRE(t.is_absolute() == _t.is_absolute());
	REQUIRE(t1.is_absolute() == _t1.is_absolute());
	REQUIRE(t2.is_absolute() == _t2.is_absolute());
	REQUIRE(t3.is_absolute() == _t3.is_absolute());
	REQUIRE(t4.is_absolute() == _t4.is_absolute());
	REQUIRE(t5.is_absolute() == _t5.is_absolute());
	REQUIRE(t6.is_absolute() == _t6.is_absolute());
	REQUIRE(t7.is_absolute() == _t7.is_absolute());
	REQUIRE(t8.is_absolute() == _t8.is_absolute());
	REQUIRE(t9.is_absolute() == _t9.is_absolute());
	REQUIRE(t10.is_absolute() == _t10.is_absolute());
}

TEST_CASE(" test_container_filesystem_static_path_is_relative()")
{
	std::filesystem::path t("a/b");
	std::filesystem::path t1("C:/a/b");
	std::filesystem::path t2("C:\\a/b");
	std::filesystem::path t3("D:/a/b");
	std::filesystem::path t4("b");
	std::filesystem::path t5("/");
	std::filesystem::path t6("\\");
	std::filesystem::path t7("\\A\\B");
	std::filesystem::path t8("/A/b");
	std::filesystem::path t9("c\\d\\");
	std::filesystem::path t10("D:c\\d");
	std::filesystem::path t11("D:");
	std::filesystem::path t12("D:\\");

	ktk_filesystem_path _t("a/b");
	ktk_filesystem_path _t1("C:/a/b");
	ktk_filesystem_path _t2("C:\\a/b");
	ktk_filesystem_path _t3("D:/a/b");
	ktk_filesystem_path _t4("b");
	ktk_filesystem_path _t5("/");
	ktk_filesystem_path _t6("\\");
	ktk_filesystem_path _t7("\\A\\B");
	ktk_filesystem_path _t8("/A/b");
	ktk_filesystem_path _t9("c\\d\\");
	ktk_filesystem_path _t10("D:c\\d");
	ktk_filesystem_path _t11("D:");
	ktk_filesystem_path _t12("D:\\");

	REQUIRE(t.is_relative() == _t.is_relative());
	REQUIRE(t1.is_relative() == _t1.is_relative());
	REQUIRE(t2.is_relative() == _t2.is_relative());
	REQUIRE(t3.is_relative() == _t3.is_relative());
	REQUIRE(t4.is_relative() == _t4.is_relative());
	REQUIRE(t5.is_relative() == _t5.is_relative());
	REQUIRE(t6.is_relative() == _t6.is_relative());
	REQUIRE(t7.is_relative() == _t7.is_relative());
	REQUIRE(t8.is_relative() == _t8.is_relative());
	REQUIRE(t9.is_relative() == _t9.is_relative());
	REQUIRE(t10.is_relative() == _t10.is_relative());
}

TEST_CASE(" test_container_filesystem_static_path_relative_path()")
{
	std::filesystem::path t("a/b");
	std::filesystem::path t1("C:/a/b");
	std::filesystem::path t2("C:\\a/b");
	std::filesystem::path t3("D:/a/b");
	std::filesystem::path t4("b");
	std::filesystem::path t5("/");
	std::filesystem::path t6("\\");
	std::filesystem::path t7("\\A\\B");
	std::filesystem::path t8("/A/b");
	std::filesystem::path t9("c\\d\\");
	std::filesystem::path t10("D:c\\d");
	std::filesystem::path t11("D:");
	std::filesystem::path t12("D:\\");
	std::filesystem::path t13("D\\:");
	std::filesystem::path t14("D\\");
	std::filesystem::path t15(":a");
	std::filesystem::path t16(":/a");
	std::filesystem::path t17(":c/a");

	ktk_filesystem_path _t("a/b");
	ktk_filesystem_path _t1("C:/a/b");
	ktk_filesystem_path _t2("C:\\a/b");
	ktk_filesystem_path _t3("D:/a/b");
	ktk_filesystem_path _t4("b");
	ktk_filesystem_path _t5("/");
	ktk_filesystem_path _t6("\\");
	ktk_filesystem_path _t7("\\A\\B");
	ktk_filesystem_path _t8("/A/b");
	ktk_filesystem_path _t9("c\\d\\");
	ktk_filesystem_path _t10("D:c\\d");
	ktk_filesystem_path _t11("D:");
	ktk_filesystem_path _t12("D:\\");
	ktk_filesystem_path _t13("D\\:");
	ktk_filesystem_path _t14("D\\");
	ktk_filesystem_path _t15(":a");
	ktk_filesystem_path _t16(":/a");
	ktk_filesystem_path _t17(":c/a");

	REQUIRE(
		t.relative_path().string().c_str() == _t.relative_path().native());
	REQUIRE(
		t1.relative_path().string().c_str() == _t1.relative_path().native());
	REQUIRE(
		t2.relative_path().string().c_str() == _t2.relative_path().native());
	REQUIRE(
		t3.relative_path().string().c_str() == _t3.relative_path().native());
	REQUIRE(
		t4.relative_path().string().c_str() == _t4.relative_path().native());
	REQUIRE(
		t5.relative_path().string().c_str() == _t5.relative_path().native());
	REQUIRE(
		t6.relative_path().string().c_str() == _t6.relative_path().native());
	REQUIRE(
		t7.relative_path().string().c_str() == _t7.relative_path().native());
	REQUIRE(
		t8.relative_path().string().c_str() == _t8.relative_path().native());
	REQUIRE(
		t9.relative_path().string().c_str() == _t9.relative_path().native());
	REQUIRE(
		t10.relative_path().string().c_str() == _t10.relative_path().native());
	REQUIRE(
		t11.relative_path().string().c_str() == _t11.relative_path().native());
	REQUIRE(
		t12.relative_path().string().c_str() == _t12.relative_path().native());
	REQUIRE(
		t13.relative_path().string().c_str() == _t13.relative_path().native());
	REQUIRE(
		t14.relative_path().string().c_str() == _t14.relative_path().native());
	REQUIRE(
		t15.relative_path().string().c_str() == _t15.relative_path().native());
	REQUIRE(
		t16.relative_path().string().c_str() == _t16.relative_path().native());
	REQUIRE(
		t17.relative_path().string().c_str() == _t17.relative_path().native());
}

TEST_CASE(" test_container_filesystem_static_path_parent_path()")
{
	std::filesystem::path t("a/b");
	std::filesystem::path t1("C:/a/b");
	std::filesystem::path t2("C:\\a/b");
	std::filesystem::path t3("D:/a/b");
	std::filesystem::path t4("b");
	std::filesystem::path t5("/");
	std::filesystem::path t6("\\");
	std::filesystem::path t7("\\A\\B");
	std::filesystem::path t8("/A/b");
	std::filesystem::path t9("c\\d\\");
	std::filesystem::path t10("D:c\\d");
	std::filesystem::path t11("D:");
	std::filesystem::path t12("D:\\");
	std::filesystem::path t13("D\\:");
	std::filesystem::path t14("D\\");
	std::filesystem::path t15(":a");
	std::filesystem::path t16(":/a");
	std::filesystem::path t17(":c/a");

	ktk_filesystem_path _t("a/b");
	ktk_filesystem_path _t1("C:/a/b");
	ktk_filesystem_path _t2("C:\\a/b");
	ktk_filesystem_path _t3("D:/a/b");
	ktk_filesystem_path _t4("b");
	ktk_filesystem_path _t5("/");
	ktk_filesystem_path _t6("\\");
	ktk_filesystem_path _t7("\\A\\B");
	ktk_filesystem_path _t8("/A/b");
	ktk_filesystem_path _t9("c\\d\\");
	ktk_filesystem_path _t10("D:c\\d");
	ktk_filesystem_path _t11("D:");
	ktk_filesystem_path _t12("D:\\");
	ktk_filesystem_path _t13("D\\:");
	ktk_filesystem_path _t14("D\\");
	ktk_filesystem_path _t15(":a");
	ktk_filesystem_path _t16(":/a");
	ktk_filesystem_path _t17(":c/a");

	REQUIRE(
		t.parent_path().string().c_str() == _t.parent_path().native());
	REQUIRE(
		t1.parent_path().string().c_str() == _t1.parent_path().native());
	REQUIRE(
		t2.parent_path().string().c_str() == _t2.parent_path().native());
	REQUIRE(
		t3.parent_path().string().c_str() == _t3.parent_path().native());
	REQUIRE(
		t4.parent_path().string().c_str() == _t4.parent_path().native());
	REQUIRE(
		t5.parent_path().string().c_str() == _t5.parent_path().native());
	REQUIRE(
		t6.parent_path().string().c_str() == _t6.parent_path().native());
	REQUIRE(
		t7.parent_path().string().c_str() == _t7.parent_path().native());
	REQUIRE(
		t8.parent_path().string().c_str() == _t8.parent_path().native());
	REQUIRE(
		t9.parent_path().string().c_str() == _t9.parent_path().native());
	REQUIRE(
		t10.parent_path().string().c_str() == _t10.parent_path().native());
	REQUIRE(
		t11.parent_path().string().c_str() == _t11.parent_path().native());
	REQUIRE(
		t12.parent_path().string().c_str() == _t12.parent_path().native());
	REQUIRE(
		t13.parent_path().string().c_str() == _t13.parent_path().native());
	REQUIRE(
		t14.parent_path().string().c_str() == _t14.parent_path().native());
	REQUIRE(
		t15.parent_path().string().c_str() == _t15.parent_path().native());
	REQUIRE(
		t16.parent_path().string().c_str() == _t16.parent_path().native());
	REQUIRE(
		t17.parent_path().string().c_str() == _t17.parent_path().native());
}

TEST_CASE(" test_container_filesystem_static_path_has_parent_path()")
{
	std::filesystem::path t("a/b");
	std::filesystem::path t1("C:/a/b");
	std::filesystem::path t2("C:\\a/b");
	std::filesystem::path t3("D:/a/b");
	std::filesystem::path t4("b");
	std::filesystem::path t5("/");
	std::filesystem::path t6("\\");
	std::filesystem::path t7("\\A\\B");
	std::filesystem::path t8("/A/b");
	std::filesystem::path t9("c\\d\\");
	std::filesystem::path t10("D:c\\d");
	std::filesystem::path t11("D:");
	std::filesystem::path t12("D:\\");
	std::filesystem::path t13("D\\:");
	std::filesystem::path t14("D\\");
	std::filesystem::path t15(":a");
	std::filesystem::path t16(":/a");
	std::filesystem::path t17(":c/a");

	ktk_filesystem_path _t("a/b");
	ktk_filesystem_path _t1("C:/a/b");
	ktk_filesystem_path _t2("C:\\a/b");
	ktk_filesystem_path _t3("D:/a/b");
	ktk_filesystem_path _t4("b");
	ktk_filesystem_path _t5("/");
	ktk_filesystem_path _t6("\\");
	ktk_filesystem_path _t7("\\A\\B");
	ktk_filesystem_path _t8("/A/b");
	ktk_filesystem_path _t9("c\\d\\");
	ktk_filesystem_path _t10("D:c\\d");
	ktk_filesystem_path _t11("D:");
	ktk_filesystem_path _t12("D:\\");
	ktk_filesystem_path _t13("D\\:");
	ktk_filesystem_path _t14("D\\");
	ktk_filesystem_path _t15(":a");
	ktk_filesystem_path _t16(":/a");
	ktk_filesystem_path _t17(":c/a");

	REQUIRE(t.has_parent_path() == _t.has_parent_path());
	REQUIRE(t1.has_parent_path() == _t1.has_parent_path());
	REQUIRE(t2.has_parent_path() == _t2.has_parent_path());
	REQUIRE(t3.has_parent_path() == _t3.has_parent_path());
	REQUIRE(t4.has_parent_path() == _t4.has_parent_path());
	REQUIRE(t5.has_parent_path() == _t5.has_parent_path());
	REQUIRE(t6.has_parent_path() == _t6.has_parent_path());
	REQUIRE(t7.has_parent_path() == _t7.has_parent_path());
	REQUIRE(t8.has_parent_path() == _t8.has_parent_path());
	REQUIRE(t9.has_parent_path() == _t9.has_parent_path());
	REQUIRE(t10.has_parent_path() == _t10.has_parent_path());
	REQUIRE(t11.has_parent_path() == _t11.has_parent_path());
	REQUIRE(t12.has_parent_path() == _t12.has_parent_path());
	REQUIRE(t13.has_parent_path() == _t13.has_parent_path());
	REQUIRE(t14.has_parent_path() == _t14.has_parent_path());
	REQUIRE(t15.has_parent_path() == _t15.has_parent_path());
	REQUIRE(t16.has_parent_path() == _t16.has_parent_path());
	REQUIRE(t17.has_parent_path() == _t17.has_parent_path());
}

TEST_CASE(" test_container_filesystem_static_path_has_stem()")
{
	std::filesystem::path t("a/b");
	std::filesystem::path t1("C:/a/b");
	std::filesystem::path t2("C:\\a/b");
	std::filesystem::path t3("D:/a/b");
	std::filesystem::path t4("b");
	std::filesystem::path t5("/");
	std::filesystem::path t6("\\");
	std::filesystem::path t7("\\A\\B");
	std::filesystem::path t8("/A/b");
	std::filesystem::path t9("c\\d\\");
	std::filesystem::path t10("D:c\\d");
	std::filesystem::path t11("D:");
	std::filesystem::path t12("D:\\");
	std::filesystem::path t13("D\\:");
	std::filesystem::path t14("D\\");
	std::filesystem::path t15(":a");
	std::filesystem::path t16(":/a");
	std::filesystem::path t17(":c/a");

	ktk_filesystem_path _t("a/b");
	ktk_filesystem_path _t1("C:/a/b");
	ktk_filesystem_path _t2("C:\\a/b");
	ktk_filesystem_path _t3("D:/a/b");
	ktk_filesystem_path _t4("b");
	ktk_filesystem_path _t5("/");
	ktk_filesystem_path _t6("\\");
	ktk_filesystem_path _t7("\\A\\B");
	ktk_filesystem_path _t8("/A/b");
	ktk_filesystem_path _t9("c\\d\\");
	ktk_filesystem_path _t10("D:c\\d");
	ktk_filesystem_path _t11("D:");
	ktk_filesystem_path _t12("D:\\");
	ktk_filesystem_path _t13("D\\:");
	ktk_filesystem_path _t14("D\\");
	ktk_filesystem_path _t15(":a");
	ktk_filesystem_path _t16(":/a");
	ktk_filesystem_path _t17(":c/a");

	REQUIRE(t.has_stem() == _t.has_stem());
	REQUIRE(t1.has_stem() == _t1.has_stem());
	REQUIRE(t2.has_stem() == _t2.has_stem());
	REQUIRE(t3.has_stem() == _t3.has_stem());
	REQUIRE(t4.has_stem() == _t4.has_stem());
	REQUIRE(t5.has_stem() == _t5.has_stem());
	REQUIRE(t6.has_stem() == _t6.has_stem());
	REQUIRE(t7.has_stem() == _t7.has_stem());
	REQUIRE(t8.has_stem() == _t8.has_stem());
	REQUIRE(t9.has_stem() == _t9.has_stem());
	REQUIRE(t10.has_stem() == _t10.has_stem());
	REQUIRE(t11.has_stem() == _t11.has_stem());
	REQUIRE(t12.has_stem() == _t12.has_stem());
	REQUIRE(t13.has_stem() == _t13.has_stem());
	REQUIRE(t14.has_stem() == _t14.has_stem());
	REQUIRE(t15.has_stem() == _t15.has_stem());
	REQUIRE(t16.has_stem() == _t16.has_stem());
	REQUIRE(t17.has_stem() == _t17.has_stem());
}

TEST_CASE(" test_container_filesystem_static_path_has_root_path()")
{
	std::filesystem::path t("a/b");
	std::filesystem::path t1("C:/a/b");
	std::filesystem::path t2("C:\\a/b");
	std::filesystem::path t3("D:/a/b");
	std::filesystem::path t4("b");
	std::filesystem::path t5("/");
	std::filesystem::path t6("\\");
	std::filesystem::path t7("\\A\\B");
	std::filesystem::path t8("/A/b");
	std::filesystem::path t9("c\\d\\");
	std::filesystem::path t10("D:c\\d");
	std::filesystem::path t11("D:");
	std::filesystem::path t12("D:\\");
	std::filesystem::path t13("D\\:");
	std::filesystem::path t14("D\\");
	std::filesystem::path t15(":a");
	std::filesystem::path t16(":/a");
	std::filesystem::path t17(":c/a");

	ktk_filesystem_path _t("a/b");
	ktk_filesystem_path _t1("C:/a/b");
	ktk_filesystem_path _t2("C:\\a/b");
	ktk_filesystem_path _t3("D:/a/b");
	ktk_filesystem_path _t4("b");
	ktk_filesystem_path _t5("/");
	ktk_filesystem_path _t6("\\");
	ktk_filesystem_path _t7("\\A\\B");
	ktk_filesystem_path _t8("/A/b");
	ktk_filesystem_path _t9("c\\d\\");
	ktk_filesystem_path _t10("D:c\\d");
	ktk_filesystem_path _t11("D:");
	ktk_filesystem_path _t12("D:\\");
	ktk_filesystem_path _t13("D\\:");
	ktk_filesystem_path _t14("D\\");
	ktk_filesystem_path _t15(":a");
	ktk_filesystem_path _t16(":/a");
	ktk_filesystem_path _t17(":c/a");

	REQUIRE(t.has_root_path() == _t.has_root_path());
	REQUIRE(t1.has_root_path() == _t1.has_root_path());
	REQUIRE(t2.has_root_path() == _t2.has_root_path());
	REQUIRE(t3.has_root_path() == _t3.has_root_path());
	REQUIRE(t4.has_root_path() == _t4.has_root_path());
	REQUIRE(t5.has_root_path() == _t5.has_root_path());
	REQUIRE(t6.has_root_path() == _t6.has_root_path());
	REQUIRE(t7.has_root_path() == _t7.has_root_path());
	REQUIRE(t8.has_root_path() == _t8.has_root_path());
	REQUIRE(t9.has_root_path() == _t9.has_root_path());
	REQUIRE(t10.has_root_path() == _t10.has_root_path());
	REQUIRE(t11.has_root_path() == _t11.has_root_path());
	REQUIRE(t12.has_root_path() == _t12.has_root_path());
	REQUIRE(t13.has_root_path() == _t13.has_root_path());
	REQUIRE(t14.has_root_path() == _t14.has_root_path());
	REQUIRE(t15.has_root_path() == _t15.has_root_path());
	REQUIRE(t16.has_root_path() == _t16.has_root_path());
	REQUIRE(t17.has_root_path() == _t17.has_root_path());
}

TEST_CASE(" test_container_filesystem_static_path_has_root_name()")
{
	std::filesystem::path t("a/b");
	std::filesystem::path t1("C:/a/b");
	std::filesystem::path t2("C:\\a/b");
	std::filesystem::path t3("D:/a/b");
	std::filesystem::path t4("b");
	std::filesystem::path t5("/");
	std::filesystem::path t6("\\");
	std::filesystem::path t7("\\A\\B");
	std::filesystem::path t8("/A/b");
	std::filesystem::path t9("c\\d\\");
	std::filesystem::path t10("D:c\\d");
	std::filesystem::path t11("D:");
	std::filesystem::path t12("D:\\");
	std::filesystem::path t13("D\\:");
	std::filesystem::path t14("D\\");
	std::filesystem::path t15(":a");
	std::filesystem::path t16(":/a");
	std::filesystem::path t17(":c/a");

	ktk_filesystem_path _t("a/b");
	ktk_filesystem_path _t1("C:/a/b");
	ktk_filesystem_path _t2("C:\\a/b");
	ktk_filesystem_path _t3("D:/a/b");
	ktk_filesystem_path _t4("b");
	ktk_filesystem_path _t5("/");
	ktk_filesystem_path _t6("\\");
	ktk_filesystem_path _t7("\\A\\B");
	ktk_filesystem_path _t8("/A/b");
	ktk_filesystem_path _t9("c\\d\\");
	ktk_filesystem_path _t10("D:c\\d");
	ktk_filesystem_path _t11("D:");
	ktk_filesystem_path _t12("D:\\");
	ktk_filesystem_path _t13("D\\:");
	ktk_filesystem_path _t14("D\\");
	ktk_filesystem_path _t15(":a");
	ktk_filesystem_path _t16(":/a");
	ktk_filesystem_path _t17(":c/a");

	REQUIRE(t.has_root_name() == _t.has_root_name());
	REQUIRE(t1.has_root_name() == _t1.has_root_name());
	REQUIRE(t2.has_root_name() == _t2.has_root_name());
	REQUIRE(t3.has_root_name() == _t3.has_root_name());
	REQUIRE(t4.has_root_name() == _t4.has_root_name());
	REQUIRE(t5.has_root_name() == _t5.has_root_name());
	REQUIRE(t6.has_root_name() == _t6.has_root_name());
	REQUIRE(t7.has_root_name() == _t7.has_root_name());
	REQUIRE(t8.has_root_name() == _t8.has_root_name());
	REQUIRE(t9.has_root_name() == _t9.has_root_name());
	REQUIRE(t10.has_root_name() == _t10.has_root_name());
	REQUIRE(t11.has_root_name() == _t11.has_root_name());
	REQUIRE(t12.has_root_name() == _t12.has_root_name());
	REQUIRE(t13.has_root_name() == _t13.has_root_name());
	REQUIRE(t14.has_root_name() == _t14.has_root_name());
	REQUIRE(t15.has_root_name() == _t15.has_root_name());
	REQUIRE(t16.has_root_name() == _t16.has_root_name());
	REQUIRE(t17.has_root_name() == _t17.has_root_name());
}

TEST_CASE(" test_container_filesystem_static_path_root_name()")
{
	std::filesystem::path t("a/b");
	std::filesystem::path t1("C:/a/b");
	std::filesystem::path t2("C:\\a/b");
	std::filesystem::path t3("D:/a/b");
	std::filesystem::path t4("b");
	std::filesystem::path t5("/");
	std::filesystem::path t6("\\");
	std::filesystem::path t7("\\A\\B");
	std::filesystem::path t8("/A/b");
	std::filesystem::path t9("c\\d\\");
	std::filesystem::path t10("D:c\\d");
	std::filesystem::path t11("D:");
	std::filesystem::path t12("D:\\");
	std::filesystem::path t13("D\\:");
	std::filesystem::path t14("D\\");
	std::filesystem::path t15(":a");
	std::filesystem::path t16(":/a");
	std::filesystem::path t17(":c/a");

	ktk_filesystem_path _t("a/b");
	ktk_filesystem_path _t1("C:/a/b");
	ktk_filesystem_path _t2("C:\\a/b");
	ktk_filesystem_path _t3("D:/a/b");
	ktk_filesystem_path _t4("b");
	ktk_filesystem_path _t5("/");
	ktk_filesystem_path _t6("\\");
	ktk_filesystem_path _t7("\\A\\B");
	ktk_filesystem_path _t8("/A/b");
	ktk_filesystem_path _t9("c\\d\\");
	ktk_filesystem_path _t10("D:c\\d");
	ktk_filesystem_path _t11("D:");
	ktk_filesystem_path _t12("D:\\");
	ktk_filesystem_path _t13("D\\:");
	ktk_filesystem_path _t14("D\\");
	ktk_filesystem_path _t15(":a");
	ktk_filesystem_path _t16(":/a");
	ktk_filesystem_path _t17(":c/a");

	REQUIRE(t.root_name().string().c_str() == _t.root_name().native());
	REQUIRE(t1.root_name().string().c_str() == _t1.root_name().native());
	REQUIRE(t2.root_name().string().c_str() == _t2.root_name().native());
	REQUIRE(t3.root_name().string().c_str() == _t3.root_name().native());
	REQUIRE(t4.root_name().string().c_str() == _t4.root_name().native());
	REQUIRE(t5.root_name().string().c_str() == _t5.root_name().native());
	REQUIRE(t6.root_name().string().c_str() == _t6.root_name().native());
	REQUIRE(t7.root_name().string().c_str() == _t7.root_name().native());
	REQUIRE(t8.root_name().string().c_str() == _t8.root_name().native());
	REQUIRE(t9.root_name().string().c_str() == _t9.root_name().native());
	REQUIRE(
		t10.root_name().string().c_str() == _t10.root_name().native());
	REQUIRE(
		t11.root_name().string().c_str() == _t11.root_name().native());
	REQUIRE(
		t12.root_name().string().c_str() == _t12.root_name().native());
	REQUIRE(
		t13.root_name().string().c_str() == _t13.root_name().native());
	REQUIRE(
		t14.root_name().string().c_str() == _t14.root_name().native());
	REQUIRE(
		t15.root_name().string().c_str() == _t15.root_name().native());
	REQUIRE(
		t16.root_name().string().c_str() == _t16.root_name().native());
	REQUIRE(
		t17.root_name().string().c_str() == _t17.root_name().native());
}

TEST_CASE(" test_container_filesystem_static_path_extension()")
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

	REQUIRE(
		test.extension().native().c_str() == std_test.extension().string());
	REQUIRE(
		test2.extension().native().c_str() == std_test2.extension().string());
	REQUIRE(
		test3.extension().native().c_str() == std_test3.extension().string());
	REQUIRE(
		test4.extension().native().c_str() == std_test4.extension().string());
	REQUIRE(
		test5.extension().native().c_str() == std_test5.extension().string());
	REQUIRE(
		test6.extension().native().c_str() == std_test6.extension().string());
	REQUIRE(
		test7.extension().native().c_str() == std_test7.extension().string());
	REQUIRE(
		test8.extension().native().c_str() == std_test8.extension().string());
	REQUIRE(
		test9.extension().native().c_str() == std_test9.extension().string());
	REQUIRE(
		test10.extension().native().c_str() == std_test10.extension().string());
	REQUIRE(
		test11.extension().native().c_str() == std_test11.extension().string());
}

TEST_CASE(" test_container_filesystem_static_path_filename()")
{
	ktk_filesystem_path _t("/");
	ktk_filesystem_path _t2("\\");
	ktk_filesystem_path _t3("/ab/test.txt");
	ktk_filesystem_path _t4("/ab/.");
	ktk_filesystem_path _t5("/ab/..");
	ktk_filesystem_path _t6("/ab/.1");
	ktk_filesystem_path _t7("/ab/..1");
	ktk_filesystem_path _t8("/ab/1.1");
	ktk_filesystem_path _t9("/ab/1.");
	ktk_filesystem_path _t10("/ab/...");
	ktk_filesystem_path _t11("/ab/.1.");
	ktk_filesystem_path _t12("/ab\\..1");
	ktk_filesystem_path _t13("/ab/1.1");
	ktk_filesystem_path _t14("\\ab/1.");
	ktk_filesystem_path _t15("\\ab\\...");
	ktk_filesystem_path _t16("/ab\\.1.");
	ktk_filesystem_path _t17("ab");
	ktk_filesystem_path _t18("1");
	ktk_filesystem_path _t19(".1");
	ktk_filesystem_path _t20(".1.");
	ktk_filesystem_path _t21("..");
	ktk_filesystem_path _t22(".");
	ktk_filesystem_path _t23("...");

	std::filesystem::path t("/");
	std::filesystem::path t2("\\");
	std::filesystem::path t3("/ab/test.txt");
	std::filesystem::path t4("/ab/.");
	std::filesystem::path t5("/ab/..");
	std::filesystem::path t6("/ab/.1");
	std::filesystem::path t7("/ab/..1");
	std::filesystem::path t8("/ab/1.1");
	std::filesystem::path t9("/ab/1.");
	std::filesystem::path t10("/ab/...");
	std::filesystem::path t11("/ab/.1.");
	std::filesystem::path t12("/ab\\..1");
	std::filesystem::path t13("/ab/1.1");
	std::filesystem::path t14("\\ab/1.");
	std::filesystem::path t15("\\ab\\...");
	std::filesystem::path t16("/ab\\.1.");
	std::filesystem::path t17("ab");
	std::filesystem::path t18("1");
	std::filesystem::path t19(".1");
	std::filesystem::path t20(".1.");
	std::filesystem::path t21("..");
	std::filesystem::path t22(".");
	std::filesystem::path t23("...");

	REQUIRE(_t.filename().native().c_str() == t.filename().string());
	REQUIRE(_t2.filename().native().c_str() == t2.filename().string());
	REQUIRE(_t3.filename().native().c_str() == t3.filename().string());
	REQUIRE(_t4.filename().native().c_str() == t4.filename().string());
	REQUIRE(_t5.filename().native().c_str() == t5.filename().string());
	REQUIRE(_t6.filename().native().c_str() == t6.filename().string());
	REQUIRE(_t7.filename().native().c_str() == t7.filename().string());
	REQUIRE(_t8.filename().native().c_str() == t8.filename().string());
	REQUIRE(_t9.filename().native().c_str() == t9.filename().string());
	REQUIRE(_t10.filename().native().c_str() == t10.filename().string());
	REQUIRE(_t11.filename().native().c_str() == t11.filename().string());
	REQUIRE(_t12.filename().native().c_str() == t12.filename().string());
	REQUIRE(_t13.filename().native().c_str() == t13.filename().string());
	REQUIRE(_t14.filename().native().c_str() == t14.filename().string());
	REQUIRE(_t15.filename().native().c_str() == t15.filename().string());
	REQUIRE(_t16.filename().native().c_str() == t16.filename().string());
	REQUIRE(_t17.filename().native().c_str() == t17.filename().string());
	REQUIRE(_t18.filename().native().c_str() == t18.filename().string());
	REQUIRE(_t19.filename().native().c_str() == t19.filename().string());
	REQUIRE(_t20.filename().native().c_str() == t20.filename().string());
	REQUIRE(_t21.filename().native().c_str() == t21.filename().string());
	REQUIRE(_t22.filename().native().c_str() == t22.filename().string());
	REQUIRE(_t23.filename().native().c_str() == t23.filename().string());
}

TEST_CASE(" test_container_filesystem_static_path_root_directory()")
{
	std::filesystem::path t("a/b");
	std::filesystem::path t1("C:/a/b");
	std::filesystem::path t2("C:\\a/b");
	std::filesystem::path t3("D:/a/b");
	std::filesystem::path t4("b");
	std::filesystem::path t5("/");
	std::filesystem::path t6("\\");
	std::filesystem::path t7("\\A\\B");
	std::filesystem::path t8("/A/b");
	std::filesystem::path t9("c\\d\\");
	std::filesystem::path t10("D:c\\d");
	std::filesystem::path t11("D:");
	std::filesystem::path t12("D:\\");
	std::filesystem::path t13("D\\:");
	std::filesystem::path t14("D\\");
	std::filesystem::path t15(":a");
	std::filesystem::path t16(":/a");
	std::filesystem::path t17(":c/a");

	ktk_filesystem_path _t("a/b");
	ktk_filesystem_path _t1("C:/a/b");
	ktk_filesystem_path _t2("C:\\a/b");
	ktk_filesystem_path _t3("D:/a/b");
	ktk_filesystem_path _t4("b");
	ktk_filesystem_path _t5("/");
	ktk_filesystem_path _t6("\\");
	ktk_filesystem_path _t7("\\A\\B");
	ktk_filesystem_path _t8("/A/b");
	ktk_filesystem_path _t9("c\\d\\");
	ktk_filesystem_path _t10("D:c\\d");
	ktk_filesystem_path _t11("D:");
	ktk_filesystem_path _t12("D:\\");
	ktk_filesystem_path _t13("D\\:");
	ktk_filesystem_path _t14("D\\");
	ktk_filesystem_path _t15(":a");
	ktk_filesystem_path _t16(":/a");
	ktk_filesystem_path _t17(":c/a");

	REQUIRE(
		t.root_directory().string().c_str() == _t.root_directory().native());
	REQUIRE(
		t1.root_directory().string().c_str() == _t1.root_directory().native());
	REQUIRE(
		t2.root_directory().string().c_str() == _t2.root_directory().native());
	REQUIRE(
		t3.root_directory().string().c_str() == _t3.root_directory().native());
	REQUIRE(
		t4.root_directory().string().c_str() == _t4.root_directory().native());
	REQUIRE(
		t5.root_directory().string().c_str() == _t5.root_directory().native());
	REQUIRE(
		t6.root_directory().string().c_str() == _t6.root_directory().native());
	REQUIRE(
		t7.root_directory().string().c_str() == _t7.root_directory().native());
	REQUIRE(
		t8.root_directory().string().c_str() == _t8.root_directory().native());
	REQUIRE(
		t9.root_directory().string().c_str() == _t9.root_directory().native());
	REQUIRE(t10.root_directory().string().c_str() ==
		_t10.root_directory().native());
	REQUIRE(t11.root_directory().string().c_str() ==
		_t11.root_directory().native());
	REQUIRE(t12.root_directory().string().c_str() ==
		_t12.root_directory().native());
	REQUIRE(t13.root_directory().string().c_str() ==
		_t13.root_directory().native());
	REQUIRE(t14.root_directory().string().c_str() ==
		_t14.root_directory().native());
	REQUIRE(t15.root_directory().string().c_str() ==
		_t15.root_directory().native());
	REQUIRE(t16.root_directory().string().c_str() ==
		_t16.root_directory().native());
	REQUIRE(t17.root_directory().string().c_str() ==
		_t17.root_directory().native());
}

TEST_CASE(" test_container_filesystem_static_path_operator_slash()")
{
	ktk_filesystem_path t;
	ktk_filesystem_path t2("/");
	ktk_filesystem_path t3("C:");

	std::filesystem::path _t;
	std::filesystem::path _t2("/");
	std::filesystem::path _t3("C:");

	auto new_t = t / "test";
	auto new__t = _t / "test";

	REQUIRE(new_t.native() == new_t.string().c_str());

	auto new_t2 = t2 / "test";
	auto new__t2 = _t2 / "test";

	REQUIRE(new_t2.native() == new__t2.string().c_str());

	auto new_t3 = t3 / "test";
	auto new__t3 = _t3 / "test";

	REQUIRE(new_t3.native() == new__t3.string().c_str());
}

TEST_CASE(" test_container_filesystem_static_path_operator_slash_equal()")
{
	ktk_filesystem_path t;
	ktk_filesystem_path t2("/");
	ktk_filesystem_path t3("C:");

	std::filesystem::path _t;
	std::filesystem::path _t2("/");
	std::filesystem::path _t3("C:");

	auto new_t = t /= "test";
	auto new__t = _t /= "test";

	REQUIRE(new_t.native() == new_t.string().c_str());

	auto new_t2 = t2 /= "test";
	auto new__t2 = _t2 /= "test";

	REQUIRE(new_t2.native() == new__t2.string().c_str());

	auto new_t3 = t3 /= "test";
	auto new__t3 = _t3 /= "test";

	REQUIRE(new_t3.native() == new__t3.string().c_str());
}

TEST_CASE(" test_container_filesystem_static_path_append()")
{
	ktk_filesystem_path t;
	ktk_filesystem_path t2("/");
	ktk_filesystem_path t3("C:");

	std::filesystem::path _t;
	std::filesystem::path _t2("/");
	std::filesystem::path _t3("C:");

	auto new_t = t.append("test");
	auto new__t = _t.append("test");

	REQUIRE(new_t.native() == new_t.string().c_str());

	auto new_t2 = t2.append("test");
	auto new__t2 = _t2.append("test");

	REQUIRE(new_t2.native() == new__t2.string().c_str());

	auto new_t3 = t3.append("test");
	auto new__t3 = _t3.append("test");

	REQUIRE(new_t3.native() == new__t3.string().c_str());
}

TEST_CASE(" test_container_filesystem_static_path_operator_plus_slash()")
{
	ktk_filesystem_path t("C:");
	ktk_filesystem_path t1("C:/");
	ktk_filesystem_path t2("C:\\");
	ktk_filesystem_path t3("\\");
	ktk_filesystem_path t4("/");
	ktk_filesystem_path t5("");
	ktk_filesystem_path t6(":a");
	ktk_filesystem_path t7(":");
	ktk_filesystem_path t8(":/");
	ktk_filesystem_path t9(":///");
	ktk_filesystem_path t10(":\\");

	std::filesystem::path _t("C:");
	std::filesystem::path _t1("C:/");
	std::filesystem::path _t2("C:\\");
	std::filesystem::path _t3("\\");
	std::filesystem::path _t4("/");
	std::filesystem::path _t5("");
	std::filesystem::path _t6(":a");
	std::filesystem::path _t7(":");
	std::filesystem::path _t8(":/");
	std::filesystem::path _t9(":///");
	std::filesystem::path _t10(":\\");

	t += "test";
	t1 += "test";
	t2 += "test";
	t3 += "test";
	t4 += "test";
	t5 += "test";
	t6 += "test";
	t7 += "test";
	t8 += "test";
	t9 += "test";
	t10 += "test";

	_t += "test";
	_t1 += "test";
	_t2 += "test";
	_t3 += "test";
	_t4 += "test";
	_t5 += "test";
	_t6 += "test";
	_t7 += "test";
	_t8 += "test";
	_t9 += "test";
	_t10 += "test";

	REQUIRE(t.native() == _t.string().c_str());
	REQUIRE(t1.native() == _t1.string().c_str());
	REQUIRE(t2.native() == _t2.string().c_str());
	REQUIRE(t3.native() == _t3.string().c_str());
	REQUIRE(t4.native() == _t4.string().c_str());
	REQUIRE(t5.native() == _t5.string().c_str());
	REQUIRE(t6.native() == _t6.string().c_str());
	REQUIRE(t7.native() == _t7.string().c_str());
	REQUIRE(t8.native() == _t8.string().c_str());
	REQUIRE(t9.native() == _t9.string().c_str());
	REQUIRE(t10.native() == _t10.string().c_str());
}

TEST_CASE(" test_container_filesystem_static_path_concat()")
{
	ktk_filesystem_path t("C:");
	ktk_filesystem_path t1("C:/");
	ktk_filesystem_path t2("C:\\");
	ktk_filesystem_path t3("\\");
	ktk_filesystem_path t4("/");
	ktk_filesystem_path t5("");
	ktk_filesystem_path t6(":a");
	ktk_filesystem_path t7(":");
	ktk_filesystem_path t8(":/");
	ktk_filesystem_path t9(":///");
	ktk_filesystem_path t10(":\\");

	std::filesystem::path _t("C:");
	std::filesystem::path _t1("C:/");
	std::filesystem::path _t2("C:\\");
	std::filesystem::path _t3("\\");
	std::filesystem::path _t4("/");
	std::filesystem::path _t5("");
	std::filesystem::path _t6(":a");
	std::filesystem::path _t7(":");
	std::filesystem::path _t8(":/");
	std::filesystem::path _t9(":///");
	std::filesystem::path _t10(":\\");

	t.concat("test");
	t1.concat("test");
	t2.concat("test");
	t3.concat("test");
	t4.concat("test");
	t5.concat("test");
	t6.concat("test");
	t7.concat("test");
	t8.concat("test");
	t9.concat("test");
	t10.concat("test");

	_t.concat("test");
	_t1.concat("test");
	_t2.concat("test");
	_t3.concat("test");
	_t4.concat("test");
	_t5.concat("test");
	_t6.concat("test");
	_t7.concat("test");
	_t8.concat("test");
	_t9.concat("test");
	_t10.concat("test");

	REQUIRE(t.native() == _t.string().c_str());
	REQUIRE(t1.native() == _t1.string().c_str());
	REQUIRE(t2.native() == _t2.string().c_str());
	REQUIRE(t3.native() == _t3.string().c_str());
	REQUIRE(t4.native() == _t4.string().c_str());
	REQUIRE(t5.native() == _t5.string().c_str());
	REQUIRE(t6.native() == _t6.string().c_str());
	REQUIRE(t7.native() == _t7.string().c_str());
	REQUIRE(t8.native() == _t8.string().c_str());
	REQUIRE(t9.native() == _t9.string().c_str());
	REQUIRE(t10.native() == _t10.string().c_str());
}

TEST_CASE(" test_container_filesystem_static_path_operator_ostream()")
{
	ktk_filesystem_path t("C:\\test\\ostream\\operator");

	std::cout << t << std::endl;
}

TEST_CASE(" test_container_filesystem_static_path_iterator_for_loop()")
{
	std::vector<std::string> kotek;
	std::vector<std::string> stl;

	ktk_filesystem_path t("C:\\test\\ostream\\operator");
	std::filesystem::path t1("C:\\test\\ostream\\operator");

	for (const auto& it : t)
	{
		std::cout << it << std::endl;
		kotek.push_back(it.native().c_str());
	}

	for (const auto& it : t1)
	{
		stl.push_back(it.string());
	}

	REQUIRE(kotek.size() == stl.size());

	for (auto i = 0; i < kotek.size(); ++i)
	{
		REQUIRE(kotek.at(i) == stl.at(i));
	}

	kotek.clear();
	stl.clear();

	t = "/a/b/c/d";
	t1 = "/a/b/c/d";

	for (const auto& it : t)
	{
		std::cout << it << std::endl;
		kotek.push_back(it.native().c_str());
	}

	for (const auto& it : t1)
	{
		stl.push_back(it.string());
	}

	REQUIRE(kotek.size() == stl.size());

	for (auto i = 0; i < kotek.size(); ++i)
	{
		REQUIRE(kotek.at(i) == stl.at(i));
	}
}

TEST_CASE(" test_container_filesystem_static_path_iterator_constructor() ")
{

}

	#endif
#endif

void RegisterTests_Filesystem_ForModule_Core()
{
#ifdef KOTEK_USE_TESTS
#endif
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
