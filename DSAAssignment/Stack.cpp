#include "Stack.h"
#include "Dictionary.h"
#include "Post.h"
using namespace std;

Stack::Stack() {
    topNode = nullptr;
    length = 0;
}

Stack::~Stack() {

}

bool Stack::push(StackType item) {
    Node* temp = new Node;
    temp->item = item;
    temp->next = nullptr;

    temp->next = topNode;
    topNode = temp;
    length += 1;
    return true;
}
bool Stack::pop() {
    if (isEmpty()) {
        return false;
    }

    Node* temp = topNode;
    topNode = temp->next;
    temp->next = nullptr;
    length -= 1;
    return true;
}
bool Stack::pop(StackType& item) {
    if (isEmpty()) {
        return false;
    }

    Node* temp = topNode;

    topNode = temp->next;
    temp->next = nullptr;

    item = temp->item;
    length -= 1;

    return true;
}
void Stack::getTop(StackType& item) {
    if (isEmpty()) {
        return;
    }

    item = topNode->item;
}

bool Stack::isEmpty() {
    return (topNode == nullptr);
}

void Stack::displayContents(Dictionary<Post>& posts) {
    Stack tempStack;

    int counter = 0;
    
    while (!isEmpty()) {
        counter++;

        string item;
        getTop(item);
        pop();
        tempStack.push(item);

        Post post = posts.get(item);
        
        cout << "[" + to_string(counter) + "] " + post.getPostName() << endl;
        
        if (post.getContent().length() > 50) {
            cout << post.getContent().substr(0, 50) + "..." << endl;
        } else {
            cout << post.getContent() << endl;
        }

        cout << endl;
    }

    while (!tempStack.isEmpty()) {
        string item;
        tempStack.getTop(item);
        tempStack.pop();
        push(item);
    }
}

int Stack::getLength() {
    Stack tempStack;
    int length = 0;
    while (!isEmpty()) {
        ItemType item;
        pop(item);
        length++;
        tempStack.push(item);
    }
    
    while (!tempStack.isEmpty()) {
        ItemType item;
        tempStack.pop(item);
        push(item);
    }
    
    return length;
}