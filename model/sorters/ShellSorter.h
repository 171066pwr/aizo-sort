#ifndef SHELLSORTER_H
#define SHELLSORTER_H
#include "InsertionSorter.h"
#include "../SorTable.h"

enum GapSequence {
    KNUTH = 0,
    SHELL = 1
};

template <typename T>
class ShellSorter: public BaseSorter<T> {
    class BaseGapSequence;
public:
    const BaseGapSequence * sequence;

    ShellSorter(GapSequence sequenceType) {
        switch (sequenceType) {
            case SHELL:
                sequence = new ShellSequence();
                break;
            case KNUTH:
            default:
                sequence = new KnuthSequence();
        }
    }

    void sort(SorTable<T> & sorTable) override {
        shellSort(sorTable);
    }

private:
    void popAndSort (SorTable<T> & tab, int h){
        InsertionSorter<T> insSorter;
        for (int i = 0; i<h; i++){
            SorTable<T> partial = SorTable<T>((tab.currentSize/h)+1);

            for(int j = 0; j < (tab.currentSize-i)/h; j++){
                partial.add(tab[j*h+i]);
            }
            insSorter.sort(partial);

            for( int j = 0; j<(tab.currentSize-i)/h; j++){
                tab[j*h+i] = partial[j];
            }
        }
    }

    void shellSort(SorTable<T> & tab){
        int gap = sequence->getInitialGap(tab.currentSize);
        while (gap>0) {
            popAndSort(tab, gap);
            gap = sequence->getNextGap(gap);
        }
    }

    //interface for gap sequences
    class BaseGapSequence {
        public:
        virtual ~BaseGapSequence() = default;
        virtual int getInitialGap(int size) const = 0;
        virtual int getNextGap(int gap) const = 0;
    };

    class KnuthSequence: public BaseGapSequence {
        public:
        int getInitialGap(int size) const override {
            int gap = 1;
            while (gap < size)
                gap = gap*3 + 1;
            gap /= 9;
            return gap < 1 ? 1 : gap;
        }

        int getNextGap(int gap) const override {
            return gap/3;
        }
    };

    class ShellSequence: public BaseGapSequence {
    public:
        int getInitialGap(int size) const override {
            return size/2;
        }

        int getNextGap(int gap) const override {
            return gap/2;
        }
    };
};


#endif //SHELLSORTER_H
