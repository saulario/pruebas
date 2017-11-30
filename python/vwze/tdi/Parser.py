import logging

log = logging.getLogger(__name__)

class ParserNULL(object):
    
    def parse(self, mensaje):
        return None

class ParserGETDRIVERINFO(object):
    
    def __init(self, context):
        self._context = context
    
    def parse(self, message):
        return None   

class ParserP(object):
    """
    classdocs
    """   

    def __init__(self, context, mascara):
        """
        Constructor
        """
        self._context = context
        self._mascara = list(x for x in (mascara))
        self._campos = list(0 for x in range(0, len(self._mascara)))

    def parse(self, message):
        self.campos = message.split(",")
        self.retval = {}
        self.retval["medio"] = self.campos[0]
        self.retval["origen"] = int(self.campos[1])
        self.retval["mensaje"] = self.campos[2]
        return self.retval
        
        
def parser_factory(context, mensaje):
    """Instancia el Parser en funcion del tipo de mensaje recibido
    """
    log.info("-----> Inicio")
    log.info("\t(message): %s" % mensaje)
    
    parser = None
    campos = mensaje.split(",")
    tipo = campos[2]
    
    if tipo.startswith("TDI*P"):
        dispositivo = int(campos[1])
        if dispositivo in context.get_devices():
            d = context.get_devices()[dispositivo]
            parser = ParserP(context, d["MASK"])
        else:
            parser = ParserNULL()
    elif tipo.startswith("TDI*GETDRIVER"):
        parser = ParserGETDRIVERINFO(context)
    else:
        parser = ParserNULL()
        
    log.info("<----- Fin")
    return parser

def parse(context, mensaje):
    """Parsea el mensaje y devuelve un objeto para insertar en base de datos
    """
    log.info("-----> Inicio")
    log.info("\t(message): %s" % mensaje)
    
    retval = parser_factory(context, mensaje).parse(mensaje);
        
    log.info("<----- Fin")        
    return retval;

