import json
import pymongo

def load_devices():
    devs = json.load(open('/home/saulario/tmp/tdi/infoTarget.txt'))
    
    client = pymongo.MongoClient('mongodb://localhost')
    db = client.get_database('tdi')
    devices = db.devices
    for dev in (devs['INFO_DEVICE']):
        dev['ID_MOVIL'] = int(dev['ID_MOVIL'])
        devices.insert_one(dev)
        
    for dev in devices.find():
        print dev
    
    client.close()
    
    return devs
    