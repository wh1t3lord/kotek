#include "../include/kotek_core.h"

#ifdef KOTEK_USE_TESTS
	#ifdef KOTEK_DEBUG
		#include <filesystem>
		#include <fstream>
		#include <vector>
		#include <iostream>
		#include <gtest/gtest.h>
	#endif
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#ifdef KOTEK_USE_TESTS
	#ifdef KOTEK_DEBUG

class PathOperatorDivEqualTest : public ::testing::Test
{
protected:
	void ComparePathOperations(
		const std::string& initial, const std::string& append
	)
	{
		ktk_filesystem_path custom_p(initial);
		std::filesystem::path std_p(initial);

		custom_p /= append;
		std_p /= append;

		EXPECT_TRUE(custom_p.native() == std_p.string().c_str())
			<< "Initial: '" << initial << "', Append: '"
			<< append << "'\nCustom result: '"
			<< custom_p.native().c_str() << "'\nStd result: '"
			<< std_p.c_str() << "'";
	}

	void CompareMultipleAppends(
		const std::vector<std::string>& appends
	)
	{
		ktk_filesystem_path custom_p;
		std::filesystem::path std_p;

		for (const auto& append : appends)
		{
			custom_p /= append;
			std_p /= append;
		}

		EXPECT_TRUE(custom_p.native() == std_p.string().c_str())
			<< "After " << appends.size()
			<< " appends\nCustom result: '"
			<< custom_p.native().c_str()
			<< "'\nStd result: '" << std_p.c_str() << "'";
	}
};

TEST_F(
	PathOperatorDivEqualTest, StandardRootDirectoryReplacement
)
{
	// When p.has_root_directory(), current relative path should
	// be removed
	ComparePathOperations(
		"C:/Users/John", "/Windows"
	); // Should become "C:/Windows"
	ComparePathOperations(
		"/home/user", "/etc"
	); // Should become "/etc"
	ComparePathOperations(
		"relative/path", "/absolute"
	); // Should become "/absolute"
}

TEST_F(
	PathOperatorDivEqualTest,
	RootNameWithRootDirectoryTransition
)
{
	ComparePathOperations(
		"C:Users", "/Windows"
	); // Should become "C:/Windows"
	ComparePathOperations(
		"C:", "/Windows"
	); // Should become "C:/Windows"
	ComparePathOperations(
		"//server", "/share"
	); // Network path behavior
}

TEST_F(PathOperatorDivEqualTest, EmptyPathSpecialBehavior)
{
	ComparePathOperations("", "file"); // Should be "file"
	ComparePathOperations(
		"", "/absolute"
	); // Should be "/absolute"
	ComparePathOperations(
		"", "C:Windows"
	); // Should be "C:Windows"
}

TEST_F(PathOperatorDivEqualTest, ConsecutiveRootDirectories)
{
	ComparePathOperations(
		"C:/", "/Windows"
	); // Should become "C://Windows"?
	ComparePathOperations(
		"/", "/usr"
	); // Should become "//usr"?
}

TEST_F(PathOperatorDivEqualTest, EmptyPathAppendRelative)
{
	ComparePathOperations("", "dir");
	ComparePathOperations("", "dir/file.txt");
	ComparePathOperations("", "a/b/c/d");
}

TEST_F(PathOperatorDivEqualTest, EmptyPathAppendAbsolute)
{
	ComparePathOperations("", "/absolute");
	ComparePathOperations("", "C:Windows");
	ComparePathOperations("", "//server/share");
}

TEST_F(PathOperatorDivEqualTest, RelativePathAppendRelative)
{
	ComparePathOperations("base", "dir");
	ComparePathOperations("base/", "dir");
	ComparePathOperations("base", "/dir");
	ComparePathOperations("base/dir", "subdir/file");
}

TEST_F(
	PathOperatorDivEqualTest, RelativePathWithTrailingSeparator
)
{
	ComparePathOperations("base/", "dir/");
	ComparePathOperations("base//", "dir");
	ComparePathOperations("base/", "/dir");
}

TEST_F(PathOperatorDivEqualTest, AbsolutePathReplacement)
{
	ComparePathOperations("relative/path", "/absolute/path");
	ComparePathOperations("a/b/c", "/x/y/z");
	ComparePathOperations("dir", "C:Windows");
}

TEST_F(PathOperatorDivEqualTest, RootNameMismatchReplacement)
{
	ComparePathOperations("C:Users", "D:Data");
	ComparePathOperations(
		"//server1/share", "//server2/volume"
	);
	ComparePathOperations("C:local", "D:/absolute");
}

TEST_F(PathOperatorDivEqualTest, DriveRootOperations)
{
	ComparePathOperations("C:", "Windows");
	ComparePathOperations("C:", "/Windows");
	ComparePathOperations("C:Users", "Documents");
	ComparePathOperations("C:Users/", "Documents");
}

TEST_F(PathOperatorDivEqualTest, UnixRootOperations)
{
	ComparePathOperations("/", "usr");
	ComparePathOperations("/", "local/bin");
	ComparePathOperations("/home", "user");
	ComparePathOperations("/home/", "user/documents");
}

TEST_F(PathOperatorDivEqualTest, TrailingSeparatorHandling)
{
	ComparePathOperations("dir/", "file");
	ComparePathOperations("no_trailing", "file");
	ComparePathOperations("dir//", "file");
	ComparePathOperations("a/b/c/", "d/e/f");
}

TEST_F(PathOperatorDivEqualTest, LeadingSeparatorInAppend)
{
	ComparePathOperations("base", "/dir");
	ComparePathOperations("base/", "/dir");
	ComparePathOperations("C:Users", "/Documents");
}

TEST_F(PathOperatorDivEqualTest, MultipleRelativeAppends)
{
	CompareMultipleAppends({"var", "log", "app", "debug.log"});
	CompareMultipleAppends({"a", "b", "c", "d", "e", "f"});
}

TEST_F(PathOperatorDivEqualTest, MultipleMixedAppends)
{
	CompareMultipleAppends(
		{"C:", "Program Files", "App", "config.ini"}
	);
	CompareMultipleAppends(
		{"/", "home", "user", "docs", "file.txt"}
	);
}

TEST_F(PathOperatorDivEqualTest, MultipleWithAbsoluteReset)
{
	ktk_filesystem_path custom_p;
	std::filesystem::path std_p;

	custom_p /= "relative";
	std_p /= "relative";
	EXPECT_TRUE(custom_p.native() == std_p.string().c_str());

	custom_p /= "/absolute";
	std_p /= "/absolute"; // Should reset
	EXPECT_TRUE(custom_p.native() == std_p.string().c_str());

	custom_p /= "more";
	std_p /= "more";
	EXPECT_TRUE(custom_p.native() == std_p.string().c_str());
}

TEST_F(PathOperatorDivEqualTest, EmptyAndDotPaths)
{
	ComparePathOperations("base", "");
	ComparePathOperations("base", ".");
	ComparePathOperations("base", "..");
	ComparePathOperations("", ".");
	ComparePathOperations("", "..");
	ComparePathOperations("/", ".");
	ComparePathOperations("C:", "..");
}

TEST_F(PathOperatorDivEqualTest, MixedAbsoluteRelativeSequence)
{
	ktk_filesystem_path custom_p = "/home";
	std::filesystem::path std_p = "/home";

	custom_p /= "user";
	std_p /= "user";
	EXPECT_TRUE(custom_p.native() == std_p.string().c_str());

	custom_p /= "/tmp";
	std_p /= "/tmp"; // Absolute replacement
	EXPECT_TRUE(custom_p.native() == std_p.string().c_str());

	custom_p /= "file";
	std_p /= "file";
	EXPECT_TRUE(custom_p.native() == std_p.string().c_str());
}

TEST_F(PathOperatorDivEqualTest, ComplexMixedSequence)
{
	CompareMultipleAppends(
		{"relative",
	     "/absolute",
	     "relative_again",
	     "/reset",
	     "final"}
	);
}

TEST_F(PathOperatorDivEqualTest, WindowsDrivePaths)
{
	ComparePathOperations("C:", "Users");
	ComparePathOperations("C:Users", "Documents");
	ComparePathOperations("C:/", "Windows");
	ComparePathOperations("C:/Windows", "System32");
	ComparePathOperations("C:/Windows/", "System32");
}

TEST_F(PathOperatorDivEqualTest, WindowsMixedSeparators)
{
	ComparePathOperations(
		"C:Users", "/Documents"
	); // Mixed root directory
	ComparePathOperations(
		"C:/Users", "Documents"
	); // Normal append
}

TEST_F(PathOperatorDivEqualTest, NetworkPaths)
{
	ComparePathOperations("//server", "share");
	ComparePathOperations("//server/share", "folder");
	ComparePathOperations("//server/share/", "subfolder");
	ComparePathOperations(
		"//server", "//other"
	); // Root name mismatch
}

TEST_F(PathOperatorDivEqualTest, ComplexMultiComponent)
{
	CompareMultipleAppends({"a", "b/c", "d/e/", "f"});
	CompareMultipleAppends({"root/", "sub1/sub2/", "file.ext"});
	CompareMultipleAppends({"", "a", "b/c/d", "e/f/g/", "file"}
	);
}

TEST_F(PathOperatorDivEqualTest, DeeplyNestedPaths)
{
	CompareMultipleAppends(
		{"level1",
	     "level2",
	     "level3",
	     "level4",
	     "level5",
	     "file"}
	);
}

TEST_F(PathOperatorDivEqualTest, SpecialCharacters)
{
	ComparePathOperations("path with spaces", "more spaces");
	ComparePathOperations(
		"normal", "path/with/multiple/components"
	);
	ComparePathOperations(
		"weird//paths", "even//weirder//appends"
	);
}

TEST_F(PathOperatorDivEqualTest, OriginalTestCase)
{
	ktk_filesystem_path custom_p;
	std::filesystem::path std_p;

	custom_p /= "test";
	std_p /= "test";
	EXPECT_TRUE(custom_p.native() == std_p.string().c_str());

	custom_p /= "docs";
	std_p /= "docs";
	EXPECT_TRUE(custom_p.native() == std_p.string().c_str());

	custom_p /= "pretty";
	std_p /= "pretty";
	EXPECT_TRUE(custom_p.native() == std_p.string().c_str());

	// Note: += is string concatenation, not path append
	custom_p += ".json";
	std_p += ".json";
	EXPECT_TRUE(custom_p.native() == std_p.string().c_str());
}

TEST_F(PathOperatorDivEqualTest, BoundaryConditions)
{
	ComparePathOperations("", "");   // Both empty
	ComparePathOperations("/", "");  // Root with empty
	ComparePathOperations("", "/");  // Empty with root
	ComparePathOperations("a", "/"); // Relative with root
	ComparePathOperations("/", "/"); // Root with root
}

TEST_F(PathOperatorDivEqualTest, SingleCharacterPaths)
{
	ComparePathOperations("a", "b");
	ComparePathOperations("a", "b/c");
	ComparePathOperations("a/", "b");
	ComparePathOperations("a", "/b");
}

TEST_F(PathOperatorDivEqualTest, PathsWithDots)
{
	ComparePathOperations("dir", ".");
	ComparePathOperations("dir", "..");
	ComparePathOperations("dir", "../parent");
	ComparePathOperations("dir", "./current");
	ComparePathOperations(".", "file");
	ComparePathOperations("..", "file");
}

TEST(
	Filesystem, test_filesystem_check_folder_tests_for_existance
)
{
	ktkFrameworkConfig cfg;

	ktkFileSystem instance;

	instance.Initialize(&cfg);

	ktk_filesystem_path test_path;

	instance.Make_Path(
		test_path, eFolderIndex::kFolderIndex_DataUser_Tests
	);

	bool status = instance.Is_Exists(test_path);

	EXPECT_TRUE(status);

	instance.Shutdown();
}

TEST(Filesystem, test_file_create_pretty_output)
{
	ktkMainManager main_manager;
	ktkFileSystem filesystem;

	ktkFrameworkConfig _engine_cfg;

	filesystem.Initialize(&_engine_cfg);

	main_manager.Set_FileSystem(&filesystem);

	ktkResourceText<1024, 4096, false> instance;

	//	auto path =
	//		filesystem.GetFolderByEnum(eFolderIndex::kFolderIndex_DataUser_Tests);

	ktk_filesystem_path path;
	filesystem.Make_Path(
		path, eFolderIndex::kFolderIndex_DataUser_Tests, true
	);

	path /= "pretty";
	path += instance.Get_FileExtensionName();

		#ifdef KOTEK_USE_UNICODE
	kun_ktk ustring test(KOTEK_TEXTU("いくつか"));
		#else
	ktk::ustring test("いくつか");
		#endif

	instance.Write("test_field1", "data");
	instance.Write("test_field2", "data2");
	instance.Write<kun_ktk ustring>("kun_ktk ustring", test);

		#ifdef KOTEK_USE_UNICODE
	instance.Write<kun_ktk ustring>(
		"KOTEK_TEXT", KOTEK_TEXTU("いくつか")
	);
	instance.Write<kun_ktk wstring>("wchar_t", L"いくつか");
	instance.Write<kun_ktk u8string>("char8_t", u8"いくつか");
	instance.Write<kun_ktk u16string>("char16_t", u"いくつか");
	instance.Write<kun_ktk u32string>("char32_t", U"いくつか");
		#endif

	//	ktkResourceSaverManager saver_instance;
	//	saver_instance.Initialize(&filesystem, &main_manager);

	//	bool status = saver_instance.Save(
	//		path, ktkResourceHandle(&instance, true)
	//	);

	//	EXPECT_TRUE(status);

	char out[1024];
	kun_ktk uint16_t out_real_length = 0;
	instance.Serialize_ToString(out, out_real_length);

	// todo: provide write operation filesystem saving

	bool status_write =
		filesystem.Write_File(path, out, out_real_length);

	KOTEK_ASSERT(
		status_write, "failed to write file: {}", path
	);

	filesystem.Shutdown();
	main_manager.Shutdown();
}

TEST(
	Filesystem,
	test_container_filesystem_static_path_constructor
)
{
	ktk_filesystem_path test1;
}

TEST(
	Filesystem,
	test_container_filesystem_static_path_make_preferred
)
{
	ktk_filesystem_path test1("a/b/c");
		#ifdef KOTEK_USE_PLATFORM_WINDOWS
	EXPECT_TRUE(test1.make_preferred().native() == "a\\b\\c");
		#elif defined(KOTEK_USE_PLATFORM_LINUX)
			#error implement
		#elif defined(KOTEK_USE_PLATFORM_MACOS)
			#error implement
		#endif
}

TEST(
	Filesystem,
	test_container_filesystem_static_path_remove_filename
)
{
	ktk_filesystem_path test("/");
	ktk_filesystem_path test1("\\");
	ktk_filesystem_path test2;
	ktk_filesystem_path test3("");
	ktk_filesystem_path test4("foo/bar");
	ktk_filesystem_path test5("foo/");
	ktk_filesystem_path test6("/foo");

	EXPECT_TRUE(test.remove_filename().native() == "/");
	EXPECT_TRUE(test1.remove_filename().native() == "\\");
	EXPECT_TRUE(test2.remove_filename().native() == "");
	EXPECT_TRUE(test3.remove_filename().native() == "");
	EXPECT_TRUE(test4.remove_filename().native() == "foo/");
	EXPECT_TRUE(test5.remove_filename().native() == "foo/");
	EXPECT_TRUE(test6.remove_filename().native() == "/");
}

TEST(
	Filesystem,
	test_container_filesystem_static_path_remove_filename2
)
{
	ktk_filesystem_path test("/");
	ktk_filesystem_path test1("\\");
	ktk_filesystem_path test2;
	ktk_filesystem_path test3("");

	EXPECT_TRUE(test.remove_filename().native() == "/");
	EXPECT_TRUE(test1.remove_filename().native() == "\\");
	EXPECT_TRUE(test2.remove_filename().native() == "");
	EXPECT_TRUE(test3.remove_filename().native() == "");
}

TEST(
	Filesystem,
	test_container_filesystem_static_path_has_extension
)
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

	EXPECT_TRUE(
		test.has_extension() == std_test.has_extension()
	);
	EXPECT_TRUE(
		test2.has_extension() == std_test2.has_extension()
	);
	EXPECT_TRUE(
		test3.has_extension() == std_test3.has_extension()
	);
	EXPECT_TRUE(
		test4.has_extension() == std_test4.has_extension()
	);
	EXPECT_TRUE(
		test5.has_extension() == std_test5.has_extension()
	);
	EXPECT_TRUE(
		test6.has_extension() == std_test6.has_extension()
	);
	EXPECT_TRUE(
		test7.has_extension() == std_test7.has_extension()
	);
	EXPECT_TRUE(
		test8.has_extension() == std_test8.has_extension()
	);
	EXPECT_TRUE(
		test9.has_extension() == std_test9.has_extension()
	);
	EXPECT_TRUE(
		test10.has_extension() == std_test10.has_extension()
	);
	EXPECT_TRUE(
		test11.has_extension() == std_test11.has_extension()
	);
}

