#!/user/bin/python
#-*- coding:utf-8 -*-

"""
Just fork one process to handle new  connection
It's block mode
"""

import socket
import os
import sys

HOST = socket.gethostname()
PORT = 1234
LISTEN_SOCK = socket.socket()
LISTEN_SOCK.bind((HOST, PORT))
LISTEN_SOCK.listen(5)



def echo_server(conn):
    """
    Receive all the data from conn,
    and also send then all
    """
    try:
        while True:
            line = conn.recv(1024)
            conn.send(line)
    except KeyboardInterrupt:
        print "Ctrl-C was caught"
        conn.close()
        sys.exit()

while True:
    ACCEPT_SOCK, ADDR = LISTEN_SOCK.accept()
    print "Got Connection from ", ADDR
    PID = os.fork()

    # parent process
    if PID > 0:
        print 'child process pid is ', PID
        ACCEPT_SOCK.close()
    # child process
    if PID == 0:

        print "child process will go to process "
        # close listen socket in child process
        LISTEN_SOCK.close()
        echo_server(ACCEPT_SOCK)

