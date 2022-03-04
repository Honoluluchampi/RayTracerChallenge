# Ray Tracer Challenge
I'm implementing Ray Tracer Challenge by Jamis Buck with C++ and Google Test.  
I wrote Makefile for easy test builds. You can build your test programs like below.

*directory structure   
---include--(something).hpp ( or .h )  
|--src------(something).cpp  
|--test-----(something)_test.cpp  

*the first line of Makefile  
UNIT_NAME = (something)

*the second line of Makefile  
GTEST_DIR = (path to the google test's directory)  

*execute following make commands
make  // compile src/(something).cpp
make test  // compile test/(something)_test.cpp
make run // execute bin/(something)_test