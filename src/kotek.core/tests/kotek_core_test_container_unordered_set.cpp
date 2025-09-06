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
using SmallSetNoRealloc =
	kun_ktk hybrid_unordered_set<int, std::hash<int>, std::equal_to<int>, 5, false>;
using DynamicSet =
	kun_ktk hybrid_unordered_set<int, std::hash<int>, std::equal_to<int>, 0, true>;
using StringSet = kun_ktk hybrid_unordered_set<std::string, std::hash<std::string>,
	std::equal_to<std::string>, 3, true>;

// Test fixture
class HybridUnorderedSetTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
		for (int i = 1; i <= 5; i++)
		{
			test_data.push_back(i);
		}
	}

	std::vector<int> test_data;
};

// Constructor Tests
TEST_F(HybridUnorderedSetTest, DefaultConstructor)
{
	SmallSet set;
	EXPECT_TRUE(set.empty());
	EXPECT_EQ(set.size(), 0);
}

TEST_F(HybridUnorderedSetTest, BucketCountConstructor)
{
	SmallSet set(10);
	EXPECT_GE(set.bucket_count(), 10);
}

TEST_F(HybridUnorderedSetTest, BucketCountWithHashConstructor)
{
	SmallSet set(10, std::hash<int>());
	EXPECT_GE(set.bucket_count(), 10);
}

TEST_F(HybridUnorderedSetTest, RangeConstructor)
{
	SmallSet set(test_data.begin(), test_data.end(), 10);
	EXPECT_EQ(set.size(), test_data.size());

	for (const auto& item : test_data)
	{
		EXPECT_NE(set.find(item), set.end());
	}
}

TEST_F(HybridUnorderedSetTest, InitializerListConstructor)
{
	SmallSet set{1, 2, 3, 4, 5};
	EXPECT_EQ(set.size(), 5);

	for (int i = 1; i <= 5; i++)
	{
		EXPECT_NE(set.find(i), set.end());
	}
}

TEST_F(HybridUnorderedSetTest, CopyConstructor)
{
	SmallSet original{1, 2, 3};
	SmallSet copy(original);

	EXPECT_EQ(original.size(), copy.size());
	for (const auto& item : original)
	{
		EXPECT_NE(copy.find(item), copy.end());
	}
}

TEST_F(HybridUnorderedSetTest, MoveConstructor)
{
	SmallSet original{1, 2, 3};
	SmallSet moved(std::move(original));

	EXPECT_EQ(moved.size(), 3);
	EXPECT_TRUE(original.empty());
}

// Assignment Operator Tests
TEST_F(HybridUnorderedSetTest, CopyAssignment)
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

TEST_F(HybridUnorderedSetTest, MoveAssignment)
{
	SmallSet original{1, 2, 3};
	SmallSet moved;
	moved = std::move(original);

	EXPECT_EQ(moved.size(), 3);
	EXPECT_TRUE(original.empty());
}

TEST_F(HybridUnorderedSetTest, InitializerListAssignment)
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
TEST_F(HybridUnorderedSetTest, Iterators)
{
	SmallSet set{1, 2, 3};

	// Test non-const iterators
	int sum = 0;
	for (auto it = set.begin(); it != set.end(); ++it)
	{
		sum += *it;
	}
	EXPECT_EQ(sum, 6);

	// Test const iterators
	sum = 0;
	for (auto it = set.cbegin(); it != set.cend(); ++it)
	{
		sum += *it;
	}
	EXPECT_EQ(sum, 6);
}

// Capacity Tests
TEST_F(HybridUnorderedSetTest, Empty)
{
	SmallSet empty_set;
	SmallSet non_empty_set{1, 2, 3};

	EXPECT_TRUE(empty_set.empty());
	EXPECT_FALSE(non_empty_set.empty());
}

TEST_F(HybridUnorderedSetTest, Size)
{
	SmallSet set;
	EXPECT_EQ(set.size(), 0);

	set.insert(1);
	EXPECT_EQ(set.size(), 1);

	set.insert(2);
	EXPECT_EQ(set.size(), 2);
}

TEST_F(HybridUnorderedSetTest, MaxSize)
{
	SmallSet set;
	EXPECT_GT(set.max_size(), 0);
}

// Modifier Tests
TEST_F(HybridUnorderedSetTest, Clear)
{
	SmallSet set{1, 2, 3};
	EXPECT_FALSE(set.empty());

	set.clear();
	EXPECT_TRUE(set.empty());
}

TEST_F(HybridUnorderedSetTest, InsertValue)
{
	SmallSet set;
	auto result = set.insert(42);

	EXPECT_TRUE(result.second);
	EXPECT_EQ(*result.first, 42);
	EXPECT_EQ(set.size(), 1);
}

