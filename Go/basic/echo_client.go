package main

import (
	"fmt"
	"net"
)

func handleConnection(conn net.Conn) {
	defer conn.Close()
	buf := make([]byte, 255)
	conn.Read(buf)
	fmt.Printf("%s", buf)
}

func main() {
	fmt.Println("begin to dialg")
	conn, err := net.Dial("tcp", ":8999")

	if err != nil {
		fmt.Println("can't connect to server ", err)
		return
	}

	buf := make([]byte, 255)

	for {
		fmt.Scanf("%s", buf)
		conn.Write(buf)
		go handleConnection(conn)
	}

}
