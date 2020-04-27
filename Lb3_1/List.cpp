//
// Created by Michael on 14.02.2020.
//

#ifndef S2LB1_2_LIST_CPP
#define S2LB1_2_LIST_CPP

#include <vector>
#include "NullPointErexception.h"
using namespace std;
template <typename T>class List {
private:
    vector<T> array;
    int length;
    int maxLength;
public:

    List(int maxSize) {
        array = new T[maxSize];
        maxLength = maxSize;
        length = 0;
    }

    List(List<T> const &listInt) {
        this->length = listInt.size();
        this->maxLength = listInt.size()*2;
        array = new T[maxLength];
        for (int i = 0; i < listInt.size(); ++i) {
            array[i] = listInt.get(i);
        }
    }

    List() {
//        int maxSize = 10;
//        array = new T[maxSize];
//        maxLength = maxSize;
        length = 0;
    }

    List(int size,T *arrayInt) {
        int maxSize = size * 2;
        array = new T[maxSize];
        maxLength = maxSize;
        length = 0;
        for (int i = 0; i < size; ++i) {
            add(arrayInt[i]);
        }
    }
    List(vector<T> arrayInt) {
        int maxSize = arrayInt.size() * 2;
        array = new T[maxSize];
        maxLength = maxSize;
        length = 0;
        for (int i = 0; i < arrayInt.size(); ++i) {
            add(arrayInt[i]);
        }
    }

    void add(T value) {
        if (length == maxLength) {
            maxLength *= 2;
            T *newArray = new T[maxLength];
            for (int i = 0; i < length; ++i) {
                newArray[i] = get(i);
            }
            array = newArray;
        }
        array[length] = value;
        length++;
    }

    const  T get(int i) const {
        if (i < length)
            return array[i];
        else
            throw NullPointErexception();
    }

    void update(int i, T value) {
        if (i < length)
            array[i] = value;
        else
            throw NullPointErexception();
    }

    int size() const {
        return length;
    }

    void clear() {
        delete[] array;
        length = 0;
    }

    void remove(int i){
        for (int j = i; j < size() - i; ++j) {
            array[j] = array[j++];
        }
    }

    T &operator[](int i) {
        if (i < length)
            return array[i];
        else
            throw NullPointErexception();
    }

};


#endif //S2LB1_2_LISTINT_CPP
