CXX = g++
CXXFLAGS = -c -std=$(STD)
STD = c++11
BINARY = test.out

.PHONY: fill erase clean

all: main.o testbench.o source.o overload.o
	$(CXX) $^ -o $(BINARY)
	./fill

main.o: main.cpp testbench.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

testbench.o: testbench.cpp testbench.hpp source.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

source.o: source.cpp source.hpp overload.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

overload.o: overload.cpp overload.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

fill:
	./fill

erase:
	echo "" > input1.text
	echo "" > input2.text
	echo "" > output.text

clean:
	rm *.text 2> /dev/null
	rm *.o 2> /dev/null
	rm $(BINARY) 2> /dev/null
