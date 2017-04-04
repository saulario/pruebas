#!/usr/bin/env python
import pika

parameters = pika.URLParameters('amqp://openriot:11111111@192.168.1.250/openriot')
connection = pika.BlockingConnection(parameters)

channel = connection.channel()

channel.exchange_declare(exchange='amq.topic', type='topic', durable=True)

result = channel.queue_declare(queue='keep_alive', durable=True)
queue_name = result.method.queue

def callback(ch, method, properties, body):
	print(" [x] %r:%r" % (method.routing_key, body))

channel.basic_consume(callback,
                      queue=queue_name,
                      no_ack=True)

channel.start_consuming()
