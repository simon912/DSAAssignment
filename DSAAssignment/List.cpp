#include "List.h"
#include "Dictionary.h"

using namespace std;

List::List() {}
List::~List() {}

bool List::add(ItemType item) {
    Node *newNode = new Node;
    newNode->item = item;
    newNode->next = NULL;

    if (size == 0)
    {
        firstNode = newNode;
    }
    else
    {
        Node *current = firstNode;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    size++;
    return true;
    return add(size, item);
}

bool List::add(int index, ItemType item) {
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

void List::remove(int index) {
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

void List::printTopic() {
    Node* topic = firstNode;
    if (size != NULL)
    {
        cout << "-----------------" << endl;
        for (int i = 0; i < size; i++) {
            cout << "[" << i << "] " << topic->item << endl;
            topic = topic->next;
            cout << "-----------------" << endl;
        }
        cout << "Type the corresponding number to view a topic: ";
    }
    else
    {
        cout << "There is no topic\n";
    }
}

/*int List::getLength() {
    cout << "Length: " << size << endl;
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