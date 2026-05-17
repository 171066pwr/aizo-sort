#ifndef BASESORTER_H
#define BASESORTER_H
#include "..\SorTable.h"


template <typename T>
class BaseSorter {
public:
    virtual void sort(SorTable<T> & sorTable) = 0;
    virtual ~BaseSorter() = default;

protected:
    void swap(SorTable<T> & sorTable, int i, int j) {
        T temp = sorTable[i];
        sorTable[i] = sorTable[j];
        sorTable[j] = temp;
    }
};


#endif //BASESORTER_H
