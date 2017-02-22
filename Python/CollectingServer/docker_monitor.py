import sys
import commands
import json
import socket
import time
import logging
import logging.config
from data_push.rabbitmq_push  import push_to_rabbitmq
import urllib2

logger_config_file = sys.path[0] + "/logger.conf"
logging.config.fileConfig(logger_config_file)
logger_name = "root"
logger = logging.getLogger(logger_name)


def getMachineInfoUrl(host, port):
    return "http://" + host + ":" + port  + "/api/v1.3" + "/machine"

def getContainerInfoUrl(host, port):
    return "http://" + host + ":" + port + "/api/v1.3" + "/containers/" 

def getMachineInfo(host, port):
    url = getMachineInfoUrl(host, port) 
    print url
    request = urllib2.Request(url) 
    res = urllib2.urlopen(request) 
    machine_info = json.loads(res.read()) 
    print json.dumps(machine_info, indent=4)

def get_info(host, port, getUrlCB, parseDataCB):
    url = getUrlCB(host, port)
    request = urllib2.Request(url)
    res = urllib2.urlopen(request)
    info = json.loads(res.read())
    print json.dumps(info, indent=4)


def parseMachineInfo():
    pass


def parseContainerInfo():
    pass



def main():
    host = "localhost"
    port = "8080" 
    ip = socket.gethostname()
    get_info(host, port, getMachineInfoUrl, parseMachineInfo)
    logger.info("============ Get container info ======")
    get_info(host, port, getContainerInfoUrl, parseContainerInfo)
    

if __name__ ==  "__main__": 
    command = 'ps -ef | grep cadvisor | wc -l'
    proc = commands.getoutput(command)
    sys.stdout.flush()
    print proc

    if int(proc) > 0 and int(proc) < 5:
        logger.info("begin  to collect docker status ")
        main()

