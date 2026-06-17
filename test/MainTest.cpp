#include <iostream>
#include "../utils/Logger.h"
#include "../model/generator/TableGenerator.h"
#include "../model/SorTable.h"
#include "../io/BasicIO.h"
#include "../io/SorTableIO.h"
#include "../model/config/DataSetConfig.h"
#include "../model/config/DisplayDataConfig.h"
#include "../model/config/PreSortMode.h"
#include "../model/config/RunnerConfig.h"
#include "../model/config/SorterConfig.h"
#include "../model/runner/Runner.h"
#include "../model/sorters/BaseSorter.h"
#include "../model/sorters/HeapSorter.h"
#include "../model/sorters/InsertionSorter.h"
#include "../model/sorters/QuickSorter.h"
#include "../model/sorters/ShellSorter.h"
#include "../model/sorters/SorterFactory.h"

struct SorterConfig;
class SorTableIO;
using namespace std;

void assertTrue(bool assertion, const string &msg);

void basicIOTest();
void basicModelTest();
void basicSerializationTest();
void deserializationTest();
void sortCheckTest();
void basicSortersTest();
void sorterFactoryTest();
void configSerializationTest();
void runWithGeneratorTest();
void runForTableTest();
void preSortTest();

int main () {
    basicIOTest();
    basicModelTest();
    basicSerializationTest();
    deserializationTest();
    sortCheckTest();
    preSortTest();
    basicSortersTest();
    sorterFactoryTest();
    configSerializationTest();
    runForTableTest();
    runWithGeneratorTest();

    system("pause");
}

void basicIOTest() {
    BasicIO io = BasicIO("test.txt", true);
    io.writeLine("1");
    io.writeLine("2");
    io.writeLine("3");
    string line = io.readLine();
    Logger::log(line);
    assertTrue(line == "1", "line == 1");
    line = io.readLine();
    Logger::log(line);
    assertTrue(line == "2", "line == 2");
}

void basicModelTest() {
    Logger::title("Basic model test");
    TableGenerator tableGenerator = TableGenerator<int>();
    SorTable<int> * sorTable = tableGenerator.generateTable(10);
    SorTable<int> * sorTable2 = sorTable->clone();
    const SorTable<int> &ref = *sorTable;
    SorTable<int> * sorTable3 = new SorTable<int>(ref);
    assertTrue(sorTable->equals(sorTable2), "sorTable == sorTable2");
    assertTrue(sorTable2->equals(sorTable3), "sorTable2 == sorTable3");
    sorTable->print();
    sorTable2->print();
    sorTable3->print();
    Logger::title("Reversing table test");
    int tab[] = {0, 1, 2, 3, 4, 5};
    int reversed[] = {5, 4, 3, 2, 1, 0};
    sorTable = new SorTable<int>(6, tab);
    sorTable2 = new SorTable<int>(6, reversed);
    sorTable->reverseOrder();
    assertTrue(sorTable->equals(sorTable2), "reversed order");
}

void basicSerializationTest() {
    Logger::title("Serialization test");
    int iarray[] = {3, 4, 5};
    SorTable<int> * iTable = new SorTable<int>(3, iarray);

    double darray[] = {1.2f, 2.3f, 3.4f};
    SorTable<double> * dTable = new SorTable<double>(3, darray);

    SorTableIO io;
    io.saveToFile("itable.txt", *iTable);
    io.saveToFile("dtable.txt", *dTable);
    SorTable<int> * iRead = io.readFromFile<int>("itable.txt");
    SorTable<double> * dRead = io.readFromFile<double>("dtable.txt");
    assertTrue(iTable->equals(iRead), "iTable == iRead");
    //direct comparison would likely fail due to precision loss, so comparing string representation
    assertTrue(dTable->toString() == dRead->toString(), "dTable == dRead");
}

void deserializationTest() {
    Logger::title("Deserialization test");
    Logger::title("Config mode 2");

    stringstream ss = stringstream();
    ss << "OUTPUT_FILE:kopytko.txt\n";
    ss << "DATA_TYPE:char\n";
    ss << "DATA_SET:100,10,9,20\n";
    ss << "PRE_SORT:1,0\n";
    ss << "DISPLAY_DATA:1\n";
    ss << "SORTERS:" << "0,0#1,0#2,3";
    vector<string> lines;
    string s;
    while(std::getline(ss, s))
        lines.push_back(s);
    RunnerConfig * config = RunnerConfig::deserialize(&lines);
    Logger::log(config->toString());

    Logger::title("Config mode 1");

    ss.clear();
    ss << "INPUT_FILE:kopytko.txt\n";
    ss << "DATA_SET:20\n";
    ss << "PRE_SORT:0,66\n";
    ss << "DISPLAY_DATA:0\n";
    ss << "SORTERS:" << "0,0#1,0#2,3#3,1";
    lines.clear();
    while(std::getline(ss, s))
        lines.push_back(s);
    config = RunnerConfig::deserialize(&lines);
    Logger::log(config->toString());
}

