#ifndef GENERATORCONFIG_H
#define GENERATORCONFIG_H

#include "Printable.h"
#include "../../io/Serializable.h"


struct DatasetConfig: public virtual Serializable, public virtual Printable {
    int initialSize;       // starting dataset size
    int increment;          // size increment step
    int steps;              // number of steps
    int samples;            // number of samples in each step

    DatasetConfig(int initial_size, int increment, int steps, int samples): initialSize(initial_size), increment(increment), steps(steps), samples(samples) {};

    virtual string toString() const override {
        string result = "Dataset:";
        result += "\ninitial size: " + to_string(initialSize);
        result += "\nincrement: " + to_string(increment);
        result += "\nsteps: " + to_string(steps);
        result += "\nsamples: " + to_string(samples);
        return result;
    }

    virtual string serialize() const override {
        string result = "DATA_SET:";
        result += to_string(initialSize);
        result += "," + to_string(increment);
        result += "," + to_string(steps);
        result += "," + to_string(samples);
        return result;
    }
};


#endif //GENERATORCONFIG_H
