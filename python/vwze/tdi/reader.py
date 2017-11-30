import logging
import pymongo

import dispositivos
import mensajes
import notificaciones

logging.basicConfig(level=logging.INFO, format="%(asctime)s %(levelname)s %(module)s.%(funcName)s %(message)s")
log = logging.getLogger(__name__)

class Context(object):
    
    def __init__(self, mq):
        self.client = pymongo.MongoClient("mongodb://localhost")
        self.mq = mq
        self.db = self.client.get_database(mq)
        self._devices = []
        
    def close(self):
        self.client.close()
        
    def get_devices(self):
        if len(self._devices) == 0:
            self._devices = dict((d["ID_MOVIL"], d) for d in self.db.devices.find())
        return self._devices
        

if __name__ == "__main__":
    """
    Main module
    """

    log.info("-----> Inicio")
    
    context = Context("SESETEST")
    context.base = "/home/saulario/tdi"  # directorio base
    
    dispositivos.procesar(context)
    notificaciones.procesar(context)
    mensajes.procesar(context)
    
    context.close()
    
    log.info("<----- Fin")
