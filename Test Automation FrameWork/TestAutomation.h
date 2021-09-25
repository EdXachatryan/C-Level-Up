#ifndef TESTAUTOMATION_H
#define TESTAUTOMATION_H

#include <vector>
#include <string>
#include <iostream>

using fnPtr =  bool (*) ();
using testInfo = std::pair<std::string, fnPtr>;

class TestAutomation
{

	static std::string FINISHED ;
	static std::string START;
	public:
		TestAutomation(bool writeToFIle) : m_WriteToFile(writeToFIle)  {}
		void addTest(testInfo);
		bool run();

	private:
		bool m_WriteToFile;
		std::vector<testInfo> arrTests;
};


#endif // TESTAUTOMATION_H
