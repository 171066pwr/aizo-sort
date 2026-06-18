#ifndef INSERTIONSORTER_H
#define INSERTIONSORTER_H
#include "BaseSorter.h"


template <typename T>
class InsertionSorter: public BaseSorter<T> {
public:
    void sort(SorTable<T> & sorTable) override {
        for(int i = 0; i < sorTable.currentSize; i++){
            for(int j = i; j > 0 && sorTable[j] < sorTable[j - 1]; j--) {
                swap(sorTable[j], sorTable[j - 1]);
            }
        }
    }
};
/*
 This variant is slightly better with random and pre-sorted DESC, but starts losing to
 implementation with swap when over 60% is sorted ASC, then completely falls off over 80% sorted.
 So I think swap variant is much better for what Insertion Sort is created.
 It's not going to win at random data with QSort/Heap anyways.

void sort(SorTable<T> & sorTable) override {
        for(int i = 0; i < sorTable.currentSize; i++){
            int j = 0;
            while(sorTable[i] > sorTable[j] && j < i){
                j++;
            }
            insert_spec(sorTable,j,i);
        }
    }

private:
    void insert_spec (SorTable<T> & tab, int dest, int src){
        T temp = tab[src];
        for(int i = src; i> dest; i--){
            tab[i] = tab[i-1];
        }
        tab[dest] = temp;
    }
*/


#endif //INSERTIONSORTER_H
