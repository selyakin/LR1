package main

import (
	"errors"
	"fmt"
)

type StackNode struct {
	Value string
	Next  *StackNode
}

func NewStackNode(value string) *StackNode {
	return &StackNode{Value: value, Next: nil}
}

type Stack struct {
	Head *StackNode
}

func NewStack() *Stack {
	return &Stack{}
}

func (s *Stack) Push(value string) {
	newNode := NewStackNode(value)
	newNode.Next = s.Head
	s.Head = newNode
}

func (s *Stack) Pop() (string, error) {
	if s.IsEmpty() {
		return "", errors.New("Stack is empty")
	}
	result := s.Head.Value
	s.Head = s.Head.Next
	return result, nil
}

func (s *Stack) Top() (string, error) {
	if s.IsEmpty() {
		return "", errors.New("Stack is empty")
	}
	return s.Head.Value, nil
}

func (s *Stack) IsEmpty() bool {
	return s.Head == nil
}

func (s *Stack) Print() {
	fmt.Print("Stack: ")
	temp := s.Head
	for temp != nil {
		fmt.Printf("%s ", temp.Value)
		temp = temp.Next
	}
	fmt.Println()
}