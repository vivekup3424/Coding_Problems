package main

import (
	"crypto/sha1"
	"encoding/hex"
	"net"
)

func encrypt(s string) string {
	hashSum := sha1.Sum([]byte(s))
	return hex.EncodeToString(hashSum[:])
}
func main() {
	address = &TCPAddr{net.ParseIP("localhost"), 8080}
	listener, err := net.ListenTCP("tcp")
}
