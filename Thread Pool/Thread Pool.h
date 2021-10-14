#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <array>
#include <vector>
#include <queue>
#include <pthread.h>
#include "SafeQueue.h"

class ThreadPool
{
	public:
		using typeOfPhtreadTask = void *(*)(void *);
		using typeOfTasks = void(*)(); 
	public:

		class ThreadWorker
		{
			public:
				ThreadWorker(ThreadPool* pool, const int id)
					: m_pool(pool), m_Id(id) { }

				void execute();
			private:
				int 		m_Id;
				ThreadPool* m_pool;
		};


	public:
		ThreadPool(const int maxThreads) 
			: m_threads(std::vector<pthread_t>(maxThreads)), m_shutdown(false)  
			{
				init();
			}

		ThreadPool(const ThreadPool&) = delete;
		ThreadPool(ThreadPool&& ) = delete;

		ThreadPool& operator=(const ThreadPool&) = delete;
		ThreadPool& operator=(ThreadPool&& ) = delete;

		void init();
		void shutDown();
		void addTask(typeOfPhtreadTask fn);

		struct ThreadWorkerWrapper
		{
			
			ThreadWorkerWrapper(ThreadWorker& worker) : m_worker(worker) {}
			ThreadWorker m_worker;
		};
		

	private:
  		bool m_shutdown;
		SafeQueue<typeOfPhtreadTask> m_TaskQueue;
		std::vector<pthread_t>	m_threads;

		std::vector<ThreadWorkerWrapper> m_WorkersWrapper;

		pthread_cond_t m_PoolCV;  // conditional variable , wait/signal if queue empty/non empty
		pthread_mutex_t m_PoolMutex;  
};

#endif