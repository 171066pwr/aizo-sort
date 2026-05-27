#ifndef TABLEGENERATOR_H
#define TABLEGENERATOR_H
#include "..\SorTable.h"


class TableGenerator {
public:
    TableGenerator();
    TableGenerator(bool ascending, int percentSorted);

    void populateInt(SorTable<int> sortable);
    SorTable<int> * generateIntTable(int size);

    SorTable<double> * generateDoubleTable(int size);
private:
    int percentSorted;
    bool ascending;

    int getRandomInt();
};


#endif //TABLEGENERATOR_H
