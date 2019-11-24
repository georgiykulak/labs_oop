#include "testbench.hpp"
#include "source.hpp"

void print(std::string const& s)
{
        std::cout << s << std::endl;
}

void tilda()
{
		std::cout << 
		"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}

void testbench()
{
		tilda();
        print("~~~~~~THE TESTBENCH IS STARTING...~~~~~~");
        tilda();
        tilda();
		tilda();

		print("Test 1: Sorting with one file");
		print("Result of sotring:");		
		test_sort1("input1.text");
		tilda();

		print("Test 2: Sorting with two files");
		print("Result of sotring:");		
		test_sort2("input2.text", "output.text");

		tilda();
        tilda();
        tilda();
        print("~~~~~~~~~FINISH OF THE TESBENCH~~~~~~~~~");
        tilda();
}

void test_sort1(std::string const& path)
{
        Sorter sorter;
        std::vector<std::vector<std::string>> test;
        
        sorter.sort(path);
        
		test = sorter.getAllBlocks();
        std::cout << sorter.getNumber()  << "\n";
		std::cout << sorter.getCounter() << "\n"; 
	
        for ( auto const& v: test ) {
                for ( auto const& s: v ) {
                        std::cout << s << " ";
                }
                std::cout << "\n";
        }
}

void test_sort2(std::string const& path_in,
                std::string const& path_out)
{
        Sorter sorter(path_in, path_out);
        std::vector<std::vector<std::string>> test;
        
		test = sorter.getAllBlocks();
        std::cout << sorter.getNumber()  << "\n";
		std::cout << sorter.getCounter() << "\n"; 
	
        for ( auto const& v: test ) {
                for ( auto const& s: v ) {
                        std::cout << s << " ";
                }
                std::cout << "\n";
        }
}
