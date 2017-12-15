#include <string>
#include <strompare/ngram.h>
#include <iostream>

// Make Visual Studio happy
#ifndef min
#define min(a,b) (a<b?a:b)
#endif // min

using namespace std;

/************************************************************************//**
 * \brief     Saves a text and its ngrams
 * \param     [in]  text to ngramify
 * \param     [in]  nLength: the length of ngrams
 * \exception -
 * \author    Shadouw
 *
 * With the word "bonbon" and ngram length of two it splits into:
 * - bon 2x
 * - onb 1x
 * - nbo 1x
 ****************************************************************************/
template<class T> strompare::nGram<T>::nGram ( T text, unsigned int nLength ) :
    m_Text ( text ),
    m_nLength ( nLength ),
    m_nCount ( 0 )
{
    for ( auto s = m_Text.begin(); s<m_Text.end(); ++s )
    {
        T subst;

        for ( unsigned n=0; n<m_nLength; ++n )
            if ( s+n < m_Text.end() )
                subst += *(s+n);
            else
                break;

        if ( m_nLength == subst.size() )
        {
            ++m_mapNGram[subst];
            ++m_nCount;
        }
    }
}

/************************************************************************//**
 * \brief     Compares ngrams of two texts and returns the number of matches
 * \param     [in]  other: the other text to compare with
 * \return    Number of matching ngrams in both texts
 * \exception invalid_argument
 * \author    Shadouw
 *
 * "bonbon" (2x bon, onb, nbo) and "bonjour" (bon, onj, njo, jou, our) have
 * only 1 trigram "bon" in common.
 ****************************************************************************/
template<class T> unsigned int strompare::nGram<T>::countmatches ( const nGram<T>& other ) const throw(std::invalid_argument)
{
    if ( m_nLength!= other.m_nLength )
        throw std::invalid_argument("ngram length is different.");

    // Find matching ngrams, both words have in common
    unsigned int nc = 0;

    for ( auto elem : m_mapNGram )
    {
        auto otherelem = other.m_mapNGram.find(elem.first);
        nc += min ( elem.second, ( other.m_mapNGram.end()==otherelem ? 0 : otherelem->second ) );
    }

    return nc;
}

/************************************************************************//**
 * \brief     Calculates ngram comparison
 * \param     [in]  other: the other text to compare with
 * \return    2 * MatchingNGrams / ( NumOfNGrams1 + NumOfNGrams2 )
 * \exception invalid_argument
 * \author    Shadouw
 *
 * "bonbon" (2x bon, onb, nbo) and "bonjour" (bon, onj, njo, jou, our) have
 * 1 trigram "bon" in common, but in total 4+5=9 ngrams.
 *
 * ngram based similarity is hence 2/9.
 ****************************************************************************/
template<class T> double strompare::nGram<T>::compare ( const nGram<T>& other ) const throw(std::invalid_argument)
{
    // If both are empty they are equal
    if ( 0 == m_nCount + other.m_nCount )
        return 1.0;

    // Calculate return value S
    return ( 2.0 * (double)countmatches(other) / ((double)m_nCount+(double)other.m_nCount) );
}

/************************************************************************//**
 * \brief     Prints (for debugging reasons) a map of ngrams
 * \exception -
 * \author    Shadouw
 ****************************************************************************/
 template<class T> void strompare::nGram<T>::printmap () const
{
    for ( auto elem : m_mapNGram )
        cout << elem.first << "[" << elem.second << "] ";

    cout << endl;
}

/************************************************************************//**
 * \brief     Returns the "original" text
 * \return    the saved text
 * \exception -
 * \author    Shadouw
 ****************************************************************************/
template<class T> T strompare::nGram<T>::getText() const
{
    return m_Text;
}

// Force compiler to generate specialized classes
template class strompare::nGram<std::string>;
