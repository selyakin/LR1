#pragma once

#include <string>


class Stack {
public:
    struct Node {
        std::string value;
        Node* next;
        Node(const std::string& str) : value(str), next(nullptr) {}
    };

    Stack();  
    ~Stack();

    void push(const std::string& value); 
    std::string pop();                          
    std::string top() const;             
    bool isEmpty() const;                
    void print() const;
    
    std::string toJson() const;
    void fromJson(const std::string& json);

private:
    Node* head; 
};