/*
=============================================
|	Group 10							    |
|	Name of Member 1: Simon Kwek			|
|	Student ID of Member 1 : S10228098J		|
|	Name of Member 2 : Yee Jia Chen			|
|	Student ID of Member 2 : S10219344C		|
=============================================
*/
// Queue.h - Specification of Queue ADT (Pointer-based)
#pragma once
#include<string>
#include<iostream>

using namespace std;

typedef string ItemType;

class Queue
{
private:
    struct Node
    {
        ItemType item;    // item
        Node* next;    // pointer pointing to next item
    };

    Node* frontNode;    // point to the first item
    Node* backNode;    // point to the first item

    int length;


public:
    // constructor
    Queue();

    ~Queue();

    // enqueue (add) item at the back of queue
    bool enqueue(ItemType item);

    // dequeue (remove) item from front of queue
    bool dequeue();

    // dequeue (remove) and retrieve item from front of queue
    bool dequeue(ItemType& item);

    // retrieve (get) item from front of queue
    void getFront(ItemType& item);

    // check if the queue is empty
    bool isEmpty();

    // display items in queue from front to back
    void displayItems();

    int getLength();
};
