#ifndef BASEGENERATOR_H
#define BASEGENERATOR_H
#include <random>


class BaseGenerator {
protected:
    static std::random_device rd;
    static std::mt19937 gen;
    int percentSorted;
    bool ascending;
    //seeding the marsenne twister engine

    BaseGenerator(bool ascending = true, int percentSorted = 0): ascending(ascending), percentSorted(percentSorted) {}
};


#endif //BASEGENERATOR_H
