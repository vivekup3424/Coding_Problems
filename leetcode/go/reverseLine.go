package main

import (
	"bufio"
	"os"
)

func main() {
	r := bufio.NewReader(os.Stdin)
	w := bufio.NewWriter(os.Stdout)
	data, _, _ := r.ReadLine()
	i, j := 0, len(data)-1
	for i < j {
		data[i], data[j] = data[j], data[i]
		i++
		j--
	}
	dataString := string(data)
	w.WriteString(dataString)
	w.Flush()
}
