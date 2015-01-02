#/usr/bin/python
import sys 
from socket import *

my_ip_address = ''
listen_port = 5007

def echoServer():
    sockobj = socket(AF_INET,SOCK_STREAM)
    sockobj.bind((my_ip_address,listen_port))
    sockobj.listen(5)
    
    while True:
        connection,address = sockobj.accept()
        print('server connection by ',address)

        while True:
            data = connection.recv(1024)

            if not data:
                break
            connection.send(b'Echo->'+data);

        connection.close()



if __name__ == "__main__":
    echoServer()








