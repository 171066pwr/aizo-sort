#ifndef RUNNERCONFIG_H
#define RUNNERCONFIG_H

#include "PreSortMode.h"
#include <vector>

#include "DatasetConfig.h"
#include "DataTypeConfig.h"
#include "DisplayDataConfig.h"
#include "SorterConfig.h"

using namespace std;

struct RunnerConfig: public virtual Serializable, public virtual Printable {
    DataTypeConfig dataTypeConfig;
    DatasetConfig datasetConfig;
    PreSortMode preSortMode;
    DisplayDataConfig displayData;
    vector<SorterConfig> sorterConfigs;

    RunnerConfig(const DataTypeConfig &data_type_config, const DatasetConfig &dataset_config,
        const PreSortMode &pre_sort_mode, const DisplayDataConfig &display_data,
        const vector<SorterConfig> &sorter_configs)
        : dataTypeConfig(data_type_config),
          datasetConfig(dataset_config),
          preSortMode(pre_sort_mode),
          displayData(display_data),
          sorterConfigs(sorter_configs) {
    }

    virtual string toString() const override {
        string result = "Run configuration:\nData type: ";
        result += dataTypeConfig.toString();
        result += "\n" + datasetConfig.toString();
        result += "\n" + preSortMode.toString();
        result += "\n" + displayData.toString();
        result += "\nSorters:";
        for (int i = 0; i < sorterConfigs.size(); i++) {
            result += "\n" + sorterConfigs[i].toString();
        }
        return result;
    }

    virtual string serialize() const override {
        string result = dataTypeConfig.serialize();
        result += "\n" + datasetConfig.serialize();
        result += "\n" + preSortMode.serialize();
        result += "\n" + displayData.serialize();
        result += "\nSORTERS:";
        for (int i = 0; i < sorterConfigs.size(); i++) {
            result += "\n" + sorterConfigs[i].serialize();
        }
        return result;
    }
};


#endif //RUNNERCONFIG_H
