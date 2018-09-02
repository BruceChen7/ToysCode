from enum import Enum
class TokenType(Enum):
    Add = 0,
    Minus = 1,
    Multiple = 2,
    Divide = 3,
    MinusEqual = 4,
    AddEqual = 5,
    MultipleEqual = 6,
    DivideEqual = 7,
    Great = 8,
    GreatEqual = 9,
    Less = 10,
    LessEqual = 11,
    NotEqual = 12,
    EqualEqual = 13,
    Bang = 14,
    VAR = 15,
    FUNC = 16,
    IDENTIFIER = 17,
    Assign = 18,
    Num = 19,


class Token:
    def __init__(self, type, value, line_num):
        self.type = type
        self.value = value 
        self.line_num = line_num