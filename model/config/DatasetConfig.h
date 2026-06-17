#ifndef GENERATORCONFIG_H
#define GENERATORCONFIG_H

#include <sstream>

#include "../../io/Printable.h"
#include "../../io/Serializable.h"


struct DataSetConfig: public virtual Serializable, public virtual Printable {
    int initialSize;       // starting dataset size
    int increment;          // size increment step
    int steps;              // number of steps
    int samples;            // number of samples in each step

    DataSetConfig(int initial_size, int increment, int steps, int samples): initialSize(initial_size), increment(increment), steps(steps), samples(samples) {};

    DataSetConfig(int samples = 10): initialSize(0), increment(0), steps(0), samples(samples) {};

    static DataSetConfig deserialize(const string &line) {
        string s;
        stringstream ss(line);
        vector<int> tokens;
        while (std::getline(ss, s, ','))
            tokens.push_back(std::stoi(s));
        if(tokens.size() == 0)
            return DataSetConfig();
        if (tokens.size() == 1)
            return DataSetConfig(tokens[0]);
        return DataSetConfig(tokens[0], tokens[1], tokens[2], tokens[3]);
    }

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