TEST(
	Filesystem,
	test_container_filesystem_static_path_has_filename
)
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

	EXPECT_TRUE(test.has_filename() == std_test.has_filename());
	EXPECT_TRUE(
		test2.has_filename() == std_test2.has_filename()
	);
	EXPECT_TRUE(
		test3.has_filename() == std_test3.has_filename()
	);
	EXPECT_TRUE(
		test4.has_filename() == std_test4.has_filename()
	);
	EXPECT_TRUE(
		test5.has_filename() == std_test5.has_filename()
	);
	EXPECT_TRUE(
		test6.has_filename() == std_test6.has_filename()
	);
	EXPECT_TRUE(
		test7.has_filename() == std_test7.has_filename()
	);
	EXPECT_TRUE(
		test8.has_filename() == std_test8.has_filename()
	);
	EXPECT_TRUE(
		test9.has_filename() == std_test9.has_filename()
	);
	EXPECT_TRUE(
		test10.has_filename() == std_test10.has_filename()
	);
	EXPECT_TRUE(
		test11.has_filename() == std_test11.has_filename()
	);
	EXPECT_TRUE(
		test12.has_filename() == std_test12.has_filename()
	);
	EXPECT_TRUE(
		test13.has_filename() == std_test13.has_filename()
	);
	EXPECT_TRUE(
		test14.has_filename() == std_test14.has_filename()
	);
	EXPECT_TRUE(
		test15.has_filename() == std_test15.has_filename()
	);
	EXPECT_TRUE(
		test16.has_filename() == std_test16.has_filename()
	);
}

TEST(
	Filesystem,
	test_container_filesystem_static_path_replace_extension
)
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

	EXPECT_TRUE(test.native() == "/foo/bar.png");
	EXPECT_TRUE(test2.native() == "/foo/bar.png");
	EXPECT_TRUE(test3.native() == "/foo/bar.");
	EXPECT_TRUE(test4.native() == "/foo/bar");
	EXPECT_TRUE(test5.native() == "/foo/bar.png");
	EXPECT_TRUE(test6.native() == "/foo/bar.png");
	EXPECT_TRUE(test7.native() == "/foo/bar.png");
	EXPECT_TRUE(test8.native() == "/foo/bar.");
	EXPECT_TRUE(test9.native() == "/foo/bar");
	EXPECT_TRUE(test10.native() == "/foo/..png");
	EXPECT_TRUE(test11.native() == "/foo/..png");
	EXPECT_TRUE(test12.native() == "/foo/..");
	EXPECT_TRUE(test13.native() == "/foo/.");
	EXPECT_TRUE(test14.native() == "/foo/.png");
	EXPECT_TRUE(test15.native() == "/foo/.png");
	EXPECT_TRUE(test16.native() == "/foo/bar");
}

TEST(Filesystem, test_container_filesystem_static_path_swap)
{
	ktk_filesystem_path test("C:/test");
	ktk_filesystem_path b("D:/kek");

	test.swap(b);

	EXPECT_TRUE(test.native() == "D:/kek");
	EXPECT_TRUE(b.native() == "C:/test");

	ktk_filesystem_path test2(
		"D:\\Godot\\4.2.1\\GodotSharp\\Tools\\nupkgs"
	);
	ktk_filesystem_path b2(
		"C:\\Program Files (x86)\\Microsoft SQL "
		"Server\\150\\LocalDB\\Binn\\Resources\\es-ES"
	);

	test2.swap(b2);

	EXPECT_TRUE(
		test2.native() ==
		"C:\\Program Files (x86)\\Microsoft SQL "
		"Server\\150\\LocalDB\\Binn\\Resources\\es-ES"
	);
	EXPECT_TRUE(
		b2.native() ==
		"D:\\Godot\\4.2.1\\GodotSharp\\Tools\\nupkgs"
	);

	ktk_filesystem_path test3(
		"D:\\Godot\\4.2.1\\GodotSharp\\Tools\\nupkgs"
	);
	ktk_filesystem_path b3("");

	test3.swap(b3);
	EXPECT_TRUE(test3.native() == "");
	EXPECT_TRUE(
		b3.native() ==
		"D:\\Godot\\4.2.1\\GodotSharp\\Tools\\nupkgs"
	);
}

TEST(Filesystem, test_container_filesystem_static_path_compare)
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

	EXPECT_TRUE(a.compare(b) == 0);
	EXPECT_TRUE(a2.compare(b2) < 0);
	EXPECT_TRUE(a3.compare(b3) > 0);
	EXPECT_TRUE(a4.compare(b4) < 0);
	EXPECT_TRUE(a5.compare(b5) > 0);

	a.compare("");
}

TEST(
	Filesystem,
	test_container_filesystem_static_path_has_root_directory
)
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

	EXPECT_TRUE(
		t.has_root_directory() == _t.has_root_directory()
	);
	EXPECT_TRUE(
		t1.has_root_directory() == _t1.has_root_directory()
	);
	EXPECT_TRUE(
		t2.has_root_directory() == _t2.has_root_directory()
	);
	EXPECT_TRUE(
		t3.has_root_directory() == _t3.has_root_directory()
	);
	EXPECT_TRUE(
		t4.has_root_directory() == _t4.has_root_directory()
	);
	EXPECT_TRUE(
		t5.has_root_directory() == _t5.has_root_directory()
	);
	EXPECT_TRUE(
		t6.has_root_directory() == _t6.has_root_directory()
	);
	EXPECT_TRUE(
		t7.has_root_directory() == _t7.has_root_directory()
	);
	EXPECT_TRUE(
		t8.has_root_directory() == _t8.has_root_directory()
	);
	EXPECT_TRUE(
		t9.has_root_directory() == _t9.has_root_directory()
	);
	EXPECT_TRUE(
		t10.has_root_directory() == _t10.has_root_directory()
	);
}

TEST(
	Filesystem,
	test_container_filesystem_static_path_is_absolute
)
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

	EXPECT_TRUE(t.is_absolute() == _t.is_absolute());
	EXPECT_TRUE(t1.is_absolute() == _t1.is_absolute());
	EXPECT_TRUE(t2.is_absolute() == _t2.is_absolute());
	EXPECT_TRUE(t3.is_absolute() == _t3.is_absolute());
	EXPECT_TRUE(t4.is_absolute() == _t4.is_absolute());
	EXPECT_TRUE(t5.is_absolute() == _t5.is_absolute());
	EXPECT_TRUE(t6.is_absolute() == _t6.is_absolute());
	EXPECT_TRUE(t7.is_absolute() == _t7.is_absolute());
	EXPECT_TRUE(t8.is_absolute() == _t8.is_absolute());
	EXPECT_TRUE(t9.is_absolute() == _t9.is_absolute());
	EXPECT_TRUE(t10.is_absolute() == _t10.is_absolute());
}

TEST(
	Filesystem,
	test_container_filesystem_static_path_is_relative
)
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

	EXPECT_TRUE(t.is_relative() == _t.is_relative());
	EXPECT_TRUE(t1.is_relative() == _t1.is_relative());
	EXPECT_TRUE(t2.is_relative() == _t2.is_relative());
	EXPECT_TRUE(t3.is_relative() == _t3.is_relative());
	EXPECT_TRUE(t4.is_relative() == _t4.is_relative());
	EXPECT_TRUE(t5.is_relative() == _t5.is_relative());
	EXPECT_TRUE(t6.is_relative() == _t6.is_relative());
	EXPECT_TRUE(t7.is_relative() == _t7.is_relative());
	EXPECT_TRUE(t8.is_relative() == _t8.is_relative());
	EXPECT_TRUE(t9.is_relative() == _t9.is_relative());
	EXPECT_TRUE(t10.is_relative() == _t10.is_relative());
}

TEST(
	Filesystem,
	test_container_filesystem_static_path_relative_path
)
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

	EXPECT_TRUE(
		t.relative_path().string().c_str() ==
		_t.relative_path().native()
	);
	EXPECT_TRUE(
		t1.relative_path().string().c_str() ==
		_t1.relative_path().native()
	);
	EXPECT_TRUE(
		t2.relative_path().string().c_str() ==
		_t2.relative_path().native()
	);
	EXPECT_TRUE(
		t3.relative_path().string().c_str() ==
		_t3.relative_path().native()
	);
	EXPECT_TRUE(
		t4.relative_path().string().c_str() ==
		_t4.relative_path().native()
	);
	EXPECT_TRUE(
		t5.relative_path().string().c_str() ==
		_t5.relative_path().native()
	);
	EXPECT_TRUE(
		t6.relative_path().string().c_str() ==
		_t6.relative_path().native()
	);
	EXPECT_TRUE(
		t7.relative_path().string().c_str() ==
		_t7.relative_path().native()
	);
	EXPECT_TRUE(
		t8.relative_path().string().c_str() ==
		_t8.relative_path().native()
	);
	EXPECT_TRUE(
		t9.relative_path().string().c_str() ==
		_t9.relative_path().native()
	);
	EXPECT_TRUE(
		t10.relative_path().string().c_str() ==
		_t10.relative_path().native()
	);
	EXPECT_TRUE(
		t11.relative_path().string().c_str() ==
		_t11.relative_path().native()
	);
	EXPECT_TRUE(
		t12.relative_path().string().c_str() ==
		_t12.relative_path().native()
	);
	EXPECT_TRUE(
		t13.relative_path().string().c_str() ==
		_t13.relative_path().native()
	);
	EXPECT_TRUE(
		t14.relative_path().string().c_str() ==
		_t14.relative_path().native()
	);
	EXPECT_TRUE(
		t15.relative_path().string().c_str() ==
		_t15.relative_path().native()
	);
	EXPECT_TRUE(
		t16.relative_path().string().c_str() ==
		_t16.relative_path().native()
	);
	EXPECT_TRUE(
		t17.relative_path().string().c_str() ==
		_t17.relative_path().native()
	);
}

TEST(
	Filesystem,
	test_container_filesystem_static_path_parent_path
)
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

	EXPECT_TRUE(
		t.parent_path().string().c_str() ==
		_t.parent_path().native()
	);
	EXPECT_TRUE(
		t1.parent_path().string().c_str() ==
		_t1.parent_path().native()
	);
	EXPECT_TRUE(
		t2.parent_path().string().c_str() ==
		_t2.parent_path().native()
	);
	EXPECT_TRUE(
		t3.parent_path().string().c_str() ==
		_t3.parent_path().native()
	);
	EXPECT_TRUE(
		t4.parent_path().string().c_str() ==
		_t4.parent_path().native()
	);
	EXPECT_TRUE(
		t5.parent_path().string().c_str() ==
		_t5.parent_path().native()
	);
	EXPECT_TRUE(
		t6.parent_path().string().c_str() ==
		_t6.parent_path().native()
	);
	EXPECT_TRUE(
		t7.parent_path().string().c_str() ==
		_t7.parent_path().native()
	);
	EXPECT_TRUE(
		t8.parent_path().string().c_str() ==
		_t8.parent_path().native()
	);
	EXPECT_TRUE(
		t9.parent_path().string().c_str() ==
		_t9.parent_path().native()
	);
	EXPECT_TRUE(
		t10.parent_path().string().c_str() ==
		_t10.parent_path().native()
	);
	EXPECT_TRUE(
		t11.parent_path().string().c_str() ==
		_t11.parent_path().native()
	);
	EXPECT_TRUE(
		t12.parent_path().string().c_str() ==
		_t12.parent_path().native()
	);
	EXPECT_TRUE(
		t13.parent_path().string().c_str() ==
		_t13.parent_path().native()
	);
	EXPECT_TRUE(
		t14.parent_path().string().c_str() ==
		_t14.parent_path().native()
	);
	EXPECT_TRUE(
		t15.parent_path().string().c_str() ==
		_t15.parent_path().native()
	);
	EXPECT_TRUE(
		t16.parent_path().string().c_str() ==
		_t16.parent_path().native()
	);
	EXPECT_TRUE(
		t17.parent_path().string().c_str() ==
		_t17.parent_path().native()
	);
}

TEST(
	Filesystem,
	test_container_filesystem_static_path_has_parent_path
)
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

	EXPECT_TRUE(t.has_parent_path() == _t.has_parent_path());
	EXPECT_TRUE(t1.has_parent_path() == _t1.has_parent_path());
	EXPECT_TRUE(t2.has_parent_path() == _t2.has_parent_path());
	EXPECT_TRUE(t3.has_parent_path() == _t3.has_parent_path());
	EXPECT_TRUE(t4.has_parent_path() == _t4.has_parent_path());
	EXPECT_TRUE(t5.has_parent_path() == _t5.has_parent_path());
	EXPECT_TRUE(t6.has_parent_path() == _t6.has_parent_path());
	EXPECT_TRUE(t7.has_parent_path() == _t7.has_parent_path());
	EXPECT_TRUE(t8.has_parent_path() == _t8.has_parent_path());
	EXPECT_TRUE(t9.has_parent_path() == _t9.has_parent_path());
	EXPECT_TRUE(
		t10.has_parent_path() == _t10.has_parent_path()
	);
	EXPECT_TRUE(
		t11.has_parent_path() == _t11.has_parent_path()
	);
	EXPECT_TRUE(
		t12.has_parent_path() == _t12.has_parent_path()
	);
	EXPECT_TRUE(
		t13.has_parent_path() == _t13.has_parent_path()
	);
	EXPECT_TRUE(
		t14.has_parent_path() == _t14.has_parent_path()
	);
	EXPECT_TRUE(
		t15.has_parent_path() == _t15.has_parent_path()
	);
	EXPECT_TRUE(
		t16.has_parent_path() == _t16.has_parent_path()
	);
	EXPECT_TRUE(
		t17.has_parent_path() == _t17.has_parent_path()
	);
}

TEST(Filesystem, test_container_filesystem_static_path_has_stem)
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

	EXPECT_TRUE(t.has_stem() == _t.has_stem());
	EXPECT_TRUE(t1.has_stem() == _t1.has_stem());
	EXPECT_TRUE(t2.has_stem() == _t2.has_stem());
	EXPECT_TRUE(t3.has_stem() == _t3.has_stem());
	EXPECT_TRUE(t4.has_stem() == _t4.has_stem());
	EXPECT_TRUE(t5.has_stem() == _t5.has_stem());
	EXPECT_TRUE(t6.has_stem() == _t6.has_stem());
	EXPECT_TRUE(t7.has_stem() == _t7.has_stem());
	EXPECT_TRUE(t8.has_stem() == _t8.has_stem());
	EXPECT_TRUE(t9.has_stem() == _t9.has_stem());
	EXPECT_TRUE(t10.has_stem() == _t10.has_stem());
	EXPECT_TRUE(t11.has_stem() == _t11.has_stem());
	EXPECT_TRUE(t12.has_stem() == _t12.has_stem());
	EXPECT_TRUE(t13.has_stem() == _t13.has_stem());
	EXPECT_TRUE(t14.has_stem() == _t14.has_stem());
	EXPECT_TRUE(t15.has_stem() == _t15.has_stem());
	EXPECT_TRUE(t16.has_stem() == _t16.has_stem());
	EXPECT_TRUE(t17.has_stem() == _t17.has_stem());
}

TEST(
	Filesystem,
	test_container_filesystem_static_path_has_root_path
)
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

	EXPECT_TRUE(t.has_root_path() == _t.has_root_path());
	EXPECT_TRUE(t1.has_root_path() == _t1.has_root_path());
	EXPECT_TRUE(t2.has_root_path() == _t2.has_root_path());
	EXPECT_TRUE(t3.has_root_path() == _t3.has_root_path());
	EXPECT_TRUE(t4.has_root_path() == _t4.has_root_path());
	EXPECT_TRUE(t5.has_root_path() == _t5.has_root_path());
	EXPECT_TRUE(t6.has_root_path() == _t6.has_root_path());
	EXPECT_TRUE(t7.has_root_path() == _t7.has_root_path());
	EXPECT_TRUE(t8.has_root_path() == _t8.has_root_path());
	EXPECT_TRUE(t9.has_root_path() == _t9.has_root_path());
	EXPECT_TRUE(t10.has_root_path() == _t10.has_root_path());
	EXPECT_TRUE(t11.has_root_path() == _t11.has_root_path());
	EXPECT_TRUE(t12.has_root_path() == _t12.has_root_path());
	EXPECT_TRUE(t13.has_root_path() == _t13.has_root_path());
	EXPECT_TRUE(t14.has_root_path() == _t14.has_root_path());
	EXPECT_TRUE(t15.has_root_path() == _t15.has_root_path());
	EXPECT_TRUE(t16.has_root_path() == _t16.has_root_path());
	EXPECT_TRUE(t17.has_root_path() == _t17.has_root_path());
}

