#ifndef BASERUNNER_H
#define BASERUNNER_H

#include "BatchResult.h"
#include "../config/SorterConfig.h"
#include <map>
#include <vector>

using namespace std;

class BaseRunner {
    public:
        virtual map<SorterConfig,BatchResult> run() = 0;
};


#endif //BASERUNNER_H
