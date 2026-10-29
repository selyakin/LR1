#include "stack.h"
#include <iostream>
#include <stdexcept>

using namespace std;

Stack::Stack() : head(nullptr) {} 
Stack::~Stack() {
    Node* current = head;
    while(current != nullptr){
        Node* local = current->next;
        delete current;
        current = local;
    }
} 

void Stack::push(const string& value) {
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
}

string Stack::pop() {
    if(isEmpty()) 
        throw out_of_range("Stack is empty: pop()");
    Node* deleteNode = head;
    string result = head->value;
    head = deleteNode->next;
    delete deleteNode;
    return result;
}

string Stack::top() const {
    if (isEmpty()) {
        throw out_of_range("Stack is empty");
    }
    return head->value; 
}

bool Stack::isEmpty() const {
    return head == nullptr;
}

void Stack::print() const {
    cout << "Stack: ";
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->value << " ";
        temp = temp->next;
    }
    cout << "\n";
}
#include <sstream>
#include <vector>
#include <algorithm>

string Stack::toJson() const {
    vector<string> items;
    Node* cur = head;
    while (cur) {
        items.push_back(cur->value);
        cur = cur->next;
    }
    reverse(items.begin(), items.end()); 

    stringstream ss;
    ss << "[";
    for (size_t i = 0; i < items.size(); ++i) {
        if (i > 0) ss << ", ";
        ss << "\"" << items[i] << "\"";
    }
    ss << "]";
    return ss.str();
}

void Stack::fromJson(const string& json) {
    *this = Stack();
    size_t pos = 0;
    while ((pos = json.find('"', pos)) != string::npos) {
        size_t endQuote = json.find('"', pos + 1);
        if (endQuote == string::npos) break;
        string val = json.substr(pos + 1, endQuote - pos - 1);
        push(val); // Добавляем от дна к вершине
        pos = endQuote + 1;
    }
}