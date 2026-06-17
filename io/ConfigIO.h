#ifndef CONFIGIO_H
#define CONFIGIO_H

#include "BasicIO.h"
#include "../model/config/RunnerConfig.h"

class ConfigIO: public BasicIO {
    RunnerConfig* runnerConfig;
    void readRunnerConfig();

public:
    ConfigIO(string filename): BasicIO(filename, false) {
        readRunnerConfig();
    }

    inline RunnerConfig* getRunnerConfig() {
        return runnerConfig;
    };

    void writeRunnerConfig(string filename);
};



#endif //CONFIGIO_H
