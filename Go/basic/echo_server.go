package main

import (
	"fmt"
	"log"
	"net"
)

func handleConnection(c net.Conn) {
	defer c.Close()
	for {
		buf := make([]byte, 256)
		fmt.Printf("start to read from connection ")
		n, err := c.Read(buf)

		if err != nil {
			log.Println("can't read from connection ")
			return
		}
		fmt.Printf("read %d bytes, content is %s\n", n, string(buf[:n]))
		//	fmt.Println("begin to write content %s", string(buf[:n]))
		c.Write(buf)
	}

}

func main() {
	conn, err := net.Listen("tcp", ":8999")
	if err != nil {
		panic("couldn't start listening: " + err.Error())
	}

	for {
		c, err := conn.Accept()

		if err != nil {
			fmt.Println("accept error", err)
			break
		}
		go handleConnection(c)

	}

}
