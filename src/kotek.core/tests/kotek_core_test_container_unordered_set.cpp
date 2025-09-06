#include "../include/kotek_core.h"

#ifdef KOTEK_USE_TESTS
	#ifdef KOTEK_DEBUG
		#include <gtest/gtest.h>
	#endif
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

// Test configurations
using SmallSet =
	kun_ktk hybrid_unordered_set<int, std::hash<int>, std::equal_to<int>, 5, true>;

using SmallSetStd = std::pmr::unordered_set<int>;

using SmallSetNoRealloc = kun_ktk hybrid_unordered_set<int, std::hash<int>,
	std::equal_to<int>, 5, false>;
using DynamicSet =
	kun_ktk hybrid_unordered_set<int, std::hash<int>, std::equal_to<int>, 0, true>;
using StringSet = kun_ktk hybrid_unordered_set<std::string, std::hash<std::string>,
	std::equal_to<std::string>, 3, true>;

// Constructor Tests
TEST(Containers, test_container_hybrid_unordered_set_default_constructor)
{
	SmallSet set;
	EXPECT_TRUE(set.empty());
	EXPECT_EQ(set.size(), 0);
}

TEST(Containers, test_container_hybrid_unordered_set_bucket_count_constructor)
{
	SmallSet set(10);
	EXPECT_GE(set.bucket_count(), 10);
}

TEST(Containers,
	test_container_hybrid_unordered_set_bucket_count_with_hash_constructor)
{
	SmallSet set(10, std::hash<int>());
	EXPECT_GE(set.bucket_count(), 10);
}

TEST(Containers, test_container_hybrid_unordered_set_range_constructor)
{
	std::vector<int> test_data = {1, 2, 3, 4, 5};
	SmallSet set(test_data.begin(), test_data.end(), 10);
	EXPECT_EQ(set.size(), test_data.size());

	for (const auto& item : test_data)
	{
		EXPECT_NE(set.find(item), set.end());
	}
}

TEST(Containers,
	test_container_hybrid_unordered_set_initializer_list_constructor)
{
	SmallSet set{1, 2, 3, 4, 5};
	EXPECT_EQ(set.size(), 5);

	for (int i = 1; i <= 5; i++)
	{
		EXPECT_NE(set.find(i), set.end());
	}
}

TEST(Containers, test_container_hybrid_unordered_set_copy_constructor)
{
	SmallSet original{1, 2, 3};
	SmallSet copy(original);

	EXPECT_EQ(original.size(), copy.size());
	for (const auto& item : original)
	{
		EXPECT_NE(copy.find(item), copy.end());
	}
}

TEST(Containers, test_container_hybrid_unordered_set_move_constructor)
{
	SmallSet original{1, 2, 3};
	SmallSet moved(std::move(original));

	unsigned char mem_org[512];
	unsigned char mem_mov[512];

	std::pmr::monotonic_buffer_resource mr_so{
		mem_org, sizeof(mem_org), std::pmr::get_default_resource()};
	std::pmr::monotonic_buffer_resource mr_sm{
		mem_mov, sizeof(mem_mov), std::pmr::get_default_resource()};

	SmallSetStd std_original{{1, 2, 3}, &mr_so};
	SmallSetStd std_moved(std::move(std_original), &mr_sm);

	EXPECT_EQ(std_moved.size(), 3);
	EXPECT_TRUE(std_original.empty());

	EXPECT_EQ(moved.size(), 3);
	EXPECT_TRUE(original.empty());

	EXPECT_EQ(original.empty(), std_original.empty());
}

// Assignment Operator Tests
TEST(Containers, test_container_hybrid_unordered_set_copy_assignment)
{
	SmallSet original{1, 2, 3};
	SmallSet copy;
	copy = original;

	EXPECT_EQ(original.size(), copy.size());
	for (const auto& item : original)
	{
		EXPECT_NE(copy.find(item), copy.end());
	}
}

