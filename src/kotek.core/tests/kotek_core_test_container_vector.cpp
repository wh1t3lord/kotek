#include "../include/kotek_core.h"

#ifdef KOTEK_USE_TESTS
	#ifdef KOTEK_DEBUG
		#include <gtest/gtest.h>
	#endif
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#ifdef KOTEK_USE_TESTS
	#ifdef KOTEK_DEBUG
	
// Default constructor
TEST(Containers, test_container_vector_constructor_default)
{
	kun_kotek kun_ktk hybrid_vector<int, 8> vec;
	EXPECT_TRUE(vec.empty());
}

// Constructor with count
TEST(Containers, test_container_vector_constructor_count)
{
	kun_kotek kun_ktk hybrid_vector<int, 8> vec(5);
	EXPECT_EQ(vec.size(), 5);
}

// Constructor with count and value
TEST(Containers, test_container_vector_constructor_count_value)
{
	kun_kotek kun_ktk hybrid_vector<int, 8> vec(5, 42);
	EXPECT_EQ(vec.size(), 5);
	for (auto v : vec)
		EXPECT_EQ(v, 42);
}

// Constructor from iterators
TEST(Containers, test_container_vector_constructor_iterators)
{
	int arr[] = {1, 2, 3, 4};
	kun_kotek kun_ktk hybrid_vector<int, 8> vec(std::begin(arr), std::end(arr));
	EXPECT_EQ(vec.size(), 4);
	EXPECT_EQ(vec[0], 1);
	EXPECT_EQ(vec[3], 4);
}

// Copy constructor (same type)
TEST(Containers, test_container_vector_constructor_copy)
{
	kun_kotek kun_ktk hybrid_vector<int, 8> src(3, 7);
	kun_kotek kun_ktk hybrid_vector<int, 8> vec(src);
	EXPECT_EQ(vec.size(), 3);
	EXPECT_EQ(vec[0], 7);
}

// Copy constructor (different type/params)
TEST(Containers, test_container_vector_constructor_copy_other)
{
	kun_kotek kun_ktk hybrid_vector<int, 4> src(2, 5);
	kun_kotek kun_ktk hybrid_vector<int, 8> vec(src);
	EXPECT_EQ(vec.size(), 2);
	EXPECT_EQ(vec[0], 5);
}

// Move constructor (same type)
TEST(Containers, test_container_vector_constructor_move)
{
	kun_kotek kun_ktk hybrid_vector<int, 8> src(2, 9);
	kun_kotek kun_ktk hybrid_vector<int, 8> vec(std::move(src));
	EXPECT_EQ(vec.size(), 2);
	EXPECT_EQ(vec[0], 9);
}

// Move constructor (different type/params)
TEST(Containers, test_container_vector_constructor_move_other)
{
	kun_kotek kun_ktk hybrid_vector<int, 4> src(2, 11);
	kun_kotek kun_ktk hybrid_vector<int, 8> vec(std::move(src));
	EXPECT_EQ(vec.size(), 2);
	EXPECT_EQ(vec[0], 11);
}

// Initializer list constructor
TEST(Containers, test_container_vector_constructor_initializer_list)
{
	kun_kotek kun_ktk hybrid_vector<int, 8> vec{1, 2, 3, 4};
	EXPECT_EQ(vec.size(), 4);
	EXPECT_EQ(vec[2], 3);
}

// push_back
TEST(Containers, test_container_vector_push_back)
{
	kun_kotek kun_ktk hybrid_vector<int, 8> vec;
	vec.push_back(5);
	EXPECT_EQ(vec.size(), 1);
	EXPECT_EQ(vec[0], 5);
}

// pop_back
TEST(Containers, test_container_vector_pop_back)
{
	kun_kotek kun_ktk hybrid_vector<int, 8> vec{1, 2, 3};
	vec.pop_back();
	EXPECT_EQ(vec.size(), 2);
	EXPECT_EQ(vec.back(), 2);
}

// insert
TEST(Containers, test_container_vector_insert)
{
	kun_kotek kun_ktk hybrid_vector<int, 8> vec{1, 2, 4};
	vec.insert(vec.begin() + 2, 3);
	EXPECT_EQ(vec[2], 3);
}

// erase
TEST(Containers, test_container_vector_erase)
{
	kun_kotek kun_ktk hybrid_vector<int, 8> vec{1, 2, 3};
	vec.erase(vec.begin());
	EXPECT_EQ(vec[0], 2);
	EXPECT_EQ(vec.size(), 2);
}

