#pragma once

#include <string>
#include <map>

namespace strompare
{
    template<class T> class nGram
    {
    public:
        //nGram() = delete;
        nGram( T, unsigned int );
        unsigned int countmatches ( const nGram<T>& ) const throw(std::invalid_argument);
        double compare( const nGram<T>& ) const throw(std::invalid_argument);

        void printmap() const;

        T getText() const {return m_Text;}
    private:
        unsigned int m_nLength;
        T m_Text;
        std::map<std::string, int> m_mapNGram;
        unsigned int m_nCount;
    };
}
