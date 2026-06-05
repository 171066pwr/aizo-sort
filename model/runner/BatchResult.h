#ifndef BATCHRESULT_H
#define BATCHRESULT_H

#include "../SorTable.h"
#include "../sorters/QuickSorter.h"
#include "Summary.h"

using namespace std;

class BatchResult {
    typedef long long L;
    SorTable<L> timetable;

    L getMedian() {
        if(timetable.currentSize%2 == 1)
            return timetable[timetable.currentSize/2];
        return (timetable[timetable.currentSize/2] + timetable[timetable.currentSize/2 - 1])/2;
    }

    L getAverage() {
        L sum = 0;
        for(int i = 0; i < timetable.currentSize; i++)
            sum += timetable[i];
        return sum/timetable.currentSize;
    }

    void sort() {
        QuickSorter<L> sorter = QuickSorter<L>();
        sorter.sort(timetable);
    }

public:
    BatchResult(int size): timetable(SorTable<L>(size)) {}

    void addResult(L time) {
        timetable.add(time);
    }

    Summary compileSummary() {
        sort();
        L min = timetable[0]/1000;
        L max = timetable[timetable.currentSize-1]/1000;
        L avg = getAverage()/1000;
        L med = getMedian()/1000;
        return Summary(min, max, avg, med);
    }
};


#endif //BATCHRESULT_H
