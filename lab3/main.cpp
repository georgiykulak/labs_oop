#include <iostream>

template <typename T>
struct Position {
        protected:
        T x;
        T y;

        public:
        virtual void setPos(T const& x, T const& y) = 0;
        virtual bool inField() const = 0;
        virtual std::string getPos() const = 0;
};

struct ChessFigure : public Position<uint8_t> {  
        public:
        virtual bool check(
                uint8_t const&,
                uint8_t const&)
                const = 0;

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
                return x <= 16 && y <= 16;
        }

        std::string getPos() const
        {
                if ( !inField(this->x, this->y) ) {
                        return "error: wrong coordinates";
                }

                std::string str;
                str += 'A' - 1 + x;
                str += ' ';
                str += '0' + y;
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
                return x == this->x && y != this->y ||
                       y == this->y && x != this->x;
        }

        virtual ~Castle() {}
        Castle() {}

        virtual bool check(
                uint8_t const& x,
                uint8_t const& y)
                const
        {
                return inField(x, y) &&
                       _straight(x, y);
        }
};

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
                                                        //переопределить методы
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

int main()
{
        
        return 0;
}
