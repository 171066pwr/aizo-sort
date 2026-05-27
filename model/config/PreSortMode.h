#ifndef PRESORTCONFIG_H
#define PRESORTCONFIG_H


struct PreSortMode {
    const bool ascending;
    const int percentage;

    PreSortMode(const bool ascending, const int percentage): ascending(ascending), percentage(percentage%101) {}
};


#endif //PRESORTCONFIG_H
