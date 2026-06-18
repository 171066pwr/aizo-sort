#ifndef CONFIGIO_H
#define CONFIGIO_H

#include "BasicIO.h"
#include "../model/config/RunnerConfig.h"

class ConfigIO: public BasicIO {
    RunnerConfig* runnerConfig;
    void readRunnerConfig();

public:
    ConfigIO(const string& filename): BasicIO(filename, false) {
        readRunnerConfig();
    }

    inline RunnerConfig* getRunnerConfig() {
        return runnerConfig;
    };

    void writeRunnerConfig(const string& filename);
};



#endif //CONFIGIO_H
