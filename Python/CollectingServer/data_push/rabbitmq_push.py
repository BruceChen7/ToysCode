#!/usr/bin/python
#-*- coding:utf-8 -*-

"""
It's a file to push all collecting data to RabbitMQ
"""
import pika
from pika.spec import BasicProperties

def push_to_rabbitmq(host="", data=""):
    """
        push data to RabbitMQ
    """
    if not data:
        return
    if  host in ["", None]:
        host = "localhost"
    connection = pika.BlockingConnection(pika.ConnectionParameters(host=host))
    channel = connection.channel()
    channel.exchange_declare(exchange="topic", type="topic", durable=True)
    channel.basic_publish(exchange="topic",
                          routing_key="redis",
                          body=data,
                          properties=BasicProperties(content_type="application/json"))
    connection.close()
