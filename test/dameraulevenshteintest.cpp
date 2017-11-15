#include <strompare.h>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE ( DamerauLevenshteinEmpty )
{
    // Identical text
    BOOST_CHECK ( 0  == strompare::Levenshtein<std::string>("", "", true) );
    BOOST_CHECK ( 43 == strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "", true) );
    BOOST_CHECK ( 43 == strompare::Levenshtein<std::string>("", "The quick brown fox jumps over the lazy dog", true) );
}

BOOST_AUTO_TEST_CASE ( DamerauLevenshteinIdentity )
{
    // Identical text
    BOOST_CHECK ( 0 == strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "The quick brown fox jumps over the lazy dog", true) );
}

BOOST_AUTO_TEST_CASE ( DamerauLevenshteinSingleCharacter )
{
    // Replace one character
    BOOST_CHECK ( 1 == strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "The quick brown fox jomps over the lazy dog", true) );
    BOOST_CHECK ( 1 == strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "Ahe quick brown fox jumps over the lazy dog", true) );
    BOOST_CHECK ( 1 == strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "The quick brown fox jumps over the lazy doZ", true) );

    // Insert one character
    BOOST_CHECK ( 1 == strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "The quick brown fox joumps over the lazy dog", true) );
    BOOST_CHECK ( 1 == strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", " The quick brown fox jumps over the lazy dog", true) );
    BOOST_CHECK ( 1 == strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "The quick brown fox jumps over the lazy dog ", true) );

    // Delete one character
    BOOST_CHECK ( 1 == strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "The quick brown fox jmps over the lazy dog", true) );
    BOOST_CHECK ( 1 == strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "he quick brown fox jumps over the lazy dog", true) );
    BOOST_CHECK ( 1 == strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "The quick brown fox jumps over the lazy do", true) );
}

BOOST_AUTO_TEST_CASE ( DamerauLevenshteinTwoOperations )
{
    // Replace two, insert two, delete two
    BOOST_CHECK ( 6 == strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "Tha quik broiwn fox jumps oaer te lazy diog", true) );
}

BOOST_AUTO_TEST_CASE ( DamerauLevenshteinExchanges )
{
    // Exchange three times two adjacent characters
    BOOST_CHECK ( 3 == strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "hTe quick brown fxo jumps over the lazy dgo", true) );
}
