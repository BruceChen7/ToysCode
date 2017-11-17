# coding:utf-8
#!/usr/bin/env python
"""It's a module to represent local proxy' and sever's settings
"""

import os.path
import json

class Config():
    """ Config class
    """
    CONFIG_PATH = os.path.join(os.environ['HOME'], '.lightsockets')
    def __init__(self, local_addr='127.0.0.1', local_port="7488", remote_addr='127.0.0.1', remote_port="7489", password=''):
        self.local_port = local_port
        self.local_addr = local_addr
        self.remote_addr = remote_addr
        self.remote_port = remote_port
        self.password = password

    @staticmethod
    def readConfig():
        with open(Config.CONFIG_PATH) as config_data:
            data = json.load(config_data)
            remote_addr = data["remote_addr"]
            remote_port = data['remote_port']
            local_port = data['local_port']
            local_addr = data['local_addr']
            password = data['password']
            config = Config(local_addr, local_port, remote_addr, remote_port, password)
            return config
    def saveConfig(self):
        data = {
            "remote_addr": self.remote_addr,
            "remote_port": self.remote_port,
            "local_addr": self.local_addr,
            "local_port": self.local_port,
            "password": self.password
        }
        with open(Config.CONFIG_PATH, 'w') as fp:
           fp.write(json.dumps(data, indent=4, encoding='utf-8'))