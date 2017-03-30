import socket 
import os

_server_string = "Server: toyhttp/0.1\r\n"
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
    buf = "<body><p>the server could not fulfill your ruquest because the request you specified"
    conn.send(buf)
    buf = "is unavailable or nonexistent </p> \r\n"
    conn.send(buf)
    buf = "</body></html>\r\n"
    conn.send(buf)


def handleGetRequest(uri, conn): 
    uri = uri.strip()
    absolute_path = "htdocs" + uri 
    if uri == '/':
        absolute_path = "htdocs/index.html"
    try:
        file_stat = os.stat(absolute_path)
    except OSError:
        notFound(conn)


def handleHTTPRequest(conn, addr):
    print "Accept request from ", addr
    lines = conn.recv(4096)
    line_list = lines.splitlines()
    if len(line_list) == 0:
        conn.close()
        return
    first_line = line_list[0]
    http_first_header = first_line.split(' ')

    if(len(http_first_header) != 3):
        pass
    else:
        method = http_first_header[0].upper()
        if method == "GET" or method == "POST":
            url = http_first_header[1]
            uri, question, param = url.partition('?')
            if question is '':
                handleGetRequest(uri, conn)
            else:
                pass 
        else:
            unimplement(conn)
    conn.close()

if __name__ == "__main__":
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind(("", 8888))
    s.listen(5)
    while True:
        conn, addr = s.accept()
        handleHTTPRequest(conn, addr)
