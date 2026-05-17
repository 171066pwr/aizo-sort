#include "SorTable.h"

#include <iostream>
#include <sstream>

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
SorTable<T> * SorTable<T>::clone() {
    return new SorTable(size, array);
}

template<typename T>
string SorTable<T>::getType() const {
    return typeid(T).name();
}

template<typename T>
string SorTable<T>::toString() const {
    std::stringstream ss;
    for (int i = 0; i < size; i++) {
        ss << array[i] << "\t";
    }
    return ss.str();
}

template<typename T>
void SorTable<T>::print() const {
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << "\t";
    }
    std::cout << std::endl;
}

template<typename T>
bool SorTable<T>::equals(const SorTable<T> *sort) const {
    bool result = true;
    if (size != sort->size) result &= false;
    else {
        for (int i = 0; i < size; i++) {
            if (array[i] != sort->array[i]) {
                result &= false;
                break;
            }
        }
    }
    return result;
}

template<typename T>
void SorTable<T>::copy(T *tab) const {
    for(int i = 0; i < this->size; i++) {
        array[i] = tab[i];
    }
}

template class SorTable<int>;
template class SorTable<char>;
template class SorTable<float>;
template class SorTable<double>;