TEST(
	Filesystem,
	test_container_filesystem_static_path_has_root_name
)
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

	EXPECT_TRUE(t.has_root_name() == _t.has_root_name());
	EXPECT_TRUE(t1.has_root_name() == _t1.has_root_name());
	EXPECT_TRUE(t2.has_root_name() == _t2.has_root_name());
	EXPECT_TRUE(t3.has_root_name() == _t3.has_root_name());
	EXPECT_TRUE(t4.has_root_name() == _t4.has_root_name());
	EXPECT_TRUE(t5.has_root_name() == _t5.has_root_name());
	EXPECT_TRUE(t6.has_root_name() == _t6.has_root_name());
	EXPECT_TRUE(t7.has_root_name() == _t7.has_root_name());
	EXPECT_TRUE(t8.has_root_name() == _t8.has_root_name());
	EXPECT_TRUE(t9.has_root_name() == _t9.has_root_name());
	EXPECT_TRUE(t10.has_root_name() == _t10.has_root_name());
	EXPECT_TRUE(t11.has_root_name() == _t11.has_root_name());
	EXPECT_TRUE(t12.has_root_name() == _t12.has_root_name());
	EXPECT_TRUE(t13.has_root_name() == _t13.has_root_name());
	EXPECT_TRUE(t14.has_root_name() == _t14.has_root_name());
	EXPECT_TRUE(t15.has_root_name() == _t15.has_root_name());
	EXPECT_TRUE(t16.has_root_name() == _t16.has_root_name());
	EXPECT_TRUE(t17.has_root_name() == _t17.has_root_name());
}

TEST(
	Filesystem, test_container_filesystem_static_path_root_name
)
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

	EXPECT_TRUE(
		t.root_name().string().c_str() ==
		_t.root_name().native()
	);
	EXPECT_TRUE(
		t1.root_name().string().c_str() ==
		_t1.root_name().native()
	);
	EXPECT_TRUE(
		t2.root_name().string().c_str() ==
		_t2.root_name().native()
	);
	EXPECT_TRUE(
		t3.root_name().string().c_str() ==
		_t3.root_name().native()
	);
	EXPECT_TRUE(
		t4.root_name().string().c_str() ==
		_t4.root_name().native()
	);
	EXPECT_TRUE(
		t5.root_name().string().c_str() ==
		_t5.root_name().native()
	);
	EXPECT_TRUE(
		t6.root_name().string().c_str() ==
		_t6.root_name().native()
	);
	EXPECT_TRUE(
		t7.root_name().string().c_str() ==
		_t7.root_name().native()
	);
	EXPECT_TRUE(
		t8.root_name().string().c_str() ==
		_t8.root_name().native()
	);
	EXPECT_TRUE(
		t9.root_name().string().c_str() ==
		_t9.root_name().native()
	);
	EXPECT_TRUE(
		t10.root_name().string().c_str() ==
		_t10.root_name().native()
	);
	EXPECT_TRUE(
		t11.root_name().string().c_str() ==
		_t11.root_name().native()
	);
	EXPECT_TRUE(
		t12.root_name().string().c_str() ==
		_t12.root_name().native()
	);
	EXPECT_TRUE(
		t13.root_name().string().c_str() ==
		_t13.root_name().native()
	);
	EXPECT_TRUE(
		t14.root_name().string().c_str() ==
		_t14.root_name().native()
	);
	EXPECT_TRUE(
		t15.root_name().string().c_str() ==
		_t15.root_name().native()
	);
	EXPECT_TRUE(
		t16.root_name().string().c_str() ==
		_t16.root_name().native()
	);
	EXPECT_TRUE(
		t17.root_name().string().c_str() ==
		_t17.root_name().native()
	);
}

TEST(
	Filesystem, test_container_filesystem_static_path_extension
)
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

	EXPECT_TRUE(
		test.extension().native().c_str() ==
		std_test.extension().string()
	);
	EXPECT_TRUE(
		test2.extension().native().c_str() ==
		std_test2.extension().string()
	);
	EXPECT_TRUE(
		test3.extension().native().c_str() ==
		std_test3.extension().string()
	);
	EXPECT_TRUE(
		test4.extension().native().c_str() ==
		std_test4.extension().string()
	);
	EXPECT_TRUE(
		test5.extension().native().c_str() ==
		std_test5.extension().string()
	);
	EXPECT_TRUE(
		test6.extension().native().c_str() ==
		std_test6.extension().string()
	);
	EXPECT_TRUE(
		test7.extension().native().c_str() ==
		std_test7.extension().string()
	);
	EXPECT_TRUE(
		test8.extension().native().c_str() ==
		std_test8.extension().string()
	);
	EXPECT_TRUE(
		test9.extension().native().c_str() ==
		std_test9.extension().string()
	);
	EXPECT_TRUE(
		test10.extension().native().c_str() ==
		std_test10.extension().string()
	);
	EXPECT_TRUE(
		test11.extension().native().c_str() ==
		std_test11.extension().string()
	);
}

TEST(Filesystem, test_container_filesystem_static_path_filename)
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

	EXPECT_TRUE(
		_t.filename().native().c_str() == t.filename().string()
	);
	EXPECT_TRUE(
		_t2.filename().native().c_str() ==
		t2.filename().string()
	);
	EXPECT_TRUE(
		_t3.filename().native().c_str() ==
		t3.filename().string()
	);
	EXPECT_TRUE(
		_t4.filename().native().c_str() ==
		t4.filename().string()
	);
	EXPECT_TRUE(
		_t5.filename().native().c_str() ==
		t5.filename().string()
	);
	EXPECT_TRUE(
		_t6.filename().native().c_str() ==
		t6.filename().string()
	);
	EXPECT_TRUE(
		_t7.filename().native().c_str() ==
		t7.filename().string()
	);
	EXPECT_TRUE(
		_t8.filename().native().c_str() ==
		t8.filename().string()
	);
	EXPECT_TRUE(
		_t9.filename().native().c_str() ==
		t9.filename().string()
	);
	EXPECT_TRUE(
		_t10.filename().native().c_str() ==
		t10.filename().string()
	);
	EXPECT_TRUE(
		_t11.filename().native().c_str() ==
		t11.filename().string()
	);
	EXPECT_TRUE(
		_t12.filename().native().c_str() ==
		t12.filename().string()
	);
	EXPECT_TRUE(
		_t13.filename().native().c_str() ==
		t13.filename().string()
	);
	EXPECT_TRUE(
		_t14.filename().native().c_str() ==
		t14.filename().string()
	);
	EXPECT_TRUE(
		_t15.filename().native().c_str() ==
		t15.filename().string()
	);
	EXPECT_TRUE(
		_t16.filename().native().c_str() ==
		t16.filename().string()
	);
	EXPECT_TRUE(
		_t17.filename().native().c_str() ==
		t17.filename().string()
	);
	EXPECT_TRUE(
		_t18.filename().native().c_str() ==
		t18.filename().string()
	);
	EXPECT_TRUE(
		_t19.filename().native().c_str() ==
		t19.filename().string()
	);
	EXPECT_TRUE(
		_t20.filename().native().c_str() ==
		t20.filename().string()
	);
	EXPECT_TRUE(
		_t21.filename().native().c_str() ==
		t21.filename().string()
	);
	EXPECT_TRUE(
		_t22.filename().native().c_str() ==
		t22.filename().string()
	);
	EXPECT_TRUE(
		_t23.filename().native().c_str() ==
		t23.filename().string()
	);
}

TEST(
	Filesystem,
	test_container_filesystem_static_path_root_directory
)
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

	EXPECT_TRUE(
		t.root_directory().string().c_str() ==
		_t.root_directory().native()
	);
	EXPECT_TRUE(
		t1.root_directory().string().c_str() ==
		_t1.root_directory().native()
	);
	EXPECT_TRUE(
		t2.root_directory().string().c_str() ==
		_t2.root_directory().native()
	);
	EXPECT_TRUE(
		t3.root_directory().string().c_str() ==
		_t3.root_directory().native()
	);
	EXPECT_TRUE(
		t4.root_directory().string().c_str() ==
		_t4.root_directory().native()
	);
	EXPECT_TRUE(
		t5.root_directory().string().c_str() ==
		_t5.root_directory().native()
	);
	EXPECT_TRUE(
		t6.root_directory().string().c_str() ==
		_t6.root_directory().native()
	);
	EXPECT_TRUE(
		t7.root_directory().string().c_str() ==
		_t7.root_directory().native()
	);
	EXPECT_TRUE(
		t8.root_directory().string().c_str() ==
		_t8.root_directory().native()
	);
	EXPECT_TRUE(
		t9.root_directory().string().c_str() ==
		_t9.root_directory().native()
	);
	EXPECT_TRUE(
		t10.root_directory().string().c_str() ==
		_t10.root_directory().native()
	);
	EXPECT_TRUE(
		t11.root_directory().string().c_str() ==
		_t11.root_directory().native()
	);
	EXPECT_TRUE(
		t12.root_directory().string().c_str() ==
		_t12.root_directory().native()
	);
	EXPECT_TRUE(
		t13.root_directory().string().c_str() ==
		_t13.root_directory().native()
	);
	EXPECT_TRUE(
		t14.root_directory().string().c_str() ==
		_t14.root_directory().native()
	);
	EXPECT_TRUE(
		t15.root_directory().string().c_str() ==
		_t15.root_directory().native()
	);
	EXPECT_TRUE(
		t16.root_directory().string().c_str() ==
		_t16.root_directory().native()
	);
	EXPECT_TRUE(
		t17.root_directory().string().c_str() ==
		_t17.root_directory().native()
	);
}

TEST(
	Filesystem,
	test_container_filesystem_static_path_operator_slash
)
{
	ktk_filesystem_path t;
	ktk_filesystem_path t2("/");
	ktk_filesystem_path t3("C:");

	std::filesystem::path _t;
	std::filesystem::path _t2("/");
	std::filesystem::path _t3("C:");

	auto new_t = t / "test";
	auto new__t = _t / "test";

	EXPECT_TRUE(new_t.native() == new_t.string().c_str());

	auto new_t2 = t2 / "test";
	auto new__t2 = _t2 / "test";

	EXPECT_TRUE(new_t2.native() == new__t2.string().c_str());

	auto new_t3 = t3 / "test";
	auto new__t3 = _t3 / "test";

	EXPECT_TRUE(new_t3.native() == new__t3.string().c_str());
}

TEST(
	Filesystem,
	test_container_filesystem_static_path_operator_slash_equal
)
{
	ktk_filesystem_path t;
	ktk_filesystem_path t2("/");
	ktk_filesystem_path t3("C:");

	std::filesystem::path _t;
	std::filesystem::path _t2("/");
	std::filesystem::path _t3("C:");

	auto new_t = t /= "test";
	auto new__t = _t /= "test";

	EXPECT_TRUE(new_t.native() == new_t.string().c_str());

	auto new_t2 = t2 /= "test";
	auto new__t2 = _t2 /= "test";

	EXPECT_TRUE(new_t2.native() == new__t2.string().c_str());

	auto new_t3 = t3 /= "test";
	auto new__t3 = _t3 /= "test";

	EXPECT_TRUE(new_t3.native() == new__t3.string().c_str());
}

TEST(Filesystem, test_container_filesystem_static_path_append)
{
	ktk_filesystem_path t;
	ktk_filesystem_path t2("/");
	ktk_filesystem_path t3("C:");

	std::filesystem::path _t;
	std::filesystem::path _t2("/");
	std::filesystem::path _t3("C:");

	auto new_t = t.append("test");
	auto new__t = _t.append("test");

	EXPECT_TRUE(new_t.native() == new_t.string().c_str());

	auto new_t2 = t2.append("test");
	auto new__t2 = _t2.append("test");

	EXPECT_TRUE(new_t2.native() == new__t2.string().c_str());

	auto new_t3 = t3.append("test");
	auto new__t3 = _t3.append("test");

	EXPECT_TRUE(new_t3.native() == new__t3.string().c_str());
}

TEST(
	Filesystem,
	test_container_filesystem_static_path_operator_plus_slash
)
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

	EXPECT_TRUE(t.native() == _t.string().c_str());
	EXPECT_TRUE(t1.native() == _t1.string().c_str());
	EXPECT_TRUE(t2.native() == _t2.string().c_str());
	EXPECT_TRUE(t3.native() == _t3.string().c_str());
	EXPECT_TRUE(t4.native() == _t4.string().c_str());
	EXPECT_TRUE(t5.native() == _t5.string().c_str());
	EXPECT_TRUE(t6.native() == _t6.string().c_str());
	EXPECT_TRUE(t7.native() == _t7.string().c_str());
	EXPECT_TRUE(t8.native() == _t8.string().c_str());
	EXPECT_TRUE(t9.native() == _t9.string().c_str());
	EXPECT_TRUE(t10.native() == _t10.string().c_str());
}

TEST(Filesystem, test_container_filesystem_static_path_concat)
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

	EXPECT_TRUE(t.native() == _t.string().c_str());
	EXPECT_TRUE(t1.native() == _t1.string().c_str());
	EXPECT_TRUE(t2.native() == _t2.string().c_str());
	EXPECT_TRUE(t3.native() == _t3.string().c_str());
	EXPECT_TRUE(t4.native() == _t4.string().c_str());
	EXPECT_TRUE(t5.native() == _t5.string().c_str());
	EXPECT_TRUE(t6.native() == _t6.string().c_str());
	EXPECT_TRUE(t7.native() == _t7.string().c_str());
	EXPECT_TRUE(t8.native() == _t8.string().c_str());
	EXPECT_TRUE(t9.native() == _t9.string().c_str());
	EXPECT_TRUE(t10.native() == _t10.string().c_str());
}

TEST(
	Filesystem,
	test_container_filesystem_static_path_operator_ostream
)
{
	ktk_filesystem_path t("C:\\test\\ostream\\operator");

	std::cout << t << std::endl;
}

TEST(
	Filesystem,
	test_container_filesystem_static_path_iterator_for_loop
)
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

	EXPECT_TRUE(kotek.size() == stl.size());

	for (auto i = 0; i < kotek.size(); ++i)
	{
		EXPECT_TRUE(kotek.at(i) == stl.at(i));
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

	EXPECT_TRUE(kotek.size() == stl.size());

	for (auto i = 0; i < kotek.size(); ++i)
	{
		EXPECT_TRUE(kotek.at(i) == stl.at(i));
	}
}

TEST(
	Filesystem,
	test_container_filesystem_static_path_iterator_constructor
)
{
}

TEST(
	FileSystem,
	test_virtualfilemapper_manager_default_constructor
)
{
	ktkFileSystem_VFM vfm;
}

TEST(
	FileSystem, test_virtualfilemapper_manager_init_and_shutdown
)
{
	ktkFileSystem_VFM vfm;
	vfm.Initialize();
	vfm.Shutdown();
}

TEST(FileSystem, test_virtualfilemapper_manager_mapping)
{
	ktkFileSystem_VFM vfm;
	vfm.Initialize();

	// faking handles in order to simulate working without full
	// instancing of filesystem

	ktk_filesystem_path current_path =
		kun_ktk kun_filesystem current_path();

	current_path /= kun_ktk kun_filesystem
		get_frameworks_folder_name_by_enum(
			eFolderIndex::kFolderIndex_DataUser
		);

	bool folder_exists =
		kun_ktk kun_filesystem exists(current_path);

	KOTEK_ASSERT(
		folder_exists,
		"folder {} must exist!",
		kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataUser
			)
	);

	if (folder_exists)
	{
		current_path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataUser_Tests
			);

		folder_exists =
			kun_ktk kun_filesystem exists(current_path);

		KOTEK_ASSERT(
			folder_exists,
			"folder {} must exist!",
			kun_ktk kun_filesystem
				get_frameworks_folder_name_by_enum(
					eFolderIndex::kFolderIndex_DataUser_Tests
				)
		);

		if (folder_exists)
		{
			current_path /= "tvfmmm.dat";

			FILE* p_file = fopen(current_path.c_str(), "w+");
			KOTEK_ASSERT(
				p_file,
				"failed to create file by path: {}",
				current_path
			);

			fwrite("test", sizeof("test"), 1, p_file);
			fflush(p_file);

			ktkFileHandleType handle_id = 0;

			kun_ktk uint32_t file_id = vfm.MapFile(p_file);

			KOTEK_ASSERT(
				file_id != decltype(file_id)(-1),
				"failed to MapFile"
			);

			if (p_file)
				fclose(p_file);

			vfm.UnMapFile(file_id);
		}
	}

	vfm.Shutdown();
}

