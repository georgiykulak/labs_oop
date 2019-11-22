#include "testbench.hpp"
#include "source.hpp"

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
        print("Test 1: Default constructor");
        tilda();

        RingList<int> ring1;
        
        if ( ring1.empty() ) 
                print("ring1 is empty now");
        print("Adding three elements");
        ring1.appendCurrent(13);
        ring1.appendCurrent(24);
        ring1.appendCurrent(356);
        print("Getting elements of ring1");
        ring1.getList();
        tilda();
        print("Test 2: Copy constructor");
        tilda();
        
        RingList<int> ring2(ring1);
        
        if ( !ring2.empty() )
                print("ring2 is not empty");
        print("Getting elements of ring2");
        ring2.getList();
        tilda();
        print("Test 3: Constructor with vector argument");
        tilda();

        std::vector<double> vctr{ 1.12, 4.25, -5.03, 23.4, 0.85 };
        RingList<double> ring3(vctr);
        
        print("Getting quantity of ring3 elements");
        std::cout << ring3.count() << "\n";
        print("Getting elements of ring3");
        ring3.getList();
        tilda();
        print("Test 4: Constructor with array argument");
        tilda();

        const size_t size = 4;
        unsigned* arr1(new unsigned [size]);
        for ( auto i = 0; i < size; ++i ) {
                arr1[i] = i + 1;
        }
        unsigned arr2[size] { 2, 4, 6, 8 };

        RingList<unsigned> r1(arr1, size);
        RingList<unsigned> r2(arr2, size);
        
        delete[] arr1;
        print("Getting ring r1 of first array");
        print("Getting with loop and \"moveRight()\"");
        for ( auto i = size; i; --i ) {
                std::cout
                << r1.getCurrent() 
                << " ";
                r1.moveRight();
        }
        print("");
        print("Analogically with function \"moveLeft()\"");
        for ( auto i = size; i; --i ) {
                std::cout
                << r1.getCurrent() 
                << " ";
                r1.moveLeft();
        }
        print("");
        tilda();
        print("Test 5: Poping and pushing elements");
        tilda();
        print("Poping");
        print("Getting ring r2 of second array");
        r2.getList();
        print("Appending");
        r2.appendCurrent(80);
        print("Getting ring r2 of second array");
        r2.getList();
        print("Inserting before current");
        r2.insertBeforeCurrent(60);
        print("Getting ring r2 of second array");
        r2.getList();
        print("Inserting after current");
        r2.insertAfterCurrent(70);
        print("Getting ring r2 of second array");
        r2.getList();
        tilda();
        print("Test 6: Comparing rings");
        tilda();
        
        RingList<int> ring6;
        
        print("Appending ring6");
        ring6.appendCurrent(13);
        ring6.appendCurrent(24);
        ring6.appendCurrent(356);
        print("Moving left the ring1");
        ring1.moveLeft();
        print("Getting elements of ring1");
        ring1.getList();
        print("Getting elements of ring6");
        ring6.getList();
        print("Comparing ring1 with ring6");
        if ( ring1.compare(ring6) )
                print("They are equal");
        else
                print("They are NOT equal");
        print("Comparing recursively");
        if ( ring1.compare_all(ring6) )
                print("They are equal");
        else
                print("They are NOT equal");
        tilda();
        tilda();
        tilda();
        print("~~~~~~~~~FINISH OF THE TESBENCH~~~~~~~~~");
        tilda();
        
		// release soon second testbench
        
        /*
        RingList<int> obj1(3);
        obj1++;
        obj1.getList();
        ++obj1;
        obj1.getList();
        obj1--;
        obj1.getList();
        --obj1;
        obj1.getList();
        */

        /*RingList<unsigned> obj2;
        std::cin  >> obj2;
        std::cout << obj2;
        */
}
