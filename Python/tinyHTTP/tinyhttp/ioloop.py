# -*- coding: utf-8 -*-
"""
ioloop.py
~~~~~~~
This module is used to dispatch read/write event for http server
"""
import errno
import select
import logging

class IOLoop():
    """A class which encapsulate epoll module
    """
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
        self._started = False
        self._stop = False
        # current happening events
        self._events = {}
        self._streams = {}


    def stop(self):
        self._started = True

    @classmethod
    def instance(cls):
        """A singleton pattern
        """
        if not hasattr(cls, "_instance"):
            cls._instance = IOLoop()
        return cls._instance

    def loop(self):
        """Event loop

        """
        assert not self._started, " io loop has been started"
        self._started = True
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
                 logging.info("something error to pop events")

            if self._stop:
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
        """ Add a new iostream to a ioloop
        """
        if not self._streams.get(fd):
            self._streams[fd] = stream
            self.add_handler(fd, IOLoop.READ | IOLoop.ERROR, self._handle_events)

    def _handle_events(self, fd, events):
        stream = self._streams.get(fd)

        if stream is not None:
            try:
                if events & IOLoop.READ:
                    self._handle_read(fd)

                stream = self._streams.get(fd)
                if stream is None:
                    return

                if events & IOLoop.WRITE:
                    self._handle_write(fd)

                stream = self._streams.get(fd)
                if stream is None:
                    return

                if events & IOLoop.ERROR:
                    stream.close()
                # Next time the events to be watched
                state = IOLoop.ERROR

                if stream.reading():
                    state = IOLoop.READ | IOLoop.ERROR
                if stream.writing():
                    state = IOLoop.WRITE | IOLoop.ERROR

                if state != stream.get_stream_state():
                    self.update_status(fd, state)
            except Exception, e:
                logging.error(e)

    def unregister(self, fd):
        self._poller.unregister(fd)
        self._streams.pop(fd, None)
        self._handler.pop(fd, None)

    def _handle_read(self, fd):
        """
        read from the fd
        """
        stream = self._streams.get(fd)

        if stream:
            stream.handle_read(fd)
        else:
            logging.info("%d fd has been closed", fd)

    def update_status(self, fd, events):
        stream = self._streams.get(fd)
        if stream:
            self._poller.modify(fd, events)
            stream.set_status(events)

    def _handle_write(self, fd):
        stream = self._streams.get(fd)
        if stream:
            stream.handle_write(fd)
        else:
            logging.info("connection has been closed")