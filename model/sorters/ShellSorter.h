#ifndef SHELLSORTER_H
#define SHELLSORTER_H
#include "InsertionSorter.h"
#include "../SorTable.h"


template <typename T>
class ShellSorter: public BaseSorter<T> {
public:
    void sort(SorTable<T> & sorTable) override {
        if (32 > sorTable.size) {   // funny CLion bug, if operand order is reversed it freaks out due to templates
            InsertionSorter<T> insSorter;
            insSorter.sort(sorTable);
        } else {
            shellSort(sorTable, sorTable.size/32);
        }
    }

private:
    void popAndSort (SorTable<T> & tab, int h){
        InsertionSorter<T> insSorter;
        for (int i = 0; i<h; i++){
            SorTable<T> partial = SorTable<T>((tab.size/h)+1);

            for(int j = 0; j < (tab.size-i)/h; j++){
                partial[j] = tab[j*h+i];
            }
            insSorter.sort(partial);

            for( int j = 0; j<(tab.size-i)/h; j++){
                tab[j*h+i] = partial[j];
            }
        }
    }

    void shellSort(SorTable<T> & tab, int maxh){
        int h = 1;
        while (h<=maxh)
            h = h*3+1;
        while (h>0) {
            h--;
            h/=3;
            popAndSort(tab, h);
        }
    }
};


#endif //SHELLSORTER_H
