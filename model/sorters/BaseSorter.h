#ifndef BASESORTER_H
#define BASESORTER_H
#include "..\SorTable.h"


template <typename T>
class BaseSorter {
public:
    virtual void sort(SorTable<T> * sorTable);
    virtual ~BaseSorter() = default;

};

#endif //BASESORTER_H
