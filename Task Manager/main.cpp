#include <string>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "Client.h"

std::string TSKMANAGERFIFO = "tksFIFO";

int main()
{
	TaskManager::getInsance();
	Client cc;
	cc.execCommand("lsFifo", "ls");
	sleep(10);
	cc.showCommandInfo("ls");
	cc.removeFifo("ls");

	return 0;
};



// class Task_Manager
// {
// 		std::string FIFOPath;
// 	public:
// 		int createFIFO(std::string fifoPath)
// 		{
// 			FIFOPath = fifoPath;
// 			mkfifo(FIFOPath, 0666);
// 		}

// 		void addCommand(std::string commmand)
// 		{
// 			fd = open(FIFOPath, O_WRONLY);
// 			write(fd, commmand, strlen(commmand)+1);
//         	close(fd);
// 		}

// 		void run()
// 		{
// 			std::string command;
//         	fd = open(FIFOPath, O_RDONLY);
// 	        read(fd, command, 15);

// 			if (command.empty())
// 			{
// 				if (fork() ==0 )
// 				{
// 					Task task(command);	
// 				}
// 			}
// 		}
		

// };


// class Task
// {
// 	public:
// 		Task(std::string command)
// 		{
// 			FIFOPath = command;
// 			mkfifo(FIFOPath, 0666);
// 			run();
// 		}

// 	private:
// 		void run()
// 		{
// 			// 
// 			fd = open(FIFOPath, O_WRONLY);
// 			write(fd, "I have finished", strlen(commmand)+1);
//         	close(fd);
// 		}
// 		std::string FIFOPath;
// };
