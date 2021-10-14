#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include "pthread.h"
#include <thread>
#include <unistd.h>
namespace
{
	pthread_mutex_t printMutex = PTHREAD_MUTEX_INITIALIZER; // unnamed namespace for restricting the variable scope

	std::mutex mtx;
}

namespace utils
{
	// forward declaretions
	void exitIfError(const int err, const int expectValue , const std::string& msg );

	struct uniqueLock
	{
		uniqueLock( pthread_mutex_t* mtx) : m_mutex{mtx}
		{
			int resLock = pthread_mutex_lock( m_mutex );
			exitIfError(resLock, 0, "Cannot lock mutex.");
		}

		~uniqueLock()
		{
			int resLock = pthread_mutex_unlock( m_mutex );
			exitIfError(resLock, 0, "Cannot unlock mutex.");
		}

		private:
			pthread_mutex_t* m_mutex;
	};
	

	inline void exitIfError(const int err, const int expectValue = 0, const std::string& msg = "")
	{
		if (err != expectValue)
		{
			{
				uniqueLock objLock(&printMutex);
				std::cout << msg << std::endl;
			}
			exit(EXIT_FAILURE);
		}
	}

	inline void syncPrint(const std::string& msg)
	{
		uniqueLock objLock(&printMutex);
		std::cout << msg << std::endl;
	}
}

#endif