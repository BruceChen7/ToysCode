# coding:utf-8
#!/usr/bin/env python
import random
import base64

class Password:
    def __init__(self):
        random.seed()
        password = list(range(256))
        
        self.password = []
        self.password_str = ""
        random.shuffle(password)

        for i in range(len(password)):
            self.password.append(bytes(password[i]))
        bytes_pass = bytearray(password) 
        
    def getKey(self):
        return self.password