TEST(FileSystem, test_virtualfilemapper_manager_shutdown)
{
	ktkFileSystem_VFM vfm;
	vfm.Initialize();

	// faking handles in order to simulate working without full
	// instancing of filesystem

	ktk_filesystem_path current_path =
		kun_ktk kun_filesystem current_path();

	current_path /= kun_ktk kun_filesystem
		get_frameworks_folder_name_by_enum(
			eFolderIndex::kFolderIndex_DataUser
		);

	bool folder_exists =
		kun_ktk kun_filesystem exists(current_path);

	KOTEK_ASSERT(
		folder_exists,
		"folder {} must exist!",
		kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataUser
			)
	);

	if (folder_exists)
	{
		current_path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataUser_Tests
			);

		folder_exists =
			kun_ktk kun_filesystem exists(current_path);

		KOTEK_ASSERT(
			folder_exists,
			"folder {} must exist!",
			kun_ktk kun_filesystem
				get_frameworks_folder_name_by_enum(
					eFolderIndex::kFolderIndex_DataUser_Tests
				)
		);

		if (folder_exists)
		{
			current_path /= "tvfmms.dat";

			FILE* p_file = fopen(current_path.c_str(), "w+");
			KOTEK_ASSERT(
				p_file,
				"failed to create file by path: {}",
				current_path
			);

			fwrite("test", sizeof("test"), 1, p_file);
			fflush(p_file);

			ktkFileHandleType handle_id = 0;

			kun_ktk uint32_t file_id = vfm.MapFile(p_file);

			KOTEK_ASSERT(
				file_id != decltype(file_id)(-1),
				"failed to MapFile"
			);

			if (p_file)
				fclose(p_file);

			//	vfm.UnMapFile(file_id);
		}
	}

	vfm.Shutdown();
}

// --- B0 filesystem foundation-repair proofs --------------------------
// every fixture lives under data_user/tests (the folder discipline of
// this file), is a few bytes, and is removed by the test itself

TEST(Filesystem, test_b0_missing_file_read_is_graceful)
{
	ktkFrameworkConfig cfg;
	ktkFileSystem instance;

	instance.Initialize(&cfg);

	ktk_filesystem_path path;
	instance.Make_Path(
		path, eFolderIndex::kFolderIndex_DataUser_Tests
	);
	path /= "b0_missing_read.bin";

	std::error_code ec;
	std::filesystem::remove(
		std::filesystem::path(path.c_str()), ec
	);

	kun_ktk uint8_t buffer[64];
	kun_ktk uint8_t* p_buffer = buffer;
	kun_ktk size_t buffer_size = sizeof(buffer);

	// a missing file is user data, not a programmer error:
	// false + size 0 + untouched buffer pointer, never an assert
	bool status = instance.Read_File(path, p_buffer, buffer_size);

	EXPECT_FALSE(status);
	EXPECT_TRUE(buffer_size == 0);
	EXPECT_TRUE(p_buffer == buffer);

	// the explicit-priority dispatch shape must degrade identically
	p_buffer = buffer;
	buffer_size = sizeof(buffer);

	status = instance.Read_File(
		path, p_buffer, buffer_size, eFileSystemPriorityType::kNative
	);

	EXPECT_FALSE(status);
	EXPECT_TRUE(buffer_size == 0);
	EXPECT_TRUE(p_buffer == buffer);

	// the open path: invalid handle + warning, never an abort
	ktkFileHandleType handle = instance.Open_File(
		path,
		eFileSystemPriorityType::kNative,
		eFileSystemStreamingType::kReadOnly
	);

	EXPECT_TRUE(handle == kInvalidFileHandleType);

	instance.Shutdown();
}

TEST(Filesystem, test_b0_get_file_size_by_path)
{
	ktkFrameworkConfig cfg;
	ktkFileSystem instance;

	instance.Initialize(&cfg);

	ktk_filesystem_path path;
	instance.Make_Path(
		path, eFolderIndex::kFolderIndex_DataUser_Tests
	);
	path /= "b0_file_size.dat";

	ktk_filesystem_path missing_path;
	instance.Make_Path(
		missing_path, eFolderIndex::kFolderIndex_DataUser_Tests
	);
	missing_path /= "b0_file_size_absent.dat";

	std::error_code ec;
	std::filesystem::remove(
		std::filesystem::path(path.c_str()), ec
	);
	ec.clear();
	std::filesystem::remove(
		std::filesystem::path(missing_path.c_str()), ec
	);

	const char payload[] = "size me please";

	ASSERT_TRUE(
		instance.Write_File(path, payload, sizeof(payload))
	);

	kun_ktk size_t result = 0;

	EXPECT_TRUE(instance.Get_FileSize(path, result));
	EXPECT_TRUE(result == sizeof(payload));

	// explicit priority exercises the fallback-list dispatch shape
	result = 0;
	EXPECT_TRUE(
		instance.Get_FileSize(
			path, result, eFileSystemPriorityType::kNative
		)
	);
	EXPECT_TRUE(result == sizeof(payload));

	// absent file: false + size 0, no assert
	result = 123;
	EXPECT_FALSE(instance.Get_FileSize(missing_path, result));
	EXPECT_TRUE(result == 0);

	result = 123;
	EXPECT_FALSE(
		instance.Get_FileSize(
			missing_path, result, eFileSystemPriorityType::kNative
		)
	);
	EXPECT_TRUE(result == 0);

	ec.clear();
	std::filesystem::remove(
		std::filesystem::path(path.c_str()), ec
	);

	instance.Shutdown();
}

TEST(Filesystem, test_b0_write_file_bytes_roundtrip)
{
	ktkFrameworkConfig cfg;
	ktkFileSystem instance;

	instance.Initialize(&cfg);

	ktk_filesystem_path path;
	instance.Make_Path(
		path, eFolderIndex::kFolderIndex_DataUser_Tests
	);
	path /= "b0_bytes_roundtrip.bin";

	std::error_code ec;
	std::filesystem::remove(
		std::filesystem::path(path.c_str()), ec
	);

	kun_ktk uint8_t payload[256];

	for (kun_ktk size_t i = 0; i < sizeof(payload); ++i)
		payload[i] = static_cast<kun_ktk uint8_t>(i);

	// the uint8_t single-shot write (implemented in B0) must be
	// byte-exact — 0x0A inside the payload proves binary mode (no
	// CRLF translation on Windows)
	ASSERT_TRUE(
		instance.Write_File(path, payload, sizeof(payload))
	);

	kun_ktk uint8_t readback[300];
	kun_ktk uint8_t* p_readback = readback;
	kun_ktk size_t readback_size = sizeof(readback);

	ASSERT_TRUE(instance.Read_File(path, p_readback, readback_size));
	EXPECT_TRUE(readback_size == sizeof(payload));
	EXPECT_TRUE(p_readback == readback);

	bool equal = true;

	for (kun_ktk size_t i = 0; i < sizeof(payload); ++i)
	{
		if (readback[i] != payload[i])
		{
			equal = false;
			break;
		}
	}

	EXPECT_TRUE(equal);

	ec.clear();
	std::filesystem::remove(
		std::filesystem::path(path.c_str()), ec
	);

	instance.Shutdown();
}

TEST(Filesystem, test_b0_handle_api_roundtrip)
{
	ktkFrameworkConfig cfg;
	ktkFileSystem instance;

	instance.Initialize(&cfg);

	ktk_filesystem_path path;
	instance.Make_Path(
		path, eFolderIndex::kFolderIndex_DataUser_Tests
	);
	path /= "b0_handle_api.dat";

	std::error_code ec;
	std::filesystem::remove(
		std::filesystem::path(path.c_str()), ec
	);

	// seed the file (kReadAndWrite opens an existing file)
	const char seed[] = "0123456789ABCDEF";

	ASSERT_TRUE(instance.Write_File(path, seed, sizeof(seed)));

	ktkFileHandleType handle = instance.Open_File(
		path,
		eFileSystemPriorityType::kNative,
		eFileSystemStreamingType::kReadAndWrite
	);

	ASSERT_TRUE(handle != kInvalidFileHandleType);

	kun_ktk size_t file_size = 0;
	EXPECT_TRUE(instance.Get_FileSize(handle, file_size));
	EXPECT_TRUE(file_size == sizeof(seed));

	// Get_FileSize must not disturb the stream position
	kun_ktk size_t position = static_cast<kun_ktk size_t>(-1);
	EXPECT_TRUE(instance.Tell(handle, position));
	EXPECT_TRUE(position == 0);

	EXPECT_TRUE(
		instance.Seek(handle, 4, eFileSystemSeekType::kBegin)
	);
	EXPECT_TRUE(instance.Tell(handle, position));
	EXPECT_TRUE(position == 4);

	// patch 4 bytes at offset 4
	const char patch[] = "wxyz";
	EXPECT_TRUE(instance.Write_File(handle, patch, 4));

	EXPECT_TRUE(instance.Seek(handle, 0, eFileSystemSeekType::kEnd));
	EXPECT_TRUE(instance.Tell(handle, position));
	EXPECT_TRUE(position == sizeof(seed));

	EXPECT_TRUE(instance.Close_File(handle));

	// verify the patched content through the single-shot read
	kun_ktk uint8_t readback[32];
	kun_ktk uint8_t* p_readback = readback;
	kun_ktk size_t readback_size = sizeof(readback);

	ASSERT_TRUE(instance.Read_File(path, p_readback, readback_size));
	ASSERT_TRUE(readback_size == sizeof(seed));

	const char expected[] = "0123wxyz89ABCDEF";

	bool equal = true;

	for (kun_ktk size_t i = 0; i < sizeof(seed); ++i)
	{
		if (readback[i] !=
		    static_cast<kun_ktk uint8_t>(expected[i]))
		{
			equal = false;
			break;
		}
	}

	EXPECT_TRUE(equal);

	ec.clear();
	std::filesystem::remove(
		std::filesystem::path(path.c_str()), ec
	);

	instance.Shutdown();
}

TEST(
	Filesystem,
	test_b0_read_file_buffer_too_small_reports_required_size
)
{
	ktkFrameworkConfig cfg;
	ktkFileSystem instance;

	instance.Initialize(&cfg);

	ktk_filesystem_path path;
	instance.Make_Path(
		path, eFolderIndex::kFolderIndex_DataUser_Tests
	);
	path /= "b0_too_small.bin";

	std::error_code ec;
	std::filesystem::remove(
		std::filesystem::path(path.c_str()), ec
	);

	char payload[64];

	for (kun_ktk size_t i = 0; i < sizeof(payload); ++i)
		payload[i] = static_cast<char>('a' + (i % 26));

	ASSERT_TRUE(
		instance.Write_File(path, payload, sizeof(payload))
	);

	// B0 contract: a too-small buffer fails the call, reports the
	// REQUIRED size through the size out-param and never redirects
	// the pointer to internal scratch storage
	kun_ktk uint8_t tiny[8];
	kun_ktk uint8_t* p_tiny = tiny;
	kun_ktk size_t tiny_size = sizeof(tiny);

	bool status = instance.Read_File(path, p_tiny, tiny_size);

	EXPECT_FALSE(status);
	EXPECT_TRUE(tiny_size == sizeof(payload));
	EXPECT_TRUE(p_tiny == tiny);

	// retry with the reported size succeeds
	kun_ktk uint8_t full[sizeof(payload)];
	kun_ktk uint8_t* p_full = full;
	kun_ktk size_t full_size = sizeof(full);

	ASSERT_TRUE(instance.Read_File(path, p_full, full_size));
	EXPECT_TRUE(full_size == sizeof(payload));

	bool equal = true;

	for (kun_ktk size_t i = 0; i < sizeof(payload); ++i)
	{
		if (full[i] != static_cast<kun_ktk uint8_t>(payload[i]))
		{
			equal = false;
			break;
		}
	}

	EXPECT_TRUE(equal);

	ec.clear();
	std::filesystem::remove(
		std::filesystem::path(path.c_str()), ec
	);

	instance.Shutdown();
}

// --- B1 VFM-mapped reads (behind the runtime feature flag) -----------
// same fixture discipline as B0 (data_user/tests, self-cleaning); the
// flags are driven through the test's own ktkFrameworkConfig and are
// set AFTER Initialize because Initialize parses the shipped
// sys_info.json (which carries VFM_READ) into the config
#ifdef KOTEK_USE_FILESYSTEM_FEATURE_VFM

TEST(Filesystem, test_b1_vfm_read_matches_native_bytes)
{
	ktkFrameworkConfig cfg;
	ktkFileSystem instance;

	instance.Initialize(&cfg);

	ktk_filesystem_path path;
	instance.Make_Path(
		path, eFolderIndex::kFolderIndex_DataUser_Tests
	);
	path /= "b1_vfm_parity.bin";

	std::error_code ec;
	std::filesystem::remove(
		std::filesystem::path(path.c_str()), ec
	);

	// a few KB of binary content with 0x00/0xFF coverage — i*31+7 mod
	// 256 hits every byte value (gcd(31,256)=1)
	constexpr kun_ktk size_t kPayloadSize = 4107;
	kun_ktk uint8_t payload[kPayloadSize];

	for (kun_ktk size_t i = 0; i < kPayloadSize; ++i)
		payload[i] = static_cast<kun_ktk uint8_t>(i * 31 + 7);

	ASSERT_TRUE(instance.Write_File(path, payload, kPayloadSize));

	auto p_read_and_verify =
		[&](kun_ktk uint8_t* p_out, kun_ktk size_t out_capacity
	    ) -> void
	{
		kun_ktk uint8_t* p_buffer = p_out;
		kun_ktk size_t buffer_size = out_capacity;

		bool status = instance.Read_File(path, p_buffer, buffer_size);

		EXPECT_TRUE(status);
		EXPECT_TRUE(buffer_size == kPayloadSize);
		EXPECT_TRUE(p_buffer == p_out);
		// both paths append the terminator when room remains
		EXPECT_TRUE(p_out[kPayloadSize] == 0);

		bool equal = true;

		for (kun_ktk size_t i = 0; i < kPayloadSize; ++i)
		{
			if (p_out[i] != payload[i])
			{
				equal = false;
				break;
			}
		}

		EXPECT_TRUE(equal);
	};

	// 1) the native CRT path (flags off)
	cfg.Set_FS_FeaturesFlag(0);

	kun_ktk uint8_t native_read[kPayloadSize + 64];
	p_read_and_verify(native_read, sizeof(native_read));

	// 2) the mapped read, no cache
	cfg.Set_FS_FeaturesFlag(static_cast<kun_ktk uint16_t>(
		eFileSystemFeatureType::kVFMRead
	));

	kun_ktk uint8_t vfm_read[kPayloadSize + 64];
	p_read_and_verify(vfm_read, sizeof(vfm_read));

	// 3) the RETIRED cache flag alongside: it is inert (one explanatory
	// warning, no behavior change) — the read is still the mapped path
	// and still byte-identical
	cfg.Set_FS_FeaturesFlag(static_cast<kun_ktk uint16_t>(
		eFileSystemFeatureType::kVFMRead |
		eFileSystemFeatureType::kVFMCacheEnabled
	));

	kun_ktk uint8_t retired_flag_read[kPayloadSize + 64];
	p_read_and_verify(retired_flag_read, sizeof(retired_flag_read));

	// the three paths are byte-identical (terminator included)
	bool equal = true;

	for (kun_ktk size_t i = 0; i <= kPayloadSize; ++i)
	{
		if (native_read[i] != vfm_read[i] ||
		    native_read[i] != retired_flag_read[i])
		{
			equal = false;
			break;
		}
	}

	EXPECT_TRUE(equal);

	// the B0 buffer contract holds on the mapped path too: a
	// too-small buffer fails the call, reports the REQUIRED size and
	// never redirects the pointer
	kun_ktk uint8_t tiny[16];
	kun_ktk uint8_t* p_tiny = tiny;
	kun_ktk size_t tiny_size = sizeof(tiny);

	bool status = instance.Read_File(path, p_tiny, tiny_size);

	EXPECT_FALSE(status);
	EXPECT_TRUE(tiny_size == kPayloadSize);
	EXPECT_TRUE(p_tiny == tiny);

	ec.clear();
	std::filesystem::remove(
		std::filesystem::path(path.c_str()), ec
	);

	instance.Shutdown();
}

