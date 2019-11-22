CXX = g++
CXXFLAGS = -c -std=$(STD)
STD = c++11
BINARY = test.out

all: main.o testbench.o 
	$(CXX) $^ -o $(BINARY)

main.o: main.cpp testbench.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

testbench.o: testbench.cpp testbench.hpp source.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.o
	rm $(BINARY)
