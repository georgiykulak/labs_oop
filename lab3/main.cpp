//Сделать 5 файлов: main.cpp, source.hpp, source.cpp, testbench.hpp, testbench.cpp + Makefile

#include <iostream>

struct ChessFigure {
        private:
        uint8_t x;
        uint8_t y;
        
        public:
        virtual ~ChessFigure() {}
        
        virtual bool check(
                uint8_t const&,
                uint8_t const&)
                const = 0;

        uint8_t getX() const { return x; }
        
        uint8_t getY() const { return y; }

        virtual void setPos(
                uint8_t const& x,
                uint8_t const& y)
        {
                if ( !inField(x, y) ) {
                        return;
                }
        
                this->x = x;
                this->y = y;
        }
    
        bool inField(
                uint8_t const& x,
                uint8_t const& y)
                const
        {
                return x > 0 && x < 9 && y > 0 && y < 9;
        }

        std::string getPos() const
        {
                if ( !inField(x, y) ) {
                        return "error: \
                                wrong coordinates";
                }

                std::string str;
                str += '<';
                str += 'A' - 1 + x;
                str += '0' + y;
                str += '>';

                return str;
        }
};

struct Castle : virtual public ChessFigure {
        public:
        virtual ~Castle() {}
        
        Castle(uint8_t const& x = 1,
                uint8_t const& y = 1)
        {
                if ( inField(x, y) ) {
                        setPos(x, y);
                }
                else    setPos(1, 1);
        }

        virtual bool _straight(
                uint8_t const& x,
                uint8_t const& y)
                const
        {
                return x == getX() && y != getY() ||
                       y == getY() && x != getX();
        }
        
        virtual bool check(
                uint8_t const& x,
                uint8_t const& y)
                const
        {
                return inField(x, y) &&
                       _straight(x, y);
        }
};

struct Officer : virtual public ChessFigure {
        public:
        virtual ~Officer() {}
        
        Officer(uint8_t const& x = 3,
                uint8_t const& y = 1)
        {
                if ( inField(x, y) ) {
                        setPos(x, y);
                }
                else    setPos(3, 1);
        }

        virtual bool _cross(
                uint8_t const& x,
                uint8_t const& y)
                const
        {
                return x != getX()  &&
                       y != getY()  &&
                       std::abs((int)x - (int)getX()) ==
                       std::abs((int)y - (int)getY());
        }

        virtual bool check(
                uint8_t const& x,
                uint8_t const& y)
                const
        {
                return inField(x, y) &&
                       _cross(x, y);
        }
};

struct Horse : public Officer {
        public:
        ~Horse() {}
        
        Horse(uint8_t const& x = 2,
                uint8_t const& y = 1)
        {
                if ( inField(x, y) ) {
                        setPos(x, y);
                }
                else    setPos(2, 1);
        }

        bool _cross(
                uint8_t const& x,
                uint8_t const& y)
                const
        {
                return x != getX() &&
                       y != getY() &&
                       //horizontal comparing
                      (getX() + 2 == x &&
                       getY() + 1 == y) ||
                      (getX() + 2 == x &&
                       getY() - 1 == y) ||
                      (getX() - 2 == x &&
                       getY() + 1 == y) ||
                      (getX() - 2 == x &&
                       getY() - 1 == y) ||
                       //vertical comparing
                      (getY() + 2 == y &&
                       getX() + 1 == x) ||
                      (getY() + 2 == y &&
                       getX() - 1 == x) ||
                      (getY() - 2 == y &&
                       getX() + 1 == x) ||
                      (getY() - 2 == y &&
                       getX() - 1 == x);
        }
};

struct Queen : public Castle, public Officer {
        public:
        virtual ~Queen() {}
        
        Queen(uint8_t const& x = 5,
                uint8_t const& y = 1)
        {
                if ( inField(x, y) ) {
                        setPos(x, y);
                }
                else    setPos(5, 1);
        }

        virtual bool check(
                uint8_t const& x,
                uint8_t const& y)
                const
        {
                return inField(x, y) &&
                      (_cross(x, y)  ||
                       _straight(x, y));
        }
};

struct King : public Queen {
        public:
        virtual ~King() {}
        
        King(uint8_t const& x = 4,
                uint8_t const& y = 1)
        {
                if ( inField(x, y) ) {
                        setPos(x, y);
                }
                else    setPos(4, 1);
        }
        
        virtual bool _straight(
                uint8_t const& x,
                uint8_t const& y)
                const
        {
                return (getX() + 1 == x ||
                        getX() - 1 == x) &&
                       (getY() == y)     ||
                       (getY() + 1 == y ||
                        getY() - 1 == y) &&
                       (getX() == x);
        }

        virtual bool _cross(
                uint8_t const& x,
                uint8_t const& y)
                const
        {
                return x != getX()  &&
                       y != getY()  &&
                       std::abs((int)x - (int)getX())
                       == 1 &&
                       std::abs((int)y - (int)getY())
                       == 1;
        }

        virtual bool _special(
                uint8_t const& x,
                uint8_t const& y)
                const
        {
                return  getY() == y        &&
                        getX() == 4        &&
                       (x == 1 || x == 16) &&
                       (y == 1 || y == 16);
        }

        virtual bool check(
                uint8_t const& x,
                uint8_t const& y)
                const
        {
                return inField(x, y)   &&
                      (_cross(x, y)    ||
                       _straight(x, y) ||
                       _special(x, y)  );
        }
};

struct Pawn : public King {
        public:
        ~Pawn() {}
        
        Pawn(uint8_t const& x = 1,
                uint8_t const& y = 2)
        {
                if ( inField(x, y) ) {
                        setPos(x, y);
                }
                else    setPos(1, 2);
        }

        bool _special(
                uint8_t const& x,
                uint8_t const& y)
                const
        {
                return ((2 == getY() && 4 == y) ||
                        (7 == getY() && 5 == y)) &&
                         x == getX();
        }
};

void print(std::string const& obj)
{
        std::cout << obj << std::endl;
}

void yes_no(bool const& flag)
{
        std::cout << (flag ? "yes\n" : "no\n");
}

void tilda()
{
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}

int main()
{
        tilda();
        print("~~~~~~~~~TESTBENCH~~~~~~~~~");
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
        
        return EXIT_SUCCESS;
}
