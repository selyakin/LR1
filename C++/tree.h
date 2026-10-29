#pragma once

#include <string>
#include <queue>
#include <vector>

class CompleteBinaryTree {
public:
    struct Node {
        int value;
        Node* left;
        Node* right;
        Node* parent;
        Node(int val) : value(val), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    CompleteBinaryTree();
    ~CompleteBinaryTree();

    void insert(const std::string& value);
    bool contains(const std::string& value) const;
    void print() const;
    bool isComplete() const;
    bool isEmpty() const;
    void clear();

    std::string toJson() const;
    void fromJson(const std::string& json);
    std::vector<std::string> getValuesBFS() const; 

private:
    Node* root;
    
    bool recursiveContain(Node* node, const std::string& value) const;
};