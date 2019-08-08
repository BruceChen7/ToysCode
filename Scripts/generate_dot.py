# -*- coding:utf-8 -*-
#!/usr/bin/env python

import argparse

defautl_conf = "dot.conf"
dot_head = """
digraph structs {
    graph [
        rankdir =  "%s"
    ]

    node [
        fontsize = 16
        fontcolor = black
        shape = "plaintext"
    ]
"""

dot_body = """

"""

def generateDot(lines):
    for line in lines:
        pass

def parseArgs():
    parser = argparse.ArgumentParser()
    parser.add_argument("--config", default="dot.conf", type=str, metavar="dot description file")
    parser.add_argument("--direction", default="LR", type=str, metavar="picture drawing direction")
    args = parser.parse_args()
    return vars(args)

def main():
    args = parseArgs()
    config_file = args.get("config")
    print config_file

    with open(config_file, "r") as f:
        lines = f.readlines()

    print lines

if __name__ == "__main__":
    main()

