#include "ConfigIO.h"

#include "SorTableIO.h"

void ConfigIO::readRunnerConfig() {
    try {
        BasicIO io(filename);
        auto lines = io.readLines();
        if(lines.empty())
            throw std::runtime_error("");
        runnerConfig = RunnerConfig::deserialize(&lines);
        if(!runnerConfig->inputFile.empty()) {
            runnerConfig->dataTypeConfig.dataType = SorTableIO::parseType(runnerConfig->inputFile);
        }
    } catch(const std::exception& e) {
        stringstream message("");
        message << "Failed to read config file. ";
        message << e.what();
        throw std::runtime_error(e.what());
    }
}

void ConfigIO::writeRunnerConfig(const string& filename) {
    BasicIO io(filename);
    io.writeLine(runnerConfig->serialize());
}
