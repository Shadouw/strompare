#pragma once

namespace strompare
{
char const * version();
template<typename T>  unsigned int Levenshtein ( T, T, bool = false);
}
