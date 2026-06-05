#ifndef BASEGENERATOR_H
#define BASEGENERATOR_H
#include <random>


class BaseGenerator {
protected:
    int percentSorted;
    bool ascending;
    //seeding the marsenne twister engine

public:
    BaseGenerator(bool ascending = true, int percentSorted = 0): ascending(ascending), percentSorted(percentSorted) {}
};


#endif //BASEGENERATOR_H
