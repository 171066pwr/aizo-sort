#ifndef BASEGENERATOR_H
#define BASEGENERATOR_H

#include "../SorTable.h"
#include "../sorters/QuickSorter.h"

class BaseGenerator {
protected:
    int percentSorted;
    bool ascending;

    template<typename T>
    SorTable<T> * preSort(SorTable<T> * table) {
        if (percentSorted < 1)
            return table;
        int realSize = table->currentSize;                //persisting real table size
        int limit = (percentSorted * table->currentSize)/100.f;   //limit index of pre-sorted elements
        table->currentSize = limit;
        QuickSorter<T> sorter;
        sorter.sort(*table);                             //sorting % of first elements
        if (!ascending)                                 //reversing order if descending sort
            table->reverseOrder();
        table->currentSize = realSize;                  //restoring initial table size
        return table;
    }

public:
    BaseGenerator(bool ascending = true, int percentSorted = 0): ascending(ascending), percentSorted(percentSorted%101) {}
};


#endif //BASEGENERATOR_H
