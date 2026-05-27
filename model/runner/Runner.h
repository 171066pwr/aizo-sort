#ifndef RUNNER_H
#define RUNNER_H
#include <map>
#include <vector>

#include "BaseRunner.h"
#include "BatchResult.h"
#include "../config/RunnerConfig.h"
#include "../generator/TableGenerator.h"
#include "../sorters/BaseSorter.h"

using namespace std;

class Runner: public BaseRunner {
    template<typename T>
    map<SorterConfig, BatchResult> runForType();

protected:
    RunnerConfig config;
    TableGenerator generator;

public:
    Runner(RunnerConfig config);
    map<SorterConfig,BatchResult> run() override;
};




#endif //RUNNER_H
