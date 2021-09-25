#ifndef TASK_H
#define TASK_H

#include <string>
#include <unistd.h>
  #include <fcntl.h>
#include <sys/stat.h>

class Task
{

	public:
		Task(std::string FIFOname, std::string command )
		{
  			std::cout << 15 <<std::endl;

			mkfifo(FIFOname.c_str(),0666);
			close(1);
			int fd = open(FIFOname.c_str(), O_WRONLY);
			command += " > " + FIFOname;
			execv(command.c_str(), NULL);
			// write(fd, , FIFOName.length() + 1);	
		}
};

#endif // TASK_H