#pragma once

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "overload.hpp"

struct Sorter {
        public:
        ~Sorter();
        Sorter();
        Sorter(std::string const& path);
        Sorter(std::string const&, std::string const&);
        
        std::string const& getElem(size_t const& i,
                                   size_t const& j)
                                          const;
        std::vector<std::string> const&
                  getBlock(size_t const&) const;
        size_t const& getNumber()         const;
        size_t const& getCounter()        const;
        std::vector<std::vector<std::string>> const&
                      getAllBlocks()      const;
        Sorter& sort(std::string const& path);
        Sorter& sort(std::string const& src_path,
                     std::string const& dst_path);

        private:
        std::vector<std::vector<std::string>> block; // "a"
        size_t number;                               // "N"
        size_t counter;                              // "K"
        
        void _sort();
        void  _read(std::fstream& file);
        void _write(std::fstream& file) const;
        void _erase(std::fstream&, std::string const&);
};
