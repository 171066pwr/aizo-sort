#ifndef INSERTIONSORTER_H
#define INSERTIONSORTER_H
#include "BaseSorter.h"


template <typename T>
class InsertionSorter: public BaseSorter<T> {
public:
    void sort(SorTable<T> & sorTable) override {
        T temp;
        for(int i = 1; i < sorTable.currentSize; i++){
            temp = sorTable[i];
            int j = i - 1;
            while (j >= 0 && sorTable[j] > temp) {
                sorTable[j + 1] = sorTable[j];
                j--;
            }
            sorTable[j+1] = temp;
        }
    }
};

/*
This variant with swap is better at pre-sorted ASD data, but gets ahead only around 80%
and seems to cap at 40% faster with same O(n) at 100%.
At the same time it's noticeably slower (over 100%) at random and desc sorted data.
So just leaving it there as curio.
void sort(SorTable<T> & sorTable) override {
    for(int i = 0; i < sorTable.currentSize; i++){
        for(int j = i; j > 0 && sorTable[j] < sorTable[j - 1]; j--) {
            swap(sorTable[j], sorTable[j - 1]);
*/


#endif //INSERTIONSORTER_H
