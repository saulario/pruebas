import pika
import time

channel = None

def my_open(connection):
    print("my_open")
    
def on_connected(connection):
    channel = connection.channel(on_channel_open)
    
def on_channel_open(my_channel):
    global channel
    channel = my_channel
    channel.exchange_declare(exchange='amq.topic', type='topic', durable=True)
    
    
    
    
    
if __name__ == "__main__":

    parameters = pika.URLParameters('amqp://openriot:11111111@192.168.1.250/openriot')
    connection = pika.SelectConnection(parameters, on_connected)
    
    print("inicio")
    
    time.sleep(10)
    connection.close()
    
    print("terminado")
    
    


def viejo_main():
    parameters = pika.URLParameters('amqp://openriot:11111111@192.168.1.250/openriot')
    connection = pika.BlockingConnection(parameters)

    channel = connection.channel()

    channel.exchange_declare(exchange='amq.topic', type='topic', durable=True)

    theBody="MH+0:0+1299de51-d9c8-4b0a-97d7-3208546864b5++7386f6a9-72c4-4906-8eec-3dcfd71ae39d+20170710T091245.123\'\n"
    theBody+="GP+42.1457075:0.2161982:4:20170710T091245.123:::115+UM220\'\n"
    theBody+="GP+42.1457075:0.2161982:4:20170710T091245.123\'\n"
    theBody+="MT+4+7386f6a9-72c4-4906-8eec-3dcfd71ae39d\'"

    ok = channel.basic_publish(exchange='amq.topic',
		routing_key='test',
		body=theBody)


    count = 0
    while count < 3:
            ok = channel.basic_publish(exchange='amq.topic',
                            routing_key='ka',
                            body=theBody)
            count += 1

    count = 0
    while count < 6:
            ok = channel.basic_publish(exchange='amq.topic',
                            routing_key='dd',
                            body=theBody)
            count += 1

    connection.close()
    
    
    
