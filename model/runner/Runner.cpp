#include "Runner.h"
#include <vector>

#include "../generator/TableGenerator.h"
#include "../sorters/SorterFactory.h"


Runner::Runner(RunnerConfig config): config(config) {
    generator = TableGenerator(config.preSortMode.ascending, config.preSortMode.percentage);
}

map<SorterConfig, BatchResult> Runner::run() {
    switch(config.tableType) {
        case CHAR:
            return runForType<char>();
        case FLOAT:
            return runForType<float>();
        case DOUBLE:
            return runForType<double>();
        case INT:
        default:
            return runForType<int>();
    }
}

template<typename T>
map<SorterConfig, BatchResult> Runner::runForType() {
    vector<BaseSorter<T>*> sorters;
    int current = config.generatorConfig.initial_size;
    int step = config.generatorConfig.steps+1;
    int increment = config.generatorConfig.increment;
    for(int i = 0; config.sorterConfigs.size(); i++) {
        sorters.push_back(SorterFactory<T>::createSorter(config.sorterConfigs[i].type, config.sorterConfigs[i].variant));
    }

    int iteration = config.generatorConfig.steps;


    // while (step > 0) {
    //     generator.
    // }
    return map<SorterConfig, BatchResult>();
}
