#ifndef BASERUNNER_H
#define BASERUNNER_H

#include "BatchResult.h"
#include "../config/SorterConfig.h"
#include <map>

using namespace std;

class BaseRunner {
    public:
        virtual map<SorterConfig, map<int, BatchResult>> run() = 0;
};


#endif //BASERUNNER_H
