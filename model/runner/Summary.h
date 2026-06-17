#ifndef SUMMARY_H
#define SUMMARY_H

#include "../../io/Printable.h"
#include "../../io/Serializable.h"


struct Summary: public virtual Serializable, public virtual Printable  {
typedef long long T;
    T min;
    T max;
    T avg;
    T med;

    Summary(T minimum, T maximum, T average, T median): min(minimum), max(maximum), avg(average), med(median) {}

    virtual string toString() const override {
        string result = "avg: " + to_string(avg) + "\t";
        result += "med: " + to_string(med) + "\t";
        result += "min: " + to_string(min) + "\t";
        result += "max: " + to_string(max);
        return result;
    }

    virtual string serialize() const override {
        return  to_string(avg) + "," + to_string(med) + "," + to_string(min) + "," + to_string(max);
    }
};

#endif //SUMMARY_H
