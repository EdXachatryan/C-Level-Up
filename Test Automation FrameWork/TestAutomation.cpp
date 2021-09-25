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

void TestAutomation::addTest(testInfo info)
{
	arrTests.push_back(info);
}

bool TestAutomation::run()
{

	int stdout_copy = dup(1);
	int rep_fd = open("Report", O_WRONLY | O_CREAT | O_TRUNC);
	if (rep_fd == -1)
	{
		return false;
	}

	int pipes[2];
	dup2(rep_fd, 1);
	int status;
	for (int i = 0; i < arrTests.size(); i++)
	{
		pid_t pID = fork();
		if (pID > 0)
		{
			if (m_WriteToFile)
			{
				wait(&status);
				if (WIFSIGNALED(status) != 0)
				{
					std::cout << "During "<< arrTests[i].first << " execution accrued unresolved situation" << std::endl;
				}
			}
			else
			{	
				std::stringstream ss;
				close(pipes[1]);
				char* buffer = new char[1024];
				int n;
				while((n=read(pipes[0],buffer,1))>0){
					ss << buffer;
				}
				close(pipes[0]);
				wait(&status);
				if (WIFSIGNALED(status) != 0)
				{
					ss << "During "<< arrTests[i].first << " execution accrued unresolved situation" << '\n';
				}
				std::cout << ss.str() << std::endl;
			}
		}
		else if (pID == 0)
		{
			std::string report = std::string("Start ") +  arrTests[i].first ;
			
			if (!m_WriteToFile)
			{	
				close(pipes[0]);
				dup2(pipes[1], 1);
				std::cout << "using pipes" << std::endl; // for test
			}
			std::cout << report << std::endl;

			bool retValue = arrTests[i].second();
			report = "Finished " ;
			report += arrTests[i].first;
			report += " ";
			report += enumToString(retValue);
			report += '\n';

			std::cout << report << std::endl;

			if (!m_WriteToFile)
			{
				close(pipes[1]);
			}
			exit(EXIT_SUCCESS);
		}
		else
		{
			std::cerr << "fork creation failed" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	
	dup2(stdout_copy, 1 );
	close(stdout_copy);
	return true;
}