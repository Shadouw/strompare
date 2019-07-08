#include <set>
#include <strompare/ngramsearch.h>

using namespace std;
using namespace strompare;

/************************************************************************//**
 * \brief     Initialisation, saves the ngram length for later comparison
 * \param     [in]  nLength: ngram length
 * \exception -
 * \author    Shadouw
 ****************************************************************************/
template<class T> strompare::nGramSearch<T>::nGramSearch ( unsigned int nLength ) :
    m_nLength ( nLength )
    {

    }

/************************************************************************//**
 * \brief     Adds a text to a searchable list
 * \param     [in]  text: the text to add
 * \exception -
 * \author    Shadouw
 ****************************************************************************/
template<class T> void strompare::nGramSearch<T>::addText ( T text )
{
    m_ListOfTexts.push_back ( nGram<T>(text, m_nLength) );
}

/************************************************************************//**
 * \brief     Builds reverse structures for faster search
 * \exception bad_alloc
 * \author    Shadouw
 *
 * Call this after #addText and before #find
 ****************************************************************************/
template<class T> void strompare::nGramSearch<T>::prepareSearch()
{
    m_MapNGramToTexts.clear();

    for ( typename vector<nGram<T>>::iterator text = m_ListOfTexts.begin(); text != m_ListOfTexts.end(); ++text )
    {
        for ( auto elem : text->m_mapNGram )
            m_MapNGramToTexts[elem.first].push_back( &(*text) );
    }
}

/************************************************************************//**
 * \brief     Finds a text in the saved lists of texts
 * \param     [in]  phrase: text to search
 * \return    map(set(pointer to saved text))
 * \exception -
 * \author    Shadouw
 *
 * The returned _map of pointer-sets_ is already ordered by number of
 * matching ngrams.
 * To find best matches, iterate backwards.
 ****************************************************************************/
template<class T> map<unsigned int, set<nGram<T>*>> strompare::nGramSearch<T>::find ( T phrase )
{
    // Prepare the search phrase
    nGram<T> ngramphrase ( phrase, m_nLength );

    // Search all ngrams and store results
    map<nGram<T>*, unsigned int> searchresults;
    map<unsigned int, set<nGram<T>*>> orderedsearchresults;

    for ( auto ngram: ngramphrase.m_mapNGram )
    {
        for ( auto text : m_MapNGramToTexts[ngram.first] )
        {
            // Is text already part of search results?
            // If so, remove related entry from orderedsearchresults
            typename std::map<nGram<T>*, unsigned int>::iterator findtext = searchresults.find(text);
            unsigned int oldvalue = 0, newvalue = 0;
            if ( findtext != searchresults.end() )
            {
                oldvalue = findtext->second;

                // remove text from orderedsearchresults
                typename std::map<unsigned int, std::set<nGram<T>*>>::iterator resultrow = orderedsearchresults.find(oldvalue);
                typename std::set<nGram<T>*>::iterator result = (resultrow->second).find(text);
                (resultrow->second).erase(result);
            }

            newvalue = oldvalue + min(ngram.second, text->m_mapNGram[ngram.first]);
            searchresults[text] = newvalue;
            orderedsearchresults[newvalue].insert(text);
        }
    }

    return orderedsearchresults;
}

/************************************************************************//**
 * \brief     Returns the number of stored and ngramified texts
 * \return    Numver of stored texts
 * \exception -
 * \author    Shadouw
 ****************************************************************************/
template<class T> unsigned int strompare::nGramSearch<T>::getNumberOfTexts ( )
{
    return m_ListOfTexts.size();
}

// Force compiler to generate specialized classes
template class strompare::nGramSearch<std::string>;
