#include "TableGenerator.h"
#include <ctime>
#include <stdlib.h>

TableGenerator::TableGenerator() {
    ascending = true;
    percentSorted = 100;
    srand(time(0));
}

TableGenerator::TableGenerator(bool ascending = true, int percentSorted = 100): ascending(ascending), percentSorted(percentSorted) {
}

void TableGenerator::populateInt(SorTable<int> sortable) {
    for (int i = 0; i < sortable.maxSize; i++) {
        sortable.add(getRandomInt());
    }
}

SorTable<int> * TableGenerator::generateIntTable(int size) {
    SorTable<int> * generated = new SorTable<int>(size);
    for (int i = 0; i < size; i++) {
        generated->add(getRandomInt());
    }
    return generated;
}

SorTable<double> * TableGenerator::generateDoubleTable(int size) {
    SorTable<double> * generated = new SorTable<double>(size);
    for (int i = 0; i < size; i++) {
        generated->add(getRandomInt());
    }
    return generated;
}

int TableGenerator::getRandomInt() {
    return rand();
}
