from httpserver import HTTPServer
import argparse

def parse_command_line():
    """ parse http server command line which can configuration of the server
    """
    parser = argparse.ArgumentParser()
    parser.add_argument('--port', default=8888, type=int,
                        metavar="http server port which default is 8888",
                        help="the port to http server (default: %(default)d)")
    parser.add_argument('--log_level', default="INFO", type=str, choices=["DEBUG", "INFO", "WARN", "FATAL"],
                        metavar="http server logging level")
    parser.add_argument('--log_max_file_size', type=int, default=100 * 1000 * 1000,
                        metavar="max log file size before roll over",
                        help="max log file size (default: 10 * 1000 * 1000)")
    # when use --log_to_stderr, then server can log to stderr
    parser.add_argument('--log_to_stderr', action='store_true',
                        help="whether http server log to server")
    options = parser.parse_args()
    # return someting like dict
    return vars(options)



if __name__ == "__main__":
    options = parse_command_line()
    server = HTTPServer(port = options.get("port"))
    server.listen(64)
    server.start()
