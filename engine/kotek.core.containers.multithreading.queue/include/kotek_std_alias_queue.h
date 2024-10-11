#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.containers.queue/include/kotek_core_containers_queue.h>
#include <kotek.core.containers.multithreading.mutex/include/kotek_core_containers_multithreading_mutex.h>
#include <etl/queue_mpmc_mutex.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

namespace mt
{
	template <typename Type>
	class queue
	{
	public:
		queue() {}
		~queue() {}

		void push(const Type& data)
		{
			unique_lock<mutex> lock(this->m_mutex);
			this->m_queue.push(data);
			lock.unlock();
			this->m_variable.notify_one();
		}

		void push(Type&& data)
		{
			unique_lock<mutex> lock(this->m_mutex);
			this->m_queue.push(std::move(data));

			lock.unlock();
			this->m_variable.notify_one();
		}

		void pop(Type& return_data)
		{
			unique_lock<mutex> lock(this->m_mutex);
			while (this->m_queue.empty())
			{
				this->m_variable.wait(lock);
			}

			return_data = this->m_queue.front();
			this->m_queue.pop();
		}

		bool empty() const { return this->m_queue.empty(); }

	private:
		ktk::queue<Type> m_queue;
		mutex m_mutex;
		condition_variable m_variable;
	};

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
	template <typename Type, size_t Size>
	using static_queue = etl::queue_mpmc_mutex<Type, Size>;
#endif
} // namespace mt

KOTEK_END_NAMESPACE_KTK

namespace mt
{
	template <typename Type>
	using queue_t = KUN_KOTEK KUN_KTK mt::queue<Type>;

	template <typename Type, size_t Size>
	using static_queue_t = KUN_KOTEK KUN_KTK mt::static_queue<Type, Size>;
} // namespace mt

KOTEK_END_NAMESPACE_KOTEK