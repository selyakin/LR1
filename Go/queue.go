package main

import (
	"errors"
	"fmt"
)

// Аналог struct Queue::Node
type QueueNode struct {
	Value string
	Next  *QueueNode
}

func NewQueueNode(value string) *QueueNode {
	return &QueueNode{Value: value, Next: nil}
}

type Queue struct {
	Head *QueueNode
	Tail *QueueNode
}

func NewQueue() *Queue {
	return &Queue{}
}

func (q *Queue) Push(value string) {
	newNode := NewQueueNode(value)
	if q.IsEmpty() {
		q.Head = newNode
		q.Tail = newNode
		return
	}
	q.Tail.Next = newNode
	q.Tail = newNode
}

func (q *Queue) Pop() (string, error) {
	if q.IsEmpty() {
		return "", errors.New("Queue is empty")
	}
	result := q.Head.Value
	q.Head = q.Head.Next
	if q.Head == nil {
		q.Tail = nil
	}
	return result, nil
}

func (q *Queue) Front() (string, error) {
	if q.IsEmpty() {
		return "", errors.New("Queue is empty")
	}
	return q.Head.Value, nil
}

func (q *Queue) IsEmpty() bool {
	return q.Head == nil
}

func (q *Queue) Print() {
	fmt.Print("Queue: ")
	temp := q.Head
	for temp != nil {
		fmt.Printf("%s ", temp.Value)
		temp = temp.Next
	}
	fmt.Println()
}