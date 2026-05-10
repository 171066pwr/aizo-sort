#ifndef TABLEGENERATOR_H
#define TABLEGENERATOR_H
#include "SorTable.h"


class TableGenerator {
public:
    TableGenerator();
    TableGenerator(bool ascending, int percentSorted);
    TableGenerator(int percentSorted, bool ascending);

    void populateInt(SorTable<int> sortable);
    SorTable<int> generateIntTable(int size);
private:
    int percentSorted;
    bool ascending;

    template <typename T>
    void populateSorTable(SorTable<T> sortable);

    int getRandomInt();
};



#endif //TABLEGENERATOR_H
