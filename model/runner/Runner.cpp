#include "Runner.h"

#include <chrono>
#include <iostream>
#include <vector>

#include "../generator/TableGenerator.h"
#include "../sorters/SorterFactory.h"
#include "RunResult.h"
#include "../../utils/Logger.h"


Runner::Runner(RunnerConfig config): config(config) {}

RunResult Runner::run() {
    //Set global conditional display option, responsible for displaying generated/loaded data
    Globals::DISPLAY_LOG = config.displayData.display;

    switch(config.dataTypeConfig.dataType) {
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
RunResult Runner::runForType() {
    int sortersSize = config.sorterConfigs.size();
    BaseSorter<T>** sorters = new BaseSorter<T>*[sortersSize];
    RunResult results(config.sorterConfigs);
    for(int i = 0; i < sortersSize; i++) {
        sorters[i] = SorterFactory<T>::createSorter(config.sorterConfigs[i].type, config.sorterConfigs[i].variant);
    }
    int currentSize = config.datasetConfig.initialSize;
    int step = config.datasetConfig.steps;
    int increment = config.datasetConfig.increment;
    int samples = config.datasetConfig.samples;
    TableGenerator<T> generator(config.preSortMode.ascending, config.preSortMode.percentage);
    do {
        results.initBathIteration(currentSize, samples);

        for(int i = 0; i < samples; i++) {
            Logger::log("Size: " + std::to_string(currentSize) + "\tsample " + std::to_string(i));
            SorTable<T> *table = generator.generateTable(currentSize);
            SorTable<T> *copy;
            Logger::conditional("-> Generated table:\n" + table->toString());

            for(int i = 0; i < sortersSize; i++) {
                Logger::logInline(config.sorterConfigs[i].toString());
                copy = table->clone();
                //TIME START
                auto start = std::chrono::steady_clock::now();
                sorters[i]->sort(*copy);
                auto end = std::chrono::steady_clock::now();
                auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
                //TIME STOP
                results.addResult(i, currentSize, time);
                Logger::conditional("-> Sorted table:\n" + copy->toString());
                Logger::log("\t" + to_string(time/1000000.f));
                delete copy;
            }
            delete table;
        }
        currentSize += increment;
        step--;
    } while (step >= 0);
    return results;
}
