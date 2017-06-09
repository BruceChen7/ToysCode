from httpserver import HTTPServer

if __name__ == "__main__":
    server = HTTPServer()
    server.enable_logging()
    server.listen(64)
    server.start()
