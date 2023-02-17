#pragma once
#include <stdlib.h>
#include <list>
#include "domain.h"
#include<assert.h>
using namespace std;




template <typename T>
class Comparator {
public:
    virtual bool operator()(const T& x, const T& y) = 0;
};

template <typename T>
class ComparatorAscendingByPrice : public Comparator<T> {
public:
    bool operator()(const T& x, const T& y) override;

};

template <typename T>
bool ComparatorAscendingByPrice<T>::operator()(const T& x, const T& y) {
    return x.priceGetter() < y.priceGetter();
}


template <typename T>
class ComparatorDescendingByQuantity : public Comparator<T> {
public:
    bool operator()(const T& x, const T& y) override;
};

template <typename T>
bool ComparatorDescendingByQuantity<T>::operator()(const T& x, const T& y) {
    return x.quantityGetter() > y.quantityGetter();
}