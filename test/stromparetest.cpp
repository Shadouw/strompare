#include <strompare.h>
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE ( check_version )
{
    BOOST_REQUIRE_EQUAL ( "0.0.1", strompare::version() );
}

BOOST_AUTO_TEST_CASE ( LevenshteinEmpty )
{
    // Identical text
    BOOST_REQUIRE_EQUAL ( 0, strompare::Levenshtein<std::string>("", "") );
    BOOST_REQUIRE_EQUAL ( 43, strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "") );
    BOOST_REQUIRE_EQUAL ( 43, strompare::Levenshtein<std::string>("", "The quick brown fox jumps over the lazy dog") );
}

BOOST_AUTO_TEST_CASE ( DamerauLevenshteinEmpty )
{
    // Identical text
    BOOST_REQUIRE_EQUAL ( 0, strompare::Levenshtein<std::string>("", "", true) );
    BOOST_REQUIRE_EQUAL ( 43, strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "", true) );
    BOOST_REQUIRE_EQUAL ( 43, strompare::Levenshtein<std::string>("", "The quick brown fox jumps over the lazy dog", true) );
}

BOOST_AUTO_TEST_CASE ( LevenshteinIdentity )
{
    // Identical text
    BOOST_REQUIRE_EQUAL ( 0, strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "The quick brown fox jumps over the lazy dog") );
}

BOOST_AUTO_TEST_CASE ( DamerauLevenshteinIdentity )
{
    // Identical text
    BOOST_REQUIRE_EQUAL ( 0, strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "The quick brown fox jumps over the lazy dog", true) );
}

BOOST_AUTO_TEST_CASE ( LevenshteinSingleCharacter )
{
    // Replace one character
    BOOST_REQUIRE_EQUAL ( 1, strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "The quick brown fox jomps over the lazy dog") );
    BOOST_REQUIRE_EQUAL ( 1, strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "Ahe quick brown fox jumps over the lazy dog") );
    BOOST_REQUIRE_EQUAL ( 1, strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "The quick brown fox jumps over the lazy doZ") );

    // Insert one character
    BOOST_REQUIRE_EQUAL ( 1, strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "The quick brown fox joumps over the lazy dog") );
    BOOST_REQUIRE_EQUAL ( 1, strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", " The quick brown fox jumps over the lazy dog") );
    BOOST_REQUIRE_EQUAL ( 1, strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "The quick brown fox jumps over the lazy dog ") );

    // Delete one character
    BOOST_REQUIRE_EQUAL ( 1, strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "The quick brown fox jmps over the lazy dog") );
    BOOST_REQUIRE_EQUAL ( 1, strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "he quick brown fox jumps over the lazy dog") );
    BOOST_REQUIRE_EQUAL ( 1, strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "The quick brown fox jumps over the lazy do") );
}

BOOST_AUTO_TEST_CASE ( DamerauLevenshteinSingleCharacter )
{
    // Replace one character
    BOOST_REQUIRE_EQUAL ( 1, strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "The quick brown fox jomps over the lazy dog", true) );
    BOOST_REQUIRE_EQUAL ( 1, strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "Ahe quick brown fox jumps over the lazy dog", true) );
    BOOST_REQUIRE_EQUAL ( 1, strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "The quick brown fox jumps over the lazy doZ", true) );

    // Insert one character
    BOOST_REQUIRE_EQUAL ( 1, strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "The quick brown fox joumps over the lazy dog", true) );
    BOOST_REQUIRE_EQUAL ( 1, strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", " The quick brown fox jumps over the lazy dog", true) );
    BOOST_REQUIRE_EQUAL ( 1, strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "The quick brown fox jumps over the lazy dog ", true) );

    // Delete one character
    BOOST_REQUIRE_EQUAL ( 1, strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "The quick brown fox jmps over the lazy dog", true) );
    BOOST_REQUIRE_EQUAL ( 1, strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "he quick brown fox jumps over the lazy dog", true) );
    BOOST_REQUIRE_EQUAL ( 1, strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "The quick brown fox jumps over the lazy do", true) );
}

BOOST_AUTO_TEST_CASE ( LevenshteinTwoOperations )
{
    // Replace two, insert two, delete two
    BOOST_REQUIRE_EQUAL ( 6, strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "Tha quik broiwn fox jumps oaer te lazy diog") );
}

BOOST_AUTO_TEST_CASE ( DamerauLevenshteinTwoOperations )
{
    // Replace two, insert two, delete two
    BOOST_REQUIRE_EQUAL ( 6, strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "Tha quik broiwn fox jumps oaer te lazy diog", true) );
}

BOOST_AUTO_TEST_CASE ( LevenshteinExchanges )
{
    // Exchange three times two adjacent characters
    BOOST_REQUIRE_EQUAL ( 6, strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "hTe quick brown fxo jumps over the lazy dgo") );
}

BOOST_AUTO_TEST_CASE ( DamerauLevenshteinExchanges )
{
    // Exchange three times two adjacent characters
    BOOST_REQUIRE_EQUAL ( 3, strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "hTe quick brown fxo jumps over the lazy dgo", true) );
}


