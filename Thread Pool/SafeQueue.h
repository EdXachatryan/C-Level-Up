#ifndef SAFEQUEUE_H
#define SAFEQUEUE_H

#include <queue>
#include <mutex>
#include <pthread.h>
#include "utils.h"

template<typename T>
class SafeQueue 
{
	public:
		bool empty()
		{
			utils::uniqueLock objLock(m_mutex);
			return m_queue.empty();
		}

		int size() 
		{
			utils::uniqueLock objLock(m_mutex);
			return m_queue.size();
		}

		void enqueue(T& t)
		{
			utils::uniqueLock objLock(m_mutex);
			m_queue.push(t);
		}

		bool dequeue(T& t)
		{
			utils::uniqueLock objLock(m_mutex);
			if (m_queue.empty())
				return false;

			t = m_queue.front();

			m_queue.pop();
			return true;	
		}

	private:
		std::queue<T> m_queue;
		pthread_mutex_t m_mutex;

};

#endif