#ifndef MERGESORTER_H
#define MERGESORTER_H
#include "BaseSorter.h"


template <typename T>
class InsertionSorter: public BaseSorter<T> {
public:
    void sort(SorTable<T> & sorTable) override {
        for(int i=0; i< sorTable.size; i++){
            int j=0;
            while(sorTable[i]>sorTable[j] && j<i){
                j++;
            }
            insert_spec(sorTable,j,i);
        }
    }

private:
    void insert_spec (SorTable<T> & tab, int dest, int src){
        int temp = tab[src];
        for(int i = src; i>dest; i--){
            tab[i]=tab[i-1];
        }
        tab[dest] = temp;
    }
};


#endif //MERGESORTER_H
