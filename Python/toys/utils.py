import os
import sys
import socket
import collections
import re
from urllib2 import parse_http_list
import io

# from . import __version__ 


# convert dictionary to a list sequence 
def dict_to_list(d):
	if hasattr(d,'items'):
		d = d.items()	
	return d


# according to different object 
# obtain different size of object
def super_len(o):
	if hasattr(o,'__len__'):
		return len(o)
	#any class which has len member
	if hasattr(o,'len'):
		return o.len
	if hasattr(o,'getvalue'):
		return len(o.getvalue())
	if hasattr(o,'fileno'):
		try:
			fileno = o.fileno()
		except io.UnsupportedOperation:
			pass
		else:
			return os.fstat(fileno) 
	if hasattr(o,'getvalue'):
		return len(o.getvalue()) 

def from_key_val_list(value):
	if value == None:
		return None
	if isinstance(value,(str,bytes,bool,int)):
		raise ValueError('can not encode objects that are not 2-tuples')
	return OrderedDict(value)

def to_key_val_list(value):
	"""


	"""
	if value is None:
		return None 
	if isinstance(value,(str,bytes,bool,int)):
		raise ValueError('can not encode objects that are not 2-tuples')
	if isinstance(value,collections.Mapping):
		value = value.items()
	return list(value) 
	
def unquote_value(value,is_filename):
	if value and value[0] == value[-1] == '"':
		value = value[1:-1]
		if not is_filename or value[:2] != '\\\\':
			return value.replace('\\\\','\\').replace('\\"','"') 
	return value

	
def parse_header_to_dict(value): 

	"""
	>>> d = parse_header_to_dict('foo = "hello world",bar = "BruceChen"')
	>>> type(d) is dict
	True 
	>>> sorted(d.items())
	[('bar','BruceChen'),('foo','hello world')]
	"""

	result  = dict() 
	for item in parse_http_list(value):
		if '=' not in item:
			result[item] = None
			continue 
		name,value = item.split('=',1)

		if value[:1] == value[-1:] == '"':
			value = value[1:-1]

		result[name] = value 
	return result

if __name__ == "__main__":
	x = {'one':1,"two":2}
	print dict_to_list(x)
	print super_len(x) 
	print to_key_val_list(x)
	print parse_header_to_dict('foo = "hello world"')
