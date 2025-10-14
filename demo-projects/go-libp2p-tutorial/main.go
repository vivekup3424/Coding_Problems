package main

import (
	"fmt"
	"os"
	"os/signal"
	"syscall"

	"github.com/libp2p/go-libp2p"
)
func main(){
	node,err := libp2p.New()
	if err != nil {
		panic(err)
	}
	fmt.Println("Listen addresses:", node.Addrs()[0])
	ch := make(chan os.Signal, 1)
	signal.Notify(ch, syscall.SIGINT, syscall.SIGTERM)
	<-ch
	fmt.Println("\nReceived signal, shutting down...")
	if err := node.Close(); err != nil {
		panic(err)
	}
}