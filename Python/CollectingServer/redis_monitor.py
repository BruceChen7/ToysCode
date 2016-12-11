#!/usr/bio/python
#-*- coding:utf-8 -*-

"""
It's a Python script to collecting redis information
"""


import json
import time
import socket
import re
import sys
import commands
import os
import logging
import logging.config

logger_config_file = sys.path[0] + "/logger.conf"
logging.config.fileConfig(logger_config_file)
logger_name = "root"
logger = logging.getLogger(logger_name)

class RedisStats:
    """
        _redis_cli should be customized
        It's location of redis-cli
    """
    _redis_cli = '/usr/local/bin/redis-cli'
    _stat_regex = re.compile(ur'(\w+):([0-9]+\.?[0-9]*)\r')

    def __init__(self, port='6379', passwd=None, host='127.0.0.1'):
        self._cmd = '%s -h %s -p %s info' % (self._redis_cli, host, port)
        if passwd not in ['', None]:
            self._cmd = '%s -h %s -p %s -a %s info' % (self._redis_cli, host, port, passwd)

    def stats(self):
        ' Return a dict containing redis stats '
        info = commands.getoutput(self._cmd)
        return dict(self._stat_regex.findall(info))


def main():
    """
        Collecting the redis status
    """
    # Get host name
    ip = socket.gethostname()
    timestamp = int(time.time())
    step = 60
    # inst_list = [ i for i in commands.getoutput("find  /etc/ -name 'redis*.conf'" ).split('\n') ]
    insts_list = ['/etc/redis/redis.conf']
    p = []
    monit_keys = [
        ('connected_clients', 'GAUGE'),
        ('blocked_clients', 'GAUGE'),
        ('used_memory', 'GAUGE'),
        ('used_memory_rss', 'GAUGE'),
        ('mem_fragmentation_ratio', 'GAUGE'),
        ('total_commands_processed', 'COUNTER'),
        ('rejected_connections', 'COUNTER'),
        ('expired_keys', 'COUNTER'),
        ('evicted_keys', 'COUNTER'),
        ('keyspace_hits', 'COUNTER'),
        ('keyspace_misses', 'COUNTER'),
        ('keyspace_hit_ratio', 'GAUGE'),
    ]
    for inst in insts_list:
        # Get the port
        port = commands.getoutput("sed -n 's/^port *\([0-9]\{4,5\}\)/\\1/p' %s" % inst)
        # Get the password
        passwd = commands.getoutput("sed -n 's/^requirepass *\([^ ]*\)/\\1/p' %s" % inst)
        metric = "redis"
        endpoint = ip
        tags = 'port=%s' % port

        try:
            conn = RedisStats(port, passwd)
            stats = conn.stats()
        except Exception, e:
            continue

        for key, vtype in monit_keys:
            if key == 'keyspace_hit_ratio':
                try:
                    value = float(stats['keyspace_hits'])/(int(stats['keyspace_hits']) + int(stats['keyspace_misses']))
                except ZeroDivisionError:
                    value = 0
            elif key == 'mem_fragmentation_ratio':
                value = float(stats[key])
            else:
                try:
                    value = int(stats[key])
                except Exception, e:
                    continue
            i = {
                'Metric': '%s.%s' % (metric, key),
                'Endpoint': endpoint,
                'Timestamp': timestamp,
                'Step': step,
                'Value': value,
                'CounterType': vtype,
                'TAGS': tags,
                "MiddWareName": metric
            }
            p.append(i)

    logger.info(json.dumps(p, sort_keys=True, indent=4))

if __name__ == '__main__':
    # Get the `redis-server `
    COMM = 'ps -ef | grep redis-server | grep -v grep | wc -l '
    PROC = commands.getoutput(COMM)
    sys.stdout.flush()

    if int(PROC) < 5 and int(PROC) > 0:
        logger.info("begin to collecting the redis status")
        main()
        