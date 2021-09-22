#include "TestAutomation.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <cstddef>
#include <cstring>
#include <sstream>

enum ETestResults
{
	Failure,
	Success,
	Unresolved
};

std::string TestAutomation::FINISHED = "Finished waliating regression tests...";
std::string TestAutomation::START = "Start walidating regression tests...";

const char* enumToString( int result)
{
	switch (result)
	{
		case ETestResults::Failure:
			return "Failure";
		case ETestResults::Success:
			return "Success";
		case ETestResults::Unresolved:
		default:
			return "Unresolved";
	}
}


void checkError(int err)
{
	if (err != 0)
		std::cerr << errno << std::endl; 
}

bool TestAutomation::run()
{
	if (m_WriteToFile)
	{
		writeToFile();
	}
	else
	{
		sendFeeadBack();
	}
}

void TestAutomation::addTest(testInfo info)
{
	arrTests.push_back(info);
}

void TestAutomation::writeToFile()
{

	int IOfd = close(1);
	if (IOfd)
	{
		std::cerr <<  errno << std::endl;
	}

	int fd = open("Report", O_WRONLY | O_CREAT | O_TRUNC);
	std::cout << START << std::endl;
	
	int status;
	for (int i = 0; i < arrTests.size(); i++)
	{
		pid_t pID = fork();
		if (pID > 0)
		{
			wait(&status);
			if (WIFSIGNALED(status) != 0)
			{
				std::cout << "During "<< arrTests[i].first << " execution accrued unresolved situation" << std::endl;
			}
		}
		else if (pID == 0)
		{
			std::cout << "Start "<< arrTests[i].first << std::endl;
			bool retValue = arrTests[i].second();

			std::cout << "Finished " << arrTests[i].first << " " << enumToString(retValue) << std::endl;
			exit(EXIT_SUCCESS);
		}
		else
		{
			std::cerr << "fork creation failed" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	
	std::cout << FINISHED << std::endl;
 	close(fd);
}

void TestAutomation::sendFeeadBack()
{
 	std::stringstream ss;
	char buf;
	int status;
	
	int IOfd = close(1);
	if (IOfd)
	{
		std::cerr <<  errno << std::endl;
	}

	int fd = open("Report", O_WRONLY | O_CREAT | O_TRUNC);
	ss << START << '\n';

	for (int i = 0; i < arrTests.size(); i++)
	{
		int pipes[2];
		if (pipe(pipes) == -1)
		{
			std::cerr << "An error ocurred with opening the pipi\n";
		}
		char buf[100];

		pid_t pID = fork();
		if (pID > 0)
		{
			ss << "Start "<< arrTests[i].first << '\n';

			close(pipes[1]);
			read(pipes[0], buf, 30);
			close(pipes[0]);
			wait(&status);
			if (WIFSIGNALED(status) != 0)
			{
				ss << "During "<< arrTests[i].first << " execution accrued unresolved situation" << '\n';
			} 
			else
			{
				ss << buf << '\n';
			}
		}
		else if (pID == 0)
		{
			close(pipes[0]);
			bool retValue = arrTests[i].second();
			std::string report = "Finished " ;
			report += arrTests[i].first;
			report += " ";
			report += enumToString(retValue);
			report += '\n';;

			write(pipes[1], report.c_str(),   strlen(report.c_str()) + 1);
			close(pipes[1]);
			exit(EXIT_SUCCESS);
		}
		else
		{
			std::cerr << "fork creation failed" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	ss << FINISHED << '\n';
	std::cout << ss.str() << std::endl;
}