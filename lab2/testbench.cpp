#include "testbench.hpp"
#include "source.hpp"
#include "overload.hpp"

void print(std::string s)
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

		tilda();
        print("First matrix: ");
        Matrix<int> det1(3, 4);
        det1.fill();
        std::cout << det1 << "\n";

		tilda();
        print("Second matrix: ");
        Matrix<int> det2(4, 5);
        det2.fill();
        std::cout << det2 << "\n";
		
		tilda();
		print("Third matrix: ");
        Matrix<int> det3;
        det3.resize(3, 5);
        det3.fill();
        std::cout << det3 << "\n";
        
		tilda();
		print("Multipling");
        Matrix<int> det4 = det1 * det2;
        std::cout << det4 << "\n";
		
		tilda();
        print("Adding third and fourth");
        std::cout << det4 + det3 << "\n";
		
		tilda();
        print("Determinating");
        Matrix<long> det(4, 4);
        det.fill();
        std::cout << det  << "\n";
        std::cout << *det << "\n";

		tilda();
        print("Comparing third and fourth");
        if ( det3 == det4 ) {
                print("equal");
        }
        if ( det3 != det4 ) {
                print("not equal");
        }
        if ( det3 < det4 ) {
                print("smaller");
        }
        else {
                print("bigger or equal");
        }

		tilda();
        tilda();
        tilda();
        print("~~~~~~~~~FINISH OF THE TESBENCH~~~~~~~~~");
        tilda();
}
