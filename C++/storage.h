#pragma once

#include <string>
#include <map>
#include "array.h"
#include "sll.h"
#include "dll.h"
#include "stack.h"
#include "queue.h"
#include "tree.h"

extern std::map<std::string, Array> arrays;
extern std::map<std::string, SinglyLinkedList> slls;
extern std::map<std::string, DoublyLinkedList> dlls;
extern std::map<std::string, Stack> stacks;
extern std::map<std::string, Queue> queues;
extern std::map<std::string, CompleteBinaryTree> trees;

void saveToFile(const std::string& filename);
void loadFromFile(const std::string& filename);