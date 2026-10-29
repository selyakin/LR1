package main

import "fmt"

type SLLNode struct {
	Value string
	Next  *SLLNode
}

func NewSLLNode(value string) *SLLNode {
	return &SLLNode{Value: value, Next: nil}
}

type SinglyLinkedList struct {
	Head *SLLNode
}

func NewSLL() *SinglyLinkedList {
	return &SinglyLinkedList{}
}


func (l *SinglyLinkedList) AddFront(value string) {
	newNode := NewSLLNode(value)
	newNode.Next = l.Head
	l.Head = newNode
}

func (l *SinglyLinkedList) AddBack(value string) {
	newNode := NewSLLNode(value)
	if l.Head == nil {
		l.Head = newNode
		return
	}
	temp := l.Head
	for temp.Next != nil {
		temp = temp.Next
	}
	temp.Next = newNode
}

func (l *SinglyLinkedList) AddPost(node *SLLNode, value string) {
	if node == nil {
		return
	}
	newNode := NewSLLNode(value)
	newNode.Next = node.Next
	node.Next = newNode
}

func (l *SinglyLinkedList) AddPre(node *SLLNode, value string) {
	if node == nil {
		return
	}
	if l.Head == node {
		l.AddFront(value)
		return
	}
	temp := l.Head
	for temp != nil && temp.Next != node {
		temp = temp.Next
	}
	if temp == nil {
		return
	}
	newNode := NewSLLNode(value)
	newNode.Next = node
	temp.Next = newNode
}

func (l *SinglyLinkedList) RemoveFront() {
	if l.Head == nil {
		return
	}
	l.Head = l.Head.Next
}

func (l *SinglyLinkedList) RemoveBack() {
	if l.Head == nil {
		return
	}
	if l.Head.Next == nil {
		l.Head = nil
		return
	}
	temp := l.Head
	for temp.Next.Next != nil {
		temp = temp.Next
	}
	temp.Next = nil
}

func (l *SinglyLinkedList) RemovePost(node *SLLNode) {
	if node == nil || node.Next == nil {
		return
	}
	node.Next = node.Next.Next
}

func (l *SinglyLinkedList) RemovePre(node *SLLNode) {
	if node == nil || node == l.Head {
		return
	}
	temp := l.Head
	for temp.Next != nil && temp.Next.Next != node {
		temp = temp.Next
	}
	if temp.Next != nil && temp.Next.Next == node {
		temp.Next = node
	}
}

func (l *SinglyLinkedList) RemoveByValue(value string) {
	for l.Head != nil && l.Head.Value == value {
		l.RemoveFront()
	}
	if l.Head == nil {
		return
	}
	temp := l.Head
	for temp.Next != nil {
		if temp.Next.Value == value {
			l.RemovePost(temp)
		} else {
			temp = temp.Next
		}
	}
}

func (l *SinglyLinkedList) Find(value string) *SLLNode {
	temp := l.Head
	for temp != nil {
		if temp.Value == value {
			return temp
		}
		temp = temp.Next
	}
	return nil
}

func (l *SinglyLinkedList) Contains(value string) bool {
	return l.Find(value) != nil
}

func (l *SinglyLinkedList) Print() {
	fmt.Print("SLL: ")
	temp := l.Head
	for temp != nil {
		fmt.Printf("%s ", temp.Value)
		temp = temp.Next
	}
	fmt.Println()
}