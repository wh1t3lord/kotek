#include "../include/kotek_core.h"

#ifdef KOTEK_USE_TESTS
	#ifdef KOTEK_DEBUG
		#include <filesystem>
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

	#endif
#endif

void RegisterTests_Filesystem_ForModule_Core()
{
#ifdef KOTEK_USE_TESTS
#endif
}

KOTEK_END_NAMESPACE_CORE KOTEK_END_NAMESPACE_KOTEK
