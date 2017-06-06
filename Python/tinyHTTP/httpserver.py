import socket

import errno

from ioloop import IOLoop
from iostream import IOStream

class HTTPServer():
    """It's a class to represent a http server

    """
    def __init__(self, port=8888, ioloop = None):
        self._port = port
        self._ioloop = ioloop or IOLoop.instance()


    def listen(self, backlog = 128):
        """create listen fd which is non-blocking
        """
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        s.setblocking(False)
        s.bind(("", self._port))
        s.listen(backlog)
        self.sock = s
        self._ioloop.add_handler(s.fileno(), IOLoop.READ, self._handle_connect)

    def start(self):
        self._ioloop.loop()

    def _handle_connect(self, fd, event):
        assert fd == self.sock.fileno(), "fd must be listen fd"
        assert event == IOLoop.READ
        while True:
            try:
                connection, address = self.sock.accept() 
                connection.setblocking(False)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
            except socket.error, e:
                if e.args[0] in (errno.EWOULDBLOCK, errno.EAGAIN):
                    return

            stream = IOStream(connection, address)
            self._ioloop.add_stream(connection.fileno(), stream)

