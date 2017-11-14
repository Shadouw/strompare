#include <iostream>
#include <strompare.h>
#include <strompareversion.h>

using namespace std;

/************************************************************************//**
 * \brief     Returns library version
 * \return    const char *: Library version
 * \exception -
 * \author    Shadouw
 ****************************************************************************/
const char * strompare_version()
{
    return STROMPAREVERSION;
}

const char * strompare_hello()
{
    return "Hello";
}
