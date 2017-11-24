#include <iostream>
#include <algorithm>
#include <strompare.h>
#include <boost/test/unit_test.hpp>

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
    // Taken from https://gist.github.com/kalinchernev/486393efcca01623b18d
#define ADDITEM(NAME) WordList.push_back ( WordListStruct(NAME) );
    ADDITEM("Afghanistan");ADDITEM("Albania");ADDITEM("Algeria");ADDITEM("Andorra");ADDITEM("Angola");ADDITEM("Antigua & Deps");ADDITEM("Argentina");ADDITEM("Armenia");ADDITEM("Australia");ADDITEM("Austria");ADDITEM("Azerbaijan");ADDITEM("Bahamas");ADDITEM("Bahrain");ADDITEM("Bangladesh");ADDITEM("Barbados");ADDITEM("Belarus");ADDITEM("Belgium");ADDITEM("Belize");ADDITEM("Benin");ADDITEM("Bhutan");ADDITEM("Bolivia");ADDITEM("Bosnia Herzegovina");ADDITEM("Botswana");ADDITEM("Brazil");ADDITEM("Brunei");ADDITEM("Bulgaria");ADDITEM("Burkina");ADDITEM("Burundi");ADDITEM("Cambodia");ADDITEM("Cameroon");ADDITEM("Canada");ADDITEM("Cape Verde");ADDITEM("Central African Rep");ADDITEM("Chad");ADDITEM("Chile");ADDITEM("China");ADDITEM("Colombia");ADDITEM("Comoros");ADDITEM("Congo");ADDITEM("Congo {Democratic Rep}");ADDITEM("Costa Rica");ADDITEM("Croatia");ADDITEM("Cuba");ADDITEM("Cyprus");ADDITEM("Czech Republic");ADDITEM("Denmark");ADDITEM("Djibouti");ADDITEM("Dominica");ADDITEM("Dominican Republic");ADDITEM("East Timor");ADDITEM("Ecuador");ADDITEM("Egypt");ADDITEM("El Salvador");ADDITEM("Equatorial Guinea");ADDITEM("Eritrea");ADDITEM("Estonia");ADDITEM("Ethiopia");ADDITEM("Fiji");ADDITEM("Finland");ADDITEM("France");ADDITEM("Gabon");ADDITEM("Gambia");ADDITEM("Georgia");ADDITEM("Germany");ADDITEM("Ghana");ADDITEM("Greece");ADDITEM("Grenada");ADDITEM("Guatemala");ADDITEM("Guinea");ADDITEM("Guinea-Bissau");ADDITEM("Guyana");ADDITEM("Haiti");ADDITEM("Honduras");ADDITEM("Hungary");ADDITEM("Iceland");ADDITEM("India");ADDITEM("Indonesia");ADDITEM("Iran");ADDITEM("Iraq");ADDITEM("Ireland {Republic}");ADDITEM("Israel");ADDITEM("Italy");ADDITEM("Ivory Coast");ADDITEM("Jamaica");ADDITEM("Japan");ADDITEM("Jordan");ADDITEM("Kazakhstan");ADDITEM("Kenya");ADDITEM("Kiribati");ADDITEM("Korea North");ADDITEM("Korea South");ADDITEM("Kosovo");ADDITEM("Kuwait");ADDITEM("Kyrgyzstan");ADDITEM("Laos");ADDITEM("Latvia");ADDITEM("Lebanon");ADDITEM("Lesotho");ADDITEM("Liberia");ADDITEM("Libya");ADDITEM("Liechtenstein");ADDITEM("Lithuania");ADDITEM("Luxembourg");ADDITEM("Macedonia");ADDITEM("Madagascar");ADDITEM("Malawi");ADDITEM("Malaysia");ADDITEM("Maldives");ADDITEM("Mali");ADDITEM("Malta");ADDITEM("Marshall Islands");ADDITEM("Mauritania");ADDITEM("Mauritius");ADDITEM("Mexico");ADDITEM("Micronesia");ADDITEM("Moldova");ADDITEM("Monaco");ADDITEM("Mongolia");ADDITEM("Montenegro");ADDITEM("Morocco");ADDITEM("Mozambique");ADDITEM("Myanmar, {Burma}");ADDITEM("Namibia");ADDITEM("Nauru");ADDITEM("Nepal");ADDITEM("Netherlands");ADDITEM("New Zealand");ADDITEM("Nicaragua");ADDITEM("Niger");ADDITEM("Nigeria");ADDITEM("Norway");ADDITEM("Oman");ADDITEM("Pakistan");ADDITEM("Palau");ADDITEM("Panama");ADDITEM("Papua New Guinea");ADDITEM("Paraguay");ADDITEM("Peru");ADDITEM("Philippines");ADDITEM("Poland");ADDITEM("Portugal");ADDITEM("Qatar");ADDITEM("Romania");ADDITEM("Russian Federation");ADDITEM("Rwanda");ADDITEM("St Kitts & Nevis");ADDITEM("St Lucia");ADDITEM("Saint Vincent & the Grenadines");ADDITEM("Samoa");ADDITEM("San Marino");ADDITEM("Sao Tome & Principe");ADDITEM("Saudi Arabia");ADDITEM("Senegal");ADDITEM("Serbia");ADDITEM("Seychelles");ADDITEM("Sierra Leone");ADDITEM("Singapore");ADDITEM("Slovakia");ADDITEM("Slovenia");ADDITEM("Solomon Islands");ADDITEM("Somalia");ADDITEM("South Africa");ADDITEM("South Sudan");ADDITEM("Spain");ADDITEM("Sri Lanka");ADDITEM("Sudan");ADDITEM("Suriname");ADDITEM("Swaziland");ADDITEM("Sweden");ADDITEM("Switzerland");ADDITEM("Syria");ADDITEM("Taiwan");ADDITEM("Tajikistan");ADDITEM("Tanzania");ADDITEM("Thailand");ADDITEM("Togo");ADDITEM("Tonga");ADDITEM("Trinidad & Tobago");ADDITEM("Tunisia");ADDITEM("Turkey");ADDITEM("Turkmenistan");ADDITEM("Tuvalu");ADDITEM("Uganda");ADDITEM("Ukraine");ADDITEM("United Arab Emirates");ADDITEM("United Kingdom");ADDITEM("United States");ADDITEM("Uruguay");ADDITEM("Uzbekistan");ADDITEM("Vanuatu");ADDITEM("Vatican City");ADDITEM("Venezuela");ADDITEM("Vietnam");ADDITEM("Yemen");ADDITEM("Zambia");ADDITEM("Zimbabwe");

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
