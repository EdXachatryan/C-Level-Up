#include "Message Queue.h"
#include <pthread.h>

using namespace utilities;

MessageQueueEngine::MessageQueueEngine()
{
 	m_queue_CV = PTHREAD_COND_INITIALIZER;
    m_CV_mutex = PTHREAD_MUTEX_INITIALIZER;

	int res = pthread_create(&m_mainThread, nullptr,
                             (typeOfThreadFn) &MessageQueueEngine::run, this);
    exitIfError(res, 0, "Cannot create thread.");

    res = pthread_detach(m_mainThread);
    exitIfError(res, 0, "Cannot detach thread.");
}

MessageQueueEngine::~MessageQueueEngine()
{
	for (auto it : m_FnMsgWrappers)
	{
		delete it;
		it = nullptr;
	}
}

void MessageQueueEngine::AddMessage(const std::string& msg)
{
	int resLock = pthread_mutex_lock( &m_CV_mutex );
	exitIfError(resLock, 0, "Cannot lock mutex.");

	m_QueueMsgs.push(msg);
 	int resCV = pthread_cond_signal(&m_queue_CV); // notify queue isn't empty

	resLock = pthread_mutex_unlock( &m_CV_mutex );
	exitIfError(resLock, 0, "Cannot unlock mutex.");
}

void MessageQueueEngine::RegisterHandler(void (*handler)(std::string))
{
	m_handlers.push_back(handler);
}

void* callbackAdapter(void* args)
{

	callbackMsgAdapter* adapter = static_cast<callbackMsgAdapter*> (args);

	auto msg = adapter->msg;
	auto callback = adapter->callbackFn;

	callback(msg);

	return nullptr;
}


void MessageQueueEngine::run()
{
	while (true)
	{
		int resLock = pthread_mutex_lock( &m_CV_mutex );
		exitIfError(resLock, 0, "Cannot lock mutex.");

		while (m_QueueMsgs.empty())
		{
 			int resCV = pthread_cond_wait(&m_queue_CV, &m_CV_mutex);  // wait until queue is empty
            exitIfError(resCV, 0, "Cannot wait for cond var.");
        }

		const std::string& msg = m_QueueMsgs.front();

		for (auto callback : m_handlers)
		{
			pthread_t thread;

			callbackMsgAdapter* adapter = new callbackMsgAdapter(callback, msg);
			m_FnMsgWrappers.push_back(adapter);
			int res = pthread_create(&thread, nullptr, callbackAdapter,(void*)( adapter));
			exitIfError(res, 0 , "Cannot create thread.");

			res = pthread_detach(thread);

		}

		m_QueueMsgs.pop();
		resLock = pthread_mutex_unlock( &m_CV_mutex );
		exitIfError(resLock, 0, "Cannot unlock mutex.");
	}
}

void MessageQueue::AddMessage(const std::string& msg)
{
	m_MQEngine.AddMessage(msg);
}

void MessageQueue::RegisterHandler(void (*handler)(std::string))
{
	m_MQEngine.RegisterHandler(handler);
}