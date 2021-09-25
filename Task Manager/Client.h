#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "TaskManager.h"
#include <map>

class Client
{
	public:

		~Client();
		void execCommand(const char* FIFOName, const char* command );
		void showCommandInfo(const char* fifoName);
		void removeFifo(const char* fifoName);

	private:
		//std::map<const char*, const char* > cmdfifoNames; 
};


#endif 