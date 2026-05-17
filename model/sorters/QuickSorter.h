#ifndef QUICKSORTER_H
#define QUICKSORTER_H
#include "BaseSorter.h"

template <typename T>
class QuickSorter: public BaseSorter<T> {
public:
    void sort(SorTable<T> * sorTable) override {
        qsort(sorTable, 0, sorTable->size-1);
    }
private:
    void qsort(SorTable<T> * sorTable, int left, int right) {
        if(left<right)
        {
            int m=left;
            for(int i=left+1;i<=right;i++)
                if((*sorTable)[i] < (*sorTable)[left])
                    swap(sorTable,++m,i);
            swap(sorTable,left,m);
            qsort(sorTable,left,m-1);
            qsort(sorTable,m+1,right);
        }
    }

    void swap(SorTable<T> * sorTable, int i, int j) {
        T temp = (*sorTable)[i];
        (*sorTable)[i] = (*sorTable)[j];
        (*sorTable)[j] = temp;
    };
};


#endif //QUICKSORTER_H
