CXX = g++
CXXFLAGS = -c
STD = -std=c++11

all: main.o testbench.o 
	$(CXX) -o test_ringlist $^ $(STD)

main.o: main.cpp testbench.hpp
	$(CXX) $(CXXFLAGS) main.cpp $(STD) -o $@

testbench.o: testbench.cpp testbench.hpp source.hpp
	$(CXX) $(CXXFLAGS) testbench.cpp $(STD) -o $@

clean:
	rm *.o
	rm test_ringlist
