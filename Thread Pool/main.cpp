#include <iostream>
#include "Thread Pool.h"
#include "Tasks.h"

int main()
{
	ThreadPool oThreadPool(4);

	oThreadPool.addTask(Task1);
	oThreadPool.addTask(Task2);
	oThreadPool.addTask(Task3);


	return 0;
}