#ifndef SORTABLEIO_H
#define SORTABLEIO_H
#include <string>
#include <sstream>
#include <iostream>
#include "../model/SorTable.h"
#include "../model/DataType.h"
#include "BasicIO.h"
#include "InvalidFileException.h"

using namespace std;

class SorTableIO {
public:
    DataType parseType(string filename) {
        try{
            DataType type;
            BasicIO io(filename);
            string line = io.readLine();
            char c = line[0];
            switch (c) {
                case 'i': type = INT; break;
                case 'c': type = CHAR; break;
                case 'f': type = FLOAT; break;
                case 'd': type = DOUBLE; break;
                default: {
                    if(c >= '0' && c <= '9') {
                        type = INT; break;           //type not present - default INT
                    }
                    type = UNSUPPORTED;
                }
            }
            return type;
        }  catch(...) {
            return UNSUPPORTED;
        }
    }

    template<typename T>
    void saveToFile(string filename, SorTable<T> sortable) {
        BasicIO io(filename, true);
        io.writeLine(toString(sortable));
    }

    template<typename T>
    SorTable<T> readFromFile(string filename) {
        BasicIO io(filename);
        string line = io.readLine();
        char c = line[0];
        if(c < '0' || c > '9') {
            line = io.readLine();
        }
        int size = stoi(line);
        SorTable<T> sortable(size);
        T value;
        for(int i = 0; i < size; i++) {
            io.istream >> value;
            sortable.add(value);
            if(std::cin.fail() || std::cin.bad())
                throw InvalidFileException(filename);
        }
        return sortable;
    }

    template<typename T>
    string toString(SorTable<T> sortable) {
        stringstream ss;
        ss << sortable.getType() << endl;
        ss << sortable.currentSize;
        for(int i = 0; i < sortable.currentSize; i++) {
            ss << endl << sortable.array[i];
        }
        return ss.str();
    }
};

#endif //SORTABLEIO_H
