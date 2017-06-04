import errno
import select

class IOLoop():
    # Constants from the epoll module
    _EPOLLIN = 0x001
    _EPOLLPRI = 0x002
    _EPOLLOUT = 0x004
    _EPOLLERR = 0x008
    _EPOLLHUP = 0x010
    _EPOLLRDHUP = 0x2000
    _EPOLLONESHOT = (1 << 30)
    _EPOLLET = (1 << 31)

    # Our events map exactly to the epoll events
    NONE = 0
    READ = _EPOLLIN
    WRITE = _EPOLLOUT
    ERROR = _EPOLLERR | _EPOLLHUP | _EPOLLRDHUP

    def __init__(self):
        self._poller = select.epoll()
        self._handler = {}
        self.started = False
        self.stop = False
        # current happening events
        self._events = {}
        self._streams = {}


    def stop(self):
        self.started = True

    @classmethod
    def instance(cls):
        """A singleton pattern
        """
        if not hasattr(cls, "_instance"):
            cls._instance = IOLoop()
        return cls._instance

    def loop(self):
        assert not self.started, " io loop has been started"
        self.started = True
        poll_time = 0.2

        while True:
            try:
                event_pairs = self._poller.poll(poll_time)
            except Exception, e:
                if (getattr(e, 'errno', None) == errno.EINTR or
                        (isinstance(getattr(e, 'args', None), tuple) and
                                 len(e.args) == 2 and e.args[0] == errno.EINTR)):
                    continue
                else:
                    raise

            self._events.update(event_pairs)
            try:
                while self._events:
                    fd, event = self._events.popitem()
                    self._callback(fd, event)
            except Exception, e:
                print e
            if self.stop:
                    return

    def add_handler(self, fd, events, handler):
        events = events | IOLoop.ERROR
        if not self._handler.get(fd):
            self._poller.register(fd, events)
        else:
            self._poller.modify(fd, events)
        self._handler[fd] = handler


    def _callback(self, fd, event, *args, **kargs):
            callback = self._handler[fd]
            callback(fd, event, *args, **kargs)

    def add_stream(self, fd, stream):
        if not self._streams.get(fd):
            self._streams[fd] = stream
            self.add_handler(fd, IOLoop.READ | IOLoop.ERROR, self._handle_events)

    def _handle_events(self, fd, events):
        stream = self._streams.get(fd)

        if stream is not None:
            try:
                if events & IOLoop.READ:
                    self._handle_read(fd)

                if events & IOLoop.WRITE:
                    self._handle_write(fd)

                if events & IOLoop.ERROR:
                    stream.close(fd)

                state = IOLoop.ERROR
                if stream.reading():
                    state = IOLoop.READ | IOLoop.ERROR
                if stream.writing(fd):
                    state = IOLoop.WRITE | IOLoop.ERROR

                if state != stream.get_stream_state():
                    self.update_status(fd, events)


            except:
                # FixMe: Use logger module instead
                print


    def _handle_read(self, fd):
        stream = self._stream.get(fd)
        if stream:
            stream.handle_read(fd)

    def update_status(self, fd, events):
        self._poller.modify(fd, events)

    def _handle_write(self, fd):
        stream = self._stream.get(fd)
        if stream:
            stream.handle_write(fd)