TEST(Containers, test_container_hybrid_unordered_set_move_assignment)
{
	SmallSet original{1, 2, 3};
	SmallSet moved;
	moved = std::move(original);

	unsigned char mem_so[512];
	unsigned char mem_sm[512];

	std::pmr::monotonic_buffer_resource mso(
		mem_so, sizeof(mem_so), std::pmr::get_default_resource());
	std::pmr::monotonic_buffer_resource msm(
		mem_sm, sizeof(mem_sm), std::pmr::get_default_resource());

	SmallSetStd std_original{{1, 2, 3}, &mso};
	SmallSetStd std_moved{&msm};

	std_moved = std::move(std_original);

	EXPECT_EQ(std_moved.size(), 3);
	EXPECT_FALSE(std_original.empty());

	EXPECT_EQ(moved.size(), 3);
	EXPECT_FALSE(original.empty());

	EXPECT_EQ(original.empty(), std_original.empty());
}

TEST(
	Containers, test_container_hybrid_unordered_set_initializer_list_assignment)
{
	SmallSet set;
	set = {1, 2, 3, 4, 5};

	EXPECT_EQ(set.size(), 5);
	for (int i = 1; i <= 5; i++)
	{
		EXPECT_NE(set.find(i), set.end());
	}
}

// Iterator Tests
TEST(Containers, test_container_hybrid_unordered_set_iterators)
{
	SmallSet set{1, 2, 3};

	int sum = 0;
	for (auto it = set.begin(); it != set.end(); ++it)
	{
		sum += *it;
	}
	EXPECT_EQ(sum, 6);

	sum = 0;
	for (auto it = set.cbegin(); it != set.cend(); ++it)
	{
		sum += *it;
	}
	EXPECT_EQ(sum, 6);
}

// Capacity Tests
TEST(Containers, test_container_hybrid_unordered_set_empty)
{
	SmallSet empty_set;
	SmallSet non_empty_set{1, 2, 3};

	EXPECT_TRUE(empty_set.empty());
	EXPECT_FALSE(non_empty_set.empty());
}

TEST(Containers, test_container_hybrid_unordered_set_size)
{
	SmallSet set;
	EXPECT_EQ(set.size(), 0);

	set.insert(1);
	EXPECT_EQ(set.size(), 1);

	set.insert(2);
	EXPECT_EQ(set.size(), 2);
}

TEST(Containers, test_container_hybrid_unordered_set_max_size)
{
	SmallSet set;
	EXPECT_GT(set.max_size(), 0);
}

// Modifier Tests
TEST(Containers, test_container_hybrid_unordered_set_clear)
{
	SmallSet set{1, 2, 3};
	EXPECT_FALSE(set.empty());

	set.clear();
	EXPECT_TRUE(set.empty());
}

TEST(Containers, test_container_hybrid_unordered_set_insert_value)
{
	SmallSet set;
	auto result = set.insert(42);

	EXPECT_TRUE(result.second);
	EXPECT_EQ(*result.first, 42);
	EXPECT_EQ(set.size(), 1);
}

TEST(Containers, test_container_hybrid_unordered_set_insert_duplicate)
{
	SmallSet set;
	set.insert(42);
	auto result = set.insert(42);

	EXPECT_FALSE(result.second);
	EXPECT_EQ(set.size(), 1);
}

TEST(Containers, test_container_hybrid_unordered_set_insert_rvalue)
{
	StringSet set;
	std::string value = "test";
	auto result = set.insert(std::move(value));

	EXPECT_TRUE(result.second);
	EXPECT_EQ(*result.first, "test");
	EXPECT_TRUE(value.empty());
}

TEST(Containers, test_container_hybrid_unordered_set_insert_with_hint)
{
	SmallSet set{1, 3};
	auto hint = set.find(3);
	auto result = set.insert(hint, 2);

	EXPECT_EQ(*result, 2);
	EXPECT_EQ(set.size(), 3);
}

TEST(Containers, test_container_hybrid_unordered_set_insert_range)
{
	std::vector<int> test_data = {1, 2, 3, 4, 5};
	SmallSet set;
	set.insert(test_data.begin(), test_data.end());

	EXPECT_EQ(set.size(), test_data.size());
	for (const auto& item : test_data)
	{
		EXPECT_NE(set.find(item), set.end());
	}
}

TEST(Containers, test_container_hybrid_unordered_set_insert_initializer_list)
{
	SmallSet set;
	set.insert({1, 2, 3, 4, 5});

	EXPECT_EQ(set.size(), 5);
	for (int i = 1; i <= 5; i++)
	{
		EXPECT_NE(set.find(i), set.end());
	}
}

TEST(Containers, test_container_hybrid_unordered_set_emplace)
{
	StringSet set;
	auto result = set.emplace("test");

	EXPECT_TRUE(result.second);
	EXPECT_EQ(*result.first, "test");
	EXPECT_EQ(set.size(), 1);
}

