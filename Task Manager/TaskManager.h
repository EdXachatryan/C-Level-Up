#ifndef TSKMANAGER_H
#define TSKMANAGER_H

#include <map>
#include <sys/stat.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>



class TaskManager
{
private:
	static TaskManager* instance;
	TaskManager();
	~TaskManager() { }

public:
	static std::string m_FifoName;
	static TaskManager* getInsance();
	static void releaseInstance();

	bool createTask(std::string FIFOName, std::string command );
};

#endif