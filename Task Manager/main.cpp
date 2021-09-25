#include <string>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "Client.h"

const char* s_TskManagerFifo = "tksFIFO";

int main()
{
	TaskManager::getInsance();
	Client cc;
	cc.execCommand("lsFifo", "ls");
	sleep(10);
	cc.execCommand("pwdFifo", "pwd");
	sleep(10);
	cc.showCommandInfo("ls");
	cc.showCommandInfo("pwd");

	TaskManager::releaseInstance();
	return 0;
};
