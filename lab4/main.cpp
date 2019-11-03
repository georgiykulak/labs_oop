//Распихать все на 8 файлов: main.cpp, testbench.hpp, testbench.hpp, source.hpp, source.cpp, sort.hpp(метод сортировки и перегруженный оператор для строк),
//sort.cpp, all_in.hpp(сюда включить все заголовочные файлы)
//Сделать Makefile

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

struct Sorter {
        private:
        std::vector<std::vector<std::string>> block; // "a"
        size_t number;                               // "N"
        size_t counter;                              // "K"

        public:
        ~Sorter();
        Sorter();
        Sorter(std::string const& path);
        Sorter(std::string const&, std::string const&);
        std::string const&
                getElem(size_t const& i,
                                size_t const& j)
                                          const;
        std::vector<std::string> const&
                  getBlock(size_t const&) const;
        std::size_t const& getNumber()    const;
        std::size_t const& getCounter()   const;
        std::vector<std::vector<std::string>> const&
                           getAllBlocks() const;
        Sorter& sort(std::string const& path);
        Sorter& sort(std::string const& src_path,
                     std::string const& dst_path);

        private:
        void _sort();
        void  _read(std::fstream& file);
        void _write(std::fstream& file) const;
        void _erase(std::fstream&, std::string const&);
};

inline void test_sort1(std::string path)
{
        Sorter sorter;
        std::vector<std::vector<std::string>> test;
        
        sorter.sort(path);
        
	test = sorter.getAllBlocks();
        std::cout << sorter.getNumber()  << "\n";
	std::cout << sorter.getCounter() << "\n"; 
	
        for ( auto const& v: test ) {
                for ( auto const& s: v ) {
                        std::cout << s << " ";
                }
                std::cout << "\n";
        }
}

inline void test_sort2(std::string path_in,
                       std::string path_out)
{
        Sorter sorter(path_in, path_out);
        std::vector<std::vector<std::string>> test;
        
	test = sorter.getAllBlocks();
        std::cout << sorter.getNumber()  << "\n";
	std::cout << sorter.getCounter() << "\n"; 
	
        for ( auto const& v: test ) {
                for ( auto const& s: v ) {
                        std::cout << s << " ";
                }
                std::cout << "\n";
        }
}

int main()
{
	test_sort1("/home/gosha/Desktop/test1.txt");
	test_sort2("/home/gosha/Desktop/test2.txt",
                   "/home/gosha/Desktop/out.txt");

	return EXIT_SUCCESS;
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

Sorter::~Sorter()
{}

Sorter::Sorter()
{}

Sorter::Sorter(std::string const& path)
{
        sort(path);
}

Sorter::Sorter(std::string const& src_path,
               std::string const& dst_path)
{
        sort(src_path, dst_path);
}

inline std::size_t const& Sorter::getNumber()  const
{
        return  number;
}

inline std::size_t const& Sorter::getCounter() const
{
        return counter;
}

inline std::string const&
        Sorter::getElem(
                size_t const& i,
                size_t const& j)
                const
{
        return block[i][j];
}

inline std::vector<std::string> const& 
        Sorter::getBlock(size_t const& i) const
{
        return block[i];
}

inline std::vector<std::vector<std::string>> const&
        Sorter::getAllBlocks() const
{
        return block;
}

inline Sorter& Sorter::sort(std::string const& path)
{
        std::fstream file;
        std::string temp;
        
        file.open(path);
        
        if ( !file.is_open() ) {
                std::cerr << "Error: file is not open\n";
                file.close();
                return *this;
        }
        
        _read(file);
        
        _sort();
       
        _erase(file, path);

        _write(file);

        file.close();
        
        return *this;
}

inline Sorter& Sorter::sort(std::string const& src_path,
                            std::string const& dst_path)
{
        std::fstream ifile;
        std::fstream ofile;
        std::string temp;
        
        ifile.open(src_path);
        ofile.open(dst_path);
        
        if ( !ifile.is_open() || !ofile.is_open() ) {
                std::cerr << "Error: file is not open\n";
                ifile.close();
                ofile.close();
                return *this;
        }
        
        _read(ifile);

        ifile.close();

        _sort();

        _write(ofile);

        ofile.close();

        return *this;
}

inline void Sorter::_sort()
{
        for ( auto& blk: block ) {
                std::sort(
                          blk.begin(),
                          blk.end(), 
                          [](std::string str1,
                             std::string str2)
                          { return str1 < str2; }
                );
        }
}

inline void Sorter::_read(std::fstream& file)
{
        std::string temp;

        file.seekg(0, std::ios::beg);

        file >> number;
        file.seekg(1, std::ios::cur);
        
        file >> counter;
        file.seekg(1, std::ios::cur);
        
        block.resize(number,
		     std::vector<std::string>(counter));
        
	for ( auto& v: block ) {
                for ( auto& s: v ) {
                        file >> s;
                }
        }
        
        file.seekg(0, std::ios::beg);
}

inline void Sorter::_write(std::fstream& file) const
{
        file << number << "\n";
        file << counter << "\n";
        
        for ( auto const& v: block ) {
                for ( auto const& s: v ) {
                        file << s << " ";
                }
                file << "\n";
        }
        
        file.seekg(0, std::ios::beg);
}

inline void Sorter::_erase(std::fstream& file,
                           std::string const& path)
{
        file.close();
        remove(path.c_str());
        FILE* pFile = fopen(path.c_str(), "w+r");
        fclose(pFile);
        file.open(path);
}
