#include <strompare.h>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE ( LevenshteinEmpty )
{
    // Identical text
    BOOST_CHECK ( 0  == strompare::Levenshtein<std::string>("", "") );
    BOOST_CHECK ( 43 == strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "") );
    BOOST_CHECK ( 43 == strompare::Levenshtein<std::string>("", "The quick brown fox jumps over the lazy dog") );
}

BOOST_AUTO_TEST_CASE ( LevenshteinIdentity )
{
    // Identical text
    BOOST_CHECK ( 0 == strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "The quick brown fox jumps over the lazy dog") );
}

BOOST_AUTO_TEST_CASE ( LevenshteinSingleCharacter )
{
    // Replace one character
    BOOST_CHECK ( 1 == strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "The quick brown fox jomps over the lazy dog") );
    BOOST_CHECK ( 1 == strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "Ahe quick brown fox jumps over the lazy dog") );
    BOOST_CHECK ( 1 == strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "The quick brown fox jumps over the lazy doZ") );

    // Insert one character
    BOOST_CHECK ( 1 == strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "The quick brown fox joumps over the lazy dog") );
    BOOST_CHECK ( 1 == strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", " The quick brown fox jumps over the lazy dog") );
    BOOST_CHECK ( 1 == strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "The quick brown fox jumps over the lazy dog ") );

    // Delete one character
    BOOST_CHECK ( 1 == strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "The quick brown fox jmps over the lazy dog") );
    BOOST_CHECK ( 1 == strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "he quick brown fox jumps over the lazy dog") );
    BOOST_CHECK ( 1 == strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "The quick brown fox jumps over the lazy do") );
}

BOOST_AUTO_TEST_CASE ( LevenshteinTwoOperations )
{
    // Replace two, insert two, delete two
    BOOST_CHECK ( 6 == strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "Tha quik broiwn fox jumps oaer te lazy diog") );
}

BOOST_AUTO_TEST_CASE ( LevenshteinExchanges )
{
    // Exchange three times two adjacent characters
    BOOST_CHECK ( 6 == strompare::Levenshtein<std::string>("The quick brown fox jumps over the lazy dog", "hTe quick brown fxo jumps over the lazy dgo") );
}
