
#include "TestAutomation.h"
#include "TestFunctions.h"

int main(int argc, char* argv[])
{
	std::string input ;
  	for (int i = 1; i < argc; ++i)
        input = argv[i];

	bool isRedirectional = true;
	if (input == "sendFeedBack")
	{
		isRedirectional = false;
	}
		
	TestAutomation test(isRedirectional);

	test.addTest(std::make_pair ("testIsEqualZerro", &testIsEqualZerro));
	test.addTest(std::make_pair ("testConnection", &testConnection));
	test.addTest(std::make_pair ("testDevidZerro", &testDevidZerro));
	test.run();

	return 0;
}