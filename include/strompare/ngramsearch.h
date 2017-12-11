#pragma once

#include <string>
#include <vector>
#include <set>

#include <strompare/ngram.h>

namespace strompare
{
    template<class T> class nGramSearch
    {
    public:
        nGramSearch( unsigned int );
        void addText ( T );
        void prepareSearch ();
        std::map<unsigned int, std::set<nGram<T>*>> find ( T );

    private:
        unsigned int m_nLength;                                            // ngram length
        std::vector<strompare::nGram<T>> m_ListOfTexts;                    // list of ngram-ized texts
        std::map<T, std::vector<strompare::nGram<T>*>> m_MapNGramToTexts;  // map from ngrams to text
    };

}
