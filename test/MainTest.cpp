#include <iostream>
#include "../utils/Logger.h"
#include "../model/TableGenerator.h"
#include "../model/SorTable.h"
#include "../io/BasicIO.h"
#include "../io/SorTableIO.h"
#include "../model/sorters/BaseSorter.h"
#include "../model/sorters/HeapSorter.h"
#include "../model/sorters/InsertionSorter.h"
#include "../model/sorters/QuickSorter.h"

class SorTableIO;
using namespace std;

void assertTrue(bool assertion, const string &msg);

void basicIOTest();
void basicModelTest();
void basicSerializationTest();
void sortCheckTest();
void basicSortersTest();

template<typename T>
bool checkSort(SorTable<T> s);

int main () {
    basicIOTest();
    basicModelTest();
    basicSerializationTest();
    sortCheckTest();
    basicSortersTest();
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
    TableGenerator tableGenerator = TableGenerator();
    SorTable<int> * sorTable = tableGenerator.generateIntTable(10);
    SorTable<int> * sorTable2 = sorTable->clone();
    const SorTable<int> &ref = *sorTable;
    SorTable<int> * sorTable3 = new SorTable<int>(ref);
    assertTrue(sorTable->equals(sorTable2), "sorTable == sorTable2");
    assertTrue(sorTable2->equals(sorTable3), "sorTable2 == sorTable3");
    sorTable->print();
    delete sorTable;
    sorTable2->print();
    delete sorTable2;
    sorTable3->print();
    delete sorTable3;
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
    Logger::title("QuickSort test");
    TableGenerator tableGenerator = TableGenerator();
    SorTable<int> * sorTable = tableGenerator.generateIntTable(10);
    QuickSorter<int> qs = QuickSorter<int>();
    BaseSorter<int> * bsorter = &qs;
    SorTable<int> * copy = sorTable->clone();
    bsorter->sort(*copy);
    assertTrue(checkSort(*copy), "QuickSort sorted array");
    delete copy;

    copy = sorTable->clone();
    InsertionSorter<int> is = InsertionSorter<int>();
    bsorter = &is;
    bsorter->sort(*copy);
    assertTrue(checkSort(*copy), "Insertion sorted array");

    copy = sorTable->clone();
    HeapSorter<int> hs = HeapSorter<int>();
    bsorter = &hs;
    bsorter->sort(*copy);
    assertTrue(checkSort(*copy), "Heap sorted array");

    sorTable->print();
    copy->print();
    delete copy;
    delete sorTable;
}

void assertTrue(bool assertion, const string &msg) {
    if (!assertion) {
        Logger::warn("Assertion failed: " + msg);
    }
}

template<typename T>
bool checkSort(SorTable<T> s) {
    for (int i = 1; i < s.size; ++i) {
        if (s[i-1] > s[i])
            return false;
    }
    return true;
}