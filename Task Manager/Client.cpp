#include "Client.h"

extern std::string TSKMANAGERFIFO ;


Client::~Client()
{
	for (auto it = cmdfifoNames.begin(); it != cmdfifoNames.end(); ++it)
	{
		unlink(it->second);
	}
}

void Client::execCommand(const char* FIFOName, const char* command )
{
	cmdfifoNames.insert(std::make_pair( command,FIFOName));
	TaskManager::getInsance()->createTask(FIFOName, command);
}

void Client::showCommandInfo(const char* name)
{
	auto itFifo = cmdfifoNames.find(name);
	if (itFifo == cmdfifoNames.end())
	{
		std::cout << "Here is no " << name << " file" << std::endl;
		return;
	}

	int fd = open(itFifo->second, O_RDONLY);
	char buffer[1024];
	std::cout << fd << std::endl;
	int n;
	std::cout << "Result of " << name << " command" << std::endl;
	while((n=read(fd,buffer,sizeof(buffer)))>0){
        //write(1, buffer, n);
		std::cout << buffer;
	}
	//read(fd,buffer,1024);
	//std::cout << buffer << std::endl;
	std::cout << "End of result " << name << "command" << std::endl;
    close(fd);
}


void Client::removeFifo(const char* fifoName)
{
	auto itFifo = cmdfifoNames.find(fifoName);
	if (itFifo == cmdfifoNames.end())
	{
		std::cout << "Here is no " << fifoName << " file" << std::endl;
		return;
	}

 	if (unlink(itFifo->second ) == 0)
	 	cmdfifoNames.erase(itFifo);
	else
	{
		std::cerr << "Fail to remove " << itFifo->second ;
	}	 
}