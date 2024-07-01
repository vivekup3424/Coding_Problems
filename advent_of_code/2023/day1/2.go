package main

import (
	"fmt"
	"log"
	"os"
	"strings"
)

const ALPHABET = 26

// TrieNode represents a node in a Trie
type TrieNode struct {
	Children    [ALPHABET]*TrieNode
	isEndOfWord bool
}

// NewTrieNode creates and initializes a new TrieNode
func NewTrieNode() *TrieNode {
	return &TrieNode{}
}

// insertWord inserts a word into the Trie
func insertWord(root *TrieNode, word string) {
	node := root
	for i := 0; i < len(word); i++ {
		idx := word[i] - 'a'
		if node.Children[idx] == nil {
			node.Children[idx] = NewTrieNode()
		}
		node = node.Children[idx]
	}
	node.isEndOfWord = true
}

// searchWordInTrie searches for a word in the Trie starting from the given index
func searchWordInTrie(root *TrieNode, s string, start int) (string, int) {
	node := root
	for i := start; i < len(s); i++ {
		idx := s[i] - 'a'
		if idx >= ALPHABET || node.Children[idx] == nil {
			break
		}
		node = node.Children[idx]
		if node.isEndOfWord {
			return s[start : i+1], i + 1
		}
	}
	return "", start + 1
}

func main() {
	words := []string{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"}
	strToNum := map[string]int{
		"one":   1,
		"two":   2,
		"three": 3,
		"four":  4,
		"five":  5,
		"six":   6,
		"seven": 7,
		"eight": 8,
		"nine":  9,
	}
	root := NewTrieNode()

	for _, word := range words {
		insertWord(root, word)
	}

	file, err := os.ReadFile("./1.txt")
	if err != nil {
		log.Fatal("Unable to read 1.txt:", err)
	}
	fileString := string(file)
	instructions := strings.Split(fileString, "\n")
	sum := 0
	for _, instruction := range instructions {
		numbers := []int{}
		for i := 0; i < len(instruction); i++ {
			if instruction[i] >= '0' && instruction[i] <= '9' {
				numbers = append(numbers, int(instruction[i]-'0'))
			} else {
				word, _ := searchWordInTrie(root, instruction, i)
				if word != "" {
					numbers = append(numbers, strToNum[word])
				}
			}
		}
		if len(numbers) > 0 {
			sum += numbers[0]*10 + numbers[len(numbers)-1]
		}
		fmt.Println(numbers)
	}
	fmt.Println("Sum = ", sum)
}
