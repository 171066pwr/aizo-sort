#ifndef PRESORTCONFIG_H
#define PRESORTCONFIG_H

#include "../../io/Printable.h"
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

    static PreSortMode deserialize(const string &line) {
        if(line.empty())
            return PreSortMode();
        string s;
        stringstream ss(line);
        std::getline(ss, s, ',');
        bool asc = (s.empty() || s[0] != '0');
        s.clear();
        std::getline(ss, s, ',');
        int percentage = s.empty() ? 0 : std::stoi(s);
        return PreSortMode(asc, percentage);
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
