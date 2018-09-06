import sys
from token import Token
from token import TokenType

class Scanner:
    def __init__(self, script = None):
        if script:
            self.script = script
        self.tokens = list()
        self.parse_token_ways = {
            "+": self.parsePlus,
            "-": self.parseMinus,
            "!": self.parseBang,
            "=": self.parseEqual,
            "*": self.parseMultiplication,
            "/": self.parseDivison,
            "\n": self.parseNewline,
            " ": self.parseBlank,
            #"\r": self.parseBlank
        }
        self.cur_pos =  0
        self.cur_line = 0
        self.has_error = False
    
    def isEndOfLine(self):
        return self.cur_pos >= len(self.script)

    def peek(self):
        if self.isEndOfLine():
            return "\n"
        else:
            return self.script[self.cur_pos + 1]

    def consume(self, num):
        self.cur_pos += num

    def parsePlus(self):
        if self.peek() == "=":
            t = Token(TokenType.AddEqual, "+=", self.cur_line)
            self.tokens.append(t)
            self.consume(2)
        else:
            t = Token(TokenType.Add, "+", self.cur_line)
            self.tokens.append(t)
            self.consume(1)

    
    def parseMinus(self):
        if self.peek() == "=":
            t = Token(TokenType.MinusEqual, "-=", self.cur_line)
            self.tokens.append(t)
            consume(2)
        else:
            t = Token(TokenType.Minus, "-", self.cur_line)
            self.tokens.append(t)
            consume(1)
        
    def parseNewline(self):
        self.cur_pos += 1
        self.cur_line += 1

    def parseBang(self):
        if self.peek() == "=":
            t = Token(TokenType.NotEqual, "!=", self.cur_line)
            self.tokens.append(t)
            self.consume(2)
        else:
            t = Token(TokenType.Bang, "!", self.cur_line)
            self.tokens.append(t)
            self.consume(1)

    def parseEqual(self):
        if self.peek() == "=":
            t = Token(TokenType.EqualEqual, "==", self.cur_line)
            self.tokens.append(t)
            self.consume(2)
        else:
            t = Token(TokenType.Assign, "=", self.cur_line)
            self.tokens.append(t)
            self.consume(1)

    def parseMultiplication(self):
        if self.peek() == "=":
            t = Token(TokenType.MultipleEqual, "*=", self.cur_line)
            self.tokens.append(t)
            self.consume(2)
        else:
            t = Token(TokenType.Multiple, "*", self.cur_line)
            self.tokens.append(t)
            self.consume(1)
       
    def parseDivison(self):
        if self.peek() == "=":
            t = Token(TokenType.MultipleEqual, "/=", self.cur_line)
            self.tokens.append(t)
            self.consume(2)
        else:
            t = Token(TokenType.Multiple, "/", self.cur_line)
            self.tokens.append(t)
            self.consume(1)
    
    def parseNum(self):
        begin_pos = self.cur_pos
        while not self.isEndOfLine():
            if self.script[self.cur_pos].isdigit():
                self.cur_pos += 1
            elif self.script[self.cur_pos] == '.' and self.peek().isdigit():
                self.cur_pos +=1
            else:
                num_str = self.script[begin_pos : self.cur_pos]
                t = Token(TokenType.Num, num_str, self.cur_line)
                self.tokens.append(t)
                break

        if self.isEndOfLine():
            num_str = self.script[begin_pos : len(self.script)]
            t = Token(TokenType.Num, num_str, self.cur_line)
            self.tokens.append(t)

    def parseBlank(self):
        while self.cur_pos < len(self.script):
            if self.script[self.cur_pos] == " " or self.script[self.cur_pos] == "\r":
                self.cur_pos += 1
            else:
                break
    
    def parseIdentifier(self):
        pass

    def parseDefault(self):
        if self.cur_pos < len(self.script):
            if self.script[self.cur_pos].isdigit():
                self.parseNum()
            elif self.script[self.cur_pos].isalpha():
                self.parseIdentifier()

    def Parse(self):
        while self.cur_pos < len(self.script):
            self.parse_token_ways.get(self.script[self.cur_pos], self.parseDefault)()
        
        self.GetTokenList()
        return not self.has_error
    
    def GetTokenList(self):
        for i in range(len(self.tokens)):
            print self.tokens[i].type, ",value ", self.tokens[i].value