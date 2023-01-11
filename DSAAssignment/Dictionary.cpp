#include "Dictionary.h"

Dictionary::Dictionary() {
	size = 0;
	Node* newNode = new Node();
	newNode->item = "";
	newNode->key = "";
	newNode->next = NULL;
	for (int i = 0; i < MAX_SIZE; i++) {
		items[i] = newNode;
	}
};
Dictionary::~Dictionary() {};

// Hash key (placeholder for now)
int Dictionary::hash(KeyType key) {
	int x = 0;
	for (int i : key)
	{
		x++;
	}
	return x;
}

// Add something into Hash Table with the Key and Item
bool Dictionary::add(KeyType Key, ItemType newItem) {
	int index = hash(Key);
	if (!(index > MAX_SIZE)) {
		Node* newNode = new Node();
		newNode->item = newItem;
		newNode->key = Key;
		newNode->next = NULL;
		if (items[index]->item == "")
			items[index] = newNode;
		else
		{
			Node* current = items[index];
			bool loop = true;
			while (loop)
			{
				if (current->next == NULL)
					loop = false;
				else
					current = current->next;
			}
			current->next = newNode;
		}
		size++;
		return true;
	}
	return false;
}

// Retrieve the Item using the Key
ItemType Dictionary::get(KeyType key) {
	int index = hash(key);
	Node* newNode = items[index];
	while (newNode != NULL)
	{
		if (newNode->key == key) {
			return newNode->item;
		}
		else if (newNode->next == NULL) {
			return "";
		}
		else
			newNode = newNode->next;
	}
}

// Remove an entry from the Hash Table
void Dictionary::remove(KeyType key) {
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
}
// Check if Hash Table is empty
bool Dictionary::isEmpty() {
	if (size == 0)
		return true;
	return false;
}
// Get the length of Hash Table
int Dictionary::getLength() {
	return size;
}

// Print the entire Hash Table
void Dictionary::print() {
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
