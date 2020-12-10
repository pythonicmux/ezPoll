#!/bin/bash

GTEST_HOME=/usr
LD_LIBRARY_PATH=$GTEST_HOME/lib:$LD_LIBRARY_PATH

g++ tests/ezPollTest.cpp -I ./include -I ./src -lgtest -lgtest_main -lpthread

./a.out

rm a.out
