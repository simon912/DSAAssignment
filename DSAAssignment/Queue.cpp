#include<string>
#include<iostream>
#include "Queue.h"
using namespace std;

Queue::Queue() {
    frontNode = nullptr;
    backNode = nullptr;
}

Queue::~Queue() {

}

bool Queue::enqueue(ItemType item) {
    Node* temp = new Node;
    temp->item = item;
    temp->next = nullptr;

    if (isEmpty()) {
        frontNode = temp;
    }
    else {
        backNode->next = temp;
    }

    backNode = temp;

    return true;
}

bool Queue::dequeue() {
    if (frontNode == backNode) {
        frontNode = nullptr;
        backNode = nullptr;
    }
    else {
        Node* temp = frontNode;
        frontNode = frontNode->next;
        temp->next = nullptr;
    }

    return true;
}

bool Queue::dequeue(ItemType& item) {
    if (frontNode == backNode) {
        item = frontNode->item;
        frontNode = nullptr;
        backNode = nullptr;
    }
    else {
        Node* temp = frontNode;
        frontNode = frontNode->next;
        temp->next = nullptr;

        item = temp->item;
    }

    return true;
}

void Queue::getFront(ItemType& item) {
    if (!isEmpty()) {
        item = frontNode->item;
    }
}

bool Queue::isEmpty() {
    return (frontNode == nullptr);
}

void Queue::displayItems() {
    Queue tempQueue = Queue();

    while (!isEmpty()) {
        ItemType firstItem;
        dequeue(firstItem);
        tempQueue.enqueue(firstItem);

        //        cout << firstItem << endl;
    }

    while (!tempQueue.isEmpty()) {
        ItemType firstItem;
        tempQueue.dequeue(firstItem);
        enqueue(firstItem);
    }

}
