#!/usr/bin/python
#-*- coding:utf-8 -*-

"""
It's python script to collect RabbitMQ status
"""

import json
import socket
import time
import urllib2
import base64


STEP = 60
HOST = socket.gethostname()
USER = {"user_name": "guest", "pass": "guest"}

def get_overview_url(host):
    """
    Get the whole Overview url
    """
    return "http://%s:15672/api/overview" %host

def get_all_queue_url(host):
    """
    Get the whole queues url
    """
    return "http://%s:15672/api/queue" %host


def get_all_user_url(host):
    """
    Get the whole user url
    """
    return "http://%s:15672/api/users" %host

def get_user_info(host, data, send_data, timestamp):
    """
    Get the user info
    """
    if timestamp is 0:
        timestamp = int(time.time())

    for user in data:
        for key in ["name", "tags"]:
            user_data = dict()
            user_data["endpoint"] = host
            user_data['timestamp'] = timestamp
            user_data['step'] = STEP
            user_data['counterType'] = "string"
            user_data['metric'] = 'rabbitmq.user.%s' % key
            user_data['tags'] = 'name=%s' % (user[key])
            user_data['value'] = user[key]
            send_data.append(user_data)

def get_info(get_url_cb, send_data, timestamp, parse_data_cb):
    """
    It's a wrappe  to get all rabbitmq info
    """
    url = get_url_cb(HOST)
    print url
    request = urllib2.Request(url)
    account = USER["user_name"] + ":" + (USER["pass"])
    print account
    base64string = base64.b64encode(account)
    request.add_header("Authorization", "Basic %s" % base64string)
    result = urllib2.urlopen(request)
    data = json.loads(result.read())
    print data
    parse_data_cb(HOST, data, send_data, timestamp)

def main():
    """
        Collect Rabbit Information
    """
    timestamp = int(time.time())
    send_data = []
    get_info(get_all_user_url, send_data, timestamp, get_user_info)
    print send_data

if __name__ == "__main__":
    main()
