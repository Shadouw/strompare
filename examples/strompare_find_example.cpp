#include <iostream>
#include <strompare.h>

using namespace std;
using namespace strompare;

int main ( void )
{
    // Initialize
    nGramSearch<string> ngsearch(3);

    // Add some texts to search
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
    map<unsigned int, set<nGram<string>*>> found = ngsearch.find("three");

    // Show the results
    for ( typename map<unsigned int, set<nGram<string>*>>::reverse_iterator rit=found.rbegin(); rit!=found.rend(); ++rit )
    {
        if ( 0 != rit->second.size() )
        {
            cout << rit->first << ": " ;
            for ( auto entry: rit->second )
            {
                cout << entry->getText() << "; " ;
            }
            cout << endl;
        }
    }

    /* Output:
    3: three; twentythree; thirtythree;
    1: tree;
    */

    return 0;
}
