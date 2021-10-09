#include "Client.h"
#include "utility.h"
Client::~Client()
{
	for (auto it = fifoNames.begin(); it != fifoNames.end(); ++it)
	{
		if(unlink(it->c_str()) != 0)
			std::cerr << it->c_str() << " didn't delete" << std::endl;
	}
}

void Client::execCommand(std::string fifoName, std::string command )
{
	fifoNames.insert(fifoName);
	TaskManager::getInsance()->createTask(fifoName, command);
}

void Client::showCommandInfo(std::string name)
{
	if (fifoNames.find(name) == fifoNames.end())
	{
		std::cout << "=============================================" << std::endl;
		std::cout <<  name << " not found" << std::endl;		
		std::cout << "=============================================" << std::endl;
		return;
	}

	int fd = open(name.c_str(), O_RDONLY );
	exitIfNotSucceed(fd, "cannot open fifo for read");
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


void Client::removeFifo(std::string fifoName)
{
	auto itFifo = fifoNames.find(fifoName);
	if (itFifo == fifoNames.end())
	{
		std::cout << "Here is no " << fifoName << " file" << std::endl;
		return;
	}

 	if (unlink(fifoName.c_str()) == 0)
	 	fifoNames.erase(fifoName);
	else
	{
		std::cerr << "Fail to remove " << fifoName ;
	}	 
}