from response import HTTPResponse

class Request():

    def __init__(self, addr, data, iostream):
        self._peer_addr = addr
        # just the whole http request data sent from client
        self._data = data
        self._headers = {}
        self._stream = iostream

    def _parse_headers(self):
        # HTTP request headers end with "\r\n\r\n"
        self._parse_header(self._data, "\r\n\r\n")

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

    def get_method(self):
        return self._method

    def get_path(self):
        return self._path

    def get_version(self):
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
        self._parse_headers()
        r = HTTPResponse(self._stream, self)
        r.response()