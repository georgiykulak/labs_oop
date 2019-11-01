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
        
                this->x = x - 1;
                this->y = y - 1;
        }
    
        bool inField(
                uint8_t const& x,
                uint8_t const& y)
                const
        {
                return x < 8 && y < 8;
        }

        std::string getPos() const
        {
                if ( !inField(x, y) ) {
                        return "error: \
                                wrong coordinates";
                }

                std::string str;
                str += '<';
                str += 'A' + x;
                str += '1' + y;
                str += '>';

                return str;
        }
};

struct Castle : public ChessFigure {
        public:
        virtual bool _straight(
                uint8_t const& x,
                uint8_t const& y)
                const
        {
                return x == getX() && y != getY() ||
                       y == getY() && x != getX();
        }

        virtual ~Castle() {}
        Castle(uint8_t const& x = 0,
                uint8_t const& y = 0)
        {
                setPos(x, y);
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
/*
struct Officer : public ChessFigure {
        public:
        virtual bool _cross(
                uint8_t const& x,
                uint8_t const& y)
                const
        {
                return x != this->x  &&
                       y != this->y  &&
                       x - this->x == y - this->y;
        }

        virtual ~Officer() {}
        Officer() {}

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
        virtual ~Horse() {}
        Horse() {}

        //remove virtual
        virtual bool _cross(
                uint8_t const& x,
                uint8_t const& y)
                const
        {
                return 
                //horizontal comparing
                (this->x + 2 == x &&
                 this->y + 1 == y) ||
                (this->x + 2 == x &&
                 this->y - 1 == y) ||
                (this->x - 2 == x &&
                 this->y + 1 == y) ||
                (this->x - 2 == x &&
                 this->y - 1 == y) ||
                //vertical comparing
                (this->y + 2 == y &&
                 this->x + 1 == x) ||
                (this->y + 2 == y &&
                 this->x - 1 == x) ||
                (this->y - 2 == y &&
                 this->x + 1 == x) ||
                (this->y - 2 == y &&
                 this->x - 1 == x);
        }
};

struct Queen : virtual public Castle,
               virtual public Officer
               {
        public:
        virtual ~Queen() {}
        Queen() {}

        virtual bool check(
                uint8_t const& x,
                uint8_t const& y)
                const
        {
                return Castle::inField(x, y) &&
                      (_cross(x, y)  ||
                       _straight(x, y));
        }
};

struct King : public Queen {
        private:
        bool moved;

        public:
        virtual bool _straight(
                uint8_t const& x,
                uint8_t const& y)
                const
        {
                return (this->x + 1 == x ||
                        this->x - 1 == x) &&
                        this->y == y      ||
                       (this->y + 1 == y ||
                        this->y - 1 == y) &&
                        this->x == x;
        }

        virtual bool _straight(
                uint8_t const& x,
                uint8_t const& y)
                const
        {
                return 1;
        }

        virtual bool _special(
                uint8_t const& x,
                uint8_t const& y)
                const
        {
                return y == 1 &&
                       !moved &&
                       (x == 1 || x == 16);
        }

        virtual ~King() {}
        King() : moved{false}
        {}

        virtual bool check(
                uint8_t const& x,
                uint8_t const& y)
                const
        {
                return Officer::inField(x, y)   &&
                      (_cross(x, y)    ||
                       _straight(x, y) ||
                       _special(x, y)  );
        }
};

struct Pawn : public King {
        //valuable for checking attack variant
        private:
        bool moved;

        public:
        virtual ~Pawn() {}
        Pawn() : moved{false}
        {}

        //
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
        Castle obj1;
        obj1.setPos(1, 2);
        print(obj1.getPos());
        get_point(obj1.getX(), obj1.getY());
        yes_no( obj1.check(1, 4) );
        return 0;
}
