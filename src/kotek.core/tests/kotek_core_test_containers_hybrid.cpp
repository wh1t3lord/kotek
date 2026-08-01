#include "../include/kotek_core.h"

#if defined(KOTEK_USE_TESTS) && defined(KOTEK_DEBUG)

	#include <gtest/gtest.h>

#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#if defined(KOTEK_USE_TESTS) && defined(KOTEK_DEBUG)

// ===========================================================================
// hybrid deque — API parity smoke
// ===========================================================================

TEST(Containers, test_container_hybrid_deque_constructor_default)
{
	kun_kotek kun_ktk hybrid_deque<int, 8> deq;
	EXPECT_TRUE(deq.empty());
}

TEST(Containers, test_container_hybrid_deque_constructor_count_value)
{
	kun_kotek kun_ktk hybrid_deque<int, 8> deq(3, 42);
	EXPECT_EQ(deq.size(), 3);
	EXPECT_EQ(deq[0], 42);
	EXPECT_EQ(deq[2], 42);
}

TEST(Containers, test_container_hybrid_deque_constructor_initializer_list)
{
	kun_kotek kun_ktk hybrid_deque<int, 8> deq{1, 2, 3, 4};
	EXPECT_EQ(deq.size(), 4);
	EXPECT_EQ(deq.front(), 1);
	EXPECT_EQ(deq.back(), 4);
}

TEST(Containers, test_container_hybrid_deque_constructor_copy_other)
{
	kun_kotek kun_ktk hybrid_deque<int, 4> src(2, 5);
	kun_kotek kun_ktk hybrid_deque<int, 8> deq(src);
	EXPECT_EQ(deq.size(), 2);
	EXPECT_EQ(deq[0], 5);
}

TEST(Containers, test_container_hybrid_deque_push_back_front)
{
	kun_kotek kun_ktk hybrid_deque<int, 8> deq;
	deq.push_back(2);
	deq.push_back(3);
	deq.push_front(1);
	EXPECT_EQ(deq.size(), 3);
	EXPECT_EQ(deq.front(), 1);
	EXPECT_EQ(deq.back(), 3);
}

TEST(Containers, test_container_hybrid_deque_pop_back_front)
{
	kun_kotek kun_ktk hybrid_deque<int, 8> deq{1, 2, 3};
	deq.pop_front();
	EXPECT_EQ(deq.front(), 2);
	deq.pop_back();
	EXPECT_EQ(deq.size(), 1);
	EXPECT_EQ(deq.front(), 2);
}

TEST(Containers, test_container_hybrid_deque_iterate)
{
	kun_kotek kun_ktk hybrid_deque<int, 8> deq{1, 2, 3, 4};
	int sum = 0;
	for (auto v : deq)
		sum += v;
	EXPECT_EQ(sum, 10);

	auto it = deq.begin();
	EXPECT_EQ(*it, 1);
	++it;
	EXPECT_EQ(*it, 2);
}

TEST(Containers, test_container_hybrid_deque_insert_erase)
{
	kun_kotek kun_ktk hybrid_deque<int, 8> deq{1, 2, 4};
	deq.insert(deq.begin() + 2, 3);
	EXPECT_EQ(deq[2], 3);
	EXPECT_EQ(deq.size(), 4);

	deq.erase(deq.begin());
	EXPECT_EQ(deq.front(), 2);
	EXPECT_EQ(deq.size(), 3);
}

TEST(Containers, test_container_hybrid_deque_at_operator_index)
{
	kun_kotek kun_ktk hybrid_deque<int, 8> deq{10, 20};
	EXPECT_EQ(deq.at(0), 10);
	EXPECT_EQ(deq[1], 20);
}

// ===========================================================================
// hybrid list — API parity smoke
// ===========================================================================

TEST(Containers, test_container_hybrid_list_constructor_default)
{
	kun_kotek kun_ktk hybrid_list<int, 8> ls;
	EXPECT_TRUE(ls.empty());
}

TEST(Containers, test_container_hybrid_list_constructor_initializer_list)
{
	kun_kotek kun_ktk hybrid_list<int, 8> ls{1, 2, 3};
	EXPECT_EQ(ls.size(), 3);
	EXPECT_EQ(ls.front(), 1);
	EXPECT_EQ(ls.back(), 3);
}

TEST(Containers, test_container_hybrid_list_constructor_copy_other)
{
	kun_kotek kun_ktk hybrid_list<int, 4> src(2, 5);
	kun_kotek kun_ktk hybrid_list<int, 8> ls(src);
	EXPECT_EQ(ls.size(), 2);
	EXPECT_EQ(ls.front(), 5);
}

