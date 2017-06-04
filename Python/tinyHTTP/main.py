import socket 
import os
import stat
import urllib

from httpserver import HTTPServer

_server_string = "Server: toyhttp/0.1\r\n"
_encoding = {
    "UTF-8": "utf8"
}

def unimplement(conn):
    buf = "HTTP/1.0 501 Method Not Implement\r\n"
    html = """
    <html>
        <head>
            <title>
                Method not Implemented 
            </title>
        </head>
        <body>
            <p>
                HTTP request not method not supported
            </p>
        </body>
    </html>
    """
    try:
        conn.send(buf + _server_string + html) 
    except Exception, e:
        print e


def notFound(conn):
    buf = "HTTP/1.0 404 NOT FOUND \r\n"
    conn.send(buf)
    conn.send(_server_string)
    buf = "Content-Type: text/html\r\n"
    conn.send(buf)
    buf = "\r\n"
    conn.send(buf)
    buf = "<html><title>Not Found</title>\r\n"
    conn.send(buf)
    buf = "<body><p>the server could not fulfill your request because the request you specified"
    conn.send(buf)
    buf = "is unavailable or nonexistent </p> \r\n"
    conn.send(buf)
    buf = "</body></html>\r\n"
    conn.send(buf)

def okHeaders(conn):
    conn.send("HTTP/1.1 200 OK\r\n")
    conn.send(_server_string)
    conn.send("Content-Type: text/html\r\n")
    conn.send("\r\n")

def serveFiles(absolute_path, conn):
    try: 
        fd = open(absolute_path, "r")
        okHeaders(conn)
        line = fd.readline()
        while line:
            conn.send(line) 
            line = fd.readline()
    except IOError: 
        notFound(conn)
    finally:
        fd.close()
        
def cgiExec(absolute_path, param, conn, header, body):
    pass

def handleGetRequest(uri, conn): 
    pass


def decodeURL(path, header):
    encode_type = header.get("CONTENT_TYPE", "UTF-8")
    if encode_type != "UTF-8":
        _, _, charset = encode_type.partition(";")
        _, _, encode_type = charset.partion('=')
    type_name = encode_type.strip()
    type_name = type_name.upper()
    encoding = _encoding.get(type_name, "utf8")
    return urllib.unquote(path).decode(encoding)

"""
parse url like this: 
/ -> /index.html
/home/ -> /home/index.html 
"""
def parseURL(uri, header):
    uri = uri.strip()
    absolute_path = "htdocs" + uri

    if uri == '/':
        absolute_path = "htdocs/index.html"
    print absolute_path
    try:
        absolute_path = decodeURL(absolute_path, header)
        print absolute_path
        file_stat = os.stat(absolute_path)
        file_mode = file_stat.st_mode
        # If it's is a directory
        if stat.S_ISDIR(file_mode):
            absolute_path.rstrip('/')
            absolute_path = absolute_path.join("/index.html")
        print absolute_path
        return absolute_path
    except OSError:
        return ""


def isExecFile(file_name):
    try:
        file_stat = os.stat(file_name)
        mode = file_stat.st_mode

        if stat.S_IXGRP & mode or stat.S_IXOTH & mode or stat.S_IXUSR & mode:
            return True
    except OSError:
        return False


def parseHTTPRequest(line_list):
    """
    divide http request into three parts
    """
    assert len(line_list) != 0
    first_line = line_list[0]
    first = first_line.split(' ')
    header = dict()
    body = ""

    for i in range(1, len(line_list)):
        line = line_list[i]

        if line not in ["\r\n", "\n", ""]:
            key, _, value = line.partition(':')
            header[key.upper()] = value.strip("\r\n")
        else:
            body = line_list[i+1:]

    return (first, header, body)

def handleHTTPRequest(conn, addr):
    """
    handle http request
    """
    print "Accept request from ", addr
    lines = conn.recv(4096)
    line_list = lines.splitlines()
    http_first_header, header, body = parseHTTPRequest(line_list)

    if len(http_first_header) != 3:
        conn.close()
        return
    else:
        method = http_first_header[0].upper()
        if method == "GET" or method == "POST":
            url = http_first_header[1]
            uri, question, param = url.partition('?')
            uri = parseURL(uri, header)

            if uri is "":
                notFound(conn)
                conn.close()
                return

            if isExecFile(uri) or question != '':
                cgiExec(url, param, conn, header, body)
                conn.close()
            else:
                serveFiles(uri, conn)
                conn.close()
        else:
            unimplement(conn)
            conn.close()
            return

if __name__ == "__main__":
    server = HTTPServer()
    server.listen(64)
    server.start()
