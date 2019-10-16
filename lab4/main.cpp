//Вернуть инит
//Заменить файл в инит на шаредпоинтер
//Добавить вывод ошибок

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

struct Sorter {
        private:
        std::vector<std::string> block; //a blocks
        std::size_t number;             //N
        std::size_t counter;            //K

        public:
        Sorter();
        Sorter(std::string path);
        ~Sorter();
        std::string const& getBlock(size_t) const;
        std::size_t const& getNumber()  const;
        std::size_t const& getCounter() const;
        std::vector<std::string> const& 
                        getAllBlocks()  const;
        Sorter& sort(std::string path);

        private:
        void  _read(std::fstream& file);
        void _write(std::fstream& file);
        void _erase(std::fstream&, std::string);
};

int main()
{
        Sorter sorter;
        std::string path = "/home/gosha/Desktop/test.txt";
        std::vector<std::string> test;
        
        sorter.sort(path);
        test = sorter.getAllBlocks();
        std::cout << test.size() << "\n";
        for ( auto const& i: test ) {
                std::cout << i << " ";
        }
        std::cout << "\n";
        
        return 0;
}

bool operator< (std::string s1, std::string s2)
{
    auto sz1 = s1.length();
    auto sz2 = s2.length();
    
    for ( auto i = 0; i < sz1 && i < sz2; ++i ) {
        if ( s1[i] < s2[i] )
            return  true;
        if ( s1[i] > s2[i] )
            return false;
    }
    
    return sz1 < sz2;
}

Sorter::Sorter()
{}

Sorter::Sorter(std::string path)
{
        sort(path);
}

Sorter::~Sorter()
{}

inline std::size_t const& Sorter::getNumber()  const
{
        return   number;
}

inline std::size_t const& Sorter::getCounter() const
{
        return  counter;
}

inline std::string const& 
                Sorter::getBlock(size_t i) const
{
        return block[i];
}

inline std::vector<std::string> const&
                Sorter::getAllBlocks() const
{
        return    block;
}

inline Sorter& Sorter::sort(std::string path)
{
        std::fstream file;
        std::string temp;
        
        file.open(path);
        
        if ( !file.is_open() ) {
                std::cout << "Error: file is not open\n";
                goto out;
        }
        
        _read(file);
        
        std::sort( block.begin(), block.end(), 
                   [](std::string s1, std::string s2)
                {
                        return s1 < s2;
                }
        );
        
        _erase(file, path);

        _write(file);

        out:
        
        file.close();
        
        return *this;
}

inline void Sorter::_read(std::fstream& file)
{
        std::string temp;
        size_t cnt = number;

        file.seekg(0, std::ios::beg);

        file >> number;
        file.seekg(1, std::ios::cur);
        
        file >> counter;
        file.seekg(1, std::ios::cur);
        
        while ( !file.eof() && --cnt ) {
                file >> temp;
                block.push_back(temp);
                if ( file.fail() )
                        break;
        }/////////////////////////////////////////////////////////////остановился здесь

        file.seekg(0, std::ios::beg);
}

inline void Sorter::_write(std::fstream& file)
{
        file << number << "\n";
        file << counter << "\n";
        for ( auto const& i: block ) {
                file << i << " ";
        }
        
        file.seekg(0, std::ios::beg);
}

inline void Sorter::_erase(std::fstream& file,
                           std::string path)
{
        file.close();
        remove(path.c_str());
        FILE* pFile = fopen(path.c_str(), "w+r");
        fclose(pFile);
        file.open(path);
}
