#ifdef _MSC_VER_
#include <windef.h>
#endif // _MSC_VER_

#include <string>
#include <strompare.h>
#include <iostream>

using namespace std;

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

template<class T> double strompare::nGram<T>::compare ( const nGram<T>& other ) const throw(std::invalid_argument)
{
    // If both are empty they are equal
    if ( 0 == m_nCount + other.m_nCount )
        return 1.0;

    // Calculate return value S
    return ( 2.0 * (double)countmatches(other) / ((double)m_nCount+(double)other.m_nCount) );
}

template<class T> void strompare::nGram<T>::printmap () const
{
    for ( auto elem : m_mapNGram )
        cout << elem.first << "[" << elem.second << "] ";

    cout << endl;
}

// Force compiler to generate specialized classes
template class strompare::nGram<std::string>;
