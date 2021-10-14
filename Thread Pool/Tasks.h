#ifndef TASKS_H
#define TASKS_H

#include "utils.h"

inline void Task1(void*)
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

#endif