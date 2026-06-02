#ifndef RUNNER_H
#define RUNNER_H


#include <map>

#include "BaseRunner.h"
#include "BatchResult.h"
#include "../config/RunnerConfig.h"


class Runner: public BaseRunner {
    template<typename T>
    map<SorterConfig, std::map<int, BatchResult>> runForType();

protected:
    RunnerConfig config;

public:
    Runner(RunnerConfig config);
    std::map<SorterConfig, std::map<int, BatchResult>> run() override;
};


#endif //RUNNER_H
