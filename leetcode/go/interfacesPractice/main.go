package main

import "fmt"

type Printer interface {
	Print()
}
type Person struct {
	Name string
}

func (p *Person) Print() {
	fmt.Printf("Name is %s\n", p.Name)
}
func printPrinter(p Printer) {
	p.Print()
}

type Scanner interface {
	Scan()
}
type PrinterScanner interface {
	Printer
	Scanner
}
type PrinterScannerImpl struct {
	ModelNumber string
}

func (ps PrinterScannerImpl) Print() {
	fmt.Println(("Printing the printer"))
	fmt.Printf("Model Number = %s", ps.ModelNumber)
}
func (ps PrinterScannerImpl) Scan(){
	ps.ModelNumber = 
}

func main() {
	jack := Person{"Jack Jackson"}
	printPrinter(&jack)
}
