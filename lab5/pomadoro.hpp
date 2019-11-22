#pragma once

#define DEF_POMADORO

class Pomadoro {
        public:
        ~Pomadoro();
        Pomadoro();
        Pomadoro (Pomadoro const&);
        Pomadoro& operator= (Pomadoro const&);
};
