#include "../include/kotek_core.h"
#include <boost/test/unit_test.hpp>

#ifdef KOTEK_USE_TESTS
	#ifdef KOTEK_DEBUG
		#include <filesystem>
	#endif
#endif

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

void test_container_filesystem_static_path_swap()
{
	ktk_filesystem_path test("C:/test");
	ktk_filesystem_path b("D:/kek");

	test.swap(b);

	BOOST_REQUIRE(test.native() == "D:/kek");
	BOOST_REQUIRE(b.native() == "C:/test");

	ktk_filesystem_path test2("D:\\Godot\\4.2.1\\GodotSharp\\Tools\\nupkgs");
	ktk_filesystem_path b2("C:\\Program Files (x86)\\Microsoft SQL "
						   "Server\\150\\LocalDB\\Binn\\Resources\\es-ES");

	test2.swap(b2);

	BOOST_REQUIRE(test2.native() ==
		"C:\\Program Files (x86)\\Microsoft SQL "
		"Server\\150\\LocalDB\\Binn\\Resources\\es-ES");
	BOOST_REQUIRE(b2.native() == "D:\\Godot\\4.2.1\\GodotSharp\\Tools\\nupkgs");

	ktk_filesystem_path test3("D:\\Godot\\4.2.1\\GodotSharp\\Tools\\nupkgs");
	ktk_filesystem_path b3("");

	test3.swap(b3);
	BOOST_REQUIRE(test3.native() == "");
	BOOST_REQUIRE(b3.native() == "D:\\Godot\\4.2.1\\GodotSharp\\Tools\\nupkgs");
}

void test_container_filesystem_static_path_compare()
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

	BOOST_REQUIRE(a.compare(b) == 0);
	BOOST_REQUIRE(a2.compare(b2) < 0);
	BOOST_REQUIRE(a3.compare(b3) > 0);
	BOOST_REQUIRE(a4.compare(b4) < 0);
	BOOST_REQUIRE(a5.compare(b5) > 0);

	a.compare("");
}

void test_container_filesystem_static_path_has_root_directory()
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

	BOOST_REQUIRE(t.has_root_directory() == _t.has_root_directory());
	BOOST_REQUIRE(t1.has_root_directory() == _t1.has_root_directory());
	BOOST_REQUIRE(t2.has_root_directory() == _t2.has_root_directory());
	BOOST_REQUIRE(t3.has_root_directory() == _t3.has_root_directory());
	BOOST_REQUIRE(t4.has_root_directory() == _t4.has_root_directory());
	BOOST_REQUIRE(t5.has_root_directory() == _t5.has_root_directory());
	BOOST_REQUIRE(t6.has_root_directory() == _t6.has_root_directory());
	BOOST_REQUIRE(t7.has_root_directory() == _t7.has_root_directory());
	BOOST_REQUIRE(t8.has_root_directory() == _t8.has_root_directory());
	BOOST_REQUIRE(t9.has_root_directory() == _t9.has_root_directory());
	BOOST_REQUIRE(t10.has_root_directory() == _t10.has_root_directory());
}

void test_container_filesystem_static_path_is_absolute()
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

	BOOST_REQUIRE(t.is_absolute() == _t.is_absolute());
	BOOST_REQUIRE(t1.is_absolute() == _t1.is_absolute());
	BOOST_REQUIRE(t2.is_absolute() == _t2.is_absolute());
	BOOST_REQUIRE(t3.is_absolute() == _t3.is_absolute());
	BOOST_REQUIRE(t4.is_absolute() == _t4.is_absolute());
	BOOST_REQUIRE(t5.is_absolute() == _t5.is_absolute());
	BOOST_REQUIRE(t6.is_absolute() == _t6.is_absolute());
	BOOST_REQUIRE(t7.is_absolute() == _t7.is_absolute());
	BOOST_REQUIRE(t8.is_absolute() == _t8.is_absolute());
	BOOST_REQUIRE(t9.is_absolute() == _t9.is_absolute());
	BOOST_REQUIRE(t10.is_absolute() == _t10.is_absolute());
}

void test_container_filesystem_static_path_is_relative()
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

	BOOST_REQUIRE(t.is_relative() == _t.is_relative());
	BOOST_REQUIRE(t1.is_relative() == _t1.is_relative());
	BOOST_REQUIRE(t2.is_relative() == _t2.is_relative());
	BOOST_REQUIRE(t3.is_relative() == _t3.is_relative());
	BOOST_REQUIRE(t4.is_relative() == _t4.is_relative());
	BOOST_REQUIRE(t5.is_relative() == _t5.is_relative());
	BOOST_REQUIRE(t6.is_relative() == _t6.is_relative());
	BOOST_REQUIRE(t7.is_relative() == _t7.is_relative());
	BOOST_REQUIRE(t8.is_relative() == _t8.is_relative());
	BOOST_REQUIRE(t9.is_relative() == _t9.is_relative());
	BOOST_REQUIRE(t10.is_relative() == _t10.is_relative());
}

