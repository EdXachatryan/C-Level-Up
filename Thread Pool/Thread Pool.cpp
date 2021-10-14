#include "Thread Pool.h"

// ========================================================================================
//	Nested class ThreadWorker of ThreadPool implemetation
//
void ThreadPool::ThreadWorker::execute()
{
	typeOfPhtreadTask fn;
	bool dequeued;
	while (!m_pool->m_shutdown)
	{
		{
			utils::uniqueLock obj(m_pool->m_PoolMutex);
			if (m_pool->m_TaskQueue.empty())
			{
				int resCV = pthread_cond_wait(&m_pool->m_PoolCV, &m_pool->m_PoolMutex);  // wait until queue is empty
				utils::exitIfError(resCV, 0, "Cannot wait for cond var.");
			}
			dequeued = m_pool->m_TaskQueue.dequeue(fn);
		}

		if (dequeued)
			*fn;	
	}
}

// ========================================================================================
//	 class ThreadPool implementation
//

void* callWorkerWrapper(void* args)
{
	ThreadPool::ThreadWorkerWrapper* wrapper = static_cast<ThreadPool::ThreadWorkerWrapper*> (args);
	auto callback = wrapper->m_worker;

	callback.execute();

	return nullptr;
}

void ThreadPool::init()
{
	for (size_t i = 0; i < m_threads.size(); ++i)
	{
		ThreadPool::ThreadWorkerWrapper* wrapper = new ThreadPool::ThreadWorkerWrapper(ThreadWorker(this,i));
		m_WorkersWrapper.push_back(wrapper);	

		int res = pthread_create(&m_threads[i], nullptr, callWorkerWrapper,(void*)( wrapper));
		utils::exitIfError(res, 0 , "Cannot create thread.");
	}
}

void ThreadPool::shutDown()
{
	m_shutdown = true;

	int resCV = pthread_cond_signal(&m_PoolCV); // notify queue isn't empty

	for (size_t i = 0; i < m_threads.size(); ++i)
	{
		// if joinable	if (m_threads[i])
		int status_addr;
		int status = pthread_join(m_threads[i], (void**)&status_addr);
        utils::exitIfError(status, 0 ,"main error: can't join thread.");
	}
}

void ThreadPool::addTask(typeOfPhtreadTask fn)
{
	m_TaskQueue.enqueue(fn);
	int resCV = pthread_cond_signal(&m_PoolCV); // notify queue isn't empty
}