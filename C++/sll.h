#pragma once

#include <cstddef>
#include <string>

class SinglyLinkedList {
public:
    struct Node {
        std::string value;
        Node* next;
        Node(const std::string& str) : value(str), next(nullptr) {}
    };
    
    SinglyLinkedList();
    ~SinglyLinkedList();

    void addFront(const std::string& value);
    void addBack(const std::string& value);
    void addPost(Node* node, const std::string& value);
    void addPre(Node* node, const std::string& value);

    void removeFront();
    void removeBack();
    void removePost(Node* node);
    void removePre(Node* node);
    void removeByValue(const std::string& value);

    Node* find(const std::string& value) const;
    Node* getHead() const;
    bool isEmpty() const;
    bool contain(const std::string& value) const;
    void print() const;
    
    std::string toJson() const;
    void fromJson(const std::string& json);

private:
    Node* head; 
};