#ifndef GENERATORCONFIG_H
#define GENERATORCONFIG_H


struct DatasetConfig {
    int initial_size;       // starting dataset size
    int increment;          // size increment step
    int steps;              // number of steps
    int samples;            // number of samples in each step
};


#endif //GENERATORCONFIG_H
