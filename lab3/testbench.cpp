#include "testbench.hpp"
#include "source.hpp"

void print(std::string const& s)
{
        std::cout << s << std::endl;
}

void yes_no(bool const& flag)
{
        std::cout << (flag ? "yes\n" : "no\n");
}

void tilda()
{
        std::cout << 
			"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}

void testbench()
{
		tilda();
        print("~~~THE TESTBENCH IS STARTING...~~~");
        tilda();
        tilda();
        tilda();
        print("Test 1: Creating objects");
        print("and checking moves on field");
        tilda();
        
        print("Castle:");
        Castle castle;
        castle.setPos(1, 2);
        print(castle.getPos());
        yes_no(castle.check(1, 4));
        castle.setPos(2, 2);
        print(castle.getPos());
        yes_no(castle.check(1, 4));
        tilda();

        print("Officer:");
        Officer officer(2, 5);
        print(officer.getPos());
        yes_no(officer.check(1, 6));
        officer.setPos(5, 3);
        print(officer.getPos());
        yes_no(officer.check(6, 5));
        tilda();
        
        print("Horse:");
        Horse horse;
        print(horse.getPos());
        yes_no(horse.check(3, 3));
        horse.setPos(7, 8);
        print(horse.getPos());
        yes_no(horse.check(7, 6));
        tilda();
        
        print("Queen:");
        Queen queen;
        queen.setPos(5, 1);
        print(queen.getPos());
        yes_no(queen.check(5, 3));
        print(queen.getPos());
        yes_no(queen.check(4, 6));
        tilda();

        print("King:");
        King king;
        king.setPos(8, 4);
        print(king.getPos());
        yes_no(king.check(7, 3));
        print(king.getPos());
        yes_no(king.check(6, 3));
        tilda();
        
        print("Pawn:");
        Pawn pawn(2, 2);
        print(pawn.getPos());
        yes_no(pawn.check(2, 4));
        pawn.setPos(2, 4);
        print(pawn.getPos());
        yes_no(pawn.check(2, 6));
        tilda();

        print("Test 2: Dynamic");
        print("memory checking");
        tilda();

        print("ChessFigure -> King");
        ChessFigure* ptr1 = new King(6, 2);
        print(ptr1->getPos());
        //must be "yes" because ptr point on King object
        yes_no(ptr1->check(7, 2));
        delete ptr1;
        tilda();

        print("Queen -> Pawn");
        Queen* ptr2 = new Pawn(6, 3);
        print(ptr2->getPos());
        //must be "no" because pawn can't move like that
        yes_no(ptr2->check(8, 5));
        delete ptr2;
        tilda();

        print("Officer -> Horse");
        Officer* ptr3 = new Horse(5, 5);
        print(ptr3->getPos());
        //must be "yes" because horse can move like that
        yes_no(ptr3->check(7, 6));
        delete ptr3;
       	
		tilda();
        tilda();
        tilda();
        print("~~~~~~FINISH OF THE TESBENCH~~~~~~");
        tilda();
}
