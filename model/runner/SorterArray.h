#ifndef SORTERARRAY_H
#define SORTERARRAY_H
#include <vector>

#include "SingleResult.h"
#include "../sorters/SorterFactory.h"


template <typename T>
class SorterArray {
    vector<BaseSorter<T>*> sorters;
    vector<SorterConfig> sorterConfigs;
    boolean displayData;

    SorterArray(vector<sorterConfigs> sorterConfigs, bool display): sorterConfigs(sorterConfigs), displayData(display) {
        for(int i = 0; sorterConfigs.size(); i++) {
            sorters.push_back(SorterFactory<T>::createSorter(sorterConfigs[i].type, sorterConfigs[i].variant));
        }
    };

    SingleResult<T> sort(SorTable<T> table) {

    }

};


#endif //SORTERARRAY_H
