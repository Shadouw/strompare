#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <streambuf>
#include <forward_list>
#include <tuple>

#include <boost/filesystem.hpp>

#include <unistd.h>

#include <strompare.h>

using namespace std;
using namespace boost::filesystem;
using namespace strompare;

std::forward_list<tuple<string,string,nGram<string>>> ngramfiles;

bool addfile ( const string filename )
{
    std::ifstream myfile(filename);
    if ( myfile.fail() )
    {
        cerr << "File not found: " << filename << endl;
        return false;
    }

    string str((istreambuf_iterator<char>(myfile)),
                istreambuf_iterator<char>());

    nGram<string> Word1(str, 3);

    ngramfiles.push_front( make_tuple(filename, str, Word1) );

    return true;
}

bool adddirectory ( const string directoryname )
{
    // Inspiration:
    // https://stackoverflow.com/questions/67273/how-do-you-iterate-through-every-file-directory-recursively-in-standard-c/32889434
    struct recursive_directory_range
    {
        typedef recursive_directory_iterator iterator;
        recursive_directory_range(path p) : p_(p) {}

        iterator begin() { return recursive_directory_iterator(p_); }
        iterator end() { return recursive_directory_iterator(); }

        path p_;
    };

    for (auto it : recursive_directory_range(directoryname))
    {
        addfile ( it.path().string() );
    }


    return true;
}

void coutcsv ()
{
    cout << "File 1;File 2;#Matches;ngram Comparison" << endl;

    for ( auto it1 = ngramfiles.begin(); it1 != ngramfiles.end(); ++it1 )
    {
        for ( auto it2 = next(it1,1); it2 != ngramfiles.end(); ++it2 )
        {
            cout << get<0>(*it1) << ";";
            cout << get<0>(*it2) << ";";
            cout << get<2>(*it1).countmatches(get<2>(*it2)) << ";";
            cout << setprecision(9) << get<2>(*it1).compare(get<2>(*it2)) << endl;
        }
    }

    cout << endl;
}

int main ( int argc, char **argv )
{
    while ( true )
    {
        int getoptresult = getopt ( argc, argv, "f:d:h?" );
        if ( -1 == getoptresult )
                break;

        switch ( getoptresult )
        {
        case 'f':
            addfile ( optarg );
            break;
        case 'd':
            adddirectory ( optarg );
            break;
        case 'h':
        case '?':
            cout << argv[0] << endl;
            cout << "  -f  : Add a file to compare" << endl;
            cout << "  -d  : Add all files within a directory to compare" << endl;
            cout << "  -h,?: Show this help text" << endl;
            return 0;
        }
    }

    coutcsv();
}
