#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include <queue>
#include <string>
#include <vector>

#include "utilities.h"


struct callbackMsgAdapter;

class MessageQueueEngine
{
	public:
		using typeOfHandlers = void(*)(std::string); 
		using typeOfThreadFn = void *(*) (void *); // void *(*start_routine)(void *)  PTHREAD_CREATE's argument 

	public:
		MessageQueueEngine();
		~MessageQueueEngine();
		void AddMessage(const std::string&);
		void RegisterHandler(void (*handler)(std::string));

	private:
		void run();

	private:
		std::queue<std::string>	m_QueueMsgs;
		std::vector<typeOfHandlers> m_handlers; 

		pthread_t	m_mainThread; 
		pthread_cond_t m_queue_CV;  // conditional variable , wait/signal if queue empty/non empty
		pthread_mutex_t m_CV_mutex;  
			
	private:
		std::vector<callbackMsgAdapter*> m_FnMsgWrappers;

};

//	in posix PTHREAD_CREATE function arguments type dont matche with handlers function type  
//	neeed to create adapter
struct callbackMsgAdapter
{
	callbackMsgAdapter(MessageQueueEngine::typeOfHandlers fn, const std::string& message) :
		 callbackFn(fn), msg(message) {}

	std::string msg;
	MessageQueueEngine::typeOfHandlers callbackFn;
};


class MessageQueue
{
	public:
		void AddMessage(const std::string&);
		void RegisterHandler(void (*handler)(std::string));

	private:
		MessageQueueEngine m_MQEngine;
};



#endif