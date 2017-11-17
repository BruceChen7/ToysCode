# coding:utf-8
#!/usr/bin/env python

import argparse
import os

def parseCommandLine():
    """ parse http server command line which can configuration of the server
    """
    parser = argparse.ArgumentParser()
    parser.add_argument('--local_port', default=7488, type=int,
                        metavar="local  proxy port which default is 7488",
                        help="the port to local proxy (default: %(default)d)")

    parser.add_argument('--remote_port', type=int, default=7489,
                        metavar="remote server port which default is 7489",
                        help="the port to remote proxy  server (default: %(default)d)")

    config_path = os.environ["HOME"] + "/.lightsockets"
    parser.add_argument("--config_path", type=str, default=config_path, 
                        metavar="config file path",
                        help="config file path you specify")

    default_remote_addr = "127.0.0.1"
    default_local_addr = "127.0.0.1"

    parser.add_argument('--local_addr', type=str, default=default_local_addr,
                        metavar="local proxy ip address which default is 127.0.0.1",
                        help="the port to remote proxy  server (default: %(default)d)")

    parser.add_argument('--remote_addr', type=str, default=default_remote_addr,
                        metavar="remote  proxy server port which default is 7489",
                        help="the port to remote proxy  server (default: %(default)d)")

   
    options = parser.parse_args()
    # return someting like dict
    return vars(options)