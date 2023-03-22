#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.containers.queue/include/kotek_core_containers_queue.h>
#include <kotek.core.containers.multithreading.mutex/include/kotek_core_containers_multithreading_mutex.h>

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
} // namespace mt

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK