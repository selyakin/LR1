#include <iostream>
#include "dll.h"

using namespace std;

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

DoublyLinkedList::~DoublyLinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void DoublyLinkedList::addFront(const string& value) {
    Node* newNode = new Node(value);
    if (head == nullptr) {
        head = tail = newNode;
        return;
    }
    newNode->next = head;
    head->prev = newNode;
    head = newNode;
}

void DoublyLinkedList::addBack(const string& value) {
    Node* newNode = new Node(value);
    if (tail == nullptr) {
        head = tail = newNode;
        return;
    }
    newNode->prev = tail;
    tail->next = newNode;
    tail = newNode;
}

void DoublyLinkedList::addPost(Node* node, const string& value) {
    if (node == nullptr) return;

    Node* newNode = new Node(value);
    newNode->prev = node;
    newNode->next = node->next;
    
    if (node->next != nullptr) {
        node->next->prev = newNode;
    } else {
        tail = newNode; 
    }
    node->next = newNode;
}

void DoublyLinkedList::addPre(Node* node, const string& value) {
    if (node == nullptr) return;

    Node* newNode = new Node(value);
    newNode->next = node;
    newNode->prev = node->prev;

    if (node->prev != nullptr) {
        node->prev->next = newNode;
    } else {
        head = newNode;
    }
    node->prev = newNode;
}

void DoublyLinkedList::removeFront() {
    if (head == nullptr) return;

    Node* temp = head;
    head = head->next;
    
    if (head != nullptr) {
        head->prev = nullptr;
    } else {
        tail = nullptr; 
    }
    delete temp;
}

void DoublyLinkedList::removeBack() {
    if (tail == nullptr) return;

    Node* temp = tail;
    tail = tail->prev;
    
    if (tail != nullptr) {
        tail->next = nullptr;
    } else {
        head = nullptr; 
    }
    delete temp;
}

void DoublyLinkedList::removePost(Node* node) {
    if (node == nullptr || node->next == nullptr) return;

    Node* deleteNode = node->next;
    node->next = deleteNode->next;
    
    if (deleteNode->next != nullptr) {
        deleteNode->next->prev = node;
    } else {
        tail = node; 
    }
    delete deleteNode;
}

void DoublyLinkedList::removePre(Node* node) {
    if (node == nullptr || node->prev == nullptr) return;

    Node* toDelete = node->prev;
    node->prev = toDelete->prev;
    
    if (toDelete->prev != nullptr) {
        toDelete->prev->next = node;
    } else {
        head = node; // Удалили первый
    }
    delete toDelete;
}

void DoublyLinkedList::removeByValue(const string& value) {
    Node* current = head;
    while (current != nullptr) {
        if (current->value == value) {
            Node* nextNode = current->next; 
            
            if (current->prev != nullptr) current->prev->next = current->next;
            else head = current->next;
            
            if (current->next != nullptr) current->next->prev = current->prev;
            else tail = current->prev;
            
            delete current;
            current = nextNode;
        } else {
            current = current->next;
        }
    }
}

DoublyLinkedList::Node* DoublyLinkedList::find(const string& value) const {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->value == value) return temp;
        temp = temp->next;
    }
    return nullptr;
}

bool DoublyLinkedList::contain(const string& value) const {
    return find(value) != nullptr;
}

DoublyLinkedList::Node* DoublyLinkedList::getHead() const {
    return head;
}

DoublyLinkedList::Node* DoublyLinkedList::getTail() const {
    return tail;
}

bool DoublyLinkedList::isEmpty() const {
    return head == nullptr;
}

void DoublyLinkedList::print() const {
    cout << "DLL: ";
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->value << ' ';
        temp = temp->next;
    }
    cout << '\n';
}
#include <sstream>

string DoublyLinkedList::toJson() const {
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

void DoublyLinkedList::fromJson(const string& json) {
    *this = DoublyLinkedList();
    size_t pos = 0;
    while ((pos = json.find('"', pos)) != string::npos) {
        size_t endQuote = json.find('"', pos + 1);
        if (endQuote == string::npos) break;
        string val = json.substr(pos + 1, endQuote - pos - 1);
        addBack(val);
        pos = endQuote + 1;
    }
}
