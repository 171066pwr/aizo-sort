#ifndef DATATYPECONFIG_H
#define DATATYPECONFIG_H

#include <string>

#include "../../io/Printable.h"
#include "../../io/Serializable.h"


enum DataType {
    INT,
    CHAR,
    FLOAT,
    DOUBLE,
    UNSUPPORTED
};

struct DataTypeConfig: public virtual Serializable, public virtual Printable {
    DataType dataType;

    DataTypeConfig(DataType dataType): dataType(dataType) {}
    DataTypeConfig(const string& dataType): dataType(deserialize(dataType)) {}

    static DataType deserialize(const string &s) {
        if(s == "char") return CHAR;
        if(s == "float") return FLOAT;
        if(s == "double") return DOUBLE;
        if(s == "int") return INT;
        return UNSUPPORTED;
    }

    virtual string toString() const override {
        switch (dataType) {
            case CHAR: return "char";
            case FLOAT: return "float";
            case DOUBLE: return "double";
            case INT: return "int";
            default: return "unsupported";
        }
    }

    virtual string serialize() const override {
        return "DATA_TYPE:" + toString();
    }
};


#endif //DATATYPECONFIG_H
