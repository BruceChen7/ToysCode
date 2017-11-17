# coding:utf-8
#!/usr/bin/env python

"""It's a module to encode or decode data
"""
class Cipher():
    def __init__(self, encode_key, decode_key):
        self.encode_key = encode_key
        self.decode_key = decode_key
    
    def encode(self, data):
        encoded_data = []
        for i in range(len(data)):
            v = data[i];
            encoded_data.append(self.encode_key[v])
        return bytearray(encoded_data)
            
    def decode(self, data):
        decoded_data = []
        for i in range(len(data)):
            v = data[i]
            decoded_data.append(self.decode_key[v])
        return bytearray(decoded_data)


    @staticmethod
    def newCiper(password):
        assert len(password) == 256
        encode_key = []
        decode_key = []

        for i in range(len(password)):
            v = password[i]
            encode_key[i] = v
            decode_key[v] = i
        return Cipher(encode_key, decode_key)


