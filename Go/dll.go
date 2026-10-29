package main

import "fmt"

// Аналог struct DoublyLinkedList::Node
type DLLNode struct {
	Value string
	Next  *DLLNode
	Prev  *DLLNode
}

func NewDLLNode(value string) *DLLNode {
	return &DLLNode{Value: value, Next: nil, Prev: nil}
}

type DoublyLinkedList struct {
	Head *DLLNode
	Tail *DLLNode
}

func NewDLL() *DoublyLinkedList {
	return &DoublyLinkedList{}
}

func (l *DoublyLinkedList) AddFront(value string) {
	newNode := NewDLLNode(value)
	if l.Head == nil {
		l.Head = newNode
		l.Tail = newNode
		return
	}
	newNode.Next = l.Head
	l.Head.Prev = newNode
	l.Head = newNode
}

func (l *DoublyLinkedList) AddBack(value string) {
	newNode := NewDLLNode(value)
	if l.Tail == nil {
		l.Head = newNode
		l.Tail = newNode
		return
	}
	newNode.Prev = l.Tail
	l.Tail.Next = newNode
	l.Tail = newNode
}

// ... методы addPost, addPre, removeFront, removeBack, removePost, removePre, removeByValue ...

func (l *DoublyLinkedList) AddPost(node *DLLNode, value string) {
	if node == nil {
		return
	}
	newNode := NewDLLNode(value)
	newNode.Prev = node
	newNode.Next = node.Next
	if node.Next != nil {
		node.Next.Prev = newNode
	} else {
		l.Tail = newNode
	}
	node.Next = newNode
}

func (l *DoublyLinkedList) AddPre(node *DLLNode, value string) {
	if node == nil {
		return
	}
	newNode := NewDLLNode(value)
	newNode.Next = node
	newNode.Prev = node.Prev
	if node.Prev != nil {
		node.Prev.Next = newNode
	} else {
		l.Head = newNode
	}
	node.Prev = newNode
}

func (l *DoublyLinkedList) RemoveFront() {
	if l.Head == nil {
		return
	}
	l.Head = l.Head.Next
	if l.Head != nil {
		l.Head.Prev = nil
	} else {
		l.Tail = nil
	}
}

func (l *DoublyLinkedList) RemoveBack() {
	if l.Tail == nil {
		return
	}
	l.Tail = l.Tail.Prev
	if l.Tail != nil {
		l.Tail.Next = nil
	} else {
		l.Head = nil
	}
}

func (l *DoublyLinkedList) RemovePost(node *DLLNode) {
	if node == nil || node.Next == nil {
		return
	}
	deleteNode := node.Next
	node.Next = deleteNode.Next
	if deleteNode.Next != nil {
		deleteNode.Next.Prev = node
	} else {
		l.Tail = node
	}
}

func (l *DoublyLinkedList) RemovePre(node *DLLNode) {
	if node == nil || node.Prev == nil {
		return
	}
	toDelete := node.Prev
	node.Prev = toDelete.Prev
	if toDelete.Prev != nil {
		toDelete.Prev.Next = node
	} else {
		l.Head = node
	}
}

func (l *DoublyLinkedList) RemoveByValue(value string) {
	cur := l.Head
	for cur != nil {
		if cur.Value == value {
			nextNode := cur.Next
			if cur.Prev != nil {
				cur.Prev.Next = cur.Next
			} else {
				l.Head = cur.Next
			}
			if cur.Next != nil {
				cur.Next.Prev = cur.Prev
			} else {
				l.Tail = cur.Prev
			}
			cur = nextNode
		} else {
			cur = cur.Next
		}
	}
}

func (l *DoublyLinkedList) Find(value string) *DLLNode {
	temp := l.Head
	for temp != nil {
		if temp.Value == value {
			return temp
		}
		temp = temp.Next
	}
	return nil
}

func (l *DoublyLinkedList) Contains(value string) bool {
	return l.Find(value) != nil
}

func (l *DoublyLinkedList) Print() {
	fmt.Print("DLL: ")
	temp := l.Head
	for temp != nil {
		fmt.Printf("%s ", temp.Value)
		temp = temp.Next
	}
	fmt.Println()
}