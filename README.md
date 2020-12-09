# ezPoll
An epoll wrapper that is elegant and easy-to-use.

## Setup/Testing

First, install googletest if you haven't already. 

In the Makefile, on line 20, change the GTEST_DIR variable to 
the location of your googletest root directory, i.e. if your googletest 
repo is cloned in the folder ~/A, then your path would be ~/A/googletest since 
this is the root folder of the source code.

Run ./test.sh to make the tests and run them.
