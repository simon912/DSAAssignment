// Stack.h - Specification of Stack ADT (Pointer-based)
#pragma once
#include<string>
#include<iostream>

using namespace std;

typedef string StackType;

class Stack
{
private:
    struct Node
    {
        StackType item;    // item
        Node* next;    // pointer pointing to next item
    };

    Node* topNode;    // point to the first item

public:
    // constructor
    Stack();

    ~Stack();

    // push item on top of the stack
    bool push(StackType item);

    // pop item from top of stack
    bool pop();

    // retrieve and pop item from top of stack
    bool pop(StackType& item);


    // retrieve item from top of stack
    void getTop(StackType& item);

    // check if the stack is empty
    bool isEmpty();

    void displayContents();
};
