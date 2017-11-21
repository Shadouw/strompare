#include <strompare.h>
#include <boost/test/unit_test.hpp>

using namespace strompare;

BOOST_AUTO_TEST_CASE ( nGramLength, * boost::unit_test::tolerance(0.00001) )
{
    nGram<std::string> Word1("the big brown fox", 2);
    nGram<std::string> Word2("the big brown fox", 3);

    BOOST_REQUIRE_THROW ( Word1.countmatches(Word2), std::invalid_argument );
    BOOST_REQUIRE_THROW ( Word1.compare(Word2), std::invalid_argument );
}

BOOST_AUTO_TEST_CASE ( nGramIdent, * boost::unit_test::tolerance(0.00001) )
{
    nGram<std::string> Word1("the big brown fox", 2);

    BOOST_TEST ( 16 == Word1.countmatches(Word1) );
    BOOST_TEST ( 1.0 == Word1.compare(Word1) );

    nGram<std::string> Word2("the big brown fox", 3);

    BOOST_TEST ( 15 == Word2.countmatches(Word2) );
    BOOST_TEST ( 1.0 == Word2.compare(Word2) );
}

BOOST_AUTO_TEST_CASE ( nGramEmpty2, * boost::unit_test::tolerance(0.00001) )
{
    nGram<std::string> Word1("the big brown fox", 2);
    nGram<std::string> Word2("", 2);

    BOOST_TEST ( 0 == Word1.countmatches(Word2) );
    BOOST_TEST ( 0.0 == Word1.compare(Word2) );

    BOOST_TEST ( 0 == Word2.countmatches(Word1) );
    BOOST_TEST ( 0.0 == Word2.compare(Word1) );

    BOOST_TEST ( 0 == Word2.countmatches(Word2) );
    BOOST_TEST ( 1.0 == Word2.compare(Word2) );
}

BOOST_AUTO_TEST_CASE ( nGramEmpty3, * boost::unit_test::tolerance(0.00001) )
{
    nGram<std::string> Word1("the big brown fox", 3);
    nGram<std::string> Word2("", 3);

    BOOST_TEST ( 0 == Word1.countmatches(Word2) );
    BOOST_TEST ( 0.0 == Word1.compare(Word2) );

    BOOST_TEST ( 0 == Word2.countmatches(Word1) );
    BOOST_TEST ( 0.0 == Word2.compare(Word1) );

    BOOST_TEST ( 0 == Word2.countmatches(Word2) );
    BOOST_TEST ( 1.0 == Word2.compare(Word2) );
}

BOOST_AUTO_TEST_CASE ( nGramShort, * boost::unit_test::tolerance(0.00001) )
{
    nGram<std::string> Word1("the big brown fox", 2);
    nGram<std::string> Word2("The Byg Brown Fox", 2);

    BOOST_TEST ( 8 == Word1.countmatches(Word2) );
    BOOST_TEST ( 0.5 == Word1.compare(Word2) );
}

BOOST_AUTO_TEST_CASE ( nGramShort3, * boost::unit_test::tolerance(0.00001) )
{
    nGram<std::string> Word1("the big brown fox", 3);
    nGram<std::string> Word2("The Byg Brown Fox", 3);

    BOOST_TEST ( 4 == Word1.countmatches(Word2) );
    BOOST_TEST ( 8.0/30.0 == Word1.compare(Word2) );
}
