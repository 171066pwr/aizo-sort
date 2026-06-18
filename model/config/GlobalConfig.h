#ifndef GLOBALCONFIG_H
#define GLOBALCONFIG_H
#include <random>

namespace Globals {
    enum DisplaySetting {
        NOTHING = 0,
        PROGRESS = 1,
        DATA = 2
    };

    inline extern DisplaySetting DISPLAY_LOG = NOTHING;
    //seeding the marsenne twister engine
    inline extern std::mt19937 MERSENNE_GENERATOR{std::random_device{}()};
}


#endif //GLOBALCONFIG_H
