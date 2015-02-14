import os
import sys
import socket
import collections
import re
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
		except:
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

if __name__ == "__main__":
	x = {'one':1,"two":2}
	print dict_to_list(x)
	print super_len(x)


	

