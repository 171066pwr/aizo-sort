#include "SorTable.h"

#include <iostream>
#include <sstream>

template<typename T>
SorTable<T>::SorTable(int max_size, int current_size, T *tab): maxSize(max_size), currentSize(current_size), array(new T[max_size]) {
    copy(tab);
}

template<typename T>
SorTable<T>::SorTable(int max_size, T *tab): maxSize(max_size), currentSize(max_size), array(new T[max_size]) {
    copy(tab);
}

template<typename T>
SorTable<T>::SorTable(int max_size): maxSize(max_size), array(new T[max_size]) {
}

template<typename T>
SorTable<T>::SorTable(const SorTable & sort): maxSize(sort.maxSize), currentSize(sort.currentSize), array(new T[sort.maxSize]) {
    copy(sort.array);
}

template<typename T>
SorTable<T>::~SorTable() {
    delete[] array;
}

template<typename T>
SorTable<T> * SorTable<T>::clone() {
    return new SorTable(maxSize, currentSize, array);
}

template<typename T>
bool SorTable<T>::equals(const SorTable<T> *sort) const {
    bool result = true;
    if (currentSize != sort->currentSize) result &= false;
    else {
        for (int i = 0; i < currentSize; i++) {
            if (array[i] != sort->array[i]) {
                result &= false;
                break;
            }
        }
    }
    return result;
}

template<typename T>
void SorTable<T>::add(T value) {
    if(currentSize < maxSize) {}
    array[currentSize] = value;
    currentSize++;
}

template<typename T>
void SorTable<T>::reverseOrder() {
    T buffer;
    for (int i = 0, j = currentSize-1; i < j; i++, j--) {
        buffer = array[i];
        array[i] = array[j];
        array[j] = buffer;
    }
}

template<typename T>
string SorTable<T>::getType() const {
    return typeid(T).name();
}

template<typename T>
string SorTable<T>::toString() const {
    std::stringstream ss;
    for (int i = 0; i < currentSize; i++) {
        ss << array[i] << "\t";
    }
    return ss.str();
}

template<typename T>
void SorTable<T>::print() const {
    for (int i = 0; i < currentSize; i++) {
        std::cout << array[i] << "\t";
    }
    std::cout << std::endl;
}

template<typename T>
void SorTable<T>::copy(T *tab) const {
    for(int i = 0; i < this->currentSize; i++) {
        array[i] = tab[i];
    }
}

template class SorTable<int>;
template class SorTable<char>;
template class SorTable<float>;
template class SorTable<double>;
