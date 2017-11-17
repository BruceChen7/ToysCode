# coding:utf-8
#!/usr/bin/env python
import os
import logging

from lightsockets.config import Config
from lightsockets.command import parseCommandLine
from lightsockets.password import Password

if __name__ == "__main__":
    if os.path.exists(Config.CONFIG_PATH):
        config = Config.readConfig()
        if config.password:
            logging.info("read config file suceed")
        else:
            logging.info("generate key")
            p = Password()
            config.password = p.password_str
            config.saveConfig()
    else:
        default_config = parseCommandLine()
