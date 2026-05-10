#include "SorTable.h"

#include <array>
#include <iostream>

template<typename T>
SorTable<T>::SorTable(int max_size, T *tab): size(max_size), array(new T[max_size]) {
    copy(tab);
}

template<typename T>
SorTable<T>::SorTable(int max_size): size(max_size), array(new T[max_size]) {
}

template<typename T>
SorTable<T>::SorTable(const SorTable & sort): size(sort.size), array(new T[sort.size]) {
    copy(sort.array);
}

template<typename T>
SorTable<T>::~SorTable() {
    delete[] array;
}

template<typename T>
SorTable<T> SorTable<T>::clone() {
    return new SorTable(size, array);
}

template<typename T>
void SorTable<T>::print() const {
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << "\t";
    }
}

template<typename T>
void SorTable<T>::copy(T *tab) {
    for(int i = 0; i < this->size; i++) {
        array[i] = tab[i];
    }
}
