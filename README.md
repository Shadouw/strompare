# strompare

[![Build Status](https://travis-ci.org/Shadouw/strompare.svg?branch=master)](https://travis-ci.org/Shadouw/strompare)
[![Build status](https://ci.appveyor.com/api/projects/status/sx0qo69yi4763ase?svg=true)](https://ci.appveyor.com/project/Shadouw/strompare)
[![codecov](https://codecov.io/gh/Shadouw/strompare/branch/master/graphs/badge.svg)](https://codecov.io/gh/Shadouw/strompare)
[![License: LGPL v3](https://img.shields.io/badge/License-LGPL%20v3-blue.svg)](https://www.gnu.org/licenses/lgpl-3.0)

`strompare` is text comparison library

It can calculate (Damerau-)Levenshtein distance, but its main feature is
to compare and find texts based on ngrams.

"bonbon" e.g. splits into the following 4 tri-grams:
 - bon (two times)
 - onb
 - nbo

"bonjour" has those 5 tri-grams:
 - bon
 - onj
 - njo
 - jou
 - our

ngram based comparison calculates as follows: 2 * MatchingNGrams / ( NumOfNGrams1 + NumOfNGrams2 )
For further information please see [German Wikipedia: N-Gramm](https://de.wikipedia.org/wiki/N-Gramm)

In the example above, "bonbon" and "bonjour" have 1 common tri-gram "bon" and 9 tri-grams in total. Both words are 1/9 similar.

Based on this comparison (to be more exact on the number of matching ngrams) a fast similarity search has been implemented.

`class nGramSearch` makes use of special data structures to find similar words/texts.

`examples\strompare_find_example.cpp` shows how to use the library:

Include the header:

    #include <strompare.h>

Initialize the search engine to use tri-grams:

    strompare::nGramSearch<std::string> ngsearch(3);


Add some texts to search:

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

Build reverse search structures

    ngsearch.prepareSearch();

Search and find

    std::map<unsigned int, std::set<strompare::nGram<std::string>*>> found = ngsearch.find("three");

`find` returns a map, ordered from worst to best list of texts.
To get best matches, iterate backwards:

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

The output of this example is

    3: three; twentythree; thirtythree;
    1: tree;
