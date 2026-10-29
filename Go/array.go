package main

import (
	"errors"
	"fmt"
)

type Array struct {
	data []string
	sz   int
	cp   int
}

func NewArray() *Array {
	return &Array{}
}

func NewArrayWithSize(size int) *Array {
	if size <= 0 {
		return &Array{}
	}
	return &Array{
		data: make([]string, size),
		sz:   size,
		cp:   size,
	}
}

func NewArrayFromSlice(list []string) *Array {
	arr := &Array{
		data: make([]string, len(list)),
		sz:   len(list),
		cp:   len(list),
	}
	copy(arr.data, list)
	return arr
}

func (a *Array) Reserve(newCp int) {
	if newCp <= a.cp {
		return
	}
	tempData := make([]string, newCp)
	copy(tempData, a.data[:a.sz])
	a.data = tempData
	a.cp = newCp
}

func (a *Array) Push(value string) {
	if a.sz == a.cp {
		newCp := 1
		if a.cp > 0 {
			newCp = a.cp * 2
		}
		a.Reserve(newCp)
	}
	a.data[a.sz] = value
	a.sz++
}

func (a *Array) Insert(index int, value string) error {
	if index < 0 || index > a.sz {
		return errors.New("insert: index > size")
	}
	if a.sz == a.cp {
		newCp := 1
		if a.cp > 0 {
			newCp = a.cp * 2
		}
		a.Reserve(newCp)
	}
	for i := a.sz; i > index; i-- {
		a.data[i] = a.data[i-1]
	}
	a.data[index] = value
	a.sz++
	return nil
}

func (a *Array) Get(index int) (string, error) {
	if index < 0 || index >= a.sz {
		return "", errors.New("get: index >= size")
	}
	return a.data[index], nil
}

func (a *Array) Remove(index int) error {
	if index < 0 || index >= a.sz {
		return errors.New("remove: index >= size")
	}
	for i := index; i+1 < a.sz; i++ {
		a.data[i] = a.data[i+1]
	}
	a.sz--
	return nil
}

func (a *Array) Replace(index int, value string) error {
	if index < 0 || index >= a.sz {
		return errors.New("replace: index >= size")
	}
	a.data[index] = value
	return nil
}

func (a *Array) Size() int {
	return a.sz
}

func (a *Array) Print() {
	fmt.Println("Array:")
	for i := 0; i < a.sz; i++ {
		fmt.Printf("  array[%d] = %s\n", i, a.data[i])
	}
	fmt.Println()
}