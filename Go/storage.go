package main

import (
	"encoding/json"
	"fmt"
	"os"
)

type DBState struct {
	M map[string][]string `json:"M"`
	F map[string][]string `json:"F"`
	L map[string][]string `json:"L"`
	S map[string][]string `json:"S"`
	Q map[string][]string `json:"Q"`
}

func SaveToFile(filename string) {
	state := DBState{
		M: make(map[string][]string),
		F: make(map[string][]string),
		L: make(map[string][]string),
		S: make(map[string][]string),
		Q: make(map[string][]string),
	}

	for name, arr := range Arrays {
		state.M[name] = arr.data[:arr.sz]
	}
	for name, sll := range SLLs {
		var items []string
		cur := sll.Head
		for cur != nil {
			items = append(items, cur.Value)
			cur = cur.Next
		}
		state.F[name] = items
	}
	for name, dll := range DLLs {
		var items []string
		cur := dll.Head
		for cur != nil {
			items = append(items, cur.Value)
			cur = cur.Next
		}
		state.L[name] = items
	}
	for name, s := range Stacks {
		var items []string
		cur := s.Head
		for cur != nil {
			items = append(items, cur.Value)
			cur = cur.Next
		}
		state.S[name] = items
	}
	for name, q := range Queues {
		var items []string
		cur := q.Head
		for cur != nil {
			items = append(items, cur.Value)
			cur = cur.Next
		}
		state.Q[name] = items
	}

	data, err := json.MarshalIndent(state, "", "  ")
	if err != nil {
		fmt.Println("Error marshaling:", err)
		return
	}
	if err := os.WriteFile(filename, data, 0644); err != nil {
		fmt.Println("Error writing:", err)
		return
	}
}

func LoadFromFile(filename string) {
	data, err := os.ReadFile(filename)
	if err != nil {
		return
	}
	var state DBState
	if err := json.Unmarshal(data, &state); err != nil {
		fmt.Println("Error unmarshaling:", err)
		return
	}

	for name, items := range state.M {
		arr := NewArray()
		for _, v := range items {
			arr.Push(v)
		}
		Arrays[name] = arr
	}
	for name, items := range state.F {
		sll := NewSLL()
		for _, v := range items {
			sll.AddBack(v)
		}
		SLLs[name] = sll
	}
	for name, items := range state.L {
		dll := NewDLL()
		for _, v := range items {
			dll.AddBack(v)
		}
		DLLs[name] = dll
	}
	for name, items := range state.S {
		s := NewStack()
		for _, v := range items {
			s.Push(v)
		}
		Stacks[name] = s
	}
	for name, items := range state.Q {
		q := NewQueue()
		for _, v := range items {
			q.Push(v)
		}
		Queues[name] = q
	}
}