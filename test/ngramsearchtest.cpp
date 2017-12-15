#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>

#include <boost/test/unit_test.hpp>

// Ugly hack, but I need to access test wise the private parts of the class
#define private public

#include <strompare.h>

using namespace std;
using namespace strompare;

#include "testcountries.h"
#include "testnouns.h"

BOOST_AUTO_TEST_CASE ( NGramSearchCountries )
{
    const unsigned ng=3;

    nGramSearch<string> ngsearch(ng);

    // Add countries to ListOfTexts and ngram-ize them
    for ( auto country : testcountries )
        ngsearch.addText(country);

    // Add spcial test phrase
    ngsearch.addText("Unitenited");

    ngsearch.prepareSearch();

    //
    // Now lets search anything
    //
    std::map<unsigned int, std::set<nGram<string>*>> found = ngsearch.find("unitenited");

    BOOST_TEST ( 1u == found[7].size() );
    std::set<nGram<string>*>::iterator fit = found[7].begin();
    BOOST_TEST ( "Unitenited" == (*fit++)->getText() );

    BOOST_TEST ( 0u == found[6].size() );
    BOOST_TEST ( 0u == found[5].size() );
    BOOST_TEST ( 0u == found[4].size() );

    BOOST_TEST ( 3u == found[3].size() );
    fit = found[3].begin();
    BOOST_TEST ( "United Arab Emirates" == (*fit++)->getText() );
    BOOST_TEST ( "United Kingdom" == (*fit++)->getText() );
    BOOST_TEST ( "United States" == (*fit++)->getText() );

    BOOST_TEST ( 0u == found[2].size() );

    BOOST_TEST ( 7u == found[1].size() );
    fit = found[1].begin();
    BOOST_TEST ( "Armenia" == (*fit++)->getText() );
    BOOST_TEST ( "Benin" == (*fit++)->getText() );
    BOOST_TEST ( "Liechtenstein" == (*fit++)->getText() );
    BOOST_TEST ( "Montenegro" == (*fit++)->getText() );
    BOOST_TEST ( "Slovenia" == (*fit++)->getText() );
    BOOST_TEST ( "Tunisia" == (*fit++)->getText() );
    BOOST_TEST ( "Turkmenistan" == (*fit++)->getText() );

    /*
    cout << endl << endl;
    cout << "#####################" << endl;
    cout << "orderedsearchresults:" << endl;
    cout << "#####################" << endl;
    for ( typename std::map<unsigned int, std::set<nGram<string>*>>::reverse_iterator rit=found.rbegin(); rit!=found.rend(); ++rit )
    {
        //if ( 0 != rit->second.size() )
        {
            cout << rit->first << ": " ;
            for ( auto entry: rit->second )
            {
                cout << entry->getText() << "; " ;
            }
            cout << endl;
        }
    }
    */
}

BOOST_AUTO_TEST_CASE ( NGramSearchNouns )
{
    const unsigned ng=3;
    const unsigned non=sizeof(testnouns)/sizeof(testnouns[0]);

    nGramSearch<string> ngsearch(ng);

    cout << endl << endl;
    cout << "#####################" << endl;
    cout << "# found results     :" << endl;
    cout << "#####################" << endl;
    cout << "Number of nouns : " << sizeof(testnouns)/sizeof(testnouns[0]) << endl;

    // Measure the time
    clock_t begin = clock();

    // Add nouns to ListOfTexts and ngram-ize them
    for ( unsigned long i=0; i<100000; i++ )
    {
        ngsearch.addText(testnouns[rand() % non] + " " + testnouns[rand() % non] + " " + testnouns[rand() % non]);
    }
    //for ( auto noun : testnouns )
    //    ngsearch.addText(noun);

    ngsearch.prepareSearch();

    clock_t prepared = clock();
    cout << "Number of texts : " << ngsearch.getNumberOfTexts() << endl;
    cout << "Load and prepare: " << double(prepared - begin) / CLOCKS_PER_SEC << " s" << endl;

    //
    // Now lets search something
    //
    const unsigned long numofsearches=100;
    for ( unsigned long i=0; i<numofsearches; i++ )
    {
        std::map<unsigned int, std::set<nGram<string>*>> found = ngsearch.find(testnouns[rand() % non] + " " + testnouns[rand() % non]);
    }

    clock_t end = clock();

    cout << "Search          : " << double(end - prepared) / CLOCKS_PER_SEC << " s" << endl;
    cout << "Time per Search : " << double(end - prepared) / (CLOCKS_PER_SEC*numofsearches) << " s" << endl;

    /*
    for ( typename std::map<unsigned int, std::set<nGram<string>*>>::reverse_iterator rit=found.rbegin(); rit!=found.rend(); ++rit )
    {
        //if ( 0 != rit->second.size() )
        {
            cout << rit->first << ": " ;
            for ( auto entry: rit->second )
            {
                cout << entry->getText() << "; " ;
            }
            cout << endl;
        }
    }
    */
}
