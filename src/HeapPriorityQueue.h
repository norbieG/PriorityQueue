// This is a .h file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#ifndef _heappriorityqueue_h
#define _heappriorityqueue_h

#include <iostream>
#include <string>
#include "PQEntry.h"
using namespace std;

/*
 * For documentation of each member, see VectorPriorityQueue.h.
 */
class HeapPriorityQueue {
public:
    HeapPriorityQueue();
    ~HeapPriorityQueue();
    void changePriority(string value, int newPriority);
    void clear();
    string dequeue();
    void enqueue(string value, int priority);
    bool isEmpty() const;
    string peek() const;
    int peekPriority() const;
    int size() const;
    friend ostream& operator <<(ostream& out, const HeapPriorityQueue& queue);
    PQEntry get(int index) const;
    void bubbleUp(int index);
    void bubbleDown(int index);

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