TEST(Containers, test_container_hybrid_list_push_pop)
{
	kun_kotek kun_ktk hybrid_list<int, 8> ls;
	ls.push_back(2);
	ls.push_front(1);
	ls.push_back(3);
	EXPECT_EQ(ls.size(), 3);
	EXPECT_EQ(ls.front(), 1);
	EXPECT_EQ(ls.back(), 3);

	ls.pop_front();
	ls.pop_back();
	EXPECT_EQ(ls.size(), 1);
	EXPECT_EQ(ls.front(), 2);
}

TEST(Containers, test_container_hybrid_list_iterate)
{
	kun_kotek kun_ktk hybrid_list<int, 8> ls{1, 2, 3, 4};
	int sum = 0;
	for (auto v : ls)
		sum += v;
	EXPECT_EQ(sum, 10);
}

TEST(Containers, test_container_hybrid_list_insert_erase)
{
	kun_kotek kun_ktk hybrid_list<int, 8> ls{1, 2, 4};
	auto it = ls.begin();
	++it;
	++it;
	ls.insert(it, 3);
	EXPECT_EQ(ls.size(), 4);

	ls.erase(ls.begin());
	EXPECT_EQ(ls.front(), 2);
	EXPECT_EQ(ls.size(), 3);
}

TEST(Containers, test_container_hybrid_list_sort_reverse_remove)
{
	kun_kotek kun_ktk hybrid_list<int, 8> ls{3, 1, 2, 1};
	ls.sort();
	EXPECT_EQ(ls.front(), 1);
	EXPECT_EQ(ls.back(), 3);

	ls.remove(1);
	EXPECT_EQ(ls.size(), 2);
	EXPECT_EQ(ls.front(), 2);

	ls.reverse();
	EXPECT_EQ(ls.front(), 3);
}

// ===========================================================================
// hybrid queue — API parity smoke (adaptor: no iterators, FIFO through
// front/push/pop)
// ===========================================================================

TEST(Containers, test_container_hybrid_queue_constructor_default)
{
	kun_kotek kun_ktk hybrid_queue<int, 8> que;
	EXPECT_TRUE(que.empty());
}

TEST(Containers, test_container_hybrid_queue_push_front_back)
{
	kun_kotek kun_ktk hybrid_queue<int, 8> que;
	que.push(1);
	que.push(2);
	que.push(3);
	EXPECT_EQ(que.size(), 3);
	EXPECT_EQ(que.front(), 1);
	EXPECT_EQ(que.back(), 3);
}

TEST(Containers, test_container_hybrid_queue_pop_fifo_order)
{
	kun_kotek kun_ktk hybrid_queue<int, 8> que;
	que.push(1);
	que.push(2);
	que.push(3);

	// the adaptor has no iterators — draining through front/pop is the
	// iteration model and must yield FIFO order
	int expected = 1;
	while (!que.empty())
	{
		EXPECT_EQ(que.front(), expected);
		que.pop();
		++expected;
	}
	EXPECT_EQ(expected, 4);
}

TEST(Containers, test_container_hybrid_queue_emplace)
{
	kun_kotek kun_ktk hybrid_queue<int, 8> que;
	que.emplace(7);
	EXPECT_EQ(que.front(), 7);
	EXPECT_EQ(que.size(), 1);
}

TEST(Containers, test_container_hybrid_queue_constructor_copy)
{
	kun_kotek kun_ktk hybrid_queue<int, 8> src;
	src.push(4);
	src.push(5);
	kun_kotek kun_ktk hybrid_queue<int, 8> que(src);
	EXPECT_EQ(que.size(), 2);
	EXPECT_EQ(que.front(), 4);
	EXPECT_EQ(que.back(), 5);
}

// ===========================================================================
// is_static() regression — a hybrid container is static exactly when it does
// NOT reallocate (Realloc == false). Covers the inverted
// hybrid_vector_impl::is_static that returned Realloc.
// ===========================================================================

TEST(Containers, test_container_hybrid_is_static_contract)
{
	kun_kotek kun_ktk hybrid_deque<int, 4> deq;
	EXPECT_FALSE(deq.is_static());
	kun_kotek kun_ktk static_hybrid_deque<int, 4> sdeq;
	EXPECT_TRUE(sdeq.is_static());
	kun_kotek kun_ktk hybrid_std_deque<int> ddeq;
	EXPECT_FALSE(ddeq.is_static());

	kun_kotek kun_ktk hybrid_list<int, 4> ls;
	EXPECT_FALSE(ls.is_static());
	kun_kotek kun_ktk static_hybrid_list<int, 4> sls;
	EXPECT_TRUE(sls.is_static());
	kun_kotek kun_ktk hybrid_std_list<int> dls;
	EXPECT_FALSE(dls.is_static());

	kun_kotek kun_ktk hybrid_queue<int, 4> que;
	EXPECT_FALSE(que.is_static());
	kun_kotek kun_ktk static_hybrid_queue<int, 4> sque;
	EXPECT_TRUE(sque.is_static());
	kun_kotek kun_ktk hybrid_std_queue<int> dque;
	EXPECT_FALSE(dque.is_static());

	// the regression itself: the vector returned Realloc (inverted)
	kun_kotek kun_ktk hybrid_vector<int, 4> vec;
	EXPECT_FALSE(vec.is_static());
	kun_kotek kun_ktk static_hybrid_vector<int, 4> svec;
	EXPECT_TRUE(svec.is_static());
	kun_kotek kun_ktk hybrid_std_vector<int> dvec;
	EXPECT_FALSE(dvec.is_static());
}

