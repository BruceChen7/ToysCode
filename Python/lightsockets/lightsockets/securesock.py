# coding:utf-8
#!/usr/bin/env python
import socket
import select
import logging
import errno

from lightsockets.codes import Cipher
from lightsockets.streams import IOStream

class SecureServer():
    def __init__(self, local_port, remote_addr, remote_port, password):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.setblocking(False)
        logging.debug("bind port %s", local_port)
        self.sock.bind(('', int(local_port)))
        self.remote_addr = remote_addr,
        self.remote_port = remote_port
        self.password = password
        self.connections = {}
        self.streams = {}
        self.read_buffer = []
        self.remote_connected = False
        self.remote_sock = None

    def start(self):
        self.sock.listen(64)
        self.ep = select.epoll()
        self.ep.register(self.sock.fileno(), select.EPOLLIN)

        while True:
            events = self.ep.poll(1)
            for fd, event in events:
                if fd == self.sock.fileno() and event == select.EPOLLIN:
                    conn, addr = self.sock.accept()
                    logging.info("a new connection was established")
                    # non-blocking socket
                    conn.setblocking(False)
                    self.ep.register(conn.fileno(), select.EPOLLIN)
                    self.connections[conn.fileno()] = conn
                    self.streams[conn.fileno()] = IOStream(conn)
                    continue
                if event == select.EPOLLIN:
                    assert self.connections.get(fd) != None
                    assert self.streams.get(fd) != None
                    
                    s = self.connections.get(fd)
                    stream = self.streams.get(fd)
                    # read from browser
                    if self.remote_sock is None or fd != self.remote_sock.fileno():
                        logging.info("read from %s", s.getpeername())
                        res, data = stream.read()
                        if res in [0, -1]:
                            self.close(s)
                        else:
                            ci = Cipher.newCiper(self.password)
                            logging.info(data)

                if event == select.EPOLLOUT:
                    assert self.connections.get(fd) != None
                    if fd == self.remote_sock.fileno():
                        if self.remote_connected:
                            pass
                        else:
                            self.remote_connected = True
                            self.ep.register(self.remote_sock.fileno(), select.EPOLLOUT)
                            self.connections[self.remote_sock.fileno()] = self.remote_sock

    def close(self, sock):
        if sock:
            self.connections.pop(sock.fileno())
            self.ep.unregister(sock.fileno())
            sock.close()
        else:
            logging.warn("no socket will be closed")
    

    def handleConnection(self, conn, ci):
        if self.remote_connected:
            pass
        else:
            # connected to remote proxy server socket
            self.remote_sock  = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
            self.remote_sock.setblocking(False)
            self.ep.register(self.remote_sock.fileno(), select.EPOLLOUT)