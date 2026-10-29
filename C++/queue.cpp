#include <iostream>

#include "queue.h"

using namespace std;

Queue::Queue() : head(nullptr), tail(nullptr) {} 
Queue::~Queue() {
    Node* current = head;
    while(current != nullptr){
        Node* local = current->next;
        delete current;
        current = local;
    }
} 

void Queue::push(const string& value) {
    Node* newNode = new Node(value);
    if(isEmpty()) {
        head = tail = newNode;
        return;
    }
    tail->next = newNode;
    tail = newNode;
}

string Queue::pop() {
    if(isEmpty())
        throw out_of_range("Queue is empty");
    Node* deleteNode = head;
    string result = head->value;
    head = head->next;

    if(head == nullptr)
        tail = nullptr;

    delete deleteNode;
    return result;
}

string Queue::front() const {
    if (isEmpty()) 
        throw out_of_range("Queue is empty");
    return head->value; 
}

bool Queue::isEmpty() const {
    return head == nullptr;
}

void Queue::print() const {
    cout << "Queue: ";
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->value << " ";
        temp = temp->next;
    }
    cout << "\n";
}
#include <sstream>

string Queue::toJson() const {
    stringstream ss;
    ss << "[";
    Node* cur = head;
    bool first = true;
    while (cur) {
        if (!first) ss << ", ";
        ss << "\"" << cur->value << "\"";
        cur = cur->next;
        first = false;
    }
    ss << "]";
    return ss.str();
}

void Queue::fromJson(const string& json) {
    *this = Queue();
    size_t pos = 0;
    while ((pos = json.find('"', pos)) != string::npos) {
        size_t endQuote = json.find('"', pos + 1);
        if (endQuote == string::npos) break;
        string val = json.substr(pos + 1, endQuote - pos - 1);
        push(val); // загружается от головы к хвосту
        pos = endQuote + 1;
    }
}