TEST(Containers, test_container_hybrid_size_preallocated)
{
	kun_kotek kun_ktk static_hybrid_deque<int, 8> deq;
	EXPECT_EQ(deq.size_preallocated(), 8);
	EXPECT_GT(deq.size_preallocated_memory(), 0);

	kun_kotek kun_ktk static_hybrid_list<int, 8> ls;
	EXPECT_EQ(ls.size_preallocated(), 8);
	EXPECT_GT(ls.size_preallocated_memory(), 0);

	kun_kotek kun_ktk static_hybrid_queue<int, 8> que;
	EXPECT_EQ(que.size_preallocated(), 8);
	EXPECT_GT(que.size_preallocated_memory(), 0);

	kun_kotek kun_ktk hybrid_std_deque<int> ddeq;
	EXPECT_EQ(ddeq.size_preallocated(), 0);
}

// ===========================================================================
// capacity boundary with Realloc == false — the container must serve its
// nominal capacity from the preallocated buffer alone and must never
// allocate past it: the upstream resource is null_memory_resource, so an
// overflow surfaces as std::bad_alloc (the pmr contract), which is exactly
// the guarantee that no hidden reallocation happened.
// ===========================================================================

TEST(Containers, test_container_static_hybrid_deque_capacity_boundary)
{
	kun_kotek kun_ktk static_hybrid_deque<int, 8> deq;
	for (int i = 0; i < 8; ++i)
		deq.push_back(i);

	EXPECT_EQ(deq.size(), 8);
	for (int i = 0; i < 8; ++i)
		EXPECT_EQ(deq[i], i);

	// far past the preallocated budget: must not silently reallocate
	EXPECT_THROW(
		{
			for (int i = 0; i < 256; ++i)
				deq.push_back(i);
		},
		std::bad_alloc);
}

TEST(Containers, test_container_static_hybrid_list_capacity_boundary)
{
	kun_kotek kun_ktk static_hybrid_list<int, 8> ls;
	for (int i = 0; i < 8; ++i)
		ls.push_back(i);

	EXPECT_EQ(ls.size(), 8);
	int expected = 0;
	for (auto v : ls)
		EXPECT_EQ(v, expected++);

	EXPECT_THROW(
		{
			for (int i = 0; i < 256; ++i)
				ls.push_back(i);
		},
		std::bad_alloc);
}

TEST(Containers, test_container_static_hybrid_queue_capacity_boundary)
{
	kun_kotek kun_ktk static_hybrid_queue<int, 8> que;
	for (int i = 0; i < 8; ++i)
		que.push(i);

	EXPECT_EQ(que.size(), 8);
	EXPECT_EQ(que.front(), 0);
	EXPECT_EQ(que.back(), 7);

	EXPECT_THROW(
		{
			for (int i = 0; i < 256; ++i)
				que.push(i);
		},
		std::bad_alloc);
}

// ===========================================================================
// growth with Realloc == true — past the preallocated budget the container
// grows through the upstream (default) resource
// ===========================================================================

TEST(Containers, test_container_hybrid_deque_growth_realloc)
{
	kun_kotek kun_ktk hybrid_deque<int, 4> deq;
	for (int i = 0; i < 32; ++i)
		deq.push_back(i);

	EXPECT_EQ(deq.size(), 32);
	for (int i = 0; i < 32; ++i)
		EXPECT_EQ(deq[i], i);
}

TEST(Containers, test_container_hybrid_list_growth_realloc)
{
	kun_kotek kun_ktk hybrid_list<int, 4> ls;
	for (int i = 0; i < 32; ++i)
		ls.push_back(i);

	EXPECT_EQ(ls.size(), 32);
	int expected = 0;
	for (auto v : ls)
		EXPECT_EQ(v, expected++);
}

TEST(Containers, test_container_hybrid_queue_growth_realloc)
{
	kun_kotek kun_ktk hybrid_queue<int, 4> que;
	for (int i = 0; i < 32; ++i)
		que.push(i);

	EXPECT_EQ(que.size(), 32);
	for (int i = 0; i < 32; ++i)
	{
		EXPECT_EQ(que.front(), i);
		que.pop();
	}
	EXPECT_TRUE(que.empty());
}

#endif

void RegisterTests_Containers_Hybrid_ForModule_Core(void)
{
#if defined(KOTEK_USE_TESTS) && defined(KOTEK_DEBUG)

#endif
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
