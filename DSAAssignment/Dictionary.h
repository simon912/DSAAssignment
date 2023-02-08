#pragma once
#include<string>
#include<iostream>

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
	int x = 0;
	for (int i : key)
	{
		x = x % MAX_SIZE;
	}
	return x;
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
	Node* newNode = items[index];
	while (newNode != NULL)
	{
		if (getKey(key) == key)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
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

/* -- Probably not needed --
// Remove an entry from the Hash Table
template <typename ItemType>
void Dictionary<ItemType>::remove(KeyType key) {
	if (!isEmpty()) {
		int index = hash(key);
		Node* newNode = items[index];
		Node* current = items[index];
		bool loop = true;
		if (current->key == key) {
			Node* temp = current;
			items[index] = current->next;
			delete temp;
			size--;
			cout << "Item removed" << endl;
			return;
		}
		current = newNode->next;
		while (loop)
		{
			if (current->key == key) {
				Node* temp = current;
				newNode->next = current->next;
				delete temp;
				size--;
				cout << "Item removed" << endl;
				break;
			}
			else if (current->next == NULL) {
				break;
			}
			else {
				newNode = newNode->next;
				current = current->next;
			}
		}
	}
	else
		cout << "Item is not removed (Item not found)" << endl;
}*/
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
