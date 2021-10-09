#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "TaskManager.h"
#include <set>

class Client
{
	public:

		~Client();
		void execCommand(std::string fifoName, std::string command );
		void showCommandInfo(std::string fifoName);
		void removeFifo(std::string fifoName);

	private:
		std::set<std::string> fifoNames; 
};

#endif 