#include "string"
#include <iostream>

namespace
{
	pthread_mutex_t printMutex = PTHREAD_MUTEX_INITIALIZER; // unnamed namespace for restricting the variable scope
}

namespace utilities
{
	inline void exitIfError(const int err, const int expectValue = 0, const std::string& msg = "")
	{
		if (err != expectValue)
		{
			int resLock = pthread_mutex_lock( &printMutex );
			std::cout << msg << std::endl;
			resLock = pthread_mutex_unlock( &printMutex );
			exit(EXIT_FAILURE);
		}
	}

	inline void syncPrint(const std::string& msg)
	{
		int resLock = pthread_mutex_lock( &printMutex );
		exitIfError(resLock, 0, "Cannot lock mutex.");

		std::cout << msg << std::endl;
		
		resLock = pthread_mutex_unlock( &printMutex );
		exitIfError(resLock, 0, "Cannot unlock mutex.");
	}


};


