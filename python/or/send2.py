#!/usr/bin/env python
import pika

parameters = pika.URLParameters('amqp://openriot:11111111@192.168.1.250/openriot')
connection = pika.BlockingConnection(parameters)


channel = connection.channel()

channel.queue_declare(queue='data1', durable=True)

theBody ="MH+0:0+1299de51-d9c8-4b0a-97d7-3208546864b5++7386f6a9-72c4-4906-8eec-3dcfd71ae39d+20170710T091245.123\'\n"
theBody+="GP+42.1457075:0.2161982:4:20170710T091245.123:::115+UM220\'\n"
theBody+="GP+42.1457075:0.2161982:4:20170710T091245.123\'\n"
theBody+="MT+4+7386f6a9-72c4-4906-8eec-3dcfd71ae39d\'"

#ok = channel.basic_publish(exchange='',
#		routing_key='hello',
#        body=theBody)

ok = channel.basic_publish(exchange = '', routing_key = 'data1', body = theBody)



if (ok) :
	print("Mensaje enviado")
connection.close()

