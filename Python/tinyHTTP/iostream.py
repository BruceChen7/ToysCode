import  collections
import socket
import errno
from ioloop import IOLoop


class IOStream():
    """It's a class to represent socket io stream
    """
    def __init__(self, sock, addr, ioloop=None, max_buffer_size=104857600,
                 max_read_buffer = 4096):
        self.ioloop = ioloop or IOLoop.instance()
        # accept socket fd
        self.sock = sock
        # peer address
        self._addr = addr
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
                if not data:
                    self.close()
                else:
                    self._read_buffer.append(data)
            except socket.error, e:
                if e.args[0] in (errno.EWOULDBLOCK, errno.EAGAIN):
                    return
            except Exception:
                print "something error"
                self.close()
    def handle_write(self, fd):
        while self._write_buffer:
            try:
                if not self._writing:
                    _merge_prefix(self._write_buffer, 128 * 1024)
                num_bytes = self.sock.send(self._write_buffer[0])
                self._write_buffer_frozen = False
                _merge_prefix(self._write_buffer, num_bytes)
                self._write_buffer.popleft()
            except socket.error, e:
                if e.args[0] in (errno.EWOULDBLOCK, errno.EAGAIN):
                    self.writing = True
                    break
                else:
                    print("Write error on %d: %s",
                                    self.sock.fileno(), e)
                    self.close()
                    return

    def get_stream_state(self):
        return self._state

    def close(self):
        pass

def _merge_prefix(self, buffer, size):
        pass
