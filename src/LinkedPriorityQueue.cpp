#include "LinkedPriorityQueue.h"

LinkedPriorityQueue::LinkedPriorityQueue() {
    front = NULL;
}

LinkedPriorityQueue::~LinkedPriorityQueue() {
    if (!isEmpty()) {
        clear();
    }
}

bool LinkedPriorityQueue::existsInQueue (string value) {

    ListNode* current = front;

    while (current!=NULL) {
        if (current->value == value) {
            return true;
        }
        current = current->next;
    }

    return false;
}

void LinkedPriorityQueue::changePriority(string value, int newPriority) {

    if (!existsInQueue(value)) throw("Attempting to change priority of non existing value");

    bool foundLowerPriority = false;

    ListNode* current = front;

    while (current!=NULL) {
        if (current->value == value) {
            if (current->priority > newPriority) {
                current->priority = newPriority;
                foundLowerPriority = true;
                break;
            }
        }
        current = current->next;
    }

    if (!foundLowerPriority) throw("Attempting to change priority of a lower value");

}

void LinkedPriorityQueue::clear() {

    while (!isEmpty()) {
        dequeue();
    }

}

string LinkedPriorityQueue::dequeue() {

    if (!isEmpty()) {

        string node = front->value;
        ListNode* trash = front; // keep a pointer to the node that will be deleted
        front = front->next;
        delete trash;

        return node;

    } else {

        throw "trying to deque from empty list";
    }
}

void LinkedPriorityQueue::enqueue(string value, int priority) {

    if (isEmpty()) {
        front = new ListNode(value,priority,NULL);

    } else if (front->priority > priority) {
        ListNode* oldFront = front;
        front = new ListNode(value,priority,oldFront);

    } else if (front->priority == priority) {

        if (front->value > value) {
            ListNode* oldFront = front;
            front = new ListNode(value,priority,oldFront);

        } else {

            ListNode* current = front;

            while (current->next->value <= value && current->next->priority == priority) {
                cout << current->value <<" : "<< current->priority << endl;
                current = current->next;
            }

            ListNode* newNode = new ListNode(value,priority,current->next);
            current->next = newNode;
        }

    } else if (size() == 1) {

        front->next = new ListNode(value,priority,NULL);

    } else {

        ListNode* current = front;

        while (current->next->priority < priority) {

            current = current->next;

            if (current->next==NULL) { // end of list
                break;
            }
        }

        if (current->next==NULL) {

           current->next = new ListNode(value,priority,NULL);

        } else if (current->next->priority == priority) {

            if (current->next->value > value) {
                ListNode* newNode = new ListNode(value,priority,current->next);
                current->next = newNode;

            } else {

                while (current->next->value < value && current->next->priority == priority) {

                    current = current->next;
                    if (current->next==NULL) { // end of list
                        break;
                    }
                }
                ListNode* newNode = new ListNode(value,priority,current->next);
                current->next = newNode;
            }

        } else {

            ListNode* newNode = new ListNode(value,priority,current->next);
            current->next = newNode;
        }
    }
}

bool LinkedPriorityQueue::isEmpty() const {
    return front == NULL;
}

string LinkedPriorityQueue::peek() const {
    return front->value;
}

int LinkedPriorityQueue::peekPriority() const {
    return front->priority;
}

int LinkedPriorityQueue::size() const {
    int counter = 0;

    ListNode* current = front;

    while (current!=NULL) {
        counter+=1;
        current = current->next;
    }

    return counter;
}

ostream& operator<<(ostream& out, const LinkedPriorityQueue& queue) {
    out << "{";
        ListNode* current = queue.front;
        while (current!=NULL) {
            out << current->value <<" : "<< current->priority;
            current = current->next;
            if (current!=NULL) {
                out << ", ";
            }
        }
        out << "}";
    return out;
}
