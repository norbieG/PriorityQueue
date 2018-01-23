#include "ArrayPriorityQueue.h"

ArrayPriorityQueue::ArrayPriorityQueue() {

    capacity = INITIAL_CAPACITY;
    array = new PQEntry[capacity];
    count = 0;

}

ArrayPriorityQueue::~ArrayPriorityQueue() {
    delete[] array;
}


bool ArrayPriorityQueue::existsInQueue (string value) {
    for (int i = 0; i < count; i++) {
        if (array[i].value == value) {
            return true;
        }
    }
    return false;
}

void ArrayPriorityQueue::changePriority(string value, int newPriority) {

    if (!existsInQueue(value)) throw("Attempting to change priority of non existing value");

    bool foundLowerPriority = false;

    for (int i = 0; i < count; i++) {
        if (array[i].value == value) {
            if (array[i].priority > newPriority) {
                array[i].priority = newPriority;
                foundLowerPriority = true;
                break;
            }
        }
    }
    if (!foundLowerPriority) throw("Attempting to change priority of a lower value");

}

void ArrayPriorityQueue::clear() {
    capacity = INITIAL_CAPACITY;
    count = 0;

}

void ArrayPriorityQueue::remove(int index) {

    for (int i = index; i < count; i++) {
        array[i] = array[i+1];
    }

    count--;

}

string ArrayPriorityQueue::dequeue() {

    if (isEmpty()) throw("Attempting to deque from an empty queue");


    int index = 0;
    int priorityMax = array[0].priority;
    string valueMax = array[0].value;

    for (int i = 1; i < count; i++) {

        if (array[i].priority < priorityMax) {
            valueMax = array[i].value;
            priorityMax = array[i].priority;
            index = i;
        } else if (array[i].priority == priorityMax) {
            if (array[i].value < valueMax) {
                priorityMax = array[i].priority;
                valueMax = array[i].value;
                index = i;
            }

        } else {
            continue;
        }
    }

    remove(index);

    return valueMax;
}

void ArrayPriorityQueue::enqueue(string value, int priority) {

    PQEntry newEntry(value,priority);

    if (count == capacity) {
        expandCapacity();
    }

    array[count] = newEntry;
    count++;
}

bool ArrayPriorityQueue::isEmpty() const {
    return count == 0;
}

string ArrayPriorityQueue::peek() const {

    if (isEmpty()) throw("Attempting to peek at an empty stack");

    int priorityMax = array[0].priority;
    string valueMax = array[0].value;

    for (int i = 1; i < count; i++) {

        if (array[i].priority < priorityMax) {
            valueMax = array[i].value;
            priorityMax = array[i].priority;
        } else if (array[i].priority == priorityMax) {
            if (array[i].value < valueMax) {
                priorityMax = array[i].priority;
                valueMax = array[i].value;

            }

        } else {
            continue;
        }
    }
    return valueMax;

}

int ArrayPriorityQueue::peekPriority() const {

    if (isEmpty()) throw("Attempting to peek at an empty stack");

    int priorityMax = array[0].priority;
    string valueMax = array[0].value;

    for (int i = 1; i < count; i++) {

        if (array[i].priority < priorityMax) {
            valueMax = array[i].value;
            priorityMax = array[i].priority;
        } else if (array[i].priority == priorityMax) {
            if (array[i].value < valueMax) {
                priorityMax = array[i].priority;
                valueMax = array[i].value;
            }

        } else {
            continue;
        }
    }

    return priorityMax;
}

int ArrayPriorityQueue::size() const {
    return count;
}

PQEntry ArrayPriorityQueue::get(int index) const {
    return array[index];
}


ostream& operator<<(ostream& out, const ArrayPriorityQueue& queue) {
    out << "{";
    for (int i = 0; i < queue.size(); i++) {
        PQEntry tmp = queue.get(i);
        out << tmp.value <<" : "<< tmp.priority;
        if (i == queue.size()-1) {
            continue;
        } else {
            out << ", ";
        }
    }
    out << "}";
    return out;
}

void ArrayPriorityQueue::expandCapacity() {

    PQEntry *oldArray = array;
    capacity *=2;
    array = new PQEntry[capacity];

    for (int i = 0; i < count; i++) {
        array[i] = oldArray[i];
    }

    delete [] oldArray;

}
