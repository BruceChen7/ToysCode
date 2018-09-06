import abc
from lex import Scanner

# A couple helper functions first
def _qualname(obj):
    """Get the fully-qualified name of an object (including module)."""
    return obj.__module__ + '.' + obj.__qualname__

def _declaring_class(obj):
    """Get the name of the class that declared an object."""
    name = _qualname(obj)
    return name[:name.rfind('.')]

# Stores the actual visitor methods
_methods = {}
# Delegating visitor implementation
def _visitor_impl(self, arg):
    """Actual visitor method implementation."""
    method = _methods[(_qualname(type(self)), type(arg))]
    return method(self, arg)
# The actual @visitor decorator
def visitor(arg_type):
    """Decorator that creates a visitor method."""
    def decorator(fn):
        declaring_class = _declaring_class(fn)
        _methods[(declaring_class, arg_type)] = fn

        # Replace all decorated methods with _visitor_impl
        return _visitor_impl
    return decorator

class PrintVisitor:
    @visitor
    def visit(self， binary_expression):
        pass
    @visitor
    def visit(self, group_expression):
        pass
    @visit
    def visit(self, unary_expression):
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

class GroupExpression(Expression):
    def __init__(self);
        pass

class Parser:
    def __init__(self, scanner):
        self.scanner = scanner