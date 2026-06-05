#ifndef QUICKSORTER_H
#define QUICKSORTER_H
#include "BaseSorter.h"

enum PivotPosition   {
    RANDOM = 0,
    LOW = 1,
    HIGH = 2,
    CENTER = 3
};

template <typename T>
class QuickSorter: public BaseSorter<T> {
    class BasePivotProvider;
public:
const BasePivotProvider * pivotProvider;
    QuickSorter(PivotPosition pivotPosition = RANDOM) {
        switch(pivotPosition) {
            case LOW:
                pivotProvider = new LeftPivotProvider();
                break;
            case HIGH:
                pivotProvider = new RightPivotProvider();
                break;
            case CENTER:
                pivotProvider = new CenterPivotProvider();
                break;
            case RANDOM:
            default:
                pivotProvider = new RandomPivotProvider();
        }
    };

    QuickSorter(int pivotPosition): QuickSorter((PivotPosition) pivotPosition) {}

    void sort(SorTable<T> & sorTable) override {
        qsort(sorTable, 0, sorTable.currentSize-1);
    }

private:
    // Slightly modified Lomuto, functionally the same
    void qsort(SorTable<T> &sorTable, int low, int high) {
        if(low<high) {
            this->swap(sorTable, pivotProvider->getPivot(low, high), high);
            int i = low-1;
            for(int j = low; j <= high; j++) {
                if(sorTable[j] <= sorTable[high]) {
                    i++;
                    if(i != j)
                        this->swap(sorTable,i,j);
                }
            }
            qsort(sorTable,low,i-1);
            qsort(sorTable,i+1, high);
        }
    }

    //interface for pivot providers
    class BasePivotProvider {
    public:
        virtual ~BasePivotProvider() = default;
        virtual int getPivot(int low, int high) const = 0;
    };

    class LeftPivotProvider: public BasePivotProvider {
        public:
        int getPivot(int low, int high) const override {
            return low;
        }
    };

    class RightPivotProvider: public BasePivotProvider {
        public:
        int getPivot(int low, int high) const override {
            return high;
        }
    };

    class CenterPivotProvider: public BasePivotProvider {
        public:
        int getPivot(int low, int high) const override {
            return low + (high - low)/2;
        }
    };

    class RandomPivotProvider: public BasePivotProvider {
        public:
        int getPivot(int low, int high) const override {
            return  low + rand()%(high - low);
        }
    };
};


#endif //QUICKSORTER_H
