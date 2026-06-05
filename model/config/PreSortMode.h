#ifndef PRESORTCONFIG_H
#define PRESORTCONFIG_H

#include "Printable.h"
#include "../../io/Serializable.h"


struct PreSortMode: public virtual Serializable, public virtual Printable {
    const bool ascending;
    const int percentage;

    PreSortMode(const bool ascending = true, const int percentage = 0): ascending(ascending), percentage(percentage%101) {}

    string toString() {
        string result = "Pre-sort mode: ";
        if(percentage <= 0) {
            result += "not pre-sorted";
        } else {
            result += ascending ? "ascending, " : "descending, ";
            result += to_string(percentage) + "% pre-sorted";
        }
        return result;
    }

    virtual string toString() const override {
        string result = "Pre-sort mode: ";
        if(percentage <= 0) {
            result += "not pre-sorted";
        } else {
            result += ascending ? "ascending, " : "descending, ";
            result += to_string(percentage) + "% pre-sorted";
        }
        return result;
    }

    virtual string serialize() const override {
        string result = "PRE_SORT:";
        result += (ascending ? "asc" : "desc");
        result += "," + to_string(percentage);
        return result;
    }
};


#endif //PRESORTCONFIG_H
