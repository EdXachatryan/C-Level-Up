#include <string>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include "Client.h"
#include "utility.h"
int main()
{
	TaskManager::getInsance();
	Client client;

	while (true)
	{
		std::cout<< "Enter Fifo name then command" << std::endl;
		std::string pipeName, command;
		std::string line;
		std::getline( std::cin, line );
		pipeName = line.substr(0, line.find_first_of(' '));
		command = line.substr(line.find_first_of(' ')+1, line.size());

		if (command == "exit")
		{
			break;
		}
		else if (command == "read")
		{
			client.showCommandInfo(pipeName.c_str());
		}
		else
		{
			client.execCommand(pipeName.c_str(),command.c_str());
		}
	}

	TaskManager::releaseInstance();
	return 0;
};
