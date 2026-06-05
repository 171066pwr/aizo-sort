#ifndef RUNNER_H
#define RUNNER_H


#include <map>

#include "BaseRunner.h"
#include "../config/RunnerConfig.h"


class Runner: public BaseRunner {
    template<typename T>
    RunResult runForType();

protected:
    RunnerConfig config;

public:
    Runner(RunnerConfig config);
    RunResult run() override;
};


#endif //RUNNER_H
