
"""
main.py this module is the entry of the http server
"""
import argparse
import sys
import logging
import logging.handlers
import time

from tinyhttp.httpserver import HTTPServer
try:
    import curses
except:
    curses = None


def parse_command_line():
    """ parse http server command line which can configuration of the server
    """
    parser = argparse.ArgumentParser()
    parser.add_argument('--port', default=8888, type=int,
                        metavar="http server port which default is 8888",
                        help="the port to http server (default: %(default)d)")
    parser.add_argument('--log_level', default="INFO", type=str, choices=["DEBUG", "INFO", "WARNING", "ERROR"],
                        metavar="http server logging level")
    parser.add_argument('--log_max_file_size', type=int, default=100 * 1000 * 1000,
                        metavar="max log file size before roll over",
                        help="max log file size (default: 10 * 1000 * 1000)")
    parser.add_argument("--log_file_prefix", type=str, default="/tmp/log", metavar="PATH",
       help=("Path prefix for log files. "))
    # when use --log_to_stderr, then server can log to stderr
    parser.add_argument('--log_to_stderr', action='store_false',
                        help="whether http server log to server")
    parser.add_argument("--log_file_num_backups", type=int, default=10,
                        help="number of log files to keep")
    options = parser.parse_args()
    # return someting like dict
    return vars(options)


# modified from tornado.options.py
def enable_pretty_logging(options):
    """ config logging options
    """
    root_logger = logging.getLogger()
    root_logger.setLevel(options.get("log_level").upper())
    # log file prefix
    file = options.get("log_file_prefix")
    max_bytes = options.get("log_max_file_size")
    backup_count = options.get("log_file_num_backups")

    # set log in a file
    if options.get("log_file_prefix"):
        channel = logging.handlers.RotatingFileHandler(
            filename=file,
            maxBytes=max_bytes,
            backupCount=backup_count)
        channel.setFormatter(_LogFormatter(color=False))
        root_logger.addHandler(channel)

    log_to_stderr = options.get("log_to_stderr")
    
    if (log_to_stderr or
            (log_to_stderr is None and not root_logger.handlers)):
        # Set up color if we are in a tty and curses is installed
        color = False
        if curses and sys.stderr.isatty():
            try:
                curses.setupterm()
                if curses.tigetnum("colors") > 0:
                    color = True
            except:
                pass
        channel = logging.StreamHandler()
        channel.setFormatter(_LogFormatter(color=color))
        root_logger.addHandler(channel)

class _LogFormatter(logging.Formatter):
    def __init__(self, color, *args, **kwargs):
        logging.Formatter.__init__(self, *args, **kwargs)
        self._color = color
        if color:
            fg_color = curses.tigetstr("setaf") or curses.tigetstr("setf") or ""
            self._colors = {
                logging.DEBUG: curses.tparm(fg_color, 4), # Blue
                logging.INFO: curses.tparm(fg_color, 2), # Green
                logging.WARNING: curses.tparm(fg_color, 3), # Yellow
                logging.ERROR: curses.tparm(fg_color, 1), # Red
            }
            self._normal = curses.tigetstr("sgr0")

    def format(self, record):
        try:
            record.message = record.getMessage()
        except Exception, e:
            record.message = "Bad message (%r): %r" % (e, record.__dict__)
        record.asctime = time.strftime(
            "%y%m%d %H:%M:%S", self.converter(record.created))
        prefix = '[%(levelname)1.1s %(asctime)s %(module)s:%(lineno)d]' % \
            record.__dict__
        if self._color:
            prefix = (self._colors.get(record.levelno, self._normal) +
                      prefix + self._normal)
        formatted = prefix + " " + record.message
        if record.exc_info:
            if not record.exc_text:
                record.exc_text = self.formatException(record.exc_info)
        if record.exc_text:
            formatted = formatted.rstrip() + "\n" + record.exc_text
        return formatted.replace("\n", "\n    ")


if __name__ == "__main__":
    options = parse_command_line()
    server = HTTPServer(port = options.get("port"))
    enable_pretty_logging(options)
    server.listen(64)
    server.start()
