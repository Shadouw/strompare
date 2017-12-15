#pragma once

#include <string>
#include <vector>
#include <set>

#include <strompare/ngram.h>

namespace strompare
{
    /************************************************************************//**
     * \brief     Provides a fast search on texts
     * \author    Shadouw
     *
     * After initializing with the ngram length, add some texts.
     * Then call #prepareSearch to build reverse structures for faster searches
     * Finally #find will be used to find best matching texts in the list.
     ****************************************************************************/
    template<class T> class nGramSearch
    {
    public:
        nGramSearch( unsigned int );
        void addText ( T );
        void prepareSearch ();
        std::map<unsigned int, std::set<nGram<T>*>> find ( T );
        unsigned int getNumberOfTexts();

    private:
        unsigned int m_nLength;                                            // ngram length
        std::vector<strompare::nGram<T>> m_ListOfTexts;                    // list of ngram-ized texts
        std::map<T, std::vector<strompare::nGram<T>*>> m_MapNGramToTexts;  // map from ngrams to text
    };

}