TEST(Filesystem, test_b1_vfm_read_large_file_chunked)
{
	ktkFrameworkConfig cfg;
	ktkFileSystem instance;

	instance.Initialize(&cfg);

	ktk_filesystem_path path;
	instance.Make_Path(
		path, eFolderIndex::kFolderIndex_DataUser_Tests
	);
	path /= "b1_vfm_large.bin";

	std::error_code ec;
	std::filesystem::remove(
		std::filesystem::path(path.c_str()), ec
	);

	// bigger than KOTEK_DEF_FILESYSTEM_VFM_STREAM_CHUNK_SIZE so the
	// mapped copy runs several full chunks plus a partial tail (heap
	// buffers — several hundred KB of stack arrays in a TestBody
	// prologue is the known overflow trap)
	constexpr kun_ktk size_t kPayloadSize =
		KOTEK_DEF_FILESYSTEM_VFM_STREAM_CHUNK_SIZE * 3 + 3403;

	static_assert(
		kPayloadSize > KOTEK_DEF_FILESYSTEM_VFM_STREAM_CHUNK_SIZE
	);

	kun_ktk uint8_t* payload = new kun_ktk uint8_t[kPayloadSize];
	kun_ktk uint8_t* native_read =
		new kun_ktk uint8_t[kPayloadSize + 64];
	kun_ktk uint8_t* vfm_read = new kun_ktk uint8_t[kPayloadSize + 64];

	// i*131+17 mod 256 hits every byte value (131 is odd) — 0x00/0xFF
	// included
	for (kun_ktk size_t i = 0; i < kPayloadSize; ++i)
		payload[i] = static_cast<kun_ktk uint8_t>(i * 131 + 17);

	ASSERT_TRUE(instance.Write_File(path, payload, kPayloadSize));

	ktkFileSystem_VFM* p_vfm = instance.Get_VFM();

	ASSERT_TRUE(p_vfm != nullptr);

	kun_ktk uint32_t maps_before = p_vfm->Get_StatMapCount();
	kun_ktk uint32_t unmaps_before = p_vfm->Get_StatUnmapCount();

	// 1) the native CRT read (flags off)
	cfg.Set_FS_FeaturesFlag(0);

	{
		kun_ktk uint8_t* p_buffer = native_read;
		kun_ktk size_t buffer_size = kPayloadSize + 64;

		ASSERT_TRUE(instance.Read_File(path, p_buffer, buffer_size));
		ASSERT_TRUE(buffer_size == kPayloadSize);
		EXPECT_TRUE(native_read[kPayloadSize] == 0);
	}

	// 2) the mapped read — several chunks through the mapping
	cfg.Set_FS_FeaturesFlag(static_cast<kun_ktk uint16_t>(
		eFileSystemFeatureType::kVFMRead
	));

	{
		kun_ktk uint8_t* p_buffer = vfm_read;
		kun_ktk size_t buffer_size = kPayloadSize + 64;

		ASSERT_TRUE(instance.Read_File(path, p_buffer, buffer_size));
		ASSERT_TRUE(buffer_size == kPayloadSize);
		EXPECT_TRUE(vfm_read[kPayloadSize] == 0);
	}

	// byte-identical over the whole multi-chunk payload
	bool equal = true;

	for (kun_ktk size_t i = 0; i < kPayloadSize; ++i)
	{
		if (native_read[i] != vfm_read[i] || native_read[i] != payload[i])
		{
			equal = false;
			break;
		}
	}

	EXPECT_TRUE(equal);

	// the map→copy→unmap contract: the mapped read balanced its
	// mapping immediately — exactly one map and one unmap, zero
	// outstanding at rest
	EXPECT_TRUE(p_vfm->Get_StatMapCount() - maps_before == 1);
	EXPECT_TRUE(p_vfm->Get_StatUnmapCount() - unmaps_before == 1);
	EXPECT_TRUE(
		(p_vfm->Get_StatMapCount() - p_vfm->Get_StatUnmapCount()) ==
		(maps_before - unmaps_before)
	);

	delete[] payload;
	delete[] native_read;
	delete[] vfm_read;

	ec.clear();
	std::filesystem::remove(
		std::filesystem::path(path.c_str()), ec
	);

	instance.Shutdown();
}

TEST(Filesystem, test_b1_vfm_read_missing_file_is_graceful)
{
	ktkFrameworkConfig cfg;
	ktkFileSystem instance;

	instance.Initialize(&cfg);

	ktk_filesystem_path path;
	instance.Make_Path(
		path, eFolderIndex::kFolderIndex_DataUser_Tests
	);
	path /= "b1_vfm_missing.bin";

	std::error_code ec;
	std::filesystem::remove(
		std::filesystem::path(path.c_str()), ec
	);

	ktkFileSystem_VFM* p_vfm = instance.Get_VFM();

	ASSERT_TRUE(p_vfm != nullptr);

	kun_ktk uint8_t buffer[64];

	auto p_try_read = [&]() -> void
	{
		kun_ktk uint8_t* p_buffer = buffer;
		kun_ktk size_t buffer_size = sizeof(buffer);

		bool status = instance.Read_File(path, p_buffer, buffer_size);

		EXPECT_FALSE(status);
		EXPECT_TRUE(buffer_size == 0);
		EXPECT_TRUE(p_buffer == buffer);
	};

	kun_ktk uint32_t maps_before = p_vfm->Get_StatMapCount();
	kun_ktk uint32_t unmaps_before = p_vfm->Get_StatUnmapCount();

	// both VFM shapes degrade identically: false + size 0 + one
	// warning, no assert, and the CRT fallback is NOT engaged (it
	// would double the warning noise) — the counters prove nothing
	// was ever mapped
	cfg.Set_FS_FeaturesFlag(static_cast<kun_ktk uint16_t>(
		eFileSystemFeatureType::kVFMRead
	));
	p_try_read();

	cfg.Set_FS_FeaturesFlag(static_cast<kun_ktk uint16_t>(
		eFileSystemFeatureType::kVFMRead |
		eFileSystemFeatureType::kVFMCacheEnabled
	));
	p_try_read();

	EXPECT_TRUE(p_vfm->Get_StatMapCount() == maps_before);
	EXPECT_TRUE(p_vfm->Get_StatUnmapCount() == unmaps_before);

	instance.Shutdown();
}

TEST(Filesystem, test_b1_vfm_read_empty_file)
{
	ktkFrameworkConfig cfg;
	ktkFileSystem instance;

	instance.Initialize(&cfg);

	ktk_filesystem_path path;
	instance.Make_Path(
		path, eFolderIndex::kFolderIndex_DataUser_Tests
	);
	path /= "b1_vfm_empty.bin";

	std::error_code ec;
	std::filesystem::remove(
		std::filesystem::path(path.c_str()), ec
	);

	// seed a genuine 0-byte fixture (Write_File's 0-length fwrite
	// reports failure, so create it directly)
	FILE* p_file = fopen(path.c_str(), "wb");
	ASSERT_TRUE(p_file != nullptr);
	fclose(p_file);

	ktkFileSystem_VFM* p_vfm = instance.Get_VFM();

	ASSERT_TRUE(p_vfm != nullptr);

	kun_ktk uint32_t maps_before = p_vfm->Get_StatMapCount();
	kun_ktk uint32_t unmaps_before = p_vfm->Get_StatUnmapCount();

	auto p_try_read = [&]() -> void
	{
		kun_ktk uint8_t storage[8];

		for (kun_ktk size_t i = 0; i < sizeof(storage); ++i)
			storage[i] = 0xAB;

		kun_ktk uint8_t* p_buffer = storage;
		kun_ktk size_t buffer_size = sizeof(storage);

		bool status = instance.Read_File(path, p_buffer, buffer_size);

		EXPECT_TRUE(status);
		EXPECT_TRUE(buffer_size == 0);
		EXPECT_TRUE(p_buffer == storage);
		// both paths land the terminator at [0]
		EXPECT_TRUE(storage[0] == 0);
	};

	// the mapped path reports a successful 0-byte read (a 0-byte map
	// is invalid on Win32 — detected explicitly, nothing ever maps)...
	cfg.Set_FS_FeaturesFlag(static_cast<kun_ktk uint16_t>(
		eFileSystemFeatureType::kVFMRead |
		eFileSystemFeatureType::kVFMCacheEnabled
	));
	p_try_read();

	// ...and the CRT path agrees byte-for-byte
	cfg.Set_FS_FeaturesFlag(0);
	p_try_read();

	EXPECT_TRUE(p_vfm->Get_StatMapCount() == maps_before);
	EXPECT_TRUE(p_vfm->Get_StatUnmapCount() == unmaps_before);

	ec.clear();
	std::filesystem::remove(
		std::filesystem::path(path.c_str()), ec
	);

	instance.Shutdown();
}

TEST(Filesystem, test_b1_vfm_shutdown_leaves_no_outstanding_mappings)
{
	ktkFrameworkConfig cfg;
	ktkFileSystem instance;

	instance.Initialize(&cfg);

	cfg.Set_FS_FeaturesFlag(static_cast<kun_ktk uint16_t>(
		eFileSystemFeatureType::kVFMRead
	));

	ktkFileSystem_VFM* p_vfm = instance.Get_VFM();

	ASSERT_TRUE(p_vfm != nullptr);

	ktk_filesystem_path folder;
	instance.Make_Path(
		folder, eFolderIndex::kFolderIndex_DataUser_Tests
	);

	kun_ktk uint32_t maps_before = p_vfm->Get_StatMapCount();
	kun_ktk uint32_t unmaps_before = p_vfm->Get_StatUnmapCount();

	// three fixtures through the mapped read path
	for (kun_ktk size_t i = 0; i < 3; ++i)
	{
		char name[64];
		std::snprintf(
			name, sizeof(name), "b1_vfm_shutdown_%u.bin",
			static_cast<unsigned>(i)
		);

		ktk_filesystem_path path = folder;
		path /= name;

		std::error_code ec;
		std::filesystem::remove(
			std::filesystem::path(path.c_str()), ec
		);

		const char payload[] = "balance me at shutdown";

		ASSERT_TRUE(instance.Write_File(path, payload, sizeof(payload)));

		kun_ktk uint8_t readback[32];
		kun_ktk uint8_t* p_readback = readback;
		kun_ktk size_t readback_size = sizeof(readback);

		ASSERT_TRUE(
			instance.Read_File(path, p_readback, readback_size)
		);
	}

	// the map→copy→unmap contract: every read already balanced its
	// mapping — zero outstanding at rest
	EXPECT_TRUE(p_vfm->Get_StatMapCount() - maps_before == 3);
	EXPECT_TRUE(p_vfm->Get_StatUnmapCount() - unmaps_before == 3);

	// shutdown with nothing outstanding: clean, no assert, and the
	// balance counters end equal (anything else would be a leaked
	// UnMapFile somewhere on the path)
	instance.Shutdown();

	EXPECT_TRUE(
		p_vfm->Get_StatUnmapCount() == p_vfm->Get_StatMapCount()
	);

	// self-cleaning
	for (kun_ktk size_t i = 0; i < 3; ++i)
	{
		char name[64];
		std::snprintf(
			name, sizeof(name), "b1_vfm_shutdown_%u.bin",
			static_cast<unsigned>(i)
		);

		ktk_filesystem_path path = folder;
		path /= name;

		std::error_code ec;
		std::filesystem::remove(
			std::filesystem::path(path.c_str()), ec
		);
	}
}

#endif

// --- B2a .kpack reader + writer (kotek.core.filesystem.pack) ------------
// same fixture discipline as B0/B1 (data_user/tests, self-cleaning); the
// packs are built IN-TEST through kpack_write_file — the same encoder the
// B2b packer tool will reuse
#ifdef KOTEK_USE_FILESYSTEM_TYPE_PACK

namespace
{
	constexpr const char* kB2A_Name_Stored =
		"data_user/tests/b2a_entry_stored.bin";
	constexpr const char* kB2A_Name_Zstd =
		"data_user/tests/b2a_entry_zstd.bin";
	constexpr const char* kB2A_Name_Zlib =
		"data_user/tests/b2a_entry_zlib.bin";

	constexpr kun_ktk size_t kB2A_StoredSize = 100;
	// 64 KB exact: exactly one full block, the boundary case
	constexpr kun_ktk size_t kB2A_ZstdSize =
		KOTEK_DEF_FILESYSTEM_PACK_BLOCK_SIZE;
	// 3 full blocks + a 3,405-byte tail — crosses block boundaries
	constexpr kun_ktk size_t kB2A_ZlibSize =
		KOTEK_DEF_FILESYSTEM_PACK_BLOCK_SIZE * 3 + 3405;

	void b2a_fill_payload(kun_ktk uint8_t* p_buffer, kun_ktk size_t size)
	{
		// i*31+7 mod 256 hits every byte value (gcd(31,256)=1)
		for (kun_ktk size_t i = 0; i < size; ++i)
			p_buffer[i] = static_cast<kun_ktk uint8_t>(i * 31 + 7);
	}

	bool b2a_bytes_equal(
		const kun_ktk uint8_t* p_left,
		const kun_ktk uint8_t* p_right,
		kun_ktk size_t size
	)
	{
		for (kun_ktk size_t i = 0; i < size; ++i)
		{
			if (p_left[i] != p_right[i])
				return false;
		}
		return true;
	}

	/// builds the mixed 3-entry pack (stored 100 B / zstd 64 KB exact /
	/// zlib 200 KB+tail) at pack_path; the payloads are heap-allocated
	/// and returned for byte comparison (delete[] by the caller)
	bool b2a_write_mixed_pack(
		const ktk_filesystem_path& pack_path,
		kun_ktk uint8_t*& p_out_stored,
		kun_ktk uint8_t*& p_out_zstd,
		kun_ktk uint8_t*& p_out_zlib
	)
	{
		p_out_stored = new kun_ktk uint8_t[kB2A_StoredSize];
		p_out_zstd = new kun_ktk uint8_t[kB2A_ZstdSize];
		p_out_zlib = new kun_ktk uint8_t[kB2A_ZlibSize];

		b2a_fill_payload(p_out_stored, kB2A_StoredSize);
		b2a_fill_payload(p_out_zstd, kB2A_ZstdSize);
		b2a_fill_payload(p_out_zlib, kB2A_ZlibSize);

		const kpack_writer_entry_t entries[] = {
			{kB2A_Name_Stored, p_out_stored, kB2A_StoredSize,
			 eKpackCompression::kStored},
			{kB2A_Name_Zstd, p_out_zstd, kB2A_ZstdSize,
			 eKpackCompression::kZstd},
			{kB2A_Name_Zlib, p_out_zlib, kB2A_ZlibSize,
			 eKpackCompression::kZlib},
		};

		return kpack_write_file(pack_path.c_str(), entries, 3);
	}
} // namespace

