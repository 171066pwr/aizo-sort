#include <iostream>
#include "../utils/Logger.h"
#include "../model/generator/TableGenerator.h"
#include "../model/SorTable.h"
#include "../io/BasicIO.h"
#include "../io/SorTableIO.h"
#include "../model/sorters/BaseSorter.h"
#include "../model/sorters/HeapSorter.h"
#include "../model/sorters/InsertionSorter.h"
#include "../model/sorters/QuickSorter.h"
#include "../model/sorters/ShellSorter.h"
#include "../model/sorters/SorterFactory.h"

class SorTableIO;
using namespace std;

void assertTrue(bool assertion, const string &msg);

void basicIOTest();
void basicModelTest();
void basicSerializationTest();
void sortCheckTest();
void basicSortersTest();
void sorterFactoryTest();

template<typename T>
bool checkSort(SorTable<T> s);

int main () {
    basicIOTest();
    basicModelTest();
    basicSerializationTest();
    sortCheckTest();
    basicSortersTest();
    sorterFactoryTest();
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
    io.~BasicIO();
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
    SorTable<int> iRead = io.readFromFile<int>("itable.txt");
    SorTable<double> dRead = io.readFromFile<double>("dtable.txt");
    assertTrue(iTable->equals(&iRead), "iTable == iRead");
    //direct comparison would likely fail due to precision loss, so comparing string representation
    assertTrue(dTable->toString() == dRead.toString(), "dTable == dRead");
}

void sortCheckTest() {
    Logger::title("Sort check test");
    char sortedArray[] = {'a', 'b', 'c', 'd'};
    char equalArray[] = {'a', 'a', 'a', 'a'};
    char unsortedArray[] = {'a', 'b', 'd', 'c'};
    SorTable<char> * cTable = new SorTable<char>(4, sortedArray);
    assertTrue(checkSort(*cTable), "sorted array");
    delete cTable;
    cTable = new SorTable<char>(4, equalArray);
    assertTrue(checkSort(*cTable), "array  of equal elements");
    delete cTable;
    cTable = new SorTable<char>(4, unsortedArray);
    assertTrue(!checkSort(*cTable), "unsorted array");
    delete cTable;
}

void basicSortersTest() {
    TableGenerator tableGenerator = TableGenerator<int>();
    SorTable<int> * sorTable = tableGenerator.generateTable(20000);

    Logger::title("Quick Sort test");
    SorTable<int> * copy = sorTable->clone();
    QuickSorter<int> qs = QuickSorter<int>(PivotPosition::RANDOM);
    BaseSorter<int> * bsorter = &qs;
    bsorter->sort(*copy);                // just checking inheritance
    assertTrue(checkSort(*copy), "QuickSort sorted array");
    SorTable<int> * sorted = copy->clone();

    Logger::title("Heap Sort test");
    copy = sorTable->clone();
    HeapSorter<int>().sort(*copy);
    assertTrue(checkSort(*copy), "Heap sorted array");
    assertTrue(copy->equals(sorted), "Heap sort data validation");
    sorted = copy->clone();

    Logger::title("Shell Sort test");
    copy = sorTable->clone();
    ShellSorter<int> ss = ShellSorter<int>(GapSequence::KNUTH);
    ss.sort(*copy);
    assertTrue(checkSort(*copy), "Shell sorted array");
    assertTrue(copy->equals(sorted), "Shell sort data validation");
    sorted = copy->clone();

    Logger::title("Insertion Sort test");
    copy = sorTable->clone();
    InsertionSorter<int> is = InsertionSorter<int>();
    bsorter = &is;
    bsorter->sort(*copy);
    assertTrue(checkSort(*copy), "Insertion sorted array");
    assertTrue(copy->equals(sorted), "Insertion sort data validation");
}

void sorterFactoryTest() {
    Logger::title("Sorter factory test");
    BaseSorter<int> * sorter;
    sorter = SorterFactory<int>::createSorter(SorterType::HEAP_SORT);
    sorter = SorterFactory<int>::createSorter(SorterType::QUICK_SORT);
    sorter = SorterFactory<int>::createSorter(SorterType::QUICK_SORT, PivotPosition::RANDOM);
    sorter = SorterFactory<int>::createSorter(SorterType::SHELL_SORT);
    sorter = SorterFactory<int>::createSorter(SorterType::SHELL_SORT, GapSequence::KNUTH);
    sorter = SorterFactory<int>::createSorter(SorterType::INSERTION_SORT);
}

void assertTrue(bool assertion, const string &msg) {
    if (!assertion) {
        Logger::warn("Assertion failed: " + msg);
    }
}

template<typename T>
bool checkSort(SorTable<T> s) {
    for (int i = 1; i < s.currentSize; ++i) {
        if (s[i-1] > s[i])
            return false;
    }
    return true;
}