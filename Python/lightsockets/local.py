# coding:utf-8
#!/usr/bin/env python
import os
import logging

from lightsockets.config import Config
from lightsockets.command import parseCommandLine
from lightsockets.password import Password
from lightsockets.securesock import SecureServer

if __name__ == "__main__":
    logging.basicConfig(level=logging.DEBUG)

    if os.path.exists(Config.CONFIG_PATH):
        config = Config.readConfig()
        key = []

        if config.password:
            logging.info("read config file suceed")
            key = list(Password.decodePassword(config.password))
        else:
            logging.info("generate key")
            key = Password.generateKey()
            password = Password.getPassword(key)
            config.password = password
            config.saveConfig()
        s = SecureServer(config.local_port, config.remote_addr, config.remote_port, key)
        s.start()

    else:
        default_config = parseCommandLine()
