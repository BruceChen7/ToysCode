import os
import sys
import socket
import re
import io

from . import __version__ 


# convert dictionary to a list sequence 
def dict_to_sequence(d):
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
	if hasattr(o,'getvalue'):
		return len(o.getvalue()) 
