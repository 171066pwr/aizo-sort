#ifndef RUNNERCONFIG_H
#define RUNNERCONFIG_H
#include "../DataType.h"
#include "PreSortMode.h"
#include <vector>

#include "DatasetConfig.h"
#include "SorterConfig.h"

using namespace std;

struct RunnerConfig {
    DataType tableType;
    DatasetConfig datasetConfig;
    PreSortMode preSortMode;
    bool displayData;
    vector<SorterConfig> sorterConfigs;
};



#endif //RUNNERCONFIG_H
