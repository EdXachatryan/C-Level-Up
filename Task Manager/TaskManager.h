#ifndef TSKMANAGER_H
#define TSKMANAGER_H

#include <map>
#include <sys/stat.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
 #include <fcntl.h>

extern int inotify_fD;
extern const char* s_TskManagerFifo ;

class TaskManager
{
private:
	static TaskManager* instance;
	TaskManager();
	~TaskManager() { }

public:

	static TaskManager* getInsance();
	static void releaseInstance();

	bool createTask(const char* FIFOName, const char* command );
};

#endif