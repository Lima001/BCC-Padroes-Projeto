#ifndef ITERATOR_H
#define ITERATOR_H

#include <limits>
#include <assert.h>

template <typename T>
class Iterator {
    public:
        virtual void first() = 0;
        virtual void last() = 0;
        virtual bool hasNext() = 0;
        virtual bool hasPrevious() = 0;
        virtual T next() = 0;
        virtual T previous() = 0;
        virtual int nextIndex() = 0;
        virtual int previousIndex() = 0; 
};

template <typename T>
class Iterable {
    public:
        virtual Iterator<T>* iterator() = 0;
};

#endif