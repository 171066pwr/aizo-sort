#ifndef TABLEGENERATOR_H
#define TABLEGENERATOR_H


#include "..\SorTable.h"
#include <ctime>
#include <random>

#include "BaseGenerator.h"


template <typename T>
class TableGenerator: protected BaseGenerator {
public:
    TableGenerator(bool ascending = true, int percentSorted = 0): BaseGenerator(ascending, percentSorted) {}

    SorTable<T> * generateTable(int size);
    T getRandom();
};

template<>
class TableGenerator<int>: protected BaseGenerator {
    std::uniform_int_distribution<> distrib;
public:
    SorTable<int> * generateTable(int size) {
        distrib = std::uniform_int_distribution<>(-size, size);
        SorTable<int> *generated = new SorTable<int>(size);
        for (int i = 0; i < size; i++) {
            generated->add(getRandom());
        }
        return generated;
    }

    int getRandom() {
        return distrib(gen);
    }
};

template<>
class TableGenerator<char>: protected BaseGenerator {
    std::uniform_int_distribution<> distrib;
public:
    SorTable<char> * generateTable(int size) {
        distrib = std::uniform_int_distribution<>(0, 255);
        SorTable<char> *generated = new SorTable<char>(size);
        for (int i = 0; i < size; i++) {
            generated->add(getRandom());
        }
        return generated;
    }

    char getRandom() {
        return distrib(gen);
    }
};

template<>
class TableGenerator<double>: protected BaseGenerator {
    std::uniform_real_distribution<> distrib;
public:
    SorTable<double> * generateTable(int size) {
        distrib = std::uniform_real_distribution<>(-1.0*size, 1.0*size);
        SorTable<double> *generated = new SorTable<double>(size);
        for (int i = 0; i < size; i++) {
            generated->add(getRandom());
        }
        return generated;
    }

    double getRandom() {
        return distrib(gen);
    }
};

template<>
class TableGenerator<float>: protected BaseGenerator {
    std::uniform_real_distribution<> distrib;
public:
    SorTable<float> * generateTable(int size) {
        distrib = std::uniform_real_distribution<>(-1.0f*size, 1.0f*size);
        SorTable<float> *generated = new SorTable<float>(size);
        for (int i = 0; i < size; i++) {
            generated->add(getRandom());
        }
        return generated;
    }

    float getRandom() {
        return distrib(gen);
    }
};


/*
template<typename T>
inline T TableGenerator<char>::getRandom() {
return (char)(rand()%256);
}

template<typename T>
inline float TableGenerator<float>::getRandom() {
return (float)rand();
}

template<typename T>
inline double TableGenerator<double>::getRandom() {
return (double)rand();
}
*/
#endif //TABLEGENERATOR_H
