#ifndef FILERUNNER_H
#define FILERUNNER_H
#include "BaseRunner.h"
#include "BatchResult.h"
#include "../config/SorterConfig.h"
#include "RunResult.h"

using namespace std;

class FileRunner: public BaseRunner {

public:
    FileRunner(string filename, SorterConfig config, int samples);
    RunResult run() override;
};


#endif //FILERUNNER_H
