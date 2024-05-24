#ifndef STACK_STACK_H
#define STACK_STACK_H

#include "DLList.h"

template<typename T>
class Stack {
public:

    Stack() {}


    ~Stack() {}




    bool empty() const {

    }


    size_t size() const {

    }


    void push(const T& value) {

    }


    void pop() {

    }


    T& top() {

    }


    const T& top() const {

    }


    void clear() {

    }

private:
    DLList<T> list;
};

#endif //STACK_STACK_H