#include <iostream>
#include <vector>
#include <strompare.h>
#include <strompareversion.h>

using namespace std;

/************************************************************************//**
 * \brief     Returns library version
 * \return    const char *: Library version
 * \exception -
 * \author    Shadouw
 ****************************************************************************/
char const * strompare::version()
{
    return STROMPAREVERSION;
}

/************************************************************************//**
 * \brief     This function calculates Levenshtein distance
 * \param     [in]  string1
 * \param     [in]  string2
 * \param     [in]  bDamerauLevenshtein
 * \return    FUNCTIONTYPE
 * \exception std::bad_alloc
 * \author    Shadouw
 *
 * The function calculates the Levenshtein distance of two strings.
 * Therefore it calculates the minimal number of operations:
 * - insert
 * - delete
 * - replace
 *
 * With Damerau-Levenshtein exchanging of two neighbour characters costs
 * one operation only, while Levenshtein costs two.
 *
 * to convert string1 into string2.
 * DTW (Dynamic Time Warping) is used to calculate the distance.
 ****************************************************************************/
template<typename T> unsigned int strompare::Levenshtein ( T string1, T string2, bool bDamerauLevenshtein )
{
    // Save string length
    const size_t nLength1 = string1.size();
    const size_t nLength2 = string2.size();

    // DistanceMatrix [0..nLength1, 0..nLength2]
	// strings in the array are moved by one position
	// Position "0" ist to represent the "empty word"
    std::vector<std::vector<unsigned int> > DistanceMatrix ( string1.size()+1, std::vector<unsigned int>(string2.size()+1));

    // Set border of DistanceMatrix
	for ( size_t i=0; i<=nLength1; ++i )
	{
		DistanceMatrix[i][0] = i;
	}
	for ( size_t j=0; j<=nLength2; ++j )
	{
		DistanceMatrix[0][j] = j;
	}

	// Now calculate the DistanceMatrix
    unsigned int c = 0;
    for ( size_t i=1; i<=nLength1; ++i )
	{
		for ( size_t j=1; j<=nLength2; ++j )
		{
		    c = ( string1[i-1] == string2[j-1] ? 0 : 1 );

            unsigned int distmin = DistanceMatrix[i-1][j  ] + 1;
            if ( DistanceMatrix[i  ][j-1] + 1 < distmin )
                distmin = DistanceMatrix[i  ][j-1] + 1;
            if ( DistanceMatrix[i-1][j-1] + c < distmin )
                distmin = DistanceMatrix[i-1][j-1] + c;

            DistanceMatrix[i][j] = distmin;

			if ( bDamerauLevenshtein )
			{
				if ( (i > 1) && (j > 1) &&
					 (string1[i-1] == string2[j-2]) &&
					 (string1[i-2] == string2[j-1]))
				{
					if ( DistanceMatrix[i][j] > DistanceMatrix[i-2][j-2] + c )
                        DistanceMatrix[i][j] = DistanceMatrix[i-2][j-2] + c;
				}
			}
		}
	}

    return DistanceMatrix[nLength1][nLength2];
}

// To export a function template I have to specify the necessary specialisations:
template unsigned int strompare::Levenshtein<std::string>(std::string string1, std::string string2, bool bDamerauLevenshtein);
