#include "Stack.h"
#include "Dictionary.h"
#include "Post.h"
using namespace std;

Stack::Stack() {
    topNode = nullptr;
}

Stack::~Stack() {

}

bool Stack::push(StackType item) {
    Node* temp = new Node;
    temp->item = item;
    temp->next = nullptr;

    temp->next = topNode;
    topNode = temp;

    return true;
}
bool Stack::pop() {
    if (isEmpty()) {
        return false;
    }

    Node* temp = topNode;
    topNode = temp->next;
    temp->next = nullptr;

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

    while (!isEmpty()) {
        string item;
        getTop(item);
        pop();
        tempStack.push(item);

        Post post = posts.get(item);
        
        cout << post.getPostName() << endl;
    }

    while (!tempStack.isEmpty()) {
        string item;
        tempStack.getTop(item);
        tempStack.pop();
        push(item);
    }
}