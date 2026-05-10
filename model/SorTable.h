#ifndef SORTABLE_H
#define SORTABLE_H

using namespace std;

template <typename T> class SorTable {
public:
    T * const array;
    const int size;

    SorTable(int max_size, T * tab);
    SorTable(int max_size);
    SorTable(const SorTable & sort);
    ~SorTable();
    SorTable<T> clone();

    void print() const;

private:
    void copy(T * tab);
};



#endif //SORTABLE_H
