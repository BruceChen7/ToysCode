# -*- coding: utf-8 -*-
from tinyhttp.response import HTTPResponse

class Request():
    """It's a class to represent a http request
    """
    def __init__(self, addr, data, iostream):
        self._peer_addr = addr
        # just the whole http request data sent from client
        self._data = data
        self._headers = {}
        self._stream = iostream
        self._is_full_request = True
        self._body = ""
        self._method = None
        self._path = "/"
        self._version = "1.0"

    def _parse_headers(self):
        # HTTP request headers end with "\r\n\r\n"
        return self._parse_header(self._data, "\r\n\r\n")

    # If data is enough, return True
    # else return False
    def _parse_header(self, data, delimiter):
        end_of_header = data.find(delimiter)

        if end_of_header != -1:
            pos = data.find("\r\n")
            start_line = data[:pos]
            self._body = data[end_of_header:].strip("\r\n")
            try:
                self._method, self._path, self._version = start_line.split(" ")
            except ValueError:
                print ("Not a http request")
                # FixMe close a connection
            if not self._version.startswith("HTTP/"):
                print ("Not corre")
                # FixMe close a connection
            self._parse_header_field(data[pos:])
            return True
        else:
            # There is no enough data which can't be constructed as a http request
            self._is_full_request = False
            # enable next round reading event
            self._stream.enable_reading()
            return False

    def is_full_request(self):
        """whether the reqeust is complete
        """
        return self._is_full_request

    def get_method(self):
        return self._method

    def get_path(self):
        return self._path

    def get_version(self):
        """ get HTTP version
        """
        return self._version

    def get_header(self):
        # FixMe: Make a deep copy is good design
        return self._headers

    def get_body(self):
        return self._body 

    def _parse_header_field(self, data):
        header_list = data.splitlines()

        for h in header_list:
            if h:
                key, _, value = h.partition(':')
                self._headers[key] = value

    def response(self):
        if self._parse_headers():
            r = HTTPResponse(self._stream, self)
            r.response()
        else:
            # FixMe
            pass