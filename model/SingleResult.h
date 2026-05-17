#ifndef SINGLERESULT_H
#define SINGLERESULT_H
#ifdef _WIN32
// Windows has a symbol byte that conflicts with Standard C++17 or newer
// std::byte if you've used "using namespace std".  If you're not willing
// to entirely change your software to eliminate the using, one solution
// is to define this flag before Windows.h might be included.
#define WIN32_LEAN_AND_MEAN 0
#endif

#include "SorTable.h"
#include <windows.h>


template<typename T>
struct SingleResult {
    SorTable<T> sorTable;
    LARGE_INTEGER time;
};



#endif //SINGLERESULT_H
