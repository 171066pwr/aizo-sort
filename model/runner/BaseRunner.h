#ifndef BASERUNNER_H
#define BASERUNNER_H

#include <map>

#include "RunResult.h"

using namespace std;

class BaseRunner {
    public:
        virtual RunResult run() = 0;
};


#endif //BASERUNNER_H
