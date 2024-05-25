package main

import (
	"math/rand"
)

type RandomizedSet struct {
	hashmap map[int]int
	length  int
}

func Constructor() RandomizedSet {
	return RandomizedSet{hashmap: make(map[int]int)}
}

func (this *RandomizedSet) Insert(val int) bool {
	if this.hashmap[val] != 0 {
		return false
	} else {
		this.hashmap[val] = 1
		this.length += 1
		return true
	}
}

func (this *RandomizedSet) Remove(val int) bool {
	if this.hashmap[val] != 0 {
		this.hashmap[val] = 0
		this.length -= 1
		return true
	} else {
		return false
	}
}

func (this *RandomizedSet) GetRandom() int {
	n := rand.Int()
	n = n % this.length
}

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * obj := Constructor();
 * param_1 := obj.Insert(val);
 * param_2 := obj.Remove(val);
 * param_3 := obj.GetRandom();
 */
