#ifndef SORTERCONFIG_H
#define SORTERCONFIG_H

struct SorterConfig {
    int type;
    int variant;

    SorterConfig(int type, int variant = 0): type(type), variant(variant) {}

    string toString() {
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
};


#endif //SORTERCONFIG_H
