#!/user/bin/python
#-*- coding:utf-8 -*-

"""
It's a script about echo client
"""
import socket
SOCK = socket.socket()

HOST = socket.gethostname()
PORT = 1234
SOCK.connect((HOST, PORT))

while True:
    SEND_DATA = raw_input()
    SOCK.send(SEND_DATA)
    print SOCK.recv(1024)

