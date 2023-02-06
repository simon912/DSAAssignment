#pragma once
#include<string>
#include<iostream>
#include"Dictionary.h"

using namespace std;


typedef string ItemType;

template <typename ItemType>
class List
{
private:
	struct Node
	{
		ItemType item;	// data item
		Node* next;	// pointer pointing to next item
	};

	Node* firstNode;	// point to the first item
	int  size;			// number of items in the list

public:
	List();			// constructor

	~List();		// destructor

	// add an item to the back of the list (append)
	// pre : size < MAX_SIZE
	// post: item is added to the back of the list
	//       size of list is increased by 1
	bool add(ItemType item);

	// add an item at a specified position in the list (insert)
	// pre : 0 <= index <= size
	// post: item is added to the specified position in the list
	//       items after the position are shifted back by 1 position
	//       size of list is increased by 1
	bool add(int index, ItemType item);

	// remove an item at a specified position in the list
	// pre : 0 <= index < size
	// post: item is removed the specified position in the list
	//       items after the position are shifted forward by 1 position
	//       size of list is decreased by 1
	void remove(int index);

	// get an item at a specified position of the list (retrieve)
	// pre : 0 <= index < size
	// post: none
	// return the item in the specified index of the list
	ItemType get(int index);

	// check if the list is empty
	// pre : none
	// post: none
	// return true if the list is empty; otherwise returns false
	bool isEmpty();

	// check the size of the list
	// pre : none
	// post: none
	// return the number of items in the list
	int getLength();

	//------------------- Other useful functions -----------------

    // sticky post or topic
    void shifttoFirst(int index);
	// display the list of topics
	void printTopic();
	ItemType getLast();
	// void replace(int index, ItemType item);
	// int search(ItemType item);
};

// ------------------------------------------- Implementation of List class -------------------------------------------
using namespace std;

template <typename ItemType>
List<ItemType>::List() {}

template <typename ItemType>
List<ItemType>::~List() {}

template <typename ItemType>
bool List<ItemType>::add(ItemType item) {
    Node* newNode = new Node;
    newNode->item = item;
    newNode->next = NULL;

    if (size == 0)
    {
        firstNode = newNode;
    }
    else
    {
        Node* current = firstNode;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    size++;
    return true;
    return add(size, item);
}

template <typename ItemType>
bool List<ItemType>::add(int index, ItemType item) {
    if (index < size && index >= 0) {
        Node* newNode = new Node;
        newNode->item = item;
        newNode->next = NULL;
        if (index == 0 && size == 0)
        {
            newNode->next = firstNode;
            firstNode = newNode;
        }
        else
        {
            Node* current = firstNode;
            for (int i = 0; i < index - 1; i++) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        size++;
        return true;
    }
    else {
        return false;
    }
}

template <typename ItemType>
void List<ItemType>::remove(int index) {
    if (index < size && index >= 0) {
        Node* current = firstNode;
        if (index == 0) {
            firstNode = current->next;
        }
        else {
            for (int i = 0; i < index - 1; i++) {
                current = current->next;
            }
            current->next = current->next->next;
        }
        size--;
    }
}
template <typename ItemType>
ItemType List<ItemType>::get(int index) {
    if (index < size && index >= 0) {
        Node* current = firstNode;
        for (int i = 0; i <= index - 1; i++) {
                if (current->next != NULL) {
                    current = current->next;
                }
            }
            return current->item;
        }
    return ItemType();
    }

// Put the item in the first index of the linked list
template <typename ItemType>
void List<ItemType>::shifttoFirst(int index) {
    if (index == 0) {
        return;
    }
    Node* previous = firstNode;
    Node* current = firstNode->next;
    for (int i = 1; i < index; i++) {
        if (current->next == NULL) {
            std::cout << "Index out of range." << std::endl;
            return;
        }
        previous = current;
        current = current->next;
    }
    previous->next = current->next;
    current->next = firstNode;
    firstNode = current;

}

// Display list of Topics
template <typename ItemType>
void List<ItemType>::printTopic() {
    Node* topic = firstNode;
    if (size != NULL)
    {
        cout << "===================================================================\n";
        for (int i = 0; i < size; i++) {
            cout << "[" << i << "] " << topic->item << endl;
            topic = topic->next;
            cout << "===================================================================\n";
        }
        
    }
    else
    {
        cout << "There is no topic\n";
    }
    
}

template <typename ItemType>
int List<ItemType>::getLength() {
    return size;
}

/*
Node *current = firstNode;
for (int i=0; i<index-1; i++){
current = current -> next;
}
Node *delNode = current->next;
current -> next = current -> next -> next;
delNode > next = NULL;
delete delNode;

*/
