#ifndef GLOBALCONFIG_H
#define GLOBALCONFIG_H
#include <random>

namespace Globals {
    inline extern bool DISPLAY_LOG = false;
    //seeding the marsenne twister engine
    inline extern std::mt19937 MERSENNE_GENERATOR{std::random_device{}()};
}


#endif //GLOBALCONFIG_H
