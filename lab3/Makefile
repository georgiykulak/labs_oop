CXX = g++
CXXFLAGS = -c -std=$(STD)
STD = c++11
BINARY = test.out

.PHONY: clean

$(BINARY): all

all: main.o testbench.o chessfigure.o castle.o officer.o horse.o queen.o king.o pawn.o
	$(CXX) $^ -o $(BINARY)

main.o: main.cpp testbench.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

testbench.o: testbench.cpp testbench.hpp source.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

chessfigure.o: chessfigure.cpp chessfigure.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

castle.o: castle.cpp castle.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

officer.o: officer.cpp officer.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

horse.o: horse.cpp horse.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

queen.o: queen.cpp queen.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

king.o: king.cpp king.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

pawn.o: pawn.cpp pawn.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.o
	rm $(BINARY)
