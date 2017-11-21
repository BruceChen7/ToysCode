# coding:utf-8
#!/usr/bin/env python
import random
import base64

class Password:
    def __init__(self, key, password):
        self.key = key
        self.password = password
        
    def getKey(self):
        return self.key
    
    def getPassword(self):
        return self.password

    @staticmethod
    def generateKey():
       random.seed()
       key = bytearray(range(256))
       random.shuffle(key)
       return key

    @staticmethod
    def generatePassword(key):
        password = []
        for i in range(len(key)):
            password.append(chr(key[i]))
        return base64.b64encode(''.join(password))

    @staticmethod
    def decodePassword(password):
        return bytearray(base64.b64decode(password))