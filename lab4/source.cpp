#include "source.hpp"

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

size_t const& Sorter::getNumber()  const
{
        return  number;
}

size_t const& Sorter::getCounter() const
{
        return counter;
}

std::string const& Sorter::getElem(
                size_t const& i,
                size_t const& j)
                const
{
        return block[i][j];
}

std::vector<std::string> const& 
        Sorter::getBlock(size_t const& i) const
{
        return block[i];
}

std::vector<std::vector<std::string>> const&
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
