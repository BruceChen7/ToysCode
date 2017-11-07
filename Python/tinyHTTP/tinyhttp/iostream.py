# -*- coding: utf-8 -*-
"""
iostream.py
~~~~~~~
This module is used to read or write data  from socket or to socket
"""
import  collections
import socket
import errno
from ioloop import IOLoop
from request import Request

class IOStream():
    """用来处理IO输入和输出的类
    """
    def __init__(self, sock, addr, ioloop=None, max_buffer_size=104857600,
                 max_read_buffer = 4096):
        self.ioloop = ioloop or IOLoop.instance()
        # accept socket 
        self.sock = sock
        # peer address
        self._addr = addr
        #  next loop, the stream' status should be IOLoop's READ or WRITE
        self._state = IOLoop.ERROR
        self._read_buffer = collections.deque()
        self._write_buffer = collections.deque()
        self._max_read_buffer = max_read_buffer
        self._max_buffer_size = max_buffer_size
        self._reading = False
        self._writing = False


    def handle_read(self, fd):
        while True:
            try:
                data = self.sock.recv(self._max_read_buffer)
                self._reading = True
                if not data:
                    self.close()
                else:
                    self._read_buffer.append(data)
            except socket.error, e:
                if e.args[0] in (errno.EWOULDBLOCK, errno.EAGAIN):
                    # FixMe: determin
                    self._reading = False
                    _merge_prefix(self._read_buffer, self._max_read_buffer)
                    request = Request(self._addr[0],self._read_buffer[0],self)
                    request.response()
                    return
            except Exception:
                print "something error"
                self.close()
                return

    def handle_write(self, fd):
        while self._write_buffer:
            try:
                _merge_prefix(self._write_buffer, 128 * 1024)
                num_bytes = self.sock.send(self._write_buffer[0])
                _merge_prefix(self._write_buffer, num_bytes)
                self._write_buffer.popleft()
            except socket.error, e:
                if e.args[0] in (errno.EWOULDBLOCK, errno.EAGAIN):
                    if self._write_buffer:
                        self._writing = True
                    break
                else:
                    print("Write error on %d: %s",
                                    self.sock.fileno(), e)
                    self.close()
                    return
        # FixMe:here is not right place to close
        self.close()

    def send(self, data):
        if self.sock is not None:
            self._write_buffer.append(data)
            self._writing = True;
            
    def get_stream_state(self):
        return self._state


    def set_status(self, status):
        """set stream next loop status which registered in poller
        """
        self._state = status

    def reading(self):
        return self._reading

    # next loop to continue read
    def enable_reading(self):
        self._reading = True
        self._state = IOLoop.READ | IOLoop.ERROR

    def writing(self):
        """Is io

        """
        return self._writing

    def close(self):
        """close a stream
        """
        if self.sock is not None:
            fd = self.sock.fileno()
            self.sock.close()
            self.sock = None
            self.ioloop.unregister(fd)


def _merge_prefix(deque, size):
    """Replace the first entries in a deque of strings with a single
        string of up to size bytes.

        >>> d = collections.deque(['abc', 'de', 'fghi', 'j'])
        >>> _merge_prefix(d, 5); print d
        deque(['abcde', 'fghi', 'j'])

        Strings will be split as necessary to reach the desired size.
        >>> _merge_prefix(d, 7); print d
        deque(['abcdefg', 'hi', 'j'])

        >>> _merge_prefix(d, 3); print d
        deque(['abc', 'defg', 'hi', 'j'])

        >>> _merge_prefix(d, 100); print d
        deque(['abcdefghij'])
        """
    prefix = []
    remaining = size
    while deque and remaining > 0:
        chunk = deque.popleft()
        if len(chunk) > remaining:
            deque.appendleft(chunk[remaining:])
            chunk = chunk[:remaining]
        prefix.append(chunk)
        remaining -= len(chunk)
    deque.appendleft(''.join(prefix))
