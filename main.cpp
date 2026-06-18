#include <iostream>

#include "io/BasicIO.h"
#include "io/ConfigIO.h"
#include "io/SorTableIO.h"
#include "model/config/GlobalConfig.h"
#include "model/runner/Runner.h"
#include "model/runner/RunResult.h"
#include "utils/Logger.h"

int main(int argc, char* argv[]) {
    std::string configFile;
    if(argc < 2) {
        configFile = "config.txt";
        Logger::log("Config file argument not present, loading default config.txt...");
    }
    else {
        configFile = argv[1];
        Logger::log("Loading config from " + configFile + "...");
    }
    ConfigIO * configIO = new ConfigIO(configFile);
    RunnerConfig * config = configIO->getRunnerConfig();
    //Set global conditional display option, responsible for displaying generated/loaded data
    Globals::DISPLAY_LOG = config->displayData.display;
    DataType type = config->dataTypeConfig.dataType;
    //when running on input data file, parse type and size from data file; else use setting from config
    bool inputFileMode = config->isInputFileMode();
    if(inputFileMode) {
        type = SorTableIO::parseType(config->inputFile);
        config->datasetConfig.initialSize = SorTableIO::parseSize(config->inputFile);
    }
    Logger::log(config->toString());

    RunResult results;
    Runner runner(config);
    switch(type) {
        case CHAR:
            results = inputFileMode ? runner.runForTable(SorTableIO::readFromFile<char>(config->inputFile))
                : runner.runForGenerated<char>();
        break;
        case FLOAT:
            results = inputFileMode ? runner.runForTable(SorTableIO::readFromFile<float>(config->inputFile))
                : runner.runForGenerated<float>();
        break;
        case DOUBLE:
            results = inputFileMode ? runner.runForTable(SorTableIO::readFromFile<double>(config->inputFile))
                : runner.runForGenerated<double>();
        break;
        case INT:
            default:
            results = inputFileMode ? runner.runForTable(SorTableIO::readFromFile<int>(config->inputFile))
                : runner.runForGenerated<int>();
    }
    Logger::log(results.toString());

    BasicIO io = BasicIO(config->outputFile);
    io.writeLine(config->toString());
    io.writeLine(results.toString());
    Logger::log("Results saved to " + config->outputFile);

    system("pause");
    return 0;
}
