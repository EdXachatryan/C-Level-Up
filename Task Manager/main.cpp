#include <string>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include "Client.h"
  #include <sys/inotify.h>


#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define EVENT_BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

const char* s_TskManagerFifo = "tksFIFO";
int inotify_fD = inotify_init();

int main()
{
	TaskManager::getInsance();
	Client cc;
	cc.execCommand("lsFifo", "ls");
	cc.execCommand("pwdFifo", "pwd");

	cc.showCommandInfo("lsFifo");
	cc.showCommandInfo("pwdFifo");

	TaskManager::releaseInstance();
	return 0;
};
