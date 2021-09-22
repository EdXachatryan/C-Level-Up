#ifndef TESTAUTOMATION_H
#define TESTAUTOMATION_H

#include <vector>
#include <string>
#include <iostream>

using fnPtr =  bool (*) ();
using testInfo = std::pair<const char*, fnPtr>;

class TestAutomation
{

	static std::string FINISHED ;
	static std::string START;
	public:
		TestAutomation(bool writeToFIle) : m_WriteToFile(writeToFIle)  {}
		void addTest(testInfo);
		void clearTests();

		bool run();


	private:
		void writeToFile();
		void sendFeeadBack();

	private:
		bool m_WriteToFile;
		std::vector<testInfo> arrTests;
};


#endif // TESTAUTOMATION_H
