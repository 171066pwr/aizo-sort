#ifndef RUNNERCONFIG_H
#define RUNNERCONFIG_H

#include <vector>
#include <ctime>
#include <map>

#include "DataSetConfig.h"
#include "DataTypeConfig.h"
#include "DisplayDataConfig.h"
#include "PreSortMode.h"
#include "SorterConfig.h"


struct RunnerConfig: public virtual Serializable, public virtual Printable {
    string inputFile;
    string outputFile;
    DataTypeConfig dataTypeConfig;
    DataSetConfig datasetConfig;
    PreSortMode preSortMode;
    DisplayDataConfig displayData;
    vector<SorterConfig> sorterConfigs;

    RunnerConfig(const DataTypeConfig &data_type_config, const DataSetConfig &dataset_config,
        const PreSortMode &pre_sort_mode, const DisplayDataConfig &display_data,
        const vector<SorterConfig> &sorter_configs,
        string input_file = "", string output_file = ""):
            dataTypeConfig(data_type_config),
            datasetConfig(dataset_config),
            preSortMode(pre_sort_mode),
            displayData(display_data),
            sorterConfigs(sorter_configs),
            inputFile(input_file), outputFile(output_file)
    {
        if(sorterConfigs.empty()) {
            throw std::runtime_error("Failed to read sorter configs.");
        }
        if(output_file.empty()) {                       // default output filename if empty
            time_t now = time(nullptr);
            tm* local = localtime(&now);
            char buffer[100];
            strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S.txt", local);
            outputFile = std::string(buffer);
        }
    }

    bool isInputFileMode() const {
        return !inputFile.empty();
    }

    static RunnerConfig* deserialize(vector<std::string> *lines) {
        map<string, string> config;
        for(auto& i: *lines) {
            stringstream ss(i);
            string key;
            std::getline(ss, key, ':');
            string value;
            std::getline(ss, value, ':');
            config[key] = value;
        }
        string inputFile = config["INPUT_FILE"];
        string outputFile = config["OUTPUT_FILE"];
        DataTypeConfig dataTypeConfig = DataTypeConfig::deserialize(config["DATA_TYPE"]);
        DataSetConfig datasetConfig = DataSetConfig::deserialize(config["DATA_SET"]);
        PreSortMode preSortMode  = PreSortMode::deserialize(config["PRE_SORT"]);
        DisplayDataConfig displayConfig = DisplayDataConfig::deserialize(config["DISPLAY_DATA"]);

        stringstream ss(config["SORTERS"]);
        vector<string> sorters;
        string s;
        while (std::getline(ss, s, '#'))
            sorters.push_back(s);
        vector<SorterConfig> sorterConfigs;
        for(auto& i: sorters) {
            sorterConfigs.push_back(SorterConfig::deserialize(i));
        }
        return new RunnerConfig(
            dataTypeConfig,
            datasetConfig,
            preSortMode,
            displayConfig,
            sorterConfigs,
            inputFile,
            outputFile);
    }

    virtual string toString() const override {
        string result = "Run configuration:";
        result += inputFile.empty() ? "" : "\nInput file: " + inputFile;
        result += "\nOutput file: " + outputFile;
        result += "\nData type: " + dataTypeConfig.toString();
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
        string result = inputFile.empty() ? "" : "\nINPUT_FILE:" + inputFile;
        result += "\nOUTPUT_FILE:" + outputFile;
        result += "\n" + dataTypeConfig.serialize();
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