TEST(Containers, test_container_hybrid_unordered_set_emplace_hint)
{
	StringSet set;
	set.emplace("first");
	auto hint = set.find("first");
	auto result = set.emplace_hint(hint, "second");

	EXPECT_EQ(*result, "second");
	EXPECT_EQ(set.size(), 2);
}

TEST(Containers, test_container_hybrid_unordered_set_erase_by_iterator)
{
	SmallSet set{1, 2, 3};
	auto it = set.find(2);
	auto next = set.erase(it);

	SmallSetStd std_set{1, 2, 3};
	auto std_it = std_set.find(2);
	auto std_next = std_set.erase(std_it);

	EXPECT_EQ(std_set.size(), 2);
	EXPECT_NE(std_next, std_set.end());

	EXPECT_EQ(set.size(), 2);
	EXPECT_NE(next, set.end());
}

TEST(Containers, test_container_hybrid_unordered_set_erase_by_key)
{
	SmallSet set{1, 2, 3};
	size_t count = set.erase(2);

	EXPECT_EQ(count, 1);
	EXPECT_EQ(set.size(), 2);
	EXPECT_EQ(set.find(2), set.end());
}

TEST(Containers, test_container_hybrid_unordered_set_erase_range)
{
	SmallSet set{1, 2, 3, 4, 5};
	auto first = set.find(2);
	auto last = set.find(5);
	auto next = set.erase(first, last);

	EXPECT_EQ(set.size(), 2);
	EXPECT_EQ(*next, 5);
}

TEST(Containers, test_container_hybrid_unordered_set_swap)
{
	SmallSet set1{1, 2, 3};
	SmallSet set2{4, 5};

	set1.swap(set2);

	EXPECT_EQ(set1.size(), 2);
	EXPECT_EQ(set2.size(), 3);

	EXPECT_NE(set1.find(4), set1.end());
	EXPECT_NE(set2.find(1), set2.end());
}

TEST(Containers, test_container_hybrid_unordered_set_extract_by_iterator)
{
	SmallSet set{1, 2, 3};
	auto it = set.find(2);
	auto node = set.extract(it);

	EXPECT_EQ(set.size(), 2);
	EXPECT_EQ(node.value(), 2);
}

TEST(Containers, test_container_hybrid_unordered_set_extract_by_key)
{
	SmallSet set{1, 2, 3};
	auto node = set.extract(2);

	EXPECT_EQ(set.size(), 2);
	EXPECT_EQ(node.value(), 2);
}

TEST(Containers, test_container_hybrid_unordered_set_merge)
{
	SmallSet set1{1, 2, 3};
	SmallSet set2{3, 4, 5};

	set1.merge(set2);

	EXPECT_EQ(set1.size(), 5);
	EXPECT_EQ(set2.size(), 1);
	EXPECT_NE(set2.find(3), set2.end());
}

// Lookup Tests
TEST(Containers, test_container_hybrid_unordered_set_count)
{
	SmallSet set{1, 2, 3};

	EXPECT_EQ(set.count(2), 1);
	EXPECT_EQ(set.count(99), 0);
}

TEST(Containers, test_container_hybrid_unordered_set_find)
{
	SmallSet set{1, 2, 3};

	auto found = set.find(2);
	EXPECT_NE(found, set.end());
	EXPECT_EQ(*found, 2);

	auto not_found = set.find(99);
	EXPECT_EQ(not_found, set.end());
}

TEST(Containers, test_container_hybrid_unordered_set_equal_range)
{
	SmallSet set{1, 2, 3};

	auto range = set.equal_range(2);
	EXPECT_NE(range.first, range.second);
	EXPECT_EQ(*range.first, 2);

	range = set.equal_range(99);
	EXPECT_EQ(range.first, range.second);
}

// Bucket Interface Tests
TEST(Containers, test_container_hybrid_unordered_set_bucket_count)
{
	SmallSet set;
	EXPECT_GT(set.bucket_count(), 0);
}

TEST(Containers, test_container_hybrid_unordered_set_max_bucket_count)
{
	SmallSet set;
	EXPECT_GT(set.max_bucket_count(), 0);
}

