#ifndef TSKMANAGER_H
#define TSKMANAGER_H

#include <map>
#include <string>
#include <sys/stat.h>
#include <iostream>
#include "Task.h"
#include <string.h>


extern std::string TSKMANAGERFIFO ;

class TaskManager
{
private:
	std::map<const char*, const char* > cmdfifoNames; 
	static TaskManager* instance;
	TaskManager();

public:

	static TaskManager* getInsance();
	~TaskManager();

	bool createTask(const char* FIFOName, const char* command );
	int returnFifoFD(const char* cmdName);
	int removeFIFO(const char* fifoName);
};


#endif