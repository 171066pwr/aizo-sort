#ifndef RUNNER_H
#define RUNNER_H
#include "RunResult.h"


struct RunnerConfig;

class Runner {
    RunnerConfig * config;

    template<typename T>
    BaseSorter<T>** createSorters();
public:
    Runner(RunnerConfig * config): config(config) {};

    template<typename T>
    RunResult runForGenerated();

    template<typename T>
    RunResult runForTable(SorTable<T> * sorTable);
};


#endif //RUNNER_H
