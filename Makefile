
#  Author: Rafael Ramirez & Matt D Jaranilla
#  RedID: 825477088 & 825452453

# for c++ compiler
CXX = g++

# -std=c++11  C/C++ variant to use, e.g. C++ 2011 
# -Wall       show the necessary warning files
# -g3         include information for symbolic debugger e.g. gdb 
CXXFLAGS = -std=c++11 -Wall -g3 -c

# object files
OBJS = main.o report.o producers.o consumers.o

# Program name
PROGRAM = tradecrypto

# instead of calling countsubstrings, can just make all
all: $(PROGRAM)

# The program depends upon its object files
$(PROGRAM) : $(OBJS)
	$(CXX) -pthread -o $(PROGRAM) $(OBJS)

main.o : main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

report.o : report.cpp report.h
	$(CXX) $(CXXFLAGS) report.cpp

producers.o : producers.cpp producers.h
	$(CXX) $(CXXFLAGS) producers.cpp

consumers.o : consumers.cpp consumers.h
	$(CXX) $(CXXFLAGS) consumers.cpp

clean :
	rm -f *.o $(PROGRAM)


