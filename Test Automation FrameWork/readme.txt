===== Test Automation FrameWork ======

By default argument is redirect
redirect - each child redirect his output to the report file
sendFeedBack - each child send data to his parrent 

compile    g++ -std=c++11 TestFunctions.cpp TestAutomation.cpp main.cpp -o testFrameWork
run 	   ./testFrameWork ( redirect or sendFeedBack )  
 
e.g 		 "./testFrameWork redirect" or just "./testFrameWork"
 
e.g  		"./testFrameWork sendFeedBack"
 
 
