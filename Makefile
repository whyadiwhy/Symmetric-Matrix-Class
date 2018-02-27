#This is a Makefile, it is useful in cases like when we have to compile many files
#and writing them all again and again is tedious and time consuming.
#It also keeps a check on which files are not changed, so it doesn't have to compile them again.

CXX=g++

#add -c -Wall later
CXXFLAGS= 

testcases.o: testcases.cpp
	$(CXX) $(CXXFLAGS) -std=c++11 testcases.cpp -o testcases

#This compiles all the files
all: testcases.o 