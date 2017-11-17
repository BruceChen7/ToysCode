# coding:utf-8
#!/usr/bin/env python
import random
import base64

class Password:
    def __init__(self):
        random.seed()
        self.password = bytearray(range(256))
        random.shuffle(self.password)
        pass_str = []
        
        for i in range(len(self.password)):
            pass_str.append(chr(self.password[i]))
        self.pass_str = base64.b64encode(''.join(pass_str))
        
    def getKey(self):
        return self.password