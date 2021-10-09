#include "TaskManager.h"
#include "utility.h"

TaskManager*  TaskManager::instance = nullptr;

std::string TaskManager::m_FifoName = "mngFifo";

TaskManager* TaskManager::getInsance()
{
	if (instance == nullptr)
		instance = new TaskManager();

	return instance;
}

void TaskManager::releaseInstance()
{
	if(unlink(m_FifoName.c_str()) != 0)
	{
		std::cout << m_FifoName << " didn't delete" << std::endl;
	}
	
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

TaskManager::TaskManager()
{

	int fifo = mkfifo(m_FifoName.c_str(), S_IRWXU);
	if (fifo != 0)
		std::cerr << errno << std::endl;
}

bool TaskManager::createTask(std::string FIFOName, std::string command )
{
	pid_t pid = fork();
	if (pid > 0 )
	{
		int tskMngFD = open(m_FifoName.c_str(), O_WRONLY);
		size_t nameLenght = strlen(FIFOName.c_str()); 
		write(tskMngFD, &nameLenght, 8);
		write(tskMngFD, FIFOName.c_str(), nameLenght + 1);
		
		size_t commLenght = strlen(command.c_str());
		write(tskMngFD, &commLenght, 8);
		write(tskMngFD, command.c_str(), commLenght + 1);
		close(tskMngFD);
	}
	else if (pid == 0)
	{
		int tskMngFD_R = open(m_FifoName.c_str(), O_RDONLY); // open mngFifo 
		exitIfNotSucceed(tskMngFD_R, "Cannot open fifo for read");

		char fifoName[20];
		size_t nameLenght;
		read(tskMngFD_R, &nameLenght, 8);
		read(tskMngFD_R, fifoName, nameLenght + 1 );

		char execCommand[20];
		size_t commLenght;
		read(tskMngFD_R, &commLenght, 8);
		read(tskMngFD_R, execCommand, commLenght + 1 );

		close(tskMngFD_R); // close mngFifo 


		int fD = mkfifo(fifoName, S_IRWXU); // create custom Fifo based on user input
		exitIfNotSucceed(fD, "Cannot create fifo");
		close(1);
		

		int tskMngFD_W = open(fifoName, O_WRONLY);
		exitIfNotSucceed(tskMngFD_W, "Cannot open fifo for write");
		
	 	std::string line =  std::string (execCommand);
		std::vector<std::string> arguments = strTokenizer(line, " ");

		std::string strCommand = (arguments.empty()) ? "." : arguments[0];

		char*  argsss[arguments.size() + 1] ;
		argsss [0] =  const_cast<char*>(strCommand.c_str());

		for (size_t i = 1; i < arguments.size(); ++i)
		{
			argsss[i] =  const_cast<char*>(arguments[i].c_str());	
		}
		argsss[arguments.size()] = nullptr;
		

		if(!findCommand(strCommand))
		{
			std::cout << "No such file directory" << std::endl;
			return -1;
		}
		else  
		{
			int execRep = execv(strCommand.c_str(), argsss);
			exitIfNotSucceed(execRep, strerror(errno) );
		}
	} 
	else
	{
		exitIfNotSucceed(-1, "Fork creation failed");
	}
	return true;
}


