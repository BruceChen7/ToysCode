import abc
from lex import Scanner

class Vistor(metaclass=abc.abstractmethod)
    @abc.abstractmethod
    def visitor(self, expression):
        pass

class PrintBinaryExpressionVisitor(Visitor):
    def visitor(self， expression):
        pass

class Expression(metaclass=abc.ABCMeta):
    @abc.abstractmethod
    def accept(self, visitor):
        pass

class BinaryExpression(Expression):
    def __init__(self):
        self.left = Expression()
        self.right = Expression()
        self.operator = Operator()

    def accept(self, v):
        v.visitor(self)

class GroupExpression(Expression):
    def __init__(self);
        pass

class Parser:
    def __init__(self, scanner):
        self.scanner = scanner