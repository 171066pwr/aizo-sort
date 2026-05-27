#ifndef BATCHRESULT_H
#define BATCHRESULT_H

#include "../SorTable.h"
#include "../sorters/QuickSorter.h"
#include "Summary.h"

using namespace std;

class BatchResult {
    typedef long long T;
    SorTable<T> timetable;

    T getMedian() {
        if(timetable.currentSize%2 == 1)
            return timetable[timetable.currentSize/2];
        return (timetable[timetable.currentSize/2] + timetable[timetable.currentSize/2 - 1])/2;
    }

    T getAverage() {
        T sum = 0;
        for(int i = 0; i < timetable.currentSize; i++)
            sum += timetable[i];
        return sum/timetable.currentSize;
    }

public:
    BatchResult(int size): timetable(SorTable<T>(size)) {}

    void addResult(T time) {
        timetable.add(time);
    }

    void sort() {
        QuickSorter<T> sorter = QuickSorter<T>();
        sorter.sort(timetable);
    }

    Summary getSummary() {
        T min = timetable[0];
        T max = timetable[timetable.currentSize-1];
        T avg = getAverage();
        T med = getMedian();
        return Summary(min, max, avg, med);
    }
};


#endif //BATCHRESULT_H
