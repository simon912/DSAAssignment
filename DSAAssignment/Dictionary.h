#pragma once
#include<string>
#include<iostream>
#include <cmath>

using namespace std;

const int MAX_SIZE = 101;
typedef string KeyType;
typedef string ItemType;

template<typename ItemType>
class Dictionary
{
private:
	struct Node
	{
		KeyType	 key;   // search key
		ItemType item;	// data item
		Node* next;	// pointer pointing to next item with same search key
	};

	Node* items[MAX_SIZE];
	int  size;			// number of items in the Dictionary

public:

	// constructor
	Dictionary();

	// destructor
	~Dictionary();

	int hash(KeyType key);

	// add a new item with the specified key to the Dictionary
	// pre : none
	// post: new item is added to the Dictionary
	//       size of Dictionary is increased by 1
	bool add(KeyType newKey, ItemType newItem);

	// remove an item with the specified key in the Dictionary
	// pre : key must exist in the Dictionary
	// post: item is removed from the Dictionary
	//       size of Dictionary is decreased by 1
	//void remove(KeyType key);

	// get the key itself (retrieve)
	// pre : key must exist in the Dictionary
	// post: none
	// return the specific key from the Dictionary
	ItemType getKey(KeyType key);

	// get an item with the specified key in the Dictionary (retrieve)
	// pre : key must exist in the Dictionary
	// post: none
	// return the item with the specified key from the Dictionary
	ItemType get(KeyType key);

	// check if the Dictionary is empty
	// pre : none
	// post: none
	// return true if the Dictionary is empty; otherwise returns false
	bool isEmpty();

	// check the size of the Dictionary
	// pre : none
	// post: none
	// return the number of items in the Dictionary
	int getLength();

	//------------------- Other useful functions -----------------

	// display the items in the Dictionary
	void print();

	// checks if key exist in the Dictionary
	// pre: key must exist in the Dictionary
	// post: none
	// return true if key exist in Dictionary; otherwise returns false
	bool ifKeyExist(KeyType key);

	// checks for the user status
	// pre: key must exist in the Dictionary
	// post: none
	// return true if user is logged in as the UserID that exist; otherwise returns false
	bool loginStatus(KeyType key, ItemType item);

	int charvalue(char c);

	void remove(KeyType key);
};

// ------------------------------------------- Implementation of Dictionary class -------------------------------------------
template <typename ItemType>
Dictionary<ItemType>::Dictionary() {
	size = 0;

	for (int i = 0; i < MAX_SIZE; i++) {
		items[i] = nullptr;
	}
};
template <typename ItemType>
Dictionary<ItemType>::~Dictionary() {};

// Hash key (placeholder for now)
template <typename ItemType>
int Dictionary<ItemType>::hash(KeyType key) {
    int total = 1;
    
    for (int i = 0; i < key.size(); i++) {
        total *= charvalue(key[i]);
    }

    return abs(total % MAX_SIZE);
}

template <typename ItemType>
int Dictionary<ItemType>::charvalue(char c)
{
    if (isalpha(c))
    {
        if (isupper(c))
            return (int)c - (int) 'A';
        else
            return (int)c - (int) 'a' + 26;
    } else if (isdigit(c)) {
		return (int)c;
	}
    return -1;
}

// Add something into Hash Table with the Key and Item
template <typename ItemType>
bool Dictionary<ItemType>::add(KeyType newKey, ItemType newItem) {
	int hashValue = hash(newKey);

	if (items[hashValue] == nullptr) {
		Node* temp = new Node;

		temp->key = newKey;
		temp->item = newItem;
		temp->next = nullptr;

		items[hashValue] = temp;
	}
	else {
		Node* currentNode = items[hashValue];

		if (currentNode->key == newKey) {
			return false;
		}

		while (currentNode->next != nullptr) {
			currentNode = currentNode->next;

			if (currentNode->key == newKey) {
				return false;
			}
		}

		Node* temp = new Node;

		temp->key = newKey;
		temp->item = newItem;
		temp->next = nullptr;

		currentNode->next = temp;
	}

	size++;

	return true;
}

// Retrieve the key itself
template <typename ItemType>
ItemType Dictionary<ItemType>::getKey(KeyType key) {
	int index = hash(key);
	Node* newNode = items[index];
	while (newNode != NULL)
	{
		if (newNode->key == key) {
			return newNode->key;
		}
		else if (newNode->next == NULL) {
			return "";
		}
		else
		{
			newNode = newNode->next;
		}
	}
}
// Retrieve the Item using the Key
template <typename ItemType>
ItemType Dictionary<ItemType>::get(KeyType key) {
	int hashValue = hash(key);
    
    return items[hashValue]->item;
}

// For Register
template <typename ItemType>
bool Dictionary<ItemType>::ifKeyExist(KeyType key)
{
	int index = hash(key);
	Node* current = items[index];
	while (current != nullptr) {
		if (current->key == key) {
			return true;
		}
		current = current->next;
	}
	return false;
}
template <typename ItemType>
bool Dictionary<ItemType>::loginStatus(KeyType key, ItemType item)
{
	int index = hash(key);
	Node* newNode = items[index];
	while (newNode != NULL)
	{
		if (getKey(key) == key && get(key) == item)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

// Remove an entry from the Hash Table
template <typename ItemType>
void Dictionary<ItemType>::remove(KeyType key) {
	int hashValue = hash(key);
    
    if (items[hashValue] != nullptr) {
        items[hashValue] = nullptr;
        size--;
    }
}
// Check if Hash Table is empty
template <typename ItemType>
bool Dictionary<ItemType>::isEmpty() {
	if (size == 0)
		return true;
	return false;
}
// Get the length of Hash Table
template <typename ItemType>
int Dictionary<ItemType>::getLength() {
	return size;
}

// Print the entire Hash Table
template <typename ItemType>
void Dictionary<ItemType>::print() {
	for (int i = 0; i < MAX_SIZE; i++) {
		Node* current = items[i];
		while (true)
		{
			if (current->item != "") {
				cout << current->key << " | " << current->item << endl;
				if (current->next != NULL)
					current = current->next;
				else
					break;
			}
			else
				break;
		}
	}
}