// clear
TEST(Containers, test_container_vector_clear)
{
	kun_kotek kun_ktk hybrid_vector<int, 8> vec{1, 2, 3};
	vec.clear();
	EXPECT_TRUE(vec.empty());
}

// resize
TEST(Containers, test_container_vector_resize)
{
	kun_kotek kun_ktk hybrid_vector<int, 8> vec{1, 2};
	vec.resize(5, 7);
	EXPECT_EQ(vec.size(), 5);
	EXPECT_EQ(vec[4], 7);
}

// reserve
TEST(Containers, test_container_vector_reserve)
{
	kun_kotek kun_ktk hybrid_vector<int, 8> vec;
	vec.reserve(10);
	EXPECT_GE(vec.capacity(), 10);
}

// size
TEST(Containers, test_container_vector_size)
{
	kun_kotek kun_ktk hybrid_vector<int, 8> vec{1, 2, 3};
	EXPECT_EQ(vec.size(), 3);
}

// capacity
TEST(Containers, test_container_vector_capacity)
{
	kun_kotek kun_ktk hybrid_vector<int, 8> vec;
	EXPECT_GE(vec.capacity(), 8);
}

// operator[]
TEST(Containers, test_container_vector_operator_index)
{
	kun_kotek kun_ktk hybrid_vector<int, 8> vec{10, 20};
	EXPECT_EQ(vec[1], 20);
}

// at
TEST(Containers, test_container_vector_at)
{
	kun_kotek kun_ktk hybrid_vector<int, 8> vec{10, 20};
	EXPECT_EQ(vec.at(0), 10);
}

// front
TEST(Containers, test_container_vector_front)
{
	kun_kotek kun_ktk hybrid_vector<int, 8> vec{5, 6};
	EXPECT_EQ(vec.front(), 5);
}

// back
TEST(Containers, test_container_vector_back)
{
	kun_kotek kun_ktk hybrid_vector<int, 8> vec{5, 6};
	EXPECT_EQ(vec.back(), 6);
}

// begin/end
TEST(Containers, test_container_vector_begin_end)
{
	kun_kotek kun_ktk hybrid_vector<int, 8> vec{1, 2, 3};
	auto it = vec.begin();
	EXPECT_EQ(*it, 1);
	++it;
	EXPECT_EQ(*it, 2);
}

// empty
TEST(Containers, test_container_vector_empty)
{
	kun_kotek kun_ktk hybrid_vector<int, 8> vec;
	EXPECT_TRUE(vec.empty());
}

// assign
TEST(Containers, test_container_vector_assign)
{
	kun_kotek kun_ktk hybrid_vector<int, 8> vec;
	vec.assign(3, 99);
	EXPECT_EQ(vec.size(), 3);
	EXPECT_EQ(vec[0], 99);
}

// swap
TEST(Containers, test_container_vector_swap)
{
	kun_kotek kun_ktk hybrid_vector<int, 8> a{1, 2};
	kun_kotek kun_ktk hybrid_vector<int, 8> b{3, 4};
	a.swap(b);
	EXPECT_EQ(a[0], 3);
	EXPECT_EQ(b[0], 1);
}

// emplace
TEST(Containers, test_container_vector_emplace)
{
	kun_kotek kun_ktk hybrid_vector<int, 8> vec;
	vec.emplace(vec.end(), 42);
	EXPECT_EQ(vec.back(), 42);
}

// emplace_back
TEST(Containers, test_container_vector_emplace_back)
{
	kun_kotek kun_ktk hybrid_vector<int, 8> vec;
	vec.emplace_back(77);
	EXPECT_EQ(vec.back(), 77);
}

// shrink_to_fit
TEST(Containers, test_container_vector_shrink_to_fit)
{
	kun_kotek kun_ktk hybrid_vector<int, 8> vec{1, 2, 3};
	vec.reserve(20);
	vec.shrink_to_fit();
	EXPECT_LE(vec.capacity(), 20);
}

// data
TEST(Containers, test_container_vector_data)
{
	kun_kotek kun_ktk hybrid_vector<int, 8> vec{1, 2, 3};
	int* ptr = vec.data();
	EXPECT_EQ(ptr[0], 1);
	EXPECT_EQ(ptr[2], 3);
}
	
	#endif
#endif

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK