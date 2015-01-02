#/usr/bin/python

from socket import *
import sys 

server_host = "localhost"
server_port = 5007

message = [b'Hello Network world']

if len(sys.argv) > 1:
	server_host = sys.argv[1]
	
if len(sys.argv) > 2:
	message = (x.encode() for x in sys.argv[2:])

##### use tcp connection ###
##### create soket  ###
sockobj = socket(AF_INET,SOCK_STREAM)
##### it must be tuple for connect method ####
sockobj.connect((server_host,server_port))

for line in message:
	sockobj.send(line)
	data = sockobj.recv(1024)
	print("client received:",data)

sockobj.close()


	
