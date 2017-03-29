import socket 

def unimplement(conn):
    buf = "HTTP/1.0 501 Method Not Implement\r\n"
    sever_string = "Server: toyhttp/0.1\r\n"
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
        conn.send(buf + sever_string + html) 
    except Exception, e:
        print e

def handleHTTPRequest(conn, addr):
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
            print "method GET"
        else:
            unimplement(conn)
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
