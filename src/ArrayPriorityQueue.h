#ifndef _arraypriorityqueue_h
#define _arraypriorityqueue_h

#include <iostream>
#include <string>
#include "PQEntry.h"
using namespace std;

// TODO: comment
class ArrayPriorityQueue {
public:
    ArrayPriorityQueue();
    ~ArrayPriorityQueue();
    void changePriority(string value, int newPriority);
    void clear();
    string dequeue();
    void enqueue(string value, int priority);
    bool isEmpty() const;
    string peek() const;
    int peekPriority() const;
    int size() const;
    PQEntry get(int index) const;
    friend ostream& operator <<(ostream& out, const ArrayPriorityQueue& queue);
    void remove(int index);
    bool existsInQueue (string value);

private:
    // TODO: add any other member functions/variables necessary

    // Private constants
    static const int INITIAL_CAPACITY = 10;
    // Instance variables
    PQEntry *array; //pointer to dynamic array of PQs
    int capacity; //allocated size of array
    int count; //current count of ints pushed

    //expand capacity prototype
    void expandCapacity();
};

#endif
