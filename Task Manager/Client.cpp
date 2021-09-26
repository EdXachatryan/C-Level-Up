#include "Client.h"
extern const char* s_TskManagerFifo ;


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
	int fd = open(name, O_RDONLY );
	char* buffer = new char[1024];
	int n;
	std::cout << "=============================================" << std::endl;
	std::cout << "Result of " << name << " command" << std::endl;
	while((n=read(fd,buffer,1))>0){
		std::cout << buffer;
	}
	delete[] buffer;
	std::cout << "End of result " << name << "command" << std::endl;
	std::cout << "=============================================" << std::endl;
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