TEST(Filesystem, test_b2a_pack_write_read_roundtrip)
{
	ktkFrameworkConfig cfg;
	ktkFileSystem instance;

	instance.Initialize(&cfg);

	ktk_filesystem_path pack_path;
	instance.Make_Path(
		pack_path, eFolderIndex::kFolderIndex_DataUser_Tests
	);
	pack_path /= "b2a_mixed.kpack";

	std::error_code ec;
	std::filesystem::remove(
		std::filesystem::path(pack_path.c_str()), ec
	);

	kun_ktk uint8_t* payload_stored = nullptr;
	kun_ktk uint8_t* payload_zstd = nullptr;
	kun_ktk uint8_t* payload_zlib = nullptr;

	ASSERT_TRUE(
		b2a_write_mixed_pack(
			pack_path, payload_stored, payload_zstd, payload_zlib
		)
	);

	// mounting through the real filesystem instance also drives the
	// priority-list prepend (pack-first, the documented default)
	ASSERT_TRUE(instance.Mount_Pack(pack_path));
	EXPECT_TRUE(instance.Get_Pack()->Get_MountedPackCount() == 1);

	struct read_case_t
	{
		const char* p_name;
		const kun_ktk uint8_t* p_payload;
		kun_ktk size_t size;
	};

	const read_case_t cases[] = {
		{kB2A_Name_Stored, payload_stored, kB2A_StoredSize},
		{kB2A_Name_Zstd, payload_zstd, kB2A_ZstdSize},
		{kB2A_Name_Zlib, payload_zlib, kB2A_ZlibSize},
	};

	ktk_filesystem_path folder;
	instance.Make_Path(
		folder, eFolderIndex::kFolderIndex_DataUser_Tests
	);

	for (const auto& read_case : cases)
	{
		ktk_filesystem_path path = folder;
		path /= (read_case.p_name + strlen("data_user/tests/"));

		// Get_FileSize through the dispatcher (pack-first effective
		// order after the prepend)
		kun_ktk size_t queried_size = 0;
		EXPECT_TRUE(instance.Get_FileSize(path, queried_size));
		EXPECT_TRUE(queried_size == read_case.size);

		kun_ktk uint8_t* readback =
			new kun_ktk uint8_t[read_case.size + 64];
		kun_ktk uint8_t* p_readback = readback;
		kun_ktk size_t readback_size = read_case.size + 64;

		// the mounted-backend roundtrip: byte-identical per entry
		ASSERT_TRUE(
			instance.Read_File(path, p_readback, readback_size)
		);
		EXPECT_TRUE(readback_size == read_case.size);
		EXPECT_TRUE(p_readback == readback);
		// the native-parity terminator (room permitting)
		EXPECT_TRUE(readback[read_case.size] == 0);
		EXPECT_TRUE(
			b2a_bytes_equal(
				readback, read_case.p_payload, read_case.size
			)
		);

		delete[] readback;
	}

	// the backend's own API reports the tri-state success too
	{
		ktk_filesystem_path path = folder;
		path /= (kB2A_Name_Zstd + strlen("data_user/tests/"));

		kun_ktk uint8_t readback[kB2A_ZstdSize];
		kun_ktk size_t readback_size = sizeof(readback);

		EXPECT_TRUE(
			instance.Get_Pack()->Read_File(
				path, readback, readback_size
			) == eKpackReadResult::kSuccess
		);
		EXPECT_TRUE(readback_size == kB2A_ZstdSize);
	}

	// the B0 too-small contract holds on the pack path, INCLUDING the
	// required size surviving the chain (a found-but-too-small entry
	// stops the override chain — absence is the only fallthrough)
	{
		ktk_filesystem_path path = folder;
		path /= (kB2A_Name_Zlib + strlen("data_user/tests/"));

		kun_ktk uint8_t tiny[16];
		kun_ktk uint8_t* p_tiny = tiny;
		kun_ktk size_t tiny_size = sizeof(tiny);

		EXPECT_FALSE(instance.Read_File(path, p_tiny, tiny_size));
		EXPECT_TRUE(tiny_size == kB2A_ZlibSize);
		EXPECT_TRUE(p_tiny == tiny);
	}

	delete[] payload_stored;
	delete[] payload_zstd;
	delete[] payload_zlib;

	// Shutdown BEFORE removing the fixture: the mount holds the pack
	// file open until UnmountAll, and Windows refuses to delete an open
	// file
	instance.Shutdown();

	ec.clear();
	std::filesystem::remove(
		std::filesystem::path(pack_path.c_str()), ec
	);
}

TEST(Filesystem, test_b2a_pack_block_reads_match_full_read)
{
	ktkFrameworkConfig cfg;
	ktkFileSystem instance;

	instance.Initialize(&cfg);

	ktk_filesystem_path pack_path;
	instance.Make_Path(
		pack_path, eFolderIndex::kFolderIndex_DataUser_Tests
	);
	pack_path /= "b2a_blocks.kpack";

	std::error_code ec;
	std::filesystem::remove(
		std::filesystem::path(pack_path.c_str()), ec
	);

	kun_ktk uint8_t* payload_stored = nullptr;
	kun_ktk uint8_t* payload_zstd = nullptr;
	kun_ktk uint8_t* payload_zlib = nullptr;

	ASSERT_TRUE(
		b2a_write_mixed_pack(
			pack_path, payload_stored, payload_zstd, payload_zlib
		)
	);
	ASSERT_TRUE(instance.Mount_Pack(pack_path));

	ktk_filesystem_path folder;
	instance.Make_Path(
		folder, eFolderIndex::kFolderIndex_DataUser_Tests
	);

	// the zlib entry: 3 full 64 KB blocks + a 3,405-byte tail = 4 blocks
	constexpr kun_ktk size_t kExpectedBlocks = 4;
	static_assert(
		kB2A_ZlibSize / KOTEK_DEF_FILESYSTEM_PACK_BLOCK_SIZE + 1 ==
		kExpectedBlocks
	);

	ktk_filesystem_path zlib_path = folder;
	zlib_path /= (kB2A_Name_Zlib + strlen("data_user/tests/"));

	kun_ktk uint8_t block_buffer[KOTEK_DEF_FILESYSTEM_PACK_BLOCK_SIZE];

	for (kun_ktk uint32_t block = 0; block < kExpectedBlocks; ++block)
	{
		kun_ktk size_t block_size = sizeof(block_buffer);

		EXPECT_TRUE(
			instance.Get_Pack()->Read_File_Block(
				zlib_path, block, block_buffer, block_size
			) == eKpackReadResult::kSuccess
		);

		const kun_ktk size_t expected_size =
			(block == kExpectedBlocks - 1)
			? (kB2A_ZlibSize -
		       block * KOTEK_DEF_FILESYSTEM_PACK_BLOCK_SIZE)
			: KOTEK_DEF_FILESYSTEM_PACK_BLOCK_SIZE;

		EXPECT_TRUE(block_size == expected_size);
		EXPECT_TRUE(
			b2a_bytes_equal(
				block_buffer,
				payload_zlib +
					block * KOTEK_DEF_FILESYSTEM_PACK_BLOCK_SIZE,
				expected_size
			)
		);
	}

	// a stored entry's single block is the raw span itself
	{
		ktk_filesystem_path stored_path = folder;
		stored_path /= (kB2A_Name_Stored + strlen("data_user/tests/"));

		kun_ktk size_t block_size = sizeof(block_buffer);

		EXPECT_TRUE(
			instance.Get_Pack()->Read_File_Block(
				stored_path, 0, block_buffer, block_size
			) == eKpackReadResult::kSuccess
		);
		EXPECT_TRUE(block_size == kB2A_StoredSize);
		EXPECT_TRUE(
			b2a_bytes_equal(block_buffer, payload_stored, kB2A_StoredSize)
		);
	}

	// the 64 KB-exact zstd entry is exactly one full block
	{
		ktk_filesystem_path zstd_path = folder;
		zstd_path /= (kB2A_Name_Zstd + strlen("data_user/tests/"));

		kun_ktk size_t block_size = sizeof(block_buffer);

		EXPECT_TRUE(
			instance.Get_Pack()->Read_File_Block(
				zstd_path, 0, block_buffer, block_size
			) == eKpackReadResult::kSuccess
		);
		EXPECT_TRUE(block_size == kB2A_ZstdSize);
		EXPECT_TRUE(
			b2a_bytes_equal(block_buffer, payload_zstd, kB2A_ZstdSize)
		);

		// a block index past the entry's block count is a loud caller
		// error, not a read
		EXPECT_TRUE(
			instance.Get_Pack()->Read_File_Block(
				zstd_path, 1, block_buffer, block_size
			) == eKpackReadResult::kCorrupt
		);
	}

	// a too-small block buffer reports the REQUIRED block size
	{
		kun_ktk uint8_t tiny[8];
		kun_ktk size_t tiny_size = sizeof(tiny);

		EXPECT_TRUE(
			instance.Get_Pack()->Read_File_Block(
				zlib_path, 0, tiny, tiny_size
			) == eKpackReadResult::kTooSmall
		);
		EXPECT_TRUE(
			tiny_size ==
			static_cast<kun_ktk size_t>(
				KOTEK_DEF_FILESYSTEM_PACK_BLOCK_SIZE
			)
		);
	}

	delete[] payload_stored;
	delete[] payload_zstd;
	delete[] payload_zlib;

	// Shutdown BEFORE removing the fixture (the mount holds the pack
	// file open)
	instance.Shutdown();

	ec.clear();
	std::filesystem::remove(
		std::filesystem::path(pack_path.c_str()), ec
	);
}

TEST(Filesystem, test_b2a_pack_fallthrough_and_priority_order)
{
	ktkFrameworkConfig cfg;
	ktkFileSystem instance;

	instance.Initialize(&cfg);

	ktk_filesystem_path folder;
	instance.Make_Path(
		folder, eFolderIndex::kFolderIndex_DataUser_Tests
	);

	ktk_filesystem_path shared_path = folder;
	shared_path /= "b2a_shared.bin";

	ktk_filesystem_path pack_path = folder;
	pack_path /= "b2a_priority.kpack";

	std::error_code ec;
	std::filesystem::remove(
		std::filesystem::path(shared_path.c_str()), ec
	);
	ec.clear();
	std::filesystem::remove(
		std::filesystem::path(pack_path.c_str()), ec
	);

	// the SAME root-relative name exists in the pack AND on native disk
	const char pack_payload[] = "PACK-BYTES-WIN-OR-LOSE";
	const char native_payload[] = "NATIVE-BYTES-WIN-OR-LOSE";
	const char only_payload[] = "ONLY-IN-THE-PACK";

	const kpack_writer_entry_t entries[] = {
		{"data_user/tests/b2a_shared.bin",
		 reinterpret_cast<const kun_ktk uint8_t*>(pack_payload),
		 sizeof(pack_payload), eKpackCompression::kStored},
		{"data_user/tests/b2a_pack_only.bin",
		 reinterpret_cast<const kun_ktk uint8_t*>(only_payload),
		 sizeof(only_payload), eKpackCompression::kZstd},
	};

	ASSERT_TRUE(
		kpack_write_file(pack_path.c_str(), entries, 2)
	);

	ASSERT_TRUE(
		instance.Write_File(
			shared_path, native_payload, sizeof(native_payload)
		)
	);

	// the mount prepends kPack: the documented default is pack-first
	ASSERT_TRUE(instance.Mount_Pack(pack_path));

	kun_ktk uint8_t readback[128];

	{
		kun_ktk uint8_t* p_readback = readback;
		kun_ktk size_t readback_size = sizeof(readback);

		ASSERT_TRUE(
			instance.Read_File(shared_path, p_readback, readback_size)
		);
		EXPECT_TRUE(readback_size == sizeof(pack_payload));
		EXPECT_TRUE(
			b2a_bytes_equal(
				readback,
				reinterpret_cast<const kun_ktk uint8_t*>(pack_payload),
				sizeof(pack_payload)
			)
		);
	}

	// a pack-only name reads through the dispatcher silently (no native
	// consult once the pack answers)
	{
		ktk_filesystem_path only_path = folder;
		only_path /= "b2a_pack_only.bin";

		kun_ktk uint8_t* p_readback = readback;
		kun_ktk size_t readback_size = sizeof(readback);

		ASSERT_TRUE(
			instance.Read_File(only_path, p_readback, readback_size)
		);
		EXPECT_TRUE(readback_size == sizeof(only_payload));
	}

	// a name that is only on native disk: the pack miss is a SILENT
	// fallthrough and native answers
	{
		ktk_filesystem_path native_only_path = folder;
		native_only_path /= "b2a_native_only.bin";

		const char native_only_payload[] = "ONLY-ON-NATIVE";

		ASSERT_TRUE(
			instance.Write_File(
				native_only_path, native_only_payload,
				sizeof(native_only_payload)
			)
		);

		kun_ktk uint8_t* p_readback = readback;
		kun_ktk size_t readback_size = sizeof(readback);

		ASSERT_TRUE(
			instance.Read_File(
				native_only_path, p_readback, readback_size
			)
		);
		EXPECT_TRUE(readback_size == sizeof(native_only_payload));
		EXPECT_TRUE(
			b2a_bytes_equal(
				readback,
				reinterpret_cast<const kun_ktk uint8_t*>(
					native_only_payload
				),
				sizeof(native_only_payload)
			)
		);

		ec.clear();
		std::filesystem::remove(
			std::filesystem::path(native_only_path.c_str()), ec
		);
	}

	// the explicit ["Native","Pack"] order flips the override: the loose
	// file now shadows the pack entry
	{
		kun_ktk uint8_t native_first[static_cast<kun_ktk uint8_t>(
			eFileSystemPriorityType::kEndOfEnum
		)] = {};
		native_first[0] = static_cast<kun_ktk uint8_t>(
			eFileSystemPriorityType::kNative
		);
		native_first[1] = static_cast<kun_ktk uint8_t>(
			eFileSystemPriorityType::kPack
		);
		cfg.Set_FS_PriorityList(native_first);

		kun_ktk uint8_t* p_readback = readback;
		kun_ktk size_t readback_size = sizeof(readback);

		ASSERT_TRUE(
			instance.Read_File(shared_path, p_readback, readback_size)
		);
		EXPECT_TRUE(readback_size == sizeof(native_payload));
		EXPECT_TRUE(
			b2a_bytes_equal(
				readback,
				reinterpret_cast<const kun_ktk uint8_t*>(native_payload),
				sizeof(native_payload)
			)
		);

		// and the pack entry still answers when native has nothing
		ktk_filesystem_path only_path = folder;
		only_path /= "b2a_pack_only.bin";

		p_readback = readback;
		readback_size = sizeof(readback);

		ASSERT_TRUE(
			instance.Read_File(only_path, p_readback, readback_size)
		);
		EXPECT_TRUE(readback_size == sizeof(only_payload));
	}

	// an unknown name falls through EVERY backend: false + size 0, the
	// B0 shape (one native warning, never an assert)
	{
		ktk_filesystem_path missing_path = folder;
		missing_path /= "b2a_absent_everywhere.bin";

		kun_ktk uint8_t* p_readback = readback;
		kun_ktk size_t readback_size = sizeof(readback);

		EXPECT_FALSE(
			instance.Read_File(missing_path, p_readback, readback_size)
		);
		EXPECT_TRUE(readback_size == 0);

		kun_ktk size_t queried = 123;
		EXPECT_FALSE(instance.Get_FileSize(missing_path, queried));
		EXPECT_TRUE(queried == 0);
	}

	// Shutdown BEFORE removing the fixtures (the mount holds the pack
	// file open)
	instance.Shutdown();

	ec.clear();
	std::filesystem::remove(
		std::filesystem::path(shared_path.c_str()), ec
	);
	ec.clear();
	std::filesystem::remove(
		std::filesystem::path(pack_path.c_str()), ec
	);
}

TEST(Filesystem, test_b2a_pack_corrupt_packs_are_skipped)
{
	ktkFrameworkConfig cfg;
	ktkFileSystem instance;

	instance.Initialize(&cfg);

	ktk_filesystem_path folder;
	instance.Make_Path(
		folder, eFolderIndex::kFolderIndex_DataUser_Tests
	);

	ktk_filesystem_path good_pack = folder;
	good_pack /= "b2a_corrupt_good.kpack";
	ktk_filesystem_path bad_magic = folder;
	bad_magic /= "b2a_corrupt_magic.kpack";
	ktk_filesystem_path truncated = folder;
	truncated /= "b2a_corrupt_truncated.kpack";
	ktk_filesystem_path bogus_codec = folder;
	bogus_codec /= "b2a_corrupt_codec.kpack";

	std::error_code ec;
	for (const auto& path :
	     {good_pack, bad_magic, truncated, bogus_codec})
	{
		ec.clear();
		std::filesystem::remove(
			std::filesystem::path(path.c_str()), ec
		);
	}

	const char payload[] = "i survive every corrupt neighbour";

	const kpack_writer_entry_t entries[] = {
		{"data_user/tests/b2a_survivor.bin",
		 reinterpret_cast<const kun_ktk uint8_t*>(payload),
		 sizeof(payload), eKpackCompression::kZstd},
	};

	ASSERT_TRUE(kpack_write_file(good_pack.c_str(), entries, 1));

	// bad magic
	{
		kun_ktk uint8_t garbage[20] = {};
		garbage[0] = 'N';
		garbage[1] = 'O';
		garbage[2] = 'P';
		garbage[3] = 'E';

		FILE* p_file = fopen(bad_magic.c_str(), "wb");
		ASSERT_TRUE(p_file != nullptr);
		ASSERT_TRUE(fwrite(garbage, 1, sizeof(garbage), p_file) ==
		            sizeof(garbage));
		fclose(p_file);

		EXPECT_FALSE(instance.Mount_Pack(bad_magic));
	}

	// a truncated entry table (a valid header claiming 2 entries, only
	// 10 bytes of table behind it)
	{
		kun_ktk uint8_t header_and_stub[30] = {};
		memcpy(header_and_stub, kKpackMagic, sizeof(kKpackMagic));
		header_and_stub[8] = 2; // entry_count u32 = 2

		FILE* p_file = fopen(truncated.c_str(), "wb");
		ASSERT_TRUE(p_file != nullptr);
		ASSERT_TRUE(
			fwrite(
				header_and_stub, 1, sizeof(header_and_stub), p_file
			) == sizeof(header_and_stub)
		);
		fclose(p_file);

		EXPECT_FALSE(instance.Mount_Pack(truncated));
	}

	// a bogus compression enum in the only entry's record
	{
		ASSERT_TRUE(
			kpack_write_file(bogus_codec.c_str(), entries, 1)
		);

		FILE* p_file = fopen(bogus_codec.c_str(), "r+b");
		ASSERT_TRUE(p_file != nullptr);
		// entry 0's compression byte: 20-byte header + 32
		ASSERT_TRUE(fseek(p_file, 20 + 32, SEEK_SET) == 0);
		const kun_ktk uint8_t bogus = 7;
		ASSERT_TRUE(fwrite(&bogus, 1, 1, p_file) == 1);
		fclose(p_file);

		EXPECT_FALSE(instance.Mount_Pack(bogus_codec));
	}

	// the corrupt neighbours never mounted, and the good pack still
	// mounts + reads
	EXPECT_TRUE(instance.Get_Pack()->Get_MountedPackCount() == 0);

	ASSERT_TRUE(instance.Mount_Pack(good_pack));
	EXPECT_TRUE(instance.Get_Pack()->Get_MountedPackCount() == 1);

	{
		ktk_filesystem_path survivor_path = folder;
		survivor_path /= "b2a_survivor.bin";

		kun_ktk uint8_t readback[64];
		kun_ktk uint8_t* p_readback = readback;
		kun_ktk size_t readback_size = sizeof(readback);

		ASSERT_TRUE(
			instance.Read_File(
				survivor_path, p_readback, readback_size
			)
		);
		EXPECT_TRUE(readback_size == sizeof(payload));
		EXPECT_TRUE(
			b2a_bytes_equal(
				readback,
				reinterpret_cast<const kun_ktk uint8_t*>(payload),
				sizeof(payload)
			)
		);
	}

	// Shutdown BEFORE removing the fixtures (the mount holds the pack
	// file open)
	instance.Shutdown();

	for (const auto& path :
	     {good_pack, bad_magic, truncated, bogus_codec})
	{
		ec.clear();
		std::filesystem::remove(
			std::filesystem::path(path.c_str()), ec
		);
	}
}

