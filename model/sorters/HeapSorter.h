#ifndef HEAPSORTER_H
#define HEAPSORTER_H
#include "BaseSorter.h"


template<typename T>
class HeapSorter : public BaseSorter<T> {
public:
    void sort(SorTable<T> &sorTable) override {
        heapify(sorTable, sorTable.currentSize);
        int end = sorTable.currentSize - 1;
        while (end > 0) {
            this->swap(sorTable, end, 0);
            siftDown(sorTable, 0, end - 1);
            end--;
        }
    }

private:
    void siftDown(SorTable<T> &tab, int start, int end) {
        int root = start;
        while (root * 2 + 1 <= end) {
            int child = root * 2 + 1;
            if (child < end && tab[child] < tab[child + 1]) {
                child++;
            }
            if (tab[root] < tab[child]) {
                this->swap(tab, root, child);
                root = child;
            } else
                break;
        }
    }

    void heapify(SorTable<T> &tab, int count) {
        int start = (count - 2) / 2;
        while (start >= 0) {
            siftDown(tab, start, count - 1);
            start--;
        }
    }
};


#endif //HEAPSORTER_H
