#ifndef SORTABLE_H
#define SORTABLE_H
#include <string>

#include "Table.h"

using namespace std;

template <typename T>
class SorTable: Table {
public:
    typedef T baseType;
    T value;
    T * const array;
    const int maxSize;
    int currentSize = 0;


    SorTable(int max_size, int current_size, T * tab);
    SorTable(int max_size, T * tab);
    SorTable(int max_size);
    SorTable(const SorTable & sort);
    ~SorTable();
    SorTable * clone();

    bool equals(const SorTable * sort) const;
    void add(T value);
    void reverseOrder();
    string getType() const;
    string toString() const;
    void print() const;

    T const& operator [](std::size_t n) const
    {
        return array[n];
    }
    // similarly for non-const:
    T& operator [](std::size_t n) { return array[n]; }

private:
    void copy(T * tab) const ;
};

#endif //SORTABLE_H
