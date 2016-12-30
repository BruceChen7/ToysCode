#!/user/bin/python
#-*- coding:utf-8 -*-

"""
Just one process to accept every  connection
It's block mode
"""

import socket
HOST = socket.gethostname()
PORT = 1234
SOCK = socket.socket()
SOCK.bind((HOST, PORT))
SOCK.listen(5)

while True:
    CONN, ADDR = SOCK.accept()
    print "Got Connection from ", ADDR
    CONN.send("Thank you  for connecting")
