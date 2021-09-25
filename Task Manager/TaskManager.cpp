#include "TaskManager.h"


#define ERROR_FAILURE { \
				std::cerr << strerror(errno) << std::endl;\
				exit(EXIT_FAILURE);\
				}

TaskManager*  TaskManager::instance = nullptr;


TaskManager* TaskManager::getInsance()
{
	if (instance == nullptr)
		instance = new TaskManager();

	return instance;
}

void TaskManager::releaseInstance()
{
	if(unlink(s_TskManagerFifo) != 0)
	{
		std::cout << s_TskManagerFifo << " didn't delete" << std::endl;
	}
	
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

TaskManager::TaskManager()
{
	int fifo = mkfifo(s_TskManagerFifo, S_IRWXU);
	if (fifo != 0)
		std::cerr << errno << std::endl;
}


bool TaskManager::createTask(const char* FIFOName, const char* command )
{
	pid_t pid = fork();
	int stdout_copy = dup(1);
	
	if (pid > 0 )
	{
		int tskMngFD = open(s_TskManagerFifo, O_WRONLY);
		size_t nameLenght = strlen(FIFOName); 
		write(tskMngFD, &nameLenght, 8);
		write(tskMngFD, FIFOName, nameLenght + 1);
		
		size_t commLenght = strlen(command);
		write(tskMngFD, &commLenght, 8);
		write(tskMngFD, command, commLenght + 1);
		close(tskMngFD);
	}
	else if (pid == 0)
	{
		int tskMngFD_R = open(s_TskManagerFifo, O_RDONLY);

		char* nameSize;
		char* fifoName;
		size_t ss;
		read(tskMngFD_R, &ss, 8);
		read(tskMngFD_R, fifoName, ss + 1);
	
		char* execCommand;
		char* readComBites;
		size_t sss;
		read(tskMngFD_R, &sss, 8);
		read(tskMngFD_R, execCommand, sss + 1);
		close(tskMngFD_R);
		
		if (mkfifo(fifoName, S_IRWXU) == -1)
			std::cerr << strerror(errno) << std::endl;
		close(1);
		
		if (open(fifoName, O_WRONLY) == -1)
			ERROR_FAILURE
	
		std::string strCommand = std::string("/bin/") +  std::string(execCommand);
		char* arg =  const_cast<char*> (strCommand.c_str());
		char *args[2];
		args[0] = arg;
		args[1] = NULL;   

		if (execv( args[0], args ) == -1)
			ERROR_FAILURE
	} 
	else
	{
		std::cerr << "fork creation failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	dup2(stdout_copy, 1);
	close(stdout_copy);

	return true;
}
