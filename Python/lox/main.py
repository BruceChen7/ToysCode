#coding:utf-8
import sys
import os
from lex import Scanner

def main():
    if len(sys.argv) == 2:
        script_file = sys.argv[1]
        file = os.path.join(os.path.abspath(os.curdir), script_file)
        print file
        with open(file, "r") as f:
            content = f.read()
            scanner = Scanner(content)
            if scanner.Parse():
                print "parse right"
            else:
                print "parse error" 

    elif len(sys.argv) == 1:
        raw_input(">")
    else:
        print "python main.py | python main.py '<your script>'"

if __name__ == "__main__":
    main()
