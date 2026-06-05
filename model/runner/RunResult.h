#ifndef RUNRESULT_H
#define RUNRESULT_H
#include <iostream>
#include <map>
#include <ostream>
#include <vector>

#include "BatchResult.h"
#include "../config/SorterConfig.h"
#include "../config/Printable.h"
#include "../../io/Serializable.h"


struct RunResult: public virtual Serializable, public virtual Printable {
    vector<SorterConfig> config;
    vector<std::map<int, BatchResult>> results;

    RunResult(const vector<SorterConfig> &config): config(config) {
        for(auto i: config) results.push_back({});
    }

    void addResult(int sorterIndex, int sampleSize, long long time) {
        results[sorterIndex].at(sampleSize).addResult(time);
    }

    void initBathIteration(int size, int samples) {
        for(auto& i: results) {
           i.try_emplace(size, samples).second;
        }
    }

    virtual string toString() const override {
        string result = "Run result:\n";
        for(int i = 0; i < config.size(); i++) {
            result += config[i].toString() + ":\n";
            for(auto j: results[i]) {
                result += to_string(j.first) + "\t" + j.second.compileSummary().toString() + "\n";
            }
        }
        return result;
    }

    virtual string serialize() const override {
        string result = "Run result:\n";
        for(int i = 0; i < config.size(); i++) {
            result += config[i].serialize() + config[i].toString() + ":\n";
            for(auto j: results[i]) {
                result += to_string(j.first) + "," + j.second.compileSummary().serialize() + "\n";
            }
        }
        return result;
    }
};


#endif //RUNRESULT_H