TEST_F(HybridUnorderedSetTest, InsertDuplicate)
{
	SmallSet set;
	set.insert(42);
	auto result = set.insert(42);

	EXPECT_FALSE(result.second);
	EXPECT_EQ(set.size(), 1);
}

TEST_F(HybridUnorderedSetTest, InsertRValue)
{
	StringSet set;
	std::string value = "test";
	auto result = set.insert(std::move(value));

	EXPECT_TRUE(result.second);
	EXPECT_EQ(*result.first, "test");
	EXPECT_TRUE(value.empty()); // Value was moved from
}

TEST_F(HybridUnorderedSetTest, InsertWithHint)
{
	SmallSet set{1, 3};
	auto hint = set.find(3);
	auto result = set.insert(hint, 2);

	EXPECT_EQ(*result, 2);
	EXPECT_EQ(set.size(), 3);
}

TEST_F(HybridUnorderedSetTest, InsertRange)
{
	SmallSet set;
	set.insert(test_data.begin(), test_data.end());

	EXPECT_EQ(set.size(), test_data.size());
	for (const auto& item : test_data)
	{
		EXPECT_NE(set.find(item), set.end());
	}
}

TEST_F(HybridUnorderedSetTest, InsertInitializerList)
{
	SmallSet set;
	set.insert({1, 2, 3, 4, 5});

	EXPECT_EQ(set.size(), 5);
	for (int i = 1; i <= 5; i++)
	{
		EXPECT_NE(set.find(i), set.end());
	}
}

TEST_F(HybridUnorderedSetTest, Emplace)
{
	StringSet set;
	auto result = set.emplace("test");

	EXPECT_TRUE(result.second);
	EXPECT_EQ(*result.first, "test");
	EXPECT_EQ(set.size(), 1);
}

TEST_F(HybridUnorderedSetTest, EmplaceHint)
{
	StringSet set;
	set.emplace("first");
	auto hint = set.find("first");
	auto result = set.emplace_hint(hint, "second");

	EXPECT_EQ(*result, "second");
	EXPECT_EQ(set.size(), 2);
}

TEST_F(HybridUnorderedSetTest, EraseByIterator)
{
	SmallSet set{1, 2, 3};
	auto it = set.find(2);
	auto next = set.erase(it);

	EXPECT_EQ(set.size(), 2);
	EXPECT_NE(next, set.end());
}

TEST_F(HybridUnorderedSetTest, EraseByKey)
{
	SmallSet set{1, 2, 3};
	size_t count = set.erase(2);

	EXPECT_EQ(count, 1);
	EXPECT_EQ(set.size(), 2);
	EXPECT_EQ(set.find(2), set.end());
}

TEST_F(HybridUnorderedSetTest, EraseRange)
{
	SmallSet set{1, 2, 3, 4, 5};
	auto first = set.find(2);
	auto last = set.find(5);
	auto next = set.erase(first, last);

	EXPECT_EQ(set.size(), 2); // 1 and 5 remain
	EXPECT_EQ(*next, 5);
}

TEST_F(HybridUnorderedSetTest, Swap)
{
	SmallSet set1{1, 2, 3};
	SmallSet set2{4, 5};

	set1.swap(set2);

	EXPECT_EQ(set1.size(), 2);
	EXPECT_EQ(set2.size(), 3);

	EXPECT_NE(set1.find(4), set1.end());
	EXPECT_NE(set2.find(1), set2.end());
}

TEST_F(HybridUnorderedSetTest, ExtractByIterator)
{
	SmallSet set{1, 2, 3};
	auto it = set.find(2);
	auto node = set.extract(it);

	EXPECT_EQ(set.size(), 2);
	EXPECT_EQ(node.value(), 2);
}

TEST_F(HybridUnorderedSetTest, ExtractByKey)
{
	SmallSet set{1, 2, 3};
	auto node = set.extract(2);

	EXPECT_EQ(set.size(), 2);
	EXPECT_EQ(node.value(), 2);
}

TEST_F(HybridUnorderedSetTest, Merge)
{
	SmallSet set1{1, 2, 3};
	SmallSet set2{3, 4, 5};

	set1.merge(set2);

	EXPECT_EQ(set1.size(), 5);
	EXPECT_EQ(set2.size(), 1); // Only duplicate remains
	EXPECT_NE(set2.find(3), set2.end());
}

// Lookup Tests
TEST_F(HybridUnorderedSetTest, Count)
{
	SmallSet set{1, 2, 3};

	EXPECT_EQ(set.count(2), 1);
	EXPECT_EQ(set.count(99), 0);
}

TEST_F(HybridUnorderedSetTest, Find)
{
	SmallSet set{1, 2, 3};

	auto found = set.find(2);
	EXPECT_NE(found, set.end());
	EXPECT_EQ(*found, 2);

	auto not_found = set.find(99);
	EXPECT_EQ(not_found, set.end());
}

