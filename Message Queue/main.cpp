#include "Message Queue.h"
#include <unistd.h>
#include "handlers.h"

int main()
{

	MessageQueue oMessageQueue;

	oMessageQueue.RegisterHandler(handler1);
	oMessageQueue.RegisterHandler(handler2);

	oMessageQueue.AddMessage("Hello");	
	oMessageQueue.AddMessage("World");
	oMessageQueue.AddMessage("!!!");

    sleep(1);

	return 0;
}