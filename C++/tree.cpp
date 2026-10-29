#include "tree.h"
#include <iostream>
#include <stdexcept>
#include <sstream>

using namespace std;

CompleteBinaryTree::CompleteBinaryTree() : root(nullptr) {}

CompleteBinaryTree::~CompleteBinaryTree() {
    clear();
}

bool CompleteBinaryTree::isEmpty() const {
    return root == nullptr;
}

void CompleteBinaryTree::clear() {
    if (root == nullptr) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
        delete current;
    }
    root = nullptr;
}

void CompleteBinaryTree::insert(const string& value) {
    int intValue;
    try {
        intValue = stoi(value);
    } catch (const exception&) {
        throw invalid_argument("insert: value is not an integer: " + value);
    }

    Node* newNode = new Node(intValue);
    
    if (root == nullptr) {
        root = newNode;
        return;
    }

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        if (current->left == nullptr) {
            current->left = newNode;
            newNode->parent = current; 
            return;
        } else {
            q.push(current->left);
        }

        if (current->right == nullptr) {
            current->right = newNode;
            newNode->parent = current; 
            return;
        } else {
            q.push(current->right);
        }
    }
}

bool CompleteBinaryTree::contains(const string& value) const {
    return recursiveContain(root, value);
}

bool CompleteBinaryTree::recursiveContain(Node* node, const string& value) const {
    if (node == nullptr) return false;
    // сравниваем как строку: to_string(node->value) == value
    if (to_string(node->value) == value) return true;
    return recursiveContain(node->left, value) || recursiveContain(node->right, value);
}

bool CompleteBinaryTree::isComplete() const {
    if (root == nullptr) return true;

    queue<Node*> q;
    q.push(root);
    bool seenNull = false;

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        if (current == nullptr) {
            seenNull = true;
        } else {
            if (seenNull) return false;
            q.push(current->left);
            q.push(current->right);
        }
    }
    return true;
}

void CompleteBinaryTree::print() const {
    if (root == nullptr) {
        cout << "Tree is empty\n";
        return;
    }
    
    cout << "Tree (BFS): ";
    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        
        cout << current->value << " ";

        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
    cout << "\n";
}

std::vector<std::string> CompleteBinaryTree::getValuesBFS() const {
    std::vector<std::string> result;
    if (root == nullptr) return result;
    std::queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* cur = q.front(); q.pop();
        result.push_back(to_string(cur->value));
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
    return result;
}

string CompleteBinaryTree::toJson() const {
    auto values = getValuesBFS();
    stringstream ss;
    ss << "[";
    for (size_t i = 0; i < values.size(); ++i) {
        if (i > 0) ss << ", ";
        ss << values[i];   
    }
    ss << "]";
    return ss.str();
}

void CompleteBinaryTree::fromJson(const string& json) {
    clear();

    size_t pos = 0;
    while (pos < json.size()) {
        // ищем начало числа
        while (pos < json.size() && !(isdigit(json[pos]) || json[pos] == '-')) ++pos;
        if (pos >= json.size()) break;

        size_t start = pos;
        if (json[pos] == '-') ++pos;                 // знак
        while (pos < json.size() && isdigit(json[pos])) ++pos;
        string token = json.substr(start, pos - start);

        try {
            insert(token);
        } catch (const exception&) {
            // пропускаем некорректные токены
        }
    }
}