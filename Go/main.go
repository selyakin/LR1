package main

import (
	"fmt"
	"os"
	"strconv"
	"strings"
)

var Arrays = make(map[string]*Array)
var SLLs = make(map[string]*SinglyLinkedList)
var DLLs = make(map[string]*DoublyLinkedList)
var Stacks = make(map[string]*Stack)
var Queues = make(map[string]*Queue)

func ensureArray(name string) *Array {
	if _, ok := Arrays[name]; !ok {
		Arrays[name] = NewArray()
	}
	return Arrays[name]
}
func ensureSLL(name string) *SinglyLinkedList {
	if _, ok := SLLs[name]; !ok {
		SLLs[name] = NewSLL()
	}
	return SLLs[name]
}
func ensureDLL(name string) *DoublyLinkedList {
	if _, ok := DLLs[name]; !ok {
		DLLs[name] = NewDLL()
	}
	return DLLs[name]
}
func ensureStack(name string) *Stack {
	if _, ok := Stacks[name]; !ok {
		Stacks[name] = NewStack()
	}
	return Stacks[name]
}
func ensureQueue(name string) *Queue {
	if _, ok := Queues[name]; !ok {
		Queues[name] = NewQueue()
	}
	return Queues[name]
}

func main() {
	filename := "file.json"
	query := ""

	for i := 1; i < len(os.Args); i++ {
		if os.Args[i] == "--file" && i+1 < len(os.Args) {
			filename = os.Args[i+1]
			i++
		} else if os.Args[i] == "--query" && i+1 < len(os.Args) {
			query = os.Args[i+1]
			i++
		}
	}

	LoadFromFile(filename)

	if query == "" {
		fmt.Println("CURRENT STATE")
		for name, arr := range Arrays {
			fmt.Printf("Array '%s':\n", name)
			arr.Print()
		}
		for name, s := range SLLs {
			fmt.Printf("SLL '%s':\n", name)
			s.Print()
		}
		for name, d := range DLLs {
			fmt.Printf("DLL '%s':\n", name)
			d.Print()
		}
		for name, st := range Stacks {
			fmt.Printf("Stack '%s':\n", name)
			st.Print()
		}
		for name, q := range Queues {
			fmt.Printf("Queue '%s':\n", name)
			q.Print()
		}
		return
	}

	tokens := strings.Fields(query)
	if len(tokens) < 2 {
		fmt.Println("Error: command requires container name")
		return
	}
	cmd := tokens[0]
	name := tokens[1]

	switch cmd {
	// ARRAY
	case "MPUSH":
		ensureArray(name).Push(tokens[2])
	case "MINSERT":
		idx, _ := strconv.Atoi(tokens[2])
		if err := ensureArray(name).Insert(idx, tokens[3]); err != nil {
			fmt.Println("Error:", err)
			return
		}
	case "MGET":
		idx, _ := strconv.Atoi(tokens[2])
		val, err := ensureArray(name).Get(idx)
		if err != nil {
			fmt.Println("Error:", err)
			return
		}
		fmt.Println(val)
	case "MDEL":
		idx, _ := strconv.Atoi(tokens[2])
		if err := ensureArray(name).Remove(idx); err != nil {
			fmt.Println("Error:", err)
			return
		}
	case "MREPLACE":
		idx, _ := strconv.Atoi(tokens[2])
		if err := ensureArray(name).Replace(idx, tokens[3]); err != nil {
			fmt.Println("Error:", err)
			return
		}
	case "MSIZE":
		fmt.Println(ensureArray(name).Size())

	// SLL
	case "FPUSH_FRONT":
		ensureSLL(name).AddFront(tokens[2])
	case "FPUSH_BACK":
		ensureSLL(name).AddBack(tokens[2])
	case "FDEL_FRONT":
		ensureSLL(name).RemoveFront()
	case "FDEL_BACK":
		ensureSLL(name).RemoveBack()
	case "FDEL_VAL":
		ensureSLL(name).RemoveByValue(tokens[2])
	case "FCONTAINS":
		if ensureSLL(name).Contains(tokens[2]) {
			fmt.Println("TRUE")
		} else {
			fmt.Println("FALSE")
		}
	case "FPRINT":
		ensureSLL(name).Print()

	// DLL
	case "LPUSH_FRONT":
		ensureDLL(name).AddFront(tokens[2])
	case "LPUSH_BACK":
		ensureDLL(name).AddBack(tokens[2])
	case "LDEL_FRONT":
		ensureDLL(name).RemoveFront()
	case "LDEL_BACK":
		ensureDLL(name).RemoveBack()
	case "LDEL_VAL":
		ensureDLL(name).RemoveByValue(tokens[2])
	case "LCONTAINS":
		if ensureDLL(name).Contains(tokens[2]) {
			fmt.Println("TRUE")
		} else {
			fmt.Println("FALSE")
		}
	case "LPRINT":
		ensureDLL(name).Print()

	// STACK
	case "SPUSH":
		ensureStack(name).Push(tokens[2])
	case "SPOP":
		val, err := ensureStack(name).Pop()
		if err != nil {
			fmt.Println("Error:", err)
			return
		}
		fmt.Println(val)
	case "STOP":
		val, err := ensureStack(name).Top()
		if err != nil {
			fmt.Println("Error:", err)
			return
		}
		fmt.Println(val)
	case "SPRINT":
		ensureStack(name).Print()

	// QUEUE
	case "QPUSH":
		ensureQueue(name).Push(tokens[2])
	case "QPOP":
		val, err := ensureQueue(name).Pop()
		if err != nil {
			fmt.Println("Error:", err)
			return
		}
		fmt.Println(val)
	case "QFRONT":
		val, err := ensureQueue(name).Front()
		if err != nil {
			fmt.Println("Error:", err)
			return
		}
		fmt.Println(val)
	case "QPRINT":
		ensureQueue(name).Print()

	case "PRINT":
		if len(tokens) < 3 {
			fmt.Println("PRINT requires type and name")
			return
		}
		typ := tokens[1]
		cname := tokens[2]
		switch typ {
		case "M":
			if v, ok := Arrays[cname]; ok {
				v.Print()
			}
		case "F":
			if v, ok := SLLs[cname]; ok {
				v.Print()
			}
		case "L":
			if v, ok := DLLs[cname]; ok {
				v.Print()
			}
		case "S":
			if v, ok := Stacks[cname]; ok {
				v.Print()
			}
		case "Q":
			if v, ok := Queues[cname]; ok {
				v.Print()
			}
		default:
			fmt.Println("Container not found")
		}

	default:
		fmt.Println("Unknown command:", cmd)
		return
	}

	SaveToFile(filename)
}