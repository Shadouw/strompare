#pragma once

#include <string>
#include <map>

namespace strompare
{
    template<class T> class nGramSearch;

    /************************************************************************//**
     * \brief     Splits text in ngrams to compare severals texts.
     * \author    Shadouw
     ****************************************************************************/
    template<class T> class nGram
    {
    friend class nGramSearch<T>;
    public:
        //nGram() = delete;
        nGram( T, unsigned int );
        unsigned int countmatches ( const nGram<T>& ) const throw(std::invalid_argument);
        double compare( const nGram<T>& ) const throw(std::invalid_argument);

        void printmap() const;

        T getText() const;
    private:
        T m_Text;
        unsigned int m_nLength;
        std::map<std::string, unsigned int> m_mapNGram;
        unsigned int m_nCount;
    };
}
