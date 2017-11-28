import pymongo

import devices
import Parser

class Context:
    def __init__(self):
        self.client = pymongo.MongoClient('mongodb://localhost')
        self.db = self.client.get_database('tdi')
        self._devices = []
        
    def close(self):
        self.client.close()
        
    def get_devices(self):
        if len(self._devices) == 0:
            self._devices = dict((d['ID_MOVIL'], d) for d in self.db.devices.find())
        return self._devices
        


if __name__ == '__main__':
    
    context = Context()
    collection = context.db.get_collection('messages')
    
    ff = open('/home/saulario/tmp/tdi/multipullTarget.txt')
    for line in ff:
        data = Parser.parse(context, line)
        if not data is None:
            collection.insert_one(data)
       

    context.close()
           

    