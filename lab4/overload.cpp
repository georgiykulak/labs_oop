#include "overload.hpp"

bool operator< (std::string const& str1,
				std::string const& str2)
{
    	auto sz1 = str1.length();
    	auto sz2 = str2.length();

    	for ( auto i = 0; i < sz1 && i < sz2; ++i ) {
        		if ( str1[i] < str2[i] )
        		    	return  true;
        		if ( str1[i] > str2[i] )
            			return false;
    	}
    
    	return sz1 < sz2;
}
