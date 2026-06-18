#ifndef SORTABLEIO_H
#define SORTABLEIO_H
#include <string>
#include <sstream>
#include <iostream>
#include "../model/SorTable.h"
#include "../model/config/DataTypeConfig.h"
#include "BasicIO.h"
#include "InvalidFileException.h"

struct SorTableIO {
    static DataType parseType(const string &filename) {
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
                    if(c == '-' || (c >= '0' && c <= '9')) {
                        type = INT; break;           //type not present - default INT
                    }
                    throw InvalidFileException(filename);
                }
            }
            return type;
        }  catch(...) {
            throw InvalidFileException(filename);
        }
    }

    static int parseSize(const string &filename) {
        try{
            DataType type;
            BasicIO io(filename);
            string line = io.readLine();
            char c = line[0];
            if(c < '1' || c > '9')
                line = io.readLine();
            return std::stoi(line);
        }  catch(...) {
            throw InvalidFileException(filename);
        }
    }

    template<typename T>
    static void saveToFile(const string& filename, SorTable<T> sortable) {
        BasicIO io(filename, true);
        io.writeLine(sortable.serialize());
    }

    template<typename T>
    static SorTable<T> * readFromFile(const string& filename) {
        try {
            BasicIO io(filename);
            string line = io.readLine();
            char c = line[0];
            if(c != '-' && (c < '0' || c > '9')) {
                line = io.readLine();
            }
            int size = stoi(line);
            auto sortable = new SorTable<T>(size);
            T value;
            for(int i = 0; i < size; i++) {
                io.istream >> value;
                sortable->add(value);
                if(std::cin.fail() || std::cin.bad())
                    throw InvalidFileException(filename);
            }
            return sortable;
        } catch(...) {
            throw InvalidFileException(filename);
        }
    }
};

#endif //SORTABLEIO_H
