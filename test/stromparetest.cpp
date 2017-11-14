#include <strompare.h>
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE ( check_version )
{
    BOOST_REQUIRE_EQUAL ( "0.0.1", strompare_version() );
}

BOOST_AUTO_TEST_CASE ( hello_world )
{
    BOOST_REQUIRE_EQUAL ( "Hello", strompare_hello() );
}

