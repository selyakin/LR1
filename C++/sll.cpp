#include <iostream>
#include "sll.h"

using namespace std;

SinglyLinkedList::SinglyLinkedList() : head(nullptr) {}

SinglyLinkedList::~SinglyLinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void SinglyLinkedList::addFront(const string& value) {
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
}

void SinglyLinkedList::addBack(const string& value) {
    Node* newNode = new Node(value);
    if (head == nullptr) {
        head = newNode;
        return;
    }
    Node* temp = head;

    while (temp->next != nullptr) 
        temp = temp->next;

    temp->next = newNode;

}

void SinglyLinkedList::addPost(Node* node, const string& value) {
    if (node == nullptr) return;

    Node* newNode = new Node(value);
    newNode->next = node->next;
    node->next = newNode;
}

void SinglyLinkedList::addPre(Node* node, const string& value) {
    if (node == nullptr) return;

    if (head == node) {
        addFront(value);
        return;
    }
    
    Node* temp = head;
    while (temp != nullptr && temp->next != node)
        temp = temp->next;
    
    if (temp == nullptr) return; 

    Node* newNode = new Node(value);
    newNode->next = node;
    temp->next = newNode;
}

void SinglyLinkedList::removeFront() {
    if (head == nullptr) return;
    
    Node* temp = head;
    head = head->next;
    delete temp;
}

void SinglyLinkedList::removeBack() {
    if (head == nullptr) return;

    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        return;
    }

    Node* temp = head;
    while (temp->next->next != nullptr) 
        temp = temp->next;
    
    
    delete temp->next;
    temp->next = nullptr;
}

void SinglyLinkedList::removePost(Node* node) {
    if (node == nullptr || node->next == nullptr) return;

    Node* toDelete = node->next;
    node->next = toDelete->next;
    delete toDelete;
}

void SinglyLinkedList::removePre(Node* node) {
    if (node == nullptr || node == head) return; // Нет предшественника

    Node* temp = head;
    while (temp->next != nullptr && temp->next->next != node) {
        temp = temp->next;
    }

    if (temp->next != nullptr && temp->next->next == node) {
        Node* deleteNode = temp->next;
        temp->next = node;
        delete deleteNode;
    }
}

void SinglyLinkedList::removeByValue(const string& value) {
    while (head != nullptr && head->value == value) {
        removeFront();
    }
    if (head == nullptr) return;

    Node* temp = head;
    while (temp->next != nullptr) {
        if (temp->next->value == value) {
            removePost(temp); 
        } else {
            temp = temp->next;
        }
    }
}

SinglyLinkedList::Node* SinglyLinkedList::find(const string& value) const {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->value == value) return temp;
        temp = temp->next;
    }
    return nullptr;
}

SinglyLinkedList::Node* SinglyLinkedList::getHead() const{
    return head;
}

bool SinglyLinkedList::isEmpty() const{
    return head == nullptr;
}

bool SinglyLinkedList::contain(const string& value) const {
    return find(value) != nullptr;
}

void SinglyLinkedList::print() const {
    cout << "SLL: ";
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->value << ' ';
        temp = temp->next;
    }
    cout << '\n';
}
#include <sstream>

string SinglyLinkedList::toJson() const {
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

void SinglyLinkedList::fromJson(const string& json) {
    *this = SinglyLinkedList(); 
    
    size_t pos = 0;
    while ((pos = json.find('"', pos)) != string::npos) {
        size_t endQuote = json.find('"', pos + 1);
        if (endQuote == string::npos) break;
        string val = json.substr(pos + 1, endQuote - pos - 1);
        addBack(val); // Восстанавливаем в том же порядке
        pos = endQuote + 1;
    }
}