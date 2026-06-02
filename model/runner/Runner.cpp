#include "Runner.h"

#include <chrono>

#include <vector>

#include "../generator/TableGenerator.h"
#include "../sorters/SorterFactory.h"


Runner::Runner(RunnerConfig config): config(config) {}

std::map<SorterConfig, std::map<int, BatchResult>> Runner::run() {
    switch(config.tableType) {
        case DataType::CHAR:
            return runForType<char>();
        case DataType::FLOAT:
            return runForType<float>();
        case DataType::DOUBLE:
            return runForType<double>();
        case DataType::INT:
        default:
            return runForType<int>();
    }
}
/*
for (auto &attack : m_attack) // access by reference to avoid copying
{
    if (attack.m_num == input)
    {
        attack.makeDamage();
    }
}
 */

template<typename T>
std::map<SorterConfig, std::map<int, BatchResult>> Runner::runForType() {
    int sortersSize = config.sorterConfigs.size();
    BaseSorter<T>** sorters = new BaseSorter<T>*[sortersSize];
    auto results = std::map<SorterConfig, std::map<int, BatchResult>>();
    for(int i = 0; i < sortersSize; i++) {
        sorters[i] = SorterFactory<T>::createSorter(config.sorterConfigs[i].type, config.sorterConfigs[i].variant);
        //results[config.sorterConfigs[i]] = std::map<int, BatchResult>();
    }
    int current = config.datasetConfig.initial_size;
    int step = config.datasetConfig.steps;
    int increment = config.datasetConfig.increment;
    int samples = config.datasetConfig.samples;
    TableGenerator<T> generator(config.preSortMode.ascending, config.preSortMode.percentage);
    do {
        for(int i = 0; i < samples; i++) {
            SorTable<T> *table = generator.generateTable(current);
            SorTable<T> *copy;
            for(int i = 0; i < sortersSize; i++) {
                copy = table->clone();
                //TIME START
                auto start = std::chrono::steady_clock::now();
                sorters[i]->sort(*copy);
                auto end = std::chrono::steady_clock::now();
                auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
                //TIME STOP
                results[config.sorterConfigs[i]][samples].addResult(time);
                delete table, copy;
            }
        }
        samples += increment;
        step--;
    }
    while (step > 0);

    return results;
}
