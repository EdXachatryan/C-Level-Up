
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

	test.addTest(std::make_pair ("test1", &test1));
	test.addTest(std::make_pair ("test2", &test2));
	test.addTest(std::make_pair ("test3", &test3));
	test.addTest(std::make_pair ("test4", &test4));
	test.run();

	return 0;
}