# -*- coding: utf-8 -*-
"""
response.py
~~~~~~~
This module is used to dispatch read/write event for http server
"""
import urllib
import os
import stat
import pystache


class HTTPResponse:
    """It's a class to represent a http response
    """
    ServerString = "Server: toyhttp/0.1\r\n"
    Encoding = {
        "UTF-8": "utf8"
    }

    StatusCode = {
        100: "Continue",
        200: "OK",
        201: "Created",
        202: "Accepted",
        300: "Multiple Choice",
        301: "Moved Permanently",
        302: "Found",
        303: "See Other",
        304: "Not Modified",
        400: "Bad Request",
        401: "Unauthorized",
        402: "Payment Required",
        403: "Payment Required",
        404: "Not Found",
        405: "Method Not Allowed",
        500: "Internal Server Error",
        501: "Not Implemented",
        502: "Bad Gateway",
        503: "Service Unavailable",
        505: "HTTP Version Not Supported"
    }
 
    def read(self, path):
        """
        Read and return the contents of a text file as a unicode string.
        """
        # This function implementation was chosen to be compatible across Python 2/3.
        f = open(path, 'rb')
        # We avoid use of the with keyword for Python 2.4 support.
        try:
            b = f.read()
        finally:
            f.close()
        return b.decode(self.Encoding["UTF-8"])

    def __init__(self, stream, request):
        self._stream = stream
        self._request = request


    def get_header(self, code, des):
        header = self.ServerString
        return "HTTP/1.1 " + code + " " + des + " \r\n" + header + "\r\n\r\n"
    
    def unimplement(self):
        head = self.get_header("501", self.StatusCode[501])
        # read template html
        html = self.read("htdocs/template.html")
        value = {
            "error_code": "501",
            "error_description": self.StatusCode[501]
        }
        html = pystache.render(html, value)
        self._stream.send(head + html)


    def not_found(self):
        assert self._stream is not None
        head = self.get_header("404", self.StatusCode[404])
        html = self.read("htdocs/template.html")
        value = {
            "error_code": "404 " +  self.StatusCode[404],
            "error_description":  "Your request resource is not found"
        }
        html = pystache.render(html, value)
        self._stream.send(head + html)

    def ok_headers(self):
        self._stream.send("HTTP/1.1 200 OK\r\n")
        self._stream.send(HTTPResponse.ServerString)
        self._stream.send("Content-Type: text/html\r\n")
        self._stream.send("\r\n\r\n")

    def server_files(self, absolute_path):
        try:
            fd = open(absolute_path, "r")
            self.ok_headers()
            line = fd.readline()
            while line:
                self._stream.send(line)
                line = fd.readline()
        except IOError:
            self.not_found()
        finally:
            fd.close()

    def cgi_exec(absolute_path, param,header, body):
        pass

    def decode_url(self, path, header):
        encode_type = header.get("CONTENT_TYPE", "UTF-8")
        if encode_type != "UTF-8":
            _, _, charset = encode_type.partition(";")
            _, _, encode_type = charset.partion('=')
        type_name = encode_type.strip()
        type_name = type_name.upper()
        encoding = HTTPResponse.Encoding.get(type_name, "utf8")
        return urllib.unquote(path).decode(encoding)

    def parse_url(self, uri, header):
        """
        parse url like this:
        / -> /index.html
        /home/ -> /home/index.html
        """

        uri = uri.strip()
        absolute_path = "htdocs" + uri

        if uri == '/':
            absolute_path = "htdocs/index.html"
        try:
            absolute_path = self.decode_url(absolute_path, header)
            print absolute_path
            file_stat = os.stat(absolute_path)
            file_mode = file_stat.st_mode
            # If it's is a directory
            if stat.S_ISDIR(file_mode):
                absolute_path.rstrip('/')
                absolute_path = absolute_path.join("/index.html")
            return absolute_path
        except OSError:
            return ""

    def is_exec_file(self, file_name):
        try:
            file_stat = os.stat(file_name)
            mode = file_stat.st_mode

            if stat.S_IXGRP & mode or stat.S_IXOTH & mode or stat.S_IXUSR & mode:
                return True
        except OSError:
            return False

    def response(self):
        assert self._request is not None
        method = self._request.get_method()
        url = self._request.get_path()
        header = self._request.get_header()

        if method == "GET" or  "POST":
            uri, question, param = url.partition('?')
            uri = self.parse_url(uri, header)

            if uri is "":
                self.not_found()
                # FixMe close the stream
                return

            if self.is_exec_file(uri) or question != '':
                body = self._request.get_body()
                self.cgi_exec(url, param, header, body)
            else:
                self.server_files(uri)
        else:
            self.unimplement()
            return
    