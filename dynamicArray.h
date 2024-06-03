#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <iostream>
using namespace std;

template<class T> class DynamicArray{
    T* array;
    int currentMaxNumElements;
    int currentNumElementsStored;

    void resize(const int);

    public:
        DynamicArray();
        DynamicArray(T*, int, int);
        DynamicArray(const DynamicArray<T>& rhs);
        ~DynamicArray();

        DynamicArray<T>& operator=(const DynamicArray<T>&);

        int getCurrentNumElementsStored() const;
        int getCurrentMaxNumElements() const;

        void addElementToEndOfArr(const T&);
        T getElementAtIndex(const int) const;
        void replaceElementAtIndex(int, T);
        void removeElementAtIndex(int);
        void clearArray();
        friend ofstream& operator<<(ofstream&, DynamicArray<T>);
};

#include "dynamicArray.cpp"
#endif