TEST_F(HybridUnorderedSetTest, EqualRange)
{
	SmallSet set{1, 2, 3};

	auto range = set.equal_range(2);
	EXPECT_NE(range.first, range.second);
	EXPECT_EQ(*range.first, 2);

	range = set.equal_range(99);
	EXPECT_EQ(range.first, range.second);
}

// Bucket Interface Tests
TEST_F(HybridUnorderedSetTest, BucketCount)
{
	SmallSet set;
	EXPECT_GT(set.bucket_count(), 0);
}

TEST_F(HybridUnorderedSetTest, MaxBucketCount)
{
	SmallSet set;
	EXPECT_GT(set.max_bucket_count(), 0);
}

TEST_F(HybridUnorderedSetTest, BucketSize)
{
	SmallSet set{1, 2, 3};

	for (size_t i = 0; i < set.bucket_count(); i++)
	{
		EXPECT_GE(set.bucket_size(i), 0);
	}
}

TEST_F(HybridUnorderedSetTest, Bucket)
{
	SmallSet set{1, 2, 3};

	for (const auto& item : set)
	{
		size_t bucket = set.bucket(item);
		EXPECT_LT(bucket, set.bucket_count());
	}
}

TEST_F(HybridUnorderedSetTest, LocalIterators)
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
TEST_F(HybridUnorderedSetTest, LoadFactor)
{
	SmallSet set{1, 2, 3};
	EXPECT_GT(set.load_factor(), 0.0f);
}

TEST_F(HybridUnorderedSetTest, MaxLoadFactor)
{
	SmallSet set;
	float original = set.max_load_factor();

	set.max_load_factor(0.5f);
	EXPECT_EQ(set.max_load_factor(), 0.5f);

	set.max_load_factor(original);
}

TEST_F(HybridUnorderedSetTest, Rehash)
{
	SmallSet set{1, 2, 3};
	size_t original_buckets = set.bucket_count();

	set.rehash(original_buckets * 2);
	EXPECT_GE(set.bucket_count(), original_buckets * 2);
}

TEST_F(HybridUnorderedSetTest, Reserve)
{
	SmallSet set;
	set.reserve(100);
	EXPECT_GE(set.bucket_count(), 100);
}

// Observer Tests
TEST_F(HybridUnorderedSetTest, HashFunction)
{
	SmallSet set;
	auto hasher = set.hash_function();
	EXPECT_EQ(hasher(42), std::hash<int>()(42));
}

TEST_F(HybridUnorderedSetTest, KeyEq)
{
	SmallSet set;
	auto key_eq = set.key_eq();
	EXPECT_TRUE(key_eq(42, 42));
}

// Memory Management Tests
TEST_F(HybridUnorderedSetTest, PreallocatedMemorySize)
{
	SmallSet set;
	EXPECT_GT(set.preallocated_memory_size(), 0);
}

TEST_F(HybridUnorderedSetTest, PreallocatedSize)
{
	SmallSet set;
	EXPECT_EQ(set.preallocated_size(), 5);
}

TEST_F(HybridUnorderedSetTest, IsReallocationSupported)
{
	EXPECT_TRUE(SmallSet().is_reallocation_supported());
	EXPECT_FALSE(SmallSetNoRealloc().is_reallocation_supported());
}

TEST_F(HybridUnorderedSetTest, ContainerAccess)
{
	SmallSet set{1, 2, 3};

	auto& container = set.container();
	EXPECT_EQ(container.size(), 3);

	const auto& const_container = static_cast<const SmallSet&>(set).container();
	EXPECT_EQ(const_container.size(), 3);
}

TEST_F(HybridUnorderedSetTest, ContainerMoveOut)
{
	SmallSet set{1, 2, 3};
	auto container = set.container_move_out();

	EXPECT_EQ(container.size(), 3);
	EXPECT_TRUE(set.empty());
}

// Comparison with std::unordered_set
TEST_F(HybridUnorderedSetTest, ComparisonWithStdUnorderedSet)
{
	SmallSet hybrid_set;
	std::unordered_set<int> std_set;

	// Insert the same elements
	for (int i = 0; i < 100; i++)
	{
		hybrid_set.insert(i);
		std_set.insert(i);
	}

	// Check sizes match
	EXPECT_EQ(hybrid_set.size(), std_set.size());

	// Check all elements are present
	for (const auto& item : std_set)
	{
		EXPECT_NE(hybrid_set.find(item), hybrid_set.end());
	}

	// Check bucket counts are similar (may not be identical due to different
	// implementations)
	EXPECT_GT(hybrid_set.bucket_count(), 0);

	// Check load factors are similar
	EXPECT_GT(hybrid_set.load_factor(), 0.0f);
}


KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK