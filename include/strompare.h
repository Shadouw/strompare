#pragma once

#include <string>
#include <map>

namespace strompare
{
    char const * version();
    template<typename T>  unsigned int Levenshtein ( T, T, bool = false);

    template<class T> class nGram
    {
    public:
        nGram() = delete;
        nGram( T, unsigned int );
        unsigned int countmatches ( const nGram<T>& ) const throw(std::invalid_argument);
        double compare( const nGram<T>& ) const throw(std::invalid_argument);

        void printmap() const;
    private:
        const unsigned int m_nLength;
        const T m_Text;
        std::map<std::string, int> m_mapNGram;
        unsigned int m_nCount;


    };
}
