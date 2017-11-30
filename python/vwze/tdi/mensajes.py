import logging

import Parser


log = logging.getLogger(__name__)

def procesar(context):
    """Procesamiento de los mensajes de la cola
    """
    log.info("-----> Inicio")
    
    fuente = "%s/data/mq_%s.txt" % (context.base, context.mq)
    
    try:
        mensajes = open(fuente)
    except IOError:
        log.warn("<----- No se ha encontrado archivo de mensajes, saliendo...")
        return  
    
    for mensaje in mensajes:
        procesar_mensaje(context, mensaje)
        
    mensajes.close()  
    
    log.info("<----- Fin")
    
def procesar_mensaje(context, mensaje):
    """Procesado de un mensaje _Individual
    """
    log.info("-----> Inicio")
    log.info("\t(mensaje): %s " % mensaje)
    
    entity = Parser.parse(context, mensaje)
    
    log.info("<----- Fin")