TEST(Containers, test_container_hybrid_unordered_set_bucket_size)
{
	SmallSet set{1, 2, 3};

	for (size_t i = 0; i < set.bucket_count(); i++)
	{
		EXPECT_GE(set.bucket_size(i), 0);
	}
}

TEST(Containers, test_container_hybrid_unordered_set_bucket)
{
	SmallSet set{1, 2, 3};

	for (const auto& item : set)
	{
		size_t bucket = set.bucket(item);
		EXPECT_LT(bucket, set.bucket_count());
	}
}

TEST(Containers, test_container_hybrid_unordered_set_local_iterators)
{
	SmallSet set{1, 2, 3};

	for (size_t i = 0; i < set.bucket_count(); i++)
	{
		auto begin = set.begin(i);
		auto end = set.end(i);

		for (auto it = begin; it != end; ++it)
		{
			EXPECT_NE(set.find(*it), set.end());
		}
	}
}

// Hash Policy Tests
TEST(Containers, test_container_hybrid_unordered_set_load_factor)
{
	SmallSet set{1, 2, 3};
	EXPECT_GT(set.load_factor(), 0.0f);
}

TEST(Containers, test_container_hybrid_unordered_set_max_load_factor)
{
	SmallSet set;
	float original = set.max_load_factor();

	set.max_load_factor(0.5f);
	EXPECT_EQ(set.max_load_factor(), 0.5f);

	set.max_load_factor(original);
}

TEST(Containers, test_container_hybrid_unordered_set_rehash)
{
	SmallSet set{1, 2, 3};
	size_t original_buckets = set.bucket_count();

	set.rehash(original_buckets * 2);
	EXPECT_GE(set.bucket_count(), original_buckets * 2);
}

TEST(Containers, test_container_hybrid_unordered_set_reserve)
{
	SmallSet set;
	set.reserve(100);
	EXPECT_GE(set.bucket_count(), 100);
}

// Observer Tests
TEST(Containers, test_container_hybrid_unordered_set_hash_function)
{
	SmallSet set;
	auto hasher = set.hash_function();
	EXPECT_EQ(hasher(42), std::hash<int>()(42));
}

TEST(Containers, test_container_hybrid_unordered_set_key_eq)
{
	SmallSet set;
	auto key_eq = set.key_eq();
	EXPECT_TRUE(key_eq(42, 42));
}

// Memory Management Tests
TEST(Containers, test_container_hybrid_unordered_set_preallocated_memory_size)
{
	SmallSet set;
	EXPECT_GT(set.preallocated_memory_size(), 0);
}

TEST(Containers, test_container_hybrid_unordered_set_preallocated_size)
{
	SmallSet set;
	EXPECT_EQ(set.preallocated_size(), 5);
}

TEST(Containers, test_container_hybrid_unordered_set_is_reallocation_supported)
{
	EXPECT_TRUE(SmallSet().is_reallocation_supported());
	EXPECT_FALSE(SmallSetNoRealloc().is_reallocation_supported());
}

TEST(Containers, test_container_hybrid_unordered_set_container_access)
{
	SmallSet set{1, 2, 3};

	auto& container = set.container();
	EXPECT_EQ(container.size(), 3);

	const auto& const_container = static_cast<const SmallSet&>(set).container();
	EXPECT_EQ(const_container.size(), 3);
}

TEST(Containers, test_container_hybrid_unordered_set_container_move_out)
{
	SmallSet set{1, 2, 3};
	auto container = set.container_move_out();

	EXPECT_EQ(container.size(), 3);
	EXPECT_TRUE(set.empty());
}

// Comparison with std::unordered_set
TEST(Containers,
	test_container_hybrid_unordered_set_comparison_with_std_unordered_set)
{
	SmallSet hybrid_set;
	std::unordered_set<int> std_set;

	for (int i = 0; i < 100; i++)
	{
		hybrid_set.insert(i);
		std_set.insert(i);
	}

	EXPECT_EQ(hybrid_set.size(), std_set.size());

	for (const auto& item : std_set)
	{
		EXPECT_NE(hybrid_set.find(item), hybrid_set.end());
	}

	EXPECT_GT(hybrid_set.bucket_count(), 0);
	EXPECT_GT(hybrid_set.load_factor(), 0.0f);
}

void RegisterTests_Container_Unordered_Set_Core(void)
{
#ifdef KOTEK_USE_TESTS
	#ifdef KOTEK_DEBUG
		// Test registration handled by gtest
	#endif
#endif
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK