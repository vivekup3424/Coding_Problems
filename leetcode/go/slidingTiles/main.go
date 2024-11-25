package main

import (
	"fmt"
	"os"
	"os/exec"
	"runtime"
	"strings"
)

type Board struct {
	tiles    [][]int
	rows     int
	cols     int
	emptyRow int
	emptyCol int
}

func NewBoard(rows, cols int, initialState [][]int) *Board {
	board := &Board{
		tiles: make([][]int, rows),
		rows:  rows,
		cols:  cols,
	}

	// Initialize the board with the given state
	for i := 0; i < rows; i++ {
		board.tiles[i] = make([]int, cols)
		for j := 0; j < cols; j++ {
			board.tiles[i][j] = initialState[i][j]
			if initialState[i][j] == 0 {
				board.emptyRow = i
				board.emptyCol = j
			}
		}
	}

	return board
}

func (b *Board) Print() {
	clearScreen()
	fmt.Println("Use WASD to move tiles (Q to quit):")
	fmt.Println("─" + "──────" + strings.Repeat("─", b.cols*6))
	for i := 0; i < b.rows; i++ {
		fmt.Print("│ ")
		for j := 0; j < b.cols; j++ {
			if b.tiles[i][j] == 0 {
				fmt.Print("    │ ")
			} else {
				fmt.Printf(" %2d │ ", b.tiles[i][j])
			}
		}
		fmt.Println()
		fmt.Println("─" + "──────" + strings.Repeat("─", b.cols*6))
	}
}

func (b *Board) Move(direction byte) bool {
	newRow, newCol := b.emptyRow, b.emptyCol

	switch direction {
	case 'w', 'W':
		newRow++
	case 's', 'S':
		newRow--
	case 'a', 'A':
		newCol++
	case 'd', 'D':
		newCol--
	default:
		return false
	}

	if newRow < 0 || newRow >= b.rows || newCol < 0 || newCol >= b.cols {
		return false
	}

	// Swap the empty tile with the target tile
	b.tiles[b.emptyRow][b.emptyCol] = b.tiles[newRow][newCol]
	b.tiles[newRow][newCol] = 0
	b.emptyRow = newRow
	b.emptyCol = newCol
	return true
}

func clearScreen() {
	var cmd *exec.Cmd
	if runtime.GOOS == "windows" {
		cmd = exec.Command("cmd", "/c", "cls")
	} else {
		cmd = exec.Command("clear")
	}
	cmd.Stdout = os.Stdout
	cmd.Run()
}

func main() {
	// Initialize the board with the state from the image
	initialState := [][]int{
		{4, 1, 2},
		{5, 0, 3},
	}

	board := NewBoard(2, 3, initialState)

	// Set up raw input mode
	exec.Command("stty", "-F", "/dev/tty", "cbreak", "min", "1").Run()
	exec.Command("stty", "-F", "/dev/tty", "-echo").Run()
	defer exec.Command("stty", "-F", "/dev/tty", "echo").Run()

	var input [1]byte
	for {
		board.Print()
		os.Stdin.Read(input[:])

		if input[0] == 'q' || input[0] == 'Q' {
			fmt.Println("\nThank you for playing!")
			break
		}

		if board.Move(input[0]) {
			continue
		}
	}
}
