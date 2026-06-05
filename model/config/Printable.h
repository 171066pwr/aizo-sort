#ifndef PRINTABLE_H
#define PRINTABLE_H


struct Printable {
    virtual ~Printable() {}

    virtual std::string toString() const = 0;
};


#endif //PRINTABLE_H
