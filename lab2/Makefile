CXX = g++
CXXFLAGS = -c -std=$(STD)
STD = c++11
BINARY = test.out

.PHONY: clean

$(BINARY): all

all: main.o testbench.o 
	$(CXX) $^ -o $(BINARY)

main.o: main.cpp testbench.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

testbench.o: testbench.cpp testbench.hpp source.hpp overload.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.o
	rm $(BINARY)
