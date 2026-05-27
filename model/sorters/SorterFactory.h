#ifndef SORTERFACTORY_H
#define SORTERFACTORY_H
#include "BaseSorter.h"
#include "HeapSorter.h"
#include "InsertionSorter.h"
#include "QuickSorter.h"
#include "ShellSorter.h"

enum SorterType {
    HEAP_SORT = 0,
    INSERTION_SORT = 1,
    QUICK_SORT = 2,
    SHELL_SORT = 3
};

template <typename T>
class SorterFactory {
public:
    static BaseSorter<T>* createSorter(int type, int variant = 0) {
        switch (type) {
            case HEAP_SORT:
                return new HeapSorter<T>();
            case INSERTION_SORT:
                return new InsertionSorter<T>();
            case SHELL_SORT:
                return new ShellSorter<T>(variant);
            case QUICK_SORT:
            default:
                return new QuickSorter<T>(variant);
        }
    };
};


#endif //SORTERFACTORY_H
