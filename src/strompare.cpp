#include <strompare.h>
#include <strompareversion.h>

using namespace std;

/************************************************************************//**
 * \brief     Returns library version
 * \return    const char *: Library version
 * \exception -
 * \author    Shadouw
 ****************************************************************************/
char const * strompare::version()
{
    return STROMPAREVERSION;
}