void sortCheckTest() {
    Logger::title("Sort check test");
    char sortedArray[] = {'a', 'b', 'c', 'd'};
    char equalArray[] = {'a', 'a', 'a', 'a'};
    char unsortedArray[] = {'a', 'b', 'd', 'c'};
    SorTable<char> * cTable = new SorTable<char>(4, sortedArray);
    assertTrue(cTable->checkSort(), "sorted array");
    delete cTable;
    cTable = new SorTable<char>(4, equalArray);
    assertTrue(cTable->checkSort(), "array  of equal elements");
    delete cTable;
    cTable = new SorTable<char>(4, unsortedArray);
    assertTrue(!cTable->checkSort(), "unsorted array");
    delete cTable;
}

void basicSortersTest() {
    TableGenerator tableGenerator = TableGenerator<int>();
    SorTable<int> * sorTable = tableGenerator.generateTable(1000);

    Logger::title("Quick Sort test");
    SorTable<int> * copy = sorTable->clone();
    QuickSorter<int> qs = QuickSorter<int>(PivotPosition::RANDOM);
    BaseSorter<int> * bsorter = &qs;
    bsorter->sort(*copy);                // just checking inheritance
    assertTrue(copy->checkSort(), "QuickSort sorted array");
    SorTable<int> * sorted = copy->clone();

    Logger::title("Heap Sort test");
    copy = sorTable->clone();
    HeapSorter<int>().sort(*copy);
    assertTrue(copy->checkSort(), "Heap sorted array");
    assertTrue(copy->equals(sorted), "Heap sort data validation");
    sorted = copy->clone();

    Logger::title("Shell Sort test");
    copy = sorTable->clone();
    ShellSorter<int> ss = ShellSorter<int>(GapSequence::KNUTH);
    ss.sort(*copy);
    assertTrue(copy->checkSort(), "Shell sorted array");
    assertTrue(copy->equals(sorted), "Shell sort data validation");
    sorted = copy->clone();

    Logger::title("Insertion Sort test");
    copy = sorTable->clone();
    InsertionSorter<int> is = InsertionSorter<int>();
    bsorter = &is;
    bsorter->sort(*copy);
    assertTrue(copy->checkSort(), "Insertion sorted array");
    assertTrue(copy->equals(sorted), "Insertion sort data validation");
}

void sorterFactoryTest() {
    Logger::title("Sorter factory test");
    TableGenerator tableGenerator = TableGenerator<int>();
    SorTable<int> * sorTable = tableGenerator.generateTable(100);
    SorTable<int> * copy;
    BaseSorter<int> * sorter;

    sorter = SorterFactory<int>::createSorter(SorterType::HEAP_SORT);
    copy = sorTable->clone();
    sorter->sort(*copy);
    assertTrue(copy->checkSort(), "Heap Sort");

    sorter = SorterFactory<int>::createSorter(SorterType::QUICK_SORT);
    copy = sorTable->clone();
    sorter->sort(*copy);
    assertTrue(copy->checkSort(), "Quick Sort, default random");

    sorter = SorterFactory<int>::createSorter(SorterType::QUICK_SORT, PivotPosition::CENTER);
    copy = sorTable->clone();
    sorter->sort(*copy);
    assertTrue(copy->checkSort(), "Quick Sort, center");

    sorter = SorterFactory<int>::createSorter(SorterType::SHELL_SORT);
    copy = sorTable->clone();
    sorter->sort(*copy);
    assertTrue(copy->checkSort(), "Shell Sort, Shell");

    sorter = SorterFactory<int>::createSorter(SorterType::SHELL_SORT, GapSequence::KNUTH);
    copy = sorTable->clone();
    sorter->sort(*copy);
    assertTrue(copy->checkSort(), "Shell Sort, Knuth");

    sorter = SorterFactory<int>::createSorter(SorterType::INSERTION_SORT);
    copy = sorTable->clone();
    sorter->sort(*copy);
    assertTrue(copy->checkSort(), "Insertion Sort");
}

