#include <iostream>
#include <string>
#include <algorithm>
#include <strompare.h>
#include <boost/test/unit_test.hpp>

#include "testcountries.h"

using namespace std;
using namespace strompare;

BOOST_AUTO_TEST_CASE ( nGramLength, * boost::unit_test::tolerance(0.00001) )
{
    nGram<string> Word1("the big brown fox", 2);
    nGram<string> Word2("the big brown fox", 3);

    BOOST_REQUIRE_THROW ( Word1.countmatches(Word2), invalid_argument );
    BOOST_REQUIRE_THROW ( Word1.compare(Word2), invalid_argument );
}

BOOST_AUTO_TEST_CASE ( nGramIdent, * boost::unit_test::tolerance(0.00001) )
{
    nGram<string> Word1("the big brown fox", 2);

    BOOST_TEST ( 16 == Word1.countmatches(Word1) );
    BOOST_TEST ( 1.0 == Word1.compare(Word1) );

    nGram<string> Word2("the big brown fox", 3);

    BOOST_TEST ( 15 == Word2.countmatches(Word2) );
    BOOST_TEST ( 1.0 == Word2.compare(Word2) );
}

BOOST_AUTO_TEST_CASE ( nGramEmpty2, * boost::unit_test::tolerance(0.00001) )
{
    nGram<string> Word1("the big brown fox", 2);
    nGram<string> Word2("", 2);

    BOOST_TEST ( 0 == Word1.countmatches(Word2) );
    BOOST_TEST ( 0.0 == Word1.compare(Word2) );

    BOOST_TEST ( 0 == Word2.countmatches(Word1) );
    BOOST_TEST ( 0.0 == Word2.compare(Word1) );

    BOOST_TEST ( 0 == Word2.countmatches(Word2) );
    BOOST_TEST ( 1.0 == Word2.compare(Word2) );
}

BOOST_AUTO_TEST_CASE ( nGramEmpty3, * boost::unit_test::tolerance(0.00001) )
{
    nGram<string> Word1("the big brown fox", 3);
    nGram<string> Word2("", 3);

    BOOST_TEST ( 0 == Word1.countmatches(Word2) );
    BOOST_TEST ( 0.0 == Word1.compare(Word2) );

    BOOST_TEST ( 0 == Word2.countmatches(Word1) );
    BOOST_TEST ( 0.0 == Word2.compare(Word1) );

    BOOST_TEST ( 0 == Word2.countmatches(Word2) );
    BOOST_TEST ( 1.0 == Word2.compare(Word2) );
}

BOOST_AUTO_TEST_CASE ( nGramShort, * boost::unit_test::tolerance(0.00001) )
{
    nGram<string> Word1("the big brown fox", 2);
    nGram<string> Word2("The Byg Brown Fox", 2);

    BOOST_TEST ( 8 == Word1.countmatches(Word2) );
    BOOST_TEST ( 0.5 == Word1.compare(Word2) );
}

BOOST_AUTO_TEST_CASE ( nGramShort3, * boost::unit_test::tolerance(0.00001) )
{
    nGram<string> Word1("the big brown fox", 3);
    nGram<string> Word2("The Byg Brown Fox", 3);

    BOOST_TEST ( 4 == Word1.countmatches(Word2) );
    BOOST_TEST ( 8.0/30.0 == Word1.compare(Word2) );
}

BOOST_AUTO_TEST_CASE ( PrintDebugInfo )
{
    // This is not actually an autotest but to show how print debuging information
    nGram<string> Word1("the big brown fox is bigger than the big black fox.", 3);
    Word1.printmap();
}

BOOST_AUTO_TEST_CASE ( SortAndSearchWordList )
{
    const unsigned ng=3;

    struct WordListStruct {
        nGram<string> Word;
        double match;
        WordListStruct(string word) :
            Word(word,ng), match (0.0) {};
    };

    vector<WordListStruct> WordList;

    // Add countries
    for ( auto country : testcountries )
        WordList.push_back ( WordListStruct(country) );

    // Print Top 10 (at this stage the first 10 countries)
    cout << "### Initial:" << endl;
    for ( int i=0; i<10; ++i )
        cout << WordList[i].Word.getText() << ": " << WordList[i].match << endl;

    // Search Germany
    nGram<string> strGermany("gemany", ng);

    // Calculate the comparison
    for_each ( WordList.begin(), WordList.end(), [&strGermany](WordListStruct &n){ n.match=n.Word.compare(strGermany);} );

    // Now sort the vector:
    sort ( WordList.begin(),
                WordList.end(),
                [](const WordListStruct & a, const WordListStruct & b)
                {
                    return a.match > b.match;
                });

    // Print Top 10 (at this stage the first 10 countries)
    cout << "### germany:" << endl;
    for ( int i=0; i<10; ++i )
        cout << WordList[i].Word.getText() << ": " << WordList[i].match << endl;
}
