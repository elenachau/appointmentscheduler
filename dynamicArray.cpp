#include "dynamicArray.h"

template <class T>
DynamicArray<T>::DynamicArray(){
    currentMaxNumElements = 3;
    currentNumElementsStored = 0;
    array = new T[currentMaxNumElements];
}

template <class T>
DynamicArray<T>::DynamicArray(T* arr, int num, int max){
    currentMaxNumElements = max;
    currentNumElementsStored = num;
    array = new T[max];
    for(int i = 0; i < num; i++){
        array[i] = arr[i];
    }
}

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& rhs){
    currentMaxNumElements = rhs.currentMaxNumElements;
    currentNumElementsStored = rhs.currentNumElementsStored;
    array = new T[rhs.currentMaxNumElements];

    for(int i = 0; i < currentMaxNumElements; i++){
        array[i] = rhs.array[i];
    }
}

template <class T>
void DynamicArray<T>::resize(const int newSize){
    T* temp = new T[newSize];

    for(int i = 0; i < currentMaxNumElements; i++){
        temp[i] = array[i];
    }

    delete[] array;
    currentMaxNumElements = newSize;
    array = temp;
}

template <class T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T> &rhs){
    currentNumElementsStored = rhs.currentNumElementsStored;
    currentMaxNumElements = rhs.currentMaxNumElements;
    T* temp = new T[currentMaxNumElements];

    for(int i = 0; i < currentNumElementsStored; i++){
        temp[i] = rhs.array[i];
    }

    if(array != nullptr){
        delete[] array;
    }
    array = temp;
    
    return *this;
}

template <class T>
int DynamicArray<T>::getCurrentNumElementsStored() const{
    return currentNumElementsStored;
}

template <class T>
int DynamicArray<T>::getCurrentMaxNumElements() const{
    return currentMaxNumElements;
}

template <class T>
void DynamicArray<T>::addElementToEndOfArr(const T& newItem){
    if(currentNumElementsStored == currentMaxNumElements){
        resize(currentMaxNumElements+2);
    }

    array[currentNumElementsStored] = newItem;
    currentNumElementsStored++;
}

template <class T>
T DynamicArray<T>::getElementAtIndex(const int i) const{
    return array[i];
}

template <class T>
void DynamicArray<T>::replaceElementAtIndex(int i, T newItem){
    array[i] = newItem;
}

template <class T>
void DynamicArray<T>::removeElementAtIndex(int i){
    for(int i = 0; i < currentNumElementsStored-1; i++){
        if(i>=ind){
            array[i] = array[i+1];
        }
    }
    currentNumElementsStored--;
}

template <class T>
void DynamicArray<T>::clearArray(){
    delete[] array;
    array = new T[1]; //initialize memory
    currentMaxNumElements = 1;
    currentNumElementsStored = 0;
}

template <class T>
DynamicArray<T>::~DynamicArray(){
    delete[] array;
}