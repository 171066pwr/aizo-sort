#ifndef TABLEGENERATOR_H
#define TABLEGENERATOR_H


#include <random>

#include "BaseGenerator.h"
#include "../config/GlobalConfig.h"
#include "../SorTable.h"

using namespace Globals;

template <typename T>
class TableGenerator: protected BaseGenerator {
public:
    using BaseGenerator::BaseGenerator;

    SorTable<T> * generateTable(int size);
    T getRandom();
};

template<>
class TableGenerator<int>: protected BaseGenerator {
    std::uniform_int_distribution<> distribution;
public:
    using BaseGenerator::BaseGenerator;

    SorTable<int> * generateTable(int size) {
        distribution = std::uniform_int_distribution<>(-size, size);
        SorTable<int> *generated = new SorTable<int>(size);
        for (int i = 0; i < size; i++) {
            generated->add(getRandom());
        }
        return preSort(generated);
    }

    int getRandom() {
        return distribution(MERSENNE_GENERATOR);
    }
};

template<>
class TableGenerator<char>: protected BaseGenerator {
    std::uniform_int_distribution<> distribution;
public:
    using BaseGenerator::BaseGenerator;

    SorTable<char> * generateTable(int size) {
        distribution = std::uniform_int_distribution<>(33, 254); //mostly visible ASCII characters, except for 127 DEL
        SorTable<char> *generated = new SorTable<char>(size);
        for (int i = 0; i < size; i++) {
            generated->add(getRandom());
        }
        return preSort(generated);
    }

    char getRandom() {
        return distribution(MERSENNE_GENERATOR);
    }
};

template<>
class TableGenerator<double>: protected BaseGenerator {
    std::uniform_real_distribution<> distribution;
public:
    using BaseGenerator::BaseGenerator;

    SorTable<double> * generateTable(int size) {
        distribution = std::uniform_real_distribution<>(-1.0*size, 1.0*size);
        SorTable<double> *generated = new SorTable<double>(size);
        for (int i = 0; i < size; i++) {
            generated->add(getRandom());
        }
        return preSort(generated);
    }

    double getRandom() {
        return distribution(MERSENNE_GENERATOR);
    }
};

template<>
class TableGenerator<float>: protected BaseGenerator {
    std::uniform_real_distribution<> distribution;
public:
    using BaseGenerator::BaseGenerator;

    SorTable<float> * generateTable(int size) {
        distribution = std::uniform_real_distribution<>(-1.0f*size, 1.0f*size);
        SorTable<float> *generated = new SorTable<float>(size);
        for (int i = 0; i < size; i++) {
            generated->add(getRandom());
        }
        return preSort(generated);
    }

    float getRandom() {
        return distribution(MERSENNE_GENERATOR);
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
