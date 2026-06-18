#include "Runner.h"

#include <chrono>
#include <vector>

#include "../config/RunnerConfig.h"
#include "../generator/TableGenerator.h"
#include "../sorters/SorterFactory.h"
#include "RunResult.h"
#include "../../utils/Logger.h"
#include "../../utils/NumberUtils.h"


template<typename T>
RunResult Runner::runForGenerated() {
    Logger::log("Running for generated data...");
    BaseSorter<T>** sorters = createSorters<T>();
    RunResult results(config->sorterConfigs);

    int sortersSize = config->sorterConfigs.size();
    int currentSize = config->datasetConfig.initialSize;
    int step = config->datasetConfig.steps;
    int increment = config->datasetConfig.increment;
    int samples = config->datasetConfig.samples;
    TableGenerator<T> generator(config->preSortMode.ascending, config->preSortMode.percentage); // initialize generator
    do {
        results.initBathIteration(currentSize, samples);        // initialize empty row in results map
        for(int j = 0; j < samples; j++) {
            Logger::logProgress("Size: " + std::to_string(currentSize) + "\tsample " + std::to_string(j));
            SorTable<T> *table = generator.generateTable(currentSize);
            Logger::logData("-> Generated table:\n" + table->toString());

            for(int i = 0; i < sortersSize; i++) {
                Logger::logProgress(config->sorterConfigs[i].toString());
                SorTable<T> *copy = table->clone();
                //TIME START
                auto start = std::chrono::steady_clock::now();
                sorters[i]->sort(*copy);
                auto end = std::chrono::steady_clock::now();
                //TIME STOP
                auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
                results.addResult(i, currentSize, time);

                Logger::logData("-> Sorted table:\n" + copy->toString());
                Logger::logProgress("\t" + NumberUtils::nanoToMilis(time));
                //Sort validation
                if(!copy->checkSort())
                    Logger::warn("################ FAILED TO SORT!!! ################");
                delete copy;
            }
            delete table;
        }
        currentSize += increment;
        step--;
    } while (step >= 0);
    return results;
}

template<typename T>
RunResult Runner::runForTable(SorTable<T> * sorTable) {
    Logger::log("Running for input file...");
    int sortersSize = config->sorterConfigs.size();
    BaseSorter<T>** sorters = createSorters<T>();
    RunResult results(config->sorterConfigs);

    int currentSize = sorTable->currentSize;
    int samples = config->datasetConfig.samples;
    results.initBathIteration(currentSize, samples);        // initialize empty row in results map
    Logger::logData("-> Loaded table:\n" + sorTable->toString());
    Logger::log("Size: " + std::to_string(currentSize));

    for(int j = 0; j < sortersSize; j++) {
        Logger::log(config->sorterConfigs[j].toString());
        for(int i = 0; i < samples; i++) {
            Logger::logInline("sample " + std::to_string(i) + "\t");
            SorTable<T> *copy = sorTable->clone();
            //TIME START
            auto start = std::chrono::steady_clock::now();
            sorters[j]->sort(*copy);
            auto end = std::chrono::steady_clock::now();
            //TIME STOP
            auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            results.addResult(j, currentSize, time);

            Logger::logData("-> Sorted table:\n" + copy->toString());
            Logger::log("\t" + NumberUtils::nanoToMilis(time));
            //Sort validation
            if(!copy->checkSort())
                Logger::warn("################ FAILED TO SORT!!! ################");
            delete copy;
        }
    }
    return results;
}

template<typename T>
BaseSorter<T>** Runner::createSorters() {
    int sortersSize = config->sorterConfigs.size();
    BaseSorter<T>** sorters = new BaseSorter<T>*[sortersSize];
    RunResult results(config->sorterConfigs);
    for(int i = 0; i < sortersSize; i++) {
        sorters[i] = SorterFactory<T>::createSorter(config->sorterConfigs[i].type, config->sorterConfigs[i].variant);
    }
    return sorters;
}

// It shouldn't require explicit instantiation, especially runForGenerated.
// I really don't get templates sometimes...
template RunResult Runner::runForTable<int>(SorTable<int> * sorTable);
template RunResult Runner::runForTable<char>(SorTable<char> * sorTable);
template RunResult Runner::runForTable<float>(SorTable<float> * sorTable);
template RunResult Runner::runForTable<double>(SorTable<double> * sorTable);

template RunResult Runner::runForGenerated<int>();
template RunResult Runner::runForGenerated<char>();
template RunResult Runner::runForGenerated<float>();
template RunResult Runner::runForGenerated<double>();