void test_container_filesystem_static_path_relative_path()
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

	BOOST_REQUIRE(
		t.relative_path().string().c_str() == _t.relative_path().native());
	BOOST_REQUIRE(
		t1.relative_path().string().c_str() == _t1.relative_path().native());
	BOOST_REQUIRE(
		t2.relative_path().string().c_str() == _t2.relative_path().native());
	BOOST_REQUIRE(
		t3.relative_path().string().c_str() == _t3.relative_path().native());
	BOOST_REQUIRE(
		t4.relative_path().string().c_str() == _t4.relative_path().native());
	BOOST_REQUIRE(
		t5.relative_path().string().c_str() == _t5.relative_path().native());
	BOOST_REQUIRE(
		t6.relative_path().string().c_str() == _t6.relative_path().native());
	BOOST_REQUIRE(
		t7.relative_path().string().c_str() == _t7.relative_path().native());
	BOOST_REQUIRE(
		t8.relative_path().string().c_str() == _t8.relative_path().native());
	BOOST_REQUIRE(
		t9.relative_path().string().c_str() == _t9.relative_path().native());
	BOOST_REQUIRE(
		t10.relative_path().string().c_str() == _t10.relative_path().native());
	BOOST_REQUIRE(
		t11.relative_path().string().c_str() == _t11.relative_path().native());
	BOOST_REQUIRE(
		t12.relative_path().string().c_str() == _t12.relative_path().native());
	BOOST_REQUIRE(
		t13.relative_path().string().c_str() == _t13.relative_path().native());
	BOOST_REQUIRE(
		t14.relative_path().string().c_str() == _t14.relative_path().native());
	BOOST_REQUIRE(
		t15.relative_path().string().c_str() == _t15.relative_path().native());
	BOOST_REQUIRE(
		t16.relative_path().string().c_str() == _t16.relative_path().native());
	BOOST_REQUIRE(
		t17.relative_path().string().c_str() == _t17.relative_path().native());
}

void test_container_filesystem_static_path_parent_path() 
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

	BOOST_REQUIRE(
		t.parent_path().string().c_str() == _t.parent_path().native());
	BOOST_REQUIRE(
		t1.parent_path().string().c_str() == _t1.parent_path().native());
	BOOST_REQUIRE(
		t2.parent_path().string().c_str() == _t2.parent_path().native());
	BOOST_REQUIRE(
		t3.parent_path().string().c_str() == _t3.parent_path().native());
	BOOST_REQUIRE(
		t4.parent_path().string().c_str() == _t4.parent_path().native());
	BOOST_REQUIRE(
		t5.parent_path().string().c_str() == _t5.parent_path().native());
	BOOST_REQUIRE(
		t6.parent_path().string().c_str() == _t6.parent_path().native());
	BOOST_REQUIRE(
		t7.parent_path().string().c_str() == _t7.parent_path().native());
	BOOST_REQUIRE(
		t8.parent_path().string().c_str() == _t8.parent_path().native());
	BOOST_REQUIRE(
		t9.parent_path().string().c_str() == _t9.parent_path().native());
	BOOST_REQUIRE(
		t10.parent_path().string().c_str() == _t10.parent_path().native());
	BOOST_REQUIRE(
		t11.parent_path().string().c_str() == _t11.parent_path().native());
	BOOST_REQUIRE(
		t12.parent_path().string().c_str() == _t12.parent_path().native());
	BOOST_REQUIRE(
		t13.parent_path().string().c_str() == _t13.parent_path().native());
	BOOST_REQUIRE(
		t14.parent_path().string().c_str() == _t14.parent_path().native());
	BOOST_REQUIRE(
		t15.parent_path().string().c_str() == _t15.parent_path().native());
	BOOST_REQUIRE(
		t16.parent_path().string().c_str() == _t16.parent_path().native());
	BOOST_REQUIRE(
		t17.parent_path().string().c_str() == _t17.parent_path().native());
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
	p_suite->add(BOOST_TEST_CASE(&test_container_filesystem_static_path_swap));
	p_suite->add(
		BOOST_TEST_CASE(&test_container_filesystem_static_path_compare));
	p_suite->add(BOOST_TEST_CASE(
		&test_container_filesystem_static_path_has_root_directory));
	p_suite->add(
		BOOST_TEST_CASE(&test_container_filesystem_static_path_is_absolute));
	p_suite->add(
		BOOST_TEST_CASE(&test_container_filesystem_static_path_is_relative));
	p_suite->add(
		BOOST_TEST_CASE(&test_container_filesystem_static_path_relative_path));
	p_suite->add(
		BOOST_TEST_CASE(&test_container_filesystem_static_path_parent_path));
	boost::unit_test::framework::master_test_suite().add(p_suite);

	KOTEK_MESSAGE("registered!");
#endif
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
