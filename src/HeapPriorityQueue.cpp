#include "HeapPriorityQueue.h"
#include <limits.h>

HeapPriorityQueue::HeapPriorityQueue() {

    capacity = INITIAL_CAPACITY;
    array = new PQEntry[capacity];
    array[0] = PQEntry("<s>",0);
    count = 1;

}

HeapPriorityQueue::~HeapPriorityQueue() {
    delete[] array;

}

void HeapPriorityQueue::changePriority(string value, int newPriority) {

    bool existsInQueue = false;
    bool foundLowerPriority = false;
    int index;
    for (int i = 1; i < count; i++) {
        if (array[i].value == value) {
            existsInQueue = true;
            if (array[i].priority > newPriority) {
                array[i].priority = newPriority;
                foundLowerPriority = true;
                index = i;

                break;
            }
        }
    }
    if (!existsInQueue) {

        throw("Attempting to change priority of non existing value");
    } else  if (!foundLowerPriority){
        throw("Attempting to change priority of a lower value");

    } else {

        bubbleUp(index);
    }


}

void HeapPriorityQueue::clear() {
    capacity = INITIAL_CAPACITY;
    count = 1;
}

void HeapPriorityQueue::bubbleDown(int index) {
    int indexOfSmaller;

    if ((2*index) < count) {
        int left = 2*index;
        int right = 2*index+1;

        if (array[left].priority < array[right].priority) {
            indexOfSmaller = left;
        } else {
            indexOfSmaller = right;
        }

    } else if ((2*index) == count) {
        indexOfSmaller = 2*index;

    } else {

        return;
    }


    if (array[index].priority > array[indexOfSmaller].priority) {

        PQEntry tmp = array[indexOfSmaller];
        array[indexOfSmaller] = array[index];
        array[index] = tmp;

        bubbleDown(indexOfSmaller);

    }
}

string HeapPriorityQueue::dequeue() {

    string root = array[1].value;
    array[1] = array[count-1];
    count--;
    bubbleDown(1);

    return root;
}


void HeapPriorityQueue::bubbleUp(int index) {

    while ((index/2 > 0) && (array[index].priority < array[index/2].priority)) {
        PQEntry parent = array[index/2];
        array[index/2] = array[index];
        array[index] = parent;
        index/=2;
    }
}

void HeapPriorityQueue::enqueue(string value, int priority) {

    if (count == capacity) {
        expandCapacity();
    }

    array[count] = PQEntry(value, priority);
    bubbleUp(count);
    count++;

}

bool HeapPriorityQueue::isEmpty() const {
    return count == 1;
}

string HeapPriorityQueue::peek() const {
    if (isEmpty()) throw("Attempting to peek at an empty stack");
    return array[1].value;

}

int HeapPriorityQueue::peekPriority() const {
    if (isEmpty()) throw("Attempting to peek at an empty stack");
    return array[1].priority;
}

int HeapPriorityQueue::size() const {   
    return count-1;
}

PQEntry HeapPriorityQueue::get(int index) const {
    return array[index];
}

ostream& operator<<(ostream& out, const HeapPriorityQueue& queue) {

    out << "{";
    for (int i = 1; i < queue.count; i++) {
        PQEntry tmp = queue.get(i);
        out << tmp.value <<" : "<< tmp.priority;
        if (i == queue.count-1) {
            continue;
        } else {
            out << ", ";
        }
    }
    out << "}";
    return out;

}

void HeapPriorityQueue::expandCapacity() {

    PQEntry *oldArray = array;
    capacity *=2;
    array = new PQEntry[capacity];

    for (int i = 0; i < count; i++) {
        array[i] = oldArray[i];
    }

    delete[] oldArray;

}
