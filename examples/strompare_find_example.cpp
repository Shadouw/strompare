#include <iostream>
#include <strompare.h>

int main ( void )
{
    // Initialize the search engine to use tri-grams:
    strompare::nGramSearch<std::string> ngsearch(3);

    // Add some texts to search:
    ngsearch.addText("one");
    ngsearch.addText("two");
    ngsearch.addText("three");
    ngsearch.addText("twentyone");
    ngsearch.addText("twentytwo");
    ngsearch.addText("twentythree");
    ngsearch.addText("thirtyone");
    ngsearch.addText("thirtytwo");
    ngsearch.addText("thirtythree");

    ngsearch.addText("tree");


    // Build reverse search structures
    ngsearch.prepareSearch();

    // Search and find
    std::map<unsigned int, std::set<strompare::nGram<std::string>*>> found = ngsearch.find("three");

    // Show the results
    for ( typename std::map<unsigned int, std::set<strompare::nGram<std::string>*>>::reverse_iterator rit=found.rbegin();
          rit!=found.rend();
          ++rit )
    {
        if ( 0 != rit->second.size() )
        {
            std::cout << rit->first << ": " ;
            for ( auto entry: rit->second )
            {
                std::cout << entry->getText() << "; " ;
            }
            std::cout << std::endl;
        }
    }

    /* Output:
    3: three; twentythree; thirtythree;
    1: tree;
    */

    return 0;
}
