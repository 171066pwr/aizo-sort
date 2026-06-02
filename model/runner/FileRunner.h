#ifndef FILERUNNER_H
#define FILERUNNER_H
#include "BaseRunner.h"
#include "BatchResult.h"
#include "../config/SorterConfig.h"
#include <map>

using namespace std;

class FileRunner: public BaseRunner {

public:
    FileRunner(string filename, SorterConfig config, int samples);
    map<SorterConfig, map<int, BatchResult>> run() override;
};


#endif //FILERUNNER_H
