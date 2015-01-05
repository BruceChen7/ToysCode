#usr/bin/python
from socket import *
import os,time,sys

my_host = ''
my_port = 5007

def now():
	return time.ctime(time.time())

active_child = []
sockobj = socket(AF_INET,SOCK_STREAM)
sockobj.bind((my_host,my_port))
sockobj.listen(5)


#### retrieve the child process resource ###
def reap_child():

	while active_child:
		pid,stat = os.waitpid(0,os.WNOHANG)
		
		if not pid:
			break
		active_child.remove(pid)

def Handle_client(connection):
	time.sleep(5)

	while True:
		data = connection.recv(1024)
		if not data:
			break
		reply =  'Echo=>%s at %s' %(data,now())
		connection.send(reply.encode()) 
	connection.close()
	os._exit(0)

def dispatcher():

	while True:
		connection,address = sockobj.accept()
		print('server connect by',address)
		print('at ',now())

		child_pid  = os.fork()

                ## child process to deal with 
		if child_pid == 0:
			Handle_client(connection)
		else:
			active_child.append(child_pid)

if __name__ == "__main__":
	dispatcher()





