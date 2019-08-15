# -*- coding:utf-8 -*-
#!/usr/bin/env python

import argparse

defautl_conf = "dot.conf"
node_num = 1

dot_head = """
digraph structs {0}
    graph [
        rankdir =  {1}
    ]

    node [
        fontsize = 16
        fontcolor = black
        shape = "plaintext"
    ]
    {2}
{3}
"""

dot_body = """
    {0}[label=<
        <TABLE BORDER="0" CELLBORDER="1" CELLSPACING="0">
            {1}
        </TABLE>>];
"""


def getPortStr(port_num):
    return "port_" + str(port_num)

class SubNode(object):
    def __init__(self, child_node_name, port = "", using_port = False, gray_background = False):
        self.child_node_name = child_node_name
        self.using_port = using_port
        self.gray_background = gray_background
        if self.using_port:
            self.port_num = port

    def toDot(self):
        dot_script = "<TR> <TD"
        if self.using_port:
            dot_script += " PORT = '" + getPortStr(self.port_num) + "' "

        if self.gray_background:
            dot_script += " bgcolor = 'gray45' "
        dot_script += ">" + self.child_node_name + " </TD></TR>\n"
        return dot_script


class Node(object):
    def __init__(self, node_name, child_node_list, port = 0):
        self.node_name =  node_name
        self.child_node = child_node_list
        self.port = port

    @classmethod
    def createNode(cls, line):
        line = line.strip("\r\n\t")
        node_list = line.split("|")
        node_name = ""
        child_node_list = []

        for i in range(len(node_list)):
            if len(node_list[i]) == 0:
                continue

            split_res = node_list[i].split(":")
            child_node_name = split_res[0]
            port = 0
            using_port = False;
            using_gray_background = False

            # 第一个节点默认使用灰色的背景
            if i == 0:
                using_gray_background = True
                node_name = child_node_name.strip()
                # 按照空格区分
                strip_space_node_name = node_name.split(" ")
                node_name = strip_space_node_name[0]

            if len(split_res) > 1:
                port = split_res[1]
                using_port = True

            if len(split_res) > 2:
                gray_background = split_res[2]

                if gray_background.strip() == "*":
                    using_gray_background = True

            child_node = SubNode(child_node_name, port, using_port, using_gray_background)
            child_node_list.append(child_node)

        return Node(node_name, child_node_list)

    def toDot(self):
        child_node_dot = ""
        global node_num

        for child in self.child_node:
            child_node_dot += child.toDot();

        res = ""
        res += dot_body.format(self.node_name + str(node_num), child_node_dot)
        node_num += 1
        return res



def generateDot(lines, direction):
    node_list = []
    for line in lines:
        node = Node.createNode(line)
        node_list.append(node)

    nodes_str = ""

    for node in node_list:
        nodes_str += node.toDot()

    #print nodes_str
    dot_str = dot_head.format('{', direction, nodes_str, "}")
    print dot_str

def parseArgs():
    parser = argparse.ArgumentParser()
    parser.add_argument("--config", default="dot.conf", type=str, metavar="dot description file")
    parser.add_argument("--direction", default="LR", type=str, metavar="picture drawing direction")
    args = parser.parse_args()
    return vars(args)

def main():
    args = parseArgs()
    config_file = args.get("config")
    #print config_file

    with open(config_file, "r") as f:
        lines = f.readlines()

    generateDot(lines, args.get("direction"))

if __name__ == "__main__":
    main()

