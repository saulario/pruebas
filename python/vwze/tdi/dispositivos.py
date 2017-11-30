import json
import logging

log = logging.getLogger(__name__)

def procesar(context):
    '''Procesamiento de la descarga de dispositivos asociados a la cola de mensajes. Renueva el contenido
        de la tabla en cada procesamiento para tener la ultima informacion de las mascaras
    '''
    log.info('-----> Inicio')
    fuente = "%s/data/it_%s.txt" % (context.base, context.mq)
    try:
        dispositivos = json.load(open(fuente))
    except IOError:
        log.warn('<----- No se ha encontrado archivo de dispositivos, saliendo...')
        return
    
    dispositivosCol = context.db.get_collection('dispositivos')
    dispositivosCol.delete_many({})
       
    key = 'INFO_DEVICE'
    if key in dispositivos:
        for dispositivo in dispositivos[key]:
            dispositivo['ID_MOVIL'] = int(dispositivo['ID_MOVIL'])
            dispositivosCol.insert_one(dispositivo)
            
    log.info('<----- Fin')