void configSerializationTest() {
    Logger::title("Config Serialization Test");
    DataTypeConfig dataTypeConfig("char");
    DataSetConfig datasetConfig(100, 100, 5, 5);
    PreSortMode preSortMode;
    DisplayDataConfig displayConfig;
    vector<SorterConfig> sorterConfigs;
    sorterConfigs.push_back(SorterConfig(0, 0));
    sorterConfigs.push_back(SorterConfig(1, 0));
    sorterConfigs.push_back(SorterConfig(2, 0));
    sorterConfigs.push_back(SorterConfig(2, 3));
    sorterConfigs.push_back(SorterConfig(3, 0));
    sorterConfigs.push_back(SorterConfig(3, 1));
    RunnerConfig config(dataTypeConfig, datasetConfig, preSortMode, displayConfig, sorterConfigs);
    Logger::log(config.toString());
    Logger::log(config.serialize());
}

void runForTableTest() {
    Logger::title("Runner input table test");
    TableGenerator tableGenerator = TableGenerator<int>();
    SorTable<int> * sorTable = tableGenerator.generateTable(200);

    DataTypeConfig dataTypeConfig("int");
    DataSetConfig datasetConfig(20);
    PreSortMode preSortMode;
    DisplayDataConfig displayConfig(false);
    vector<SorterConfig> sorterConfigs;
    sorterConfigs.push_back(SorterConfig(0, 0));
    sorterConfigs.push_back(SorterConfig(2, 0));
    sorterConfigs.push_back(SorterConfig(2, 1));
    sorterConfigs.push_back(SorterConfig(2, 2));
    sorterConfigs.push_back(SorterConfig(2, 3));
    RunnerConfig config(dataTypeConfig, datasetConfig, preSortMode, displayConfig, sorterConfigs);

    Runner runner(&config);
    RunResult result = runner.runForTable<int>(sorTable);
    Logger::log(result.toString());
    Logger::log(result.serialize());

    BasicIO io = BasicIO();
    io.writeLine(result.toString());
    BasicIO io2 = BasicIO();
    io2.writeLine(result.serialize());
}

void runWithGeneratorTest() {
    Logger::title("Runner with generator test");
    DataTypeConfig dataTypeConfig("int");
    DataSetConfig datasetConfig(100, 100, 9, 10);
    PreSortMode preSortMode;
    DisplayDataConfig displayConfig(false);
    vector<SorterConfig> sorterConfigs;
    sorterConfigs.push_back(SorterConfig(0, 0));
    sorterConfigs.push_back(SorterConfig(1, 0));
    sorterConfigs.push_back(SorterConfig(2, 0));
    sorterConfigs.push_back(SorterConfig(2, 1));
    sorterConfigs.push_back(SorterConfig(2, 2));
    sorterConfigs.push_back(SorterConfig(2, 3));
    sorterConfigs.push_back(SorterConfig(3, 0));
    sorterConfigs.push_back(SorterConfig(3, 1));
    RunnerConfig config(dataTypeConfig, datasetConfig, preSortMode, displayConfig, sorterConfigs);

    Runner runner(&config);
    RunResult result = runner.runForGenerated<int>();
    Logger::log(result.toString());
    Logger::log(result.serialize());

    BasicIO io = BasicIO();
    io.writeLine(result.toString());
    BasicIO io2 = BasicIO();
    io2.writeLine(result.serialize());
}

void preSortTest() {
    Logger::title("Pre-sorted generation test");
    TableGenerator tableGenerator = TableGenerator<int>(true, 100);
    SorTable<int> * sorTable = tableGenerator.generateTable(100);
    assertTrue(sorTable->checkSort(), "Should be fully pre-sorted");

    tableGenerator = TableGenerator<int>(true, 50);
    sorTable = tableGenerator.generateTable(20);
    Logger::log("50% sorted");
    sorTable->print();

    tableGenerator = TableGenerator<int>(true, 30);
    sorTable = tableGenerator.generateTable(20);
    Logger::log("30% sorted");
    sorTable->print();

    tableGenerator = TableGenerator<int>(false, 100);
    sorTable = tableGenerator.generateTable(20);
    Logger::log("Fully descending sorted");
    sorTable->print();

    tableGenerator = TableGenerator<int>(false, 50);
    sorTable = tableGenerator.generateTable(20);
    Logger::log("50% descending sorted");
    sorTable->print();
}


void assertTrue(bool assertion, const string &msg) {
    if (!assertion) {
        Logger::warn("Assertion failed: " + msg);
    }
}
