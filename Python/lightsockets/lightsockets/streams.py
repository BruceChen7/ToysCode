# coding:utf-8
#!/usr/bin/env python


import errno
import socket

class IOStream:
    def __init__(self, sock, max_buffer_size=4096):
        self.sock = sock
        self.buffer_size = max_buffer_size
        self.reader_buffer = []
        self.writer_buffer = []
    
    def read(self):
        # read until 'EWOULDBLOCK'
        res = []
        s = self.sock
        while True:
            try:
                data = s.recv(self.buffer_size)
                print "info is", data
                if not data:
                    return 0, []
                else:
                    self.reader_buffer.append(data)
            except socket.error, e:
                if e.args[0] in (errno.EWOULDBLOCK, errno.EAGAIN):
                    res = self.reader_buffer[:]
                    self.reader_buffer = []
                    return len(res), res
                elif e.args[0] == errno.EINTR:
                    continue
                else:   
                    return -1, []
            except Exception:
               return -1, []
    
    def write(self):
        pass