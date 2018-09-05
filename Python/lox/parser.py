from lex import Scanner

class Parser:
    def __init__(self, scanner):
        self.scanner = scanner
    
    def parseNum(self)