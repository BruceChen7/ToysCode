#!/usr/bin/python
#-*- coding:utf-8 -*-

"""
It's a file to push all collecting data to RabbitMQ
"""
import pika

def push_to_rabbitmq(host="", port=4369, data=""):
    """
        push data to RabbitMQ
    """
    if not data:
        return
    if  host in ["", None]:
        host = "localhost"
    connection = pika.BlockingConnection(pika.ConnectionParameters(host=host))
    channel = connection.channel()
    channel.exchange_declare(exchange="topic", type="topic")
    # FixMe: json data to be sent
    channel.basic_publish(exchange="topic",
                          routing_key="redis",
                          body = data)
    connection.close()