TEST(Filesystem, test_b2a_pack_entry_count_overflow_is_clamped)
{
	ktkFrameworkConfig cfg;
	ktkFileSystem instance;

	instance.Initialize(&cfg);

	ktk_filesystem_path folder;
	instance.Make_Path(
		folder, eFolderIndex::kFolderIndex_DataUser_Tests
	);

	ktk_filesystem_path pack_path = folder;
	pack_path /= "b2a_overflow.kpack";

	std::error_code ec;
	std::filesystem::remove(
		std::filesystem::path(pack_path.c_str()), ec
	);

	// one entry past the reader cap — the writer is permissive (the
	// reader owns the mount caps), the mount must clamp loudly and keep
	// the first cap entries readable
	constexpr kun_ktk size_t kEntryCount =
		KOTEK_DEF_FILESYSTEM_PACK_MAX_ENTRIES + 1;

	std::vector<std::string> names(kEntryCount);
	std::vector<kpack_writer_entry_t> entries(kEntryCount);

	kun_ktk uint8_t payload_byte = 0x5A;

	for (kun_ktk size_t i = 0; i < kEntryCount; ++i)
	{
		char name[96];
		std::snprintf(
			name, sizeof(name), "data_user/tests/b2a_cap_%u.bin",
			static_cast<unsigned>(i)
		);
		names[i] = name;

		entries[i].p_name = names[i].c_str();
		entries[i].p_data = &payload_byte;
		entries[i].data_size = 1;
		entries[i].compression = eKpackCompression::kStored;
	}

	ASSERT_TRUE(
		kpack_write_file(
			pack_path.c_str(), entries.data(), entries.size()
		)
	);

	// the clamp: mount SUCCEEDS (one loud error), the excess is dropped
	ASSERT_TRUE(instance.Mount_Pack(pack_path));

	auto p_try_read_entry = [&](kun_ktk size_t index) -> bool
	{
		char name[96];
		std::snprintf(
			name, sizeof(name), "b2a_cap_%u.bin",
			static_cast<unsigned>(index)
		);

		ktk_filesystem_path path = folder;
		path /= name;

		kun_ktk uint8_t readback[8];
		kun_ktk size_t readback_size = sizeof(readback);

		return instance.Get_Pack()->Read_File(
				   path, readback, readback_size
			   ) == eKpackReadResult::kSuccess &&
			readback_size == 1 && readback[0] == payload_byte;
	};

	// the first cap entries all read
	EXPECT_TRUE(p_try_read_entry(0));
	EXPECT_TRUE(
		p_try_read_entry(KOTEK_DEF_FILESYSTEM_PACK_MAX_ENTRIES / 2)
	);
	EXPECT_TRUE(
		p_try_read_entry(KOTEK_DEF_FILESYSTEM_PACK_MAX_ENTRIES - 1)
	);

	// the excess entry answers not-found (silent fallthrough)
	EXPECT_FALSE(
		p_try_read_entry(KOTEK_DEF_FILESYSTEM_PACK_MAX_ENTRIES)
	);

	// Shutdown BEFORE removing the fixture (the mount holds the pack
	// file open)
	instance.Shutdown();

	ec.clear();
	std::filesystem::remove(
		std::filesystem::path(pack_path.c_str()), ec
	);
}

TEST(Filesystem, test_b2a_pack_empty_pack_mounts_and_answers_nothing)
{
	ktkFrameworkConfig cfg;
	ktkFileSystem instance;

	instance.Initialize(&cfg);

	ktk_filesystem_path folder;
	instance.Make_Path(
		folder, eFolderIndex::kFolderIndex_DataUser_Tests
	);

	ktk_filesystem_path pack_path = folder;
	pack_path /= "b2a_empty.kpack";

	std::error_code ec;
	std::filesystem::remove(
		std::filesystem::path(pack_path.c_str()), ec
	);

	// a 0-entry pack is legal: header only
	ASSERT_TRUE(kpack_write_file(pack_path.c_str(), nullptr, 0));

	ASSERT_TRUE(instance.Mount_Pack(pack_path));
	EXPECT_TRUE(instance.Get_Pack()->Get_MountedPackCount() == 1);

	// every name is a silent not-found for this backend (size-0 miss
	// residue, mirroring the native miss)
	{
		ktk_filesystem_path path = folder;
		path /= "b2a_anything.bin";

		kun_ktk uint8_t readback[16];
		kun_ktk size_t readback_size = sizeof(readback);

		EXPECT_TRUE(
			instance.Get_Pack()->Read_File(
				path, readback, readback_size
			) == eKpackReadResult::kNotFound
		);
		EXPECT_TRUE(readback_size == 0);

		kun_ktk size_t queried = 0;
		EXPECT_TRUE(
			instance.Get_Pack()->Get_FileSize(path, queried) ==
			eKpackReadResult::kNotFound
		);
	}

	// and through the dispatcher the fallthrough still serves native
	// files (the empty pack simply has no opinion)
	ktk_filesystem_path native_path = folder;
	native_path /= "b2a_empty_native.bin";

	{
		const char payload[] = "native keeps working";

		ASSERT_TRUE(
			instance.Write_File(native_path, payload, sizeof(payload))
		);

		kun_ktk uint8_t readback[64];
		kun_ktk uint8_t* p_readback = readback;
		kun_ktk size_t readback_size = sizeof(readback);

		ASSERT_TRUE(
			instance.Read_File(native_path, p_readback, readback_size)
		);
		EXPECT_TRUE(readback_size == sizeof(payload));
	}

	// Shutdown BEFORE removing the fixtures (the mount holds the pack
	// file open)
	instance.Shutdown();

	ec.clear();
	std::filesystem::remove(
		std::filesystem::path(native_path.c_str()), ec
	);
	ec.clear();
	std::filesystem::remove(
		std::filesystem::path(pack_path.c_str()), ec
	);
}

TEST(Filesystem, test_b2a_pack_conventional_folder_mounts_newest_first)
{
	// the conventional data_game/packs folder is the ONE directory walk:
	// packs found there mount at Initialize, NEWEST first (the mount
	// order is the override order). The folder lives outside
	// data_user/tests by necessity (the conventional location is the
	// thing under test) — everything below is removed at the end, and
	// only EXPECTs run after creation so cleanup always executes
	ktkFrameworkConfig probe_cfg;
	ktkFileSystem probe_instance;

	// initialized only for Make_Path (the conventional mount is a no-op
	// while the folder doesn't exist)
	probe_instance.Initialize(&probe_cfg);

	ktk_filesystem_path data_game;
	probe_instance.Make_Path(
		data_game, eFolderIndex::kFolderIndex_DataGame
	);

	ktk_filesystem_path packs_folder = data_game;
	packs_folder /= kKpackPacksFolderName;

	ktk_filesystem_path older_pack = packs_folder;
	older_pack /= "b2a_conv_older.kpack";
	ktk_filesystem_path newer_pack = packs_folder;
	newer_pack /= "b2a_conv_newer.kpack";

	std::error_code ec;

	// pre-clean (a previous crashed run must not pollute this one)
	std::filesystem::remove(
		std::filesystem::path(older_pack.c_str()), ec
	);
	ec.clear();
	std::filesystem::remove(
		std::filesystem::path(newer_pack.c_str()), ec
	);
	ec.clear();
	std::filesystem::remove(
		std::filesystem::path(packs_folder.c_str()), ec
	);
	ec.clear();

	ASSERT_TRUE(
		std::filesystem::create_directories(
			std::filesystem::path(packs_folder.c_str()), ec
		) || std::filesystem::exists(
			std::filesystem::path(packs_folder.c_str())
		)
	);

	// the same entry name in both packs with different payloads
	const char older_payload[] = "OLDER-PACK-BYTES";
	const char newer_payload[] = "NEWER-PACK-BYTES!!";

	const kpack_writer_entry_t older_entries[] = {
		{"data_user/tests/b2a_conv_shared.bin",
		 reinterpret_cast<const kun_ktk uint8_t*>(older_payload),
		 sizeof(older_payload), eKpackCompression::kStored},
	};
	const kpack_writer_entry_t newer_entries[] = {
		{"data_user/tests/b2a_conv_shared.bin",
		 reinterpret_cast<const kun_ktk uint8_t*>(newer_payload),
		 sizeof(newer_payload), eKpackCompression::kStored},
	};

	ASSERT_TRUE(
		kpack_write_file(older_pack.c_str(), older_entries, 1)
	);
	ASSERT_TRUE(
		kpack_write_file(newer_pack.c_str(), newer_entries, 1)
	);

	// mark the timestamps explicitly: the older pack is set to the epoch,
	// the newer keeps its natural just-written mtime
	std::filesystem::last_write_time(
		std::filesystem::path(older_pack.c_str()),
		std::filesystem::file_time_type(
			std::filesystem::file_time_type::duration::zero()
		),
		ec
	);
	ec.clear();

	probe_instance.Shutdown();

	ktkFrameworkConfig cfg;
	ktkFileSystem instance;

	// Initialize drives the conventional mount (newest-first)
	instance.Initialize(&cfg);

	EXPECT_TRUE(instance.Get_Pack()->Get_MountedPackCount() == 2);

	// the priority prepend happened: pack-first is the effective order
	EXPECT_TRUE(
		cfg.Get_FS_PriorityList()[0] ==
		static_cast<kun_ktk uint8_t>(eFileSystemPriorityType::kPack)
	);

	// the shared name resolves to the NEWEST pack's bytes
	ktk_filesystem_path shared_path;
	instance.Make_Path(
		shared_path, eFolderIndex::kFolderIndex_DataUser_Tests
	);
	shared_path /= "b2a_conv_shared.bin";

	kun_ktk uint8_t readback[64];
	kun_ktk uint8_t* p_readback = readback;
	kun_ktk size_t readback_size = sizeof(readback);

	EXPECT_TRUE(instance.Read_File(shared_path, p_readback, readback_size));
	EXPECT_TRUE(readback_size == sizeof(newer_payload));
	EXPECT_TRUE(
		b2a_bytes_equal(
			readback,
			reinterpret_cast<const kun_ktk uint8_t*>(newer_payload),
			sizeof(newer_payload)
		)
	);

	instance.Shutdown();

	// self-clean: the conventional folder returns to its shipped (no
	// packs) state — a second instance must mount NOTHING
	ec.clear();
	std::filesystem::remove(
		std::filesystem::path(older_pack.c_str()), ec
	);
	ec.clear();
	std::filesystem::remove(
		std::filesystem::path(newer_pack.c_str()), ec
	);
	ec.clear();
	std::filesystem::remove(
		std::filesystem::path(packs_folder.c_str()), ec
	);

	ktkFrameworkConfig cfg_after;
	ktkFileSystem instance_after;

	instance_after.Initialize(&cfg_after);

	EXPECT_TRUE(
		instance_after.Get_Pack()->Get_MountedPackCount() == 0
	);
	EXPECT_TRUE(
		cfg_after.Get_FS_PriorityList()[0] ==
		static_cast<kun_ktk uint8_t>(eFileSystemPriorityType::kNative)
	);

	instance_after.Shutdown();
}

// --- B2b zircon_kpacker tool: the mutation matrix -----------------------
// the tool's OWN logic (kotek.core.filesystem.pack's kpack_write_file is
// the only encoder) is driven in-proc for the deterministic matrix; ONE
// end-to-end suite shells out to the built zircon_kpacker.exe for the real
// CLI (pack -> list -> add -> remove -> verify). Same fixture discipline
// as B0/B1/B2a (data_user/tests, self-cleaning).

namespace
{
	constexpr const char* kB2B_Name_Readme =
		"data_user/tests/b2b_mut/readme.txt";
	constexpr const char* kB2B_Name_Config =
		"data_user/tests/b2b_mut/config.json";
	constexpr const char* kB2B_Name_Blob = "data_user/tests/b2b_mut/blob.bin";
	constexpr const char* kB2B_Name_Added =
		"data_user/tests/b2b_mut/added.txt";

	constexpr kun_ktk size_t kB2B_BlobSize =
		KOTEK_DEF_FILESYSTEM_PACK_BLOCK_SIZE * 3 + 3403;

	constexpr const char kB2B_ReadmePayload[] =
		"b2b mutation readme payload\n";
	constexpr const char kB2B_ConfigPayload[] =
		"{\n  \"mutation\": true,\n  \"entries\": [1, 2, 3]\n}\n";
	constexpr const char kB2B_AddedPayload[] =
		"added through the wholesale rewrite\n";

	/// reads one entry's raw bytes through the mounted backend (the
	/// mutation model's read half); nullptr + 0 on miss (never here)
	kun_ktk uint8_t* b2b_read_entry(
		ktkFileSystem& instance,
		const ktk_filesystem_path& folder,
		const char* p_name,
		kun_ktk size_t known_size
	)
	{
		ktk_filesystem_path path = folder;
		path /= (p_name + strlen("data_user/tests/"));

		kun_ktk uint8_t* p_bytes = new kun_ktk uint8_t[known_size + 1];
		kun_ktk size_t size = known_size + 1;

		const eKpackReadResult result =
			instance.Get_Pack()->Read_File(path, p_bytes, size);

		if (result != eKpackReadResult::kSuccess || size != known_size)
		{
			delete[] p_bytes;
			return nullptr;
		}

		return p_bytes;
	}
} // namespace

