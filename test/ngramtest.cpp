#include <iostream>
#include <string>

#include <boost/test/unit_test.hpp>

#include <strompare.h>

using namespace std;
using namespace strompare;

#include "testcountries.h"

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

    BOOST_TEST ( 16u == Word1.countmatches(Word1) );
    BOOST_TEST ( 1.0 == Word1.compare(Word1) );

    nGram<string> Word2("the big brown fox", 3);

    BOOST_TEST ( 15u == Word2.countmatches(Word2) );
    BOOST_TEST ( 1.0 == Word2.compare(Word2) );
}

BOOST_AUTO_TEST_CASE ( nGramEmpty2, * boost::unit_test::tolerance(0.00001) )
{
    nGram<string> Word1("the big brown fox", 2);
    nGram<string> Word2("", 2);

    BOOST_TEST ( 0u == Word1.countmatches(Word2) );
    BOOST_TEST ( 0.0 == Word1.compare(Word2) );

    BOOST_TEST ( 0u == Word2.countmatches(Word1) );
    BOOST_TEST ( 0.0 == Word2.compare(Word1) );

    BOOST_TEST ( 0u == Word2.countmatches(Word2) );
    BOOST_TEST ( 1.0 == Word2.compare(Word2) );
}

BOOST_AUTO_TEST_CASE ( nGramEmpty3, * boost::unit_test::tolerance(0.00001) )
{
    nGram<string> Word1("the big brown fox", 3);
    nGram<string> Word2("", 3);

    BOOST_TEST ( 0u == Word1.countmatches(Word2) );
    BOOST_TEST ( 0.0 == Word1.compare(Word2) );

    BOOST_TEST ( 0u == Word2.countmatches(Word1) );
    BOOST_TEST ( 0.0 == Word2.compare(Word1) );

    BOOST_TEST ( 0u == Word2.countmatches(Word2) );
    BOOST_TEST ( 1.0 == Word2.compare(Word2) );
}

BOOST_AUTO_TEST_CASE ( nGramShort, * boost::unit_test::tolerance(0.00001) )
{
    nGram<string> Word1("the big brown fox", 2);
    nGram<string> Word2("The Byg Brown Fox", 2);

    BOOST_TEST ( 8u == Word1.countmatches(Word2) );
    BOOST_TEST ( 0.5 == Word1.compare(Word2) );
}

BOOST_AUTO_TEST_CASE ( nGramShort3, * boost::unit_test::tolerance(0.00001) )
{
    nGram<string> Word1("the big brown fox", 3);
    nGram<string> Word2("The Byg Brown Fox", 3);

    BOOST_TEST ( 4u == Word1.countmatches(Word2) );
    BOOST_TEST ( 8.0/30.0 == Word1.compare(Word2) );
}

BOOST_AUTO_TEST_CASE ( nGramBonbon, * boost::unit_test::tolerance(0.00001) )
{
    nGram<string> Word1("bonbon", 3);
    nGram<string> Word2("bonjour", 3);

    BOOST_TEST ( 1u == Word1.countmatches(Word2) );
    BOOST_TEST ( 2.0/9.0 == Word1.compare(Word2) );
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

    // Test some results:
    BOOST_TEST ( std::string("Germany")   == WordList[0].Word.getText() );
    BOOST_TEST ( 4.0/9.0   == WordList[0].match );
    BOOST_TEST ( std::string("Oman")      == WordList[1].Word.getText() );
    BOOST_TEST ( 2.0/6.0   == WordList[1].match );
    BOOST_TEST ( std::string("Romania")   == WordList[2].Word.getText() );
    BOOST_TEST ( 2.0/9.0   == WordList[2].match );
    BOOST_TEST ( std::string("Guatemala") == WordList[3].Word.getText() );
    BOOST_TEST ( 2.0/11.0   == WordList[3].match );
}
