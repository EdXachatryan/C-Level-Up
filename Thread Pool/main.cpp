#include <iostream>
#include "Thread Pool.h"
#include "Tasks.h"

inline void Task1()
{
	utils::syncPrint("Running Task1 :");
}

inline void Task2()
{
	utils::syncPrint("Running Task2 :");
}

inline void Task3()
{
	utils::syncPrint("Running Task3 :");
}


int main()
{
	ThreadPool oThreadPool(4);
	sleep(1);
	
	oThreadPool.addTask(Task1);
	oThreadPool.addTask(Task2);
	oThreadPool.addTask(Task3);
	oThreadPool.shutDown();

	return 0;
}