TEST(Filesystem, test_b2b_pack_mutation_rewrite_matrix_inproc)
{
	// the OFFLINE mutation model the zircon_kpacker tool implements
	// (owner requirement): read the existing entry set back, REWRITE the
	// pack wholesale through the shared encoder — pack -> add -> remove,
	// the reader seeing exactly the new set after every step; the verify
	// analog closes the test (every block of every remaining entry
	// decompresses to the full-read bytes)
	ktkFrameworkConfig cfg;
	ktkFileSystem instance;

	instance.Initialize(&cfg);

	ktk_filesystem_path folder;
	instance.Make_Path(
		folder, eFolderIndex::kFolderIndex_DataUser_Tests
	);

	ktk_filesystem_path pack_path = folder;
	pack_path /= "b2b_mut.kpack";

	std::error_code ec;
	std::filesystem::remove(
		std::filesystem::path(pack_path.c_str()), ec
	);
	ec.clear();

	kun_ktk uint8_t* payload_blob =
		new kun_ktk uint8_t[kB2B_BlobSize];
	b2a_fill_payload(payload_blob, kB2B_BlobSize);

	// pack: three entries, one per codec (the zlib blob crosses three
	// full blocks + a tail)
	const kpack_writer_entry_t initial_entries[] = {
		{kB2B_Name_Readme,
		 reinterpret_cast<const kun_ktk uint8_t*>(kB2B_ReadmePayload),
		 sizeof(kB2B_ReadmePayload), eKpackCompression::kStored},
		{kB2B_Name_Config,
		 reinterpret_cast<const kun_ktk uint8_t*>(kB2B_ConfigPayload),
		 sizeof(kB2B_ConfigPayload), eKpackCompression::kZstd},
		{kB2B_Name_Blob, payload_blob, kB2B_BlobSize,
		 eKpackCompression::kZlib},
	};

	ASSERT_TRUE(
		kpack_write_file(pack_path.c_str(), initial_entries, 3)
	);
	ASSERT_TRUE(instance.Mount_Pack(pack_path));

	struct expected_entry_t
	{
		const char* p_name;
		const kun_ktk uint8_t* p_payload;
		kun_ktk size_t size;
		eKpackCompression compression;
	};

	const expected_entry_t expected_after_add[] = {
		{kB2B_Name_Readme,
		 reinterpret_cast<const kun_ktk uint8_t*>(kB2B_ReadmePayload),
		 sizeof(kB2B_ReadmePayload), eKpackCompression::kStored},
		{kB2B_Name_Config,
		 reinterpret_cast<const kun_ktk uint8_t*>(kB2B_ConfigPayload),
		 sizeof(kB2B_ConfigPayload), eKpackCompression::kZstd},
		{kB2B_Name_Blob, payload_blob, kB2B_BlobSize,
		 eKpackCompression::kZlib},
		{kB2B_Name_Added,
		 reinterpret_cast<const kun_ktk uint8_t*>(kB2B_AddedPayload),
		 sizeof(kB2B_AddedPayload), eKpackCompression::kZstd},
	};

	// ADD: read the current set back through the reader, rewrite
	// wholesale with one more entry (unmount first — a mount holds the
	// pack file open on Windows)
	{
		kun_ktk uint8_t* kept[3] = {};

		for (kun_ktk size_t i = 0; i < 3; ++i)
		{
			kept[i] = b2b_read_entry(
				instance, folder, initial_entries[i].p_name,
				initial_entries[i].data_size
			);
			ASSERT_TRUE(kept[i] != nullptr);
		}

		instance.Get_Pack()->UnmountAll();

		const kpack_writer_entry_t rewritten[] = {
			{kB2B_Name_Readme, kept[0], sizeof(kB2B_ReadmePayload),
			 eKpackCompression::kStored},
			{kB2B_Name_Config, kept[1], sizeof(kB2B_ConfigPayload),
			 eKpackCompression::kZstd},
			{kB2B_Name_Blob, kept[2], kB2B_BlobSize,
			 eKpackCompression::kZlib},
			{kB2B_Name_Added,
			 reinterpret_cast<const kun_ktk uint8_t*>(
				 kB2B_AddedPayload),
			 sizeof(kB2B_AddedPayload), eKpackCompression::kZstd},
		};

		ASSERT_TRUE(
			kpack_write_file(pack_path.c_str(), rewritten, 4)
		);

		delete[] kept[0];
		delete[] kept[1];
		delete[] kept[2];

		ASSERT_TRUE(instance.Mount_Pack(pack_path));
	}

	// the reader sees EXACTLY the new set: every old entry byte-identical,
	// the added entry present, a probe name a silent miss
	for (const auto& expected : expected_after_add)
	{
		ktk_filesystem_path path = folder;
		path /= (expected.p_name + strlen("data_user/tests/"));

		kun_ktk uint8_t* readback =
			new kun_ktk uint8_t[expected.size + 1];
		kun_ktk uint8_t* p_readback = readback;
		kun_ktk size_t readback_size = expected.size + 1;

		EXPECT_TRUE(
			instance.Read_File(path, p_readback, readback_size)
		);
		EXPECT_TRUE(readback_size == expected.size);
		EXPECT_TRUE(
			b2a_bytes_equal(
				readback, expected.p_payload, expected.size
			)
		);

		delete[] readback;
	}

	{
		ktk_filesystem_path probe = folder;
		probe /= "b2b_mut/never_packed.txt";

		kun_ktk uint8_t scratch[16];
		kun_ktk size_t scratch_size = sizeof(scratch);

		EXPECT_TRUE(
			instance.Get_Pack()->Read_File(probe, scratch, scratch_size
		    ) == eKpackReadResult::kNotFound
		);
	}

	// REMOVE: same wholesale rewrite minus the config entry
	{
		kun_ktk uint8_t* kept[3] = {};

		kept[0] = b2b_read_entry(
			instance, folder, kB2B_Name_Readme,
			sizeof(kB2B_ReadmePayload)
		);
		kept[1] = b2b_read_entry(
			instance, folder, kB2B_Name_Blob, kB2B_BlobSize
		);
		kept[2] = b2b_read_entry(
			instance, folder, kB2B_Name_Added,
			sizeof(kB2B_AddedPayload)
		);

		ASSERT_TRUE(
			kept[0] != nullptr && kept[1] != nullptr &&
			kept[2] != nullptr
		);

		instance.Get_Pack()->UnmountAll();

		const kpack_writer_entry_t rewritten[] = {
			{kB2B_Name_Readme, kept[0], sizeof(kB2B_ReadmePayload),
			 eKpackCompression::kStored},
			{kB2B_Name_Blob, kept[1], kB2B_BlobSize,
			 eKpackCompression::kZlib},
			{kB2B_Name_Added, kept[2], sizeof(kB2B_AddedPayload),
			 eKpackCompression::kZstd},
		};

		ASSERT_TRUE(
			kpack_write_file(pack_path.c_str(), rewritten, 3)
		);

		delete[] kept[0];
		delete[] kept[1];
		delete[] kept[2];

		ASSERT_TRUE(instance.Mount_Pack(pack_path));
	}

	// the exact set again: the removed name is a silent miss, the three
	// survivors byte-identical
	{
		ktk_filesystem_path removed_path = folder;
		removed_path /= (kB2B_Name_Config + strlen("data_user/tests/"));

		kun_ktk uint8_t scratch[16];
		kun_ktk size_t scratch_size = sizeof(scratch);

		EXPECT_TRUE(
			instance.Get_Pack()->Read_File(
				removed_path, scratch, scratch_size
			) == eKpackReadResult::kNotFound
		);
	}

	const expected_entry_t expected_after_remove[] = {
		{kB2B_Name_Readme,
		 reinterpret_cast<const kun_ktk uint8_t*>(kB2B_ReadmePayload),
		 sizeof(kB2B_ReadmePayload), eKpackCompression::kStored},
		{kB2B_Name_Blob, payload_blob, kB2B_BlobSize,
		 eKpackCompression::kZlib},
		{kB2B_Name_Added,
		 reinterpret_cast<const kun_ktk uint8_t*>(kB2B_AddedPayload),
		 sizeof(kB2B_AddedPayload), eKpackCompression::kZstd},
	};

	// the verify analog: full read + EVERY block of every entry decoded
	// to the full-read span (the tool's verify gate driven in-proc)
	for (const auto& expected : expected_after_remove)
	{
		ktk_filesystem_path path = folder;
		path /= (expected.p_name + strlen("data_user/tests/"));

		kun_ktk uint8_t* full = new kun_ktk uint8_t[expected.size + 1];
		kun_ktk size_t full_size = expected.size + 1;

		EXPECT_TRUE(
			instance.Get_Pack()->Read_File(path, full, full_size) ==
			eKpackReadResult::kSuccess
		);
		EXPECT_TRUE(full_size == expected.size);

		const kun_ktk uint64_t block_count =
			kpack_block_count_for_size(expected.size);

		for (kun_ktk uint32_t b = 0; b < block_count; ++b)
		{
			kun_ktk uint8_t block
				[KOTEK_DEF_FILESYSTEM_PACK_BLOCK_SIZE];
			kun_ktk size_t block_size = sizeof(block);

			EXPECT_TRUE(
				instance.Get_Pack()->Read_File_Block(
					path, b, block, block_size
				) == eKpackReadResult::kSuccess
			);

			const kun_ktk uint64_t expected_block_size64 =
				expected.size -
				static_cast<kun_ktk uint64_t>(b) *
					KOTEK_DEF_FILESYSTEM_PACK_BLOCK_SIZE;
			const kun_ktk size_t expected_block_size =
				static_cast<kun_ktk size_t>(
					expected_block_size64 <
							KOTEK_DEF_FILESYSTEM_PACK_BLOCK_SIZE
						? expected_block_size64
						: KOTEK_DEF_FILESYSTEM_PACK_BLOCK_SIZE
				);

			EXPECT_TRUE(block_size == expected_block_size);
			EXPECT_TRUE(
				b2a_bytes_equal(
					block,
					full +
						static_cast<kun_ktk size_t>(b) *
							KOTEK_DEF_FILESYSTEM_PACK_BLOCK_SIZE,
					expected_block_size
				)
			);
		}

		delete[] full;
	}

	delete[] payload_blob;

	// Shutdown BEFORE removing the fixture (the mount holds the pack file
	// open)
	instance.Shutdown();

	ec.clear();
	std::filesystem::remove(
		std::filesystem::path(pack_path.c_str()), ec
	);
}

TEST(Filesystem, test_b2b_tool_end_to_end)
{
	// ONE real CLI run of the built zircon_kpacker (the B2b host tool):
	// pack (with the extensions filter) -> list -> add -> remove -> verify
	// all exit 0, then the final pack is mounted in-proc and the reader
	// sees exactly the expected set. The tool exe lives in the engine
	// build tree (cmake/zircon_kpacker.cmake's nested configure) — the
	// suite SKIPS when no candidate exists (a kotek-only consumer has no
	// tool, the in-proc suite above still covers the mutation model)
	const char* candidate_paths[] = {
		"build/zircon_tools_kpacker/Debug/zircon_kpacker.exe",
		"build-gfxdev/zircon_tools_kpacker/Debug/zircon_kpacker.exe",
	};

	std::filesystem::path tool_path;

	for (const char* p_candidate : candidate_paths)
	{
		std::error_code ec;

		if (std::filesystem::exists(
			    std::filesystem::path(p_candidate), ec
		    ))
		{
			tool_path = p_candidate;
			break;
		}
	}

	if (tool_path.empty())
	{
		GTEST_SKIP() << "zircon_kpacker.exe not found in the known build "
		                "trees";
	}

	ktkFrameworkConfig cfg;
	ktkFileSystem instance;

	instance.Initialize(&cfg);

	ktk_filesystem_path folder;
	instance.Make_Path(
		folder, eFolderIndex::kFolderIndex_DataUser_Tests
	);

	ktk_filesystem_path fixture_dir = folder;
	fixture_dir /= "b2b_tool";

	ktk_filesystem_path pack_path = folder;
	pack_path /= "b2b_tool.kpack";

	// pre-clean (a crashed previous run must not pollute this one)
	std::error_code ec;
	std::filesystem::remove_all(
		std::filesystem::path(fixture_dir.c_str()), ec
	);
	ec.clear();
	std::filesystem::remove(
		std::filesystem::path(pack_path.c_str()), ec
	);
	ec.clear();

	ASSERT_TRUE(std::filesystem::create_directories(
		std::filesystem::path(fixture_dir.c_str()) / "sub", ec
	));

	// the fixture tree: mixed file types, one multi-block binary, one
	// file the extensions filter must drop
	const char app_json_payload[] =
		"{\n  \"tool\": \"zircon_kpacker\"\n}\n";
	const char notes_payload[] = "notes for the tool test\n";
	const char late_payload[] = "{\"late\": true}\n";
	const char skip_payload[] = "filtered out\n";

	constexpr kun_ktk size_t blob_size = 140000;

	kun_ktk uint8_t* payload_blob = new kun_ktk uint8_t[blob_size];
	b2a_fill_payload(payload_blob, blob_size);

	{
		std::ofstream app_json(
			std::filesystem::path(fixture_dir.c_str()) / "app.json",
			std::ios::binary
		);
		app_json.write(app_json_payload, sizeof(app_json_payload));

		std::ofstream notes(
			std::filesystem::path(fixture_dir.c_str()) / "sub" /
				"notes.txt",
			std::ios::binary
		);
		notes.write(notes_payload, sizeof(notes_payload));

		std::ofstream blob(
			std::filesystem::path(fixture_dir.c_str()) / "sub" /
				"blob.bin",
			std::ios::binary
		);
		blob.write(
			reinterpret_cast<const char*>(payload_blob), blob_size
		);

		std::ofstream skip_me(
			std::filesystem::path(fixture_dir.c_str()) / "skip.me",
			std::ios::binary
		);
		skip_me.write(skip_payload, sizeof(skip_payload));

		std::ofstream late(
			std::filesystem::path(folder.c_str()) / "b2b_late.txt",
			std::ios::binary
		);
		late.write(late_payload, sizeof(late_payload));
	}

	// the CLI sequence — the whole command is double-quoted for cmd (the
	// exe path is quoted inside)
	const std::string tool = tool_path.make_preferred().string();

	auto run_tool = [&tool](const std::string& arguments) {
		const std::string command =
			"\"\"" + tool + "\" " + arguments + "\"";
		return std::system(command.c_str());
	};

	const std::string root_arg = std::string(fixture_dir.c_str());
	const std::string pack_arg = std::string(pack_path.c_str());
	const std::string late_arg =
		std::string(folder.c_str()) + "/b2b_late.txt";

	// pack: the filter drops skip.me; the default codec is zstd
	EXPECT_TRUE(
		run_tool("pack --root \"" + root_arg + "\" --out \"" + pack_arg +
		    "\" --extensions .json,.txt,.bin") == 0
	);

	EXPECT_TRUE(run_tool("list --pack \"" + pack_arg + "\"") == 0);

	EXPECT_TRUE(
		run_tool("add --pack \"" + pack_arg + "\" --file \"" + late_arg +
		    "\" --name added/late.txt") == 0
	);

	EXPECT_TRUE(
		run_tool("remove --pack \"" + pack_arg +
		    "\" --name sub/notes.txt") == 0
	);

	EXPECT_TRUE(run_tool("verify --pack \"" + pack_arg + "\"") == 0);

	// the final pack through the real reader: exactly the expected set
	ASSERT_TRUE(instance.Mount_Pack(pack_path));

	struct final_case_t
	{
		const char* p_name;
		const kun_ktk uint8_t* p_payload;
		kun_ktk size_t size;
	};

	const final_case_t present_cases[] = {
		{"app.json",
		 reinterpret_cast<const kun_ktk uint8_t*>(app_json_payload),
		 sizeof(app_json_payload)},
		{"sub/blob.bin", payload_blob, blob_size},
		{"added/late.txt",
		 reinterpret_cast<const kun_ktk uint8_t*>(late_payload),
		 sizeof(late_payload)},
	};

	for (const auto& present : present_cases)
	{
		ktk_filesystem_path path(present.p_name);

		kun_ktk uint8_t* readback =
			new kun_ktk uint8_t[present.size + 1];
		kun_ktk size_t readback_size = present.size + 1;

		EXPECT_TRUE(
			instance.Get_Pack()->Read_File(
				path, readback, readback_size
			) == eKpackReadResult::kSuccess
		);
		EXPECT_TRUE(readback_size == present.size);
		EXPECT_TRUE(
			b2a_bytes_equal(
				readback, present.p_payload, present.size
			)
		);

		delete[] readback;
	}

	// removed / filtered names are silent misses
	const char* absent_names[] = {"sub/notes.txt", "skip.me"};

	for (const char* p_absent : absent_names)
	{
		ktk_filesystem_path path(p_absent);

		kun_ktk uint8_t scratch[16];
		kun_ktk size_t scratch_size = sizeof(scratch);

		EXPECT_TRUE(
			instance.Get_Pack()->Read_File(path, scratch, scratch_size
		    ) == eKpackReadResult::kNotFound
		);
	}

	// the tool embeds the names manifest as a real last entry
	{
		ktk_filesystem_path manifest_path("_kpack_names.json");

		kun_ktk uint8_t scratch[256];
		kun_ktk size_t scratch_size = sizeof(scratch);

		EXPECT_TRUE(
			instance.Get_Pack()->Read_File(
				manifest_path, scratch, scratch_size
			) == eKpackReadResult::kSuccess
		);
	}

	delete[] payload_blob;

	// Shutdown BEFORE the fixture cleanup (the mount holds the file)
	instance.Shutdown();

	ec.clear();
	std::filesystem::remove_all(
		std::filesystem::path(fixture_dir.c_str()), ec
	);
	ec.clear();
	std::filesystem::remove(
		std::filesystem::path(pack_path.c_str()), ec
	);
	ec.clear();
	std::filesystem::remove(
		std::filesystem::path(folder.c_str()) / "b2b_late.txt", ec
	);
}

#endif

	#endif
#endif

void RegisterTests_Filesystem_ForModule_Core()
{
#ifdef KOTEK_USE_TESTS
#endif
}

KOTEK_END_NAMESPACE_CORE KOTEK_END_NAMESPACE_KOTEK
