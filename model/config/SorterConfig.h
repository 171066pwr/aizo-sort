#ifndef SORTERCONFIG_H
#define SORTERCONFIG_H

#include "Printable.h"
#include "../../io/Serializable.h"


struct SorterConfig: public virtual Serializable, public virtual Printable {
    int type;
    int variant;

    SorterConfig(): type(0), variant(0) {}

    SorterConfig(int type, int variant = 0): type(type), variant(variant) {}

    bool operator<(const SorterConfig& other) const {
        if(type != other.type) return type < other.type;
        if(variant != other.variant) return variant < other.variant;
        return this < &other;
    }

    virtual string toString() const override {
        string result;
        switch (type) {
            case 0: result += "HeapSort"; break;
            case 1: result += "InsertionSort"; break;
            case 2: result += "QuickSort";
                switch (variant) {
                    case 1: result += " - Lowest pivot"; break;
                    case 2: result += " - Highest pivot"; break;
                    case 3: result += " - Center pivot"; break;
                    case 0:
                    default:
                        result += " - Random pivot"; break;
                }
            break;
            case 3: result += "ShellSort";
                switch (variant) {
                    case 1: result += " - Shell sequence"; break;
                    case 0:
                        default:
                            result += " - Knuth sequence"; break;
                }
            break;
            default: result += "unsupported";
        }
        return result;
    }

    virtual string serialize() const override {
        return "{" + to_string(type) + "," + to_string(variant) + "}";
    }
};


#endif //SORTERCONFIG_H
