/*
=============================================
|	Group 10							    |
|	Name of Member 1: Simon Kwek			|
|	Student ID of Member 1 : S10228098J		|
|	Name of Member 2 : Yee Jia Chen			|
|	Student ID of Member 2 : S10219344C		|
=============================================
*/
// Stack.h - Specification of Stack ADT (Pointer-based)
#pragma once
#include<string>
#include<iostream>
#include "Dictionary.h"
#include "Post.h"

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

    int length;

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

    void displayContents(Dictionary<Post>& posts);

    int getLength();
};
