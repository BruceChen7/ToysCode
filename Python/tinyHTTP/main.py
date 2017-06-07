from httpserver import HTTPServer

if __name__ == "__main__":
    server = HTTPServer()
    server.listen(64)
    server.start()
