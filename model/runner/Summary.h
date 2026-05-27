#ifndef SUMMARY_H
#define SUMMARY_H

struct Summary {
typedef long long T;
    T min;
    T max;
    T avg;
    T med;

    Summary(T minimum, T maximum, T average, T median): min(minimum), max(maximum), avg(average), med(median) {}
};

#endif //SUMMARY_H
