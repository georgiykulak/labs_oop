//доделать пешку
//закончить тестбенч
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

        int8_t getX() const { return x; }
        
        int8_t getY() const { return y; }

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
/*
struct Pawn : public King {
        public:
        ~Pawn() {}
        Pawn() : moved{false}
        {}

        bool _special(...)
};
*/

void print(std::string const& obj)
{
        std::cout << obj << std::endl;
}

void get_point(int const& x, int const& y)
{
        std::cout << x << " " << y << "\n";
}

void yes_no(bool const& flag)
{
        std::cout << (flag ? "yes\n" : "no\n");
}

int main()
{
        Castle castle;
        castle.setPos(1, 2);
        print(castle.getPos());
        get_point(castle.getX(), castle.getY());
        yes_no(castle.check(1, 4));
        
        Officer officer(2, 5);
        yes_no(officer.check(1, 6));
        
        Horse horse;
        yes_no(horse.check(3, 3));
        
        Queen queen;
        print(queen.getPos());
        queen.setPos(5, 1);
        yes_no(queen.check(5, 3));

        King king;
        yes_no(king.check(5, 2));
        
        return EXIT_SUCCESS;
}
