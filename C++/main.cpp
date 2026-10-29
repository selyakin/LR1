#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <stdexcept>

#include "array.h"
#include "sll.h"
#include "dll.h"
#include "stack.h"
#include "queue.h"
#include "tree.h"
#include "storage.h" 

using namespace std;

map<string, Array> arrays;
map<string, SinglyLinkedList> slls;
map<string, DoublyLinkedList> dlls;
map<string, Stack> stacks;
map<string, Queue> queues;
map<string, CompleteBinaryTree> trees;


vector<string> split(const string& s) {
    vector<string> tokens;
    istringstream iss(s);
    string token;
    while (iss >> token) tokens.push_back(token);
    return tokens;
}

int main(int argc, char** argv) {
    string filename = "file.json";
    string query = "";

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) filename = argv[++i];
        else if (arg == "--query" && i + 1 < argc) query = argv[++i];
    }

    try {
        loadFromFile(filename);
    } catch (const exception& e) {
        cerr << "Load error: " << e.what() << "\n";
    }

    if (query.empty()) {
        cout << "CURRENT STATE\n";
        for (const auto& [name, arr] : arrays) { cout << "Array '" << name << "':\n"; arr.print(); }
        for (const auto& [name, s] : slls) { cout << "SLL '" << name << "':\n"; s.print(); }
        for (const auto& [name, d] : dlls) { cout << "DLL '" << name << "':\n"; d.print(); }
        for (const auto& [name, st] : stacks) { cout << "Stack '" << name << "':\n"; st.print(); }
        for (const auto& [name, q] : queues) { cout << "Queue '" << name << "':\n"; q.print(); }
        for (const auto& [name, t] : trees) { cout << "Tree '" << name << "':\n"; t.print(); }
        return 0;
    }

    vector<string> tokens = split(query);
    if (tokens.size() < 2) { cerr << "Error: command requires container name\n"; return 1; }
    string cmd = tokens[0];
    string name = tokens[1];

      try {
        // ARRAY
        if (cmd == "MPUSH") { arrays[name].push(tokens[2]); }
        else if (cmd == "MINSERT") { arrays[name].insert(stoul(tokens[2]), tokens[3]); }
        else if (cmd == "MGET") { cout << arrays[name].get(stoul(tokens[2])) << "\n"; }
        else if (cmd == "MDEL") { arrays[name].remove(stoul(tokens[2])); }
        else if (cmd == "MREPLACE") { arrays[name].replace(stoul(tokens[2]), tokens[3]); }
        else if (cmd == "MSIZE") { cout << arrays[name].size() << "\n"; }

        // SINGLY LINKED LIST
        else if (cmd == "FPUSH_FRONT") { slls[name].addFront(tokens[2]); }
        else if (cmd == "FPUSH_BACK") { slls[name].addBack(tokens[2]); }
        else if (cmd == "FDEL_FRONT") { slls[name].removeFront(); }
        else if (cmd == "FDEL_BACK") { slls[name].removeBack(); }
        else if (cmd == "FDEL_VAL") { slls[name].removeByValue(tokens[2]); }
        else if (cmd == "FCONTAINS") { cout << (slls[name].contain(tokens[2]) ? "TRUE" : "FALSE") << "\n"; }
        else if (cmd == "FPRINT") { slls[name].print(); }

        // DOUBLY LINKED LIST
        else if (cmd == "LPUSH_FRONT") { dlls[name].addFront(tokens[2]); }
        else if (cmd == "LPUSH_BACK") { dlls[name].addBack(tokens[2]); }
        else if (cmd == "LDEL_FRONT") { dlls[name].removeFront(); }
        else if (cmd == "LDEL_BACK") { dlls[name].removeBack(); }
        else if (cmd == "LDEL_VAL") { dlls[name].removeByValue(tokens[2]); }
        else if (cmd == "LCONTAINS") { cout << (dlls[name].contain(tokens[2]) ? "TRUE" : "FALSE") << "\n"; }
        else if (cmd == "LPRINT") { dlls[name].print(); }

        // STACK
        else if (cmd == "SPUSH") { stacks[name].push(tokens[2]); }
        else if (cmd == "SPOP") { cout << stacks[name].pop() << "\n"; }
        else if (cmd == "STOP") { cout << stacks[name].top() << "\n"; }
        else if (cmd == "SPRINT") { stacks[name].print(); }

        // QUEUE
        else if (cmd == "QPUSH") { queues[name].push(tokens[2]); }
        else if (cmd == "QPOP") { cout << queues[name].pop() << "\n"; }
        else if (cmd == "QFRONT") { cout << queues[name].front() << "\n"; }
        else if (cmd == "QPRINT") { queues[name].print(); }

        // TREE
        else if (cmd == "TINSERT") { trees[name].insert(tokens[2]); }
        else if (cmd == "TGET") { cout << (trees[name].contains(tokens[2]) ? "TRUE" : "FALSE") << "\n"; }
        else if (cmd == "TCOMPLETE") { cout << (trees[name].isComplete() ? "TRUE" : "FALSE") << "\n"; }
        else if (cmd == "TPRINT") { trees[name].print(); }

        else if (cmd == "PRINT") {
            if (tokens.size() < 3) throw invalid_argument("PRINT requires type and name");
            string type = tokens[1];
            string cname = tokens[2];
            if (type == "M" && arrays.count(cname)) arrays[cname].print();
            else if (type == "F" && slls.count(cname)) slls[cname].print();
            else if (type == "L" && dlls.count(cname)) dlls[cname].print();
            else if (type == "S" && stacks.count(cname)) stacks[cname].print();
            else if (type == "Q" && queues.count(cname)) queues[cname].print();
            else if (type == "T" && trees.count(cname)) trees[cname].print();
            else cout << "Container not found\n";
        }
        
        else { cerr << "Unknown command: " << cmd << "\n"; return 1; }

        saveToFile(filename);

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}