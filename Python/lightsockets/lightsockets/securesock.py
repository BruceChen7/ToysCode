# coding:utf-8
#!/usr/bin/env python
import socket
import select
import logging
import errno

from lightsockets.codes import Cipher

class SercureServer():
    def __init__(self, local_port, remote_addr, remote_port, password, max_buffer=4096):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.setblocking(False)
        self.sock.bind(('', local_port))
        self.remote_addr = remote_addr,
        self.remote_port = remote_port
        self.password = password
        self.max_buffer = max_buffer
        self.connections = {}
        self.read_buffer = []

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
                    conn.setblocking(False)
                    self.ep.register(conn.fileno(), select.EPOLLIN)
                    self.connections[conn.fileno()] = conn
                    continue
                if event == select.EPOLLIN:
                    assert self.connections.get(fd) != None
                    s = self.connections.get(fd)
                    try:
                        data = s.recv(self.max_buffer)
                        if not data:
                            self.close(s)
                        else:
                            self.read_buffer.append(data)
                    except socket.error, e:
                        if e.args[0] in (errno.EWOULDBLOCK, errno.EAGAIN):
                            ci = Cipher.newCiper(self.password)
                        logging.debug("reading data next round")
                        return
                    except Exception:
                        logging.error("something error")
                        self.close(s)
                        return
    
    def close(self, sock):
        self.connections.pop(sock.fileno())
        self.ep.unregister(sock.fileno())
        sock.close()
      