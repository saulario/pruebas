import logging

log = logging.getLogger(__name__)

class ParserGETDRIVERINFO(object):
    def __init__(self):
        pass
    
    def parse(self, context, message):
        return None
    

class ParserP(object):
    """
    classdocs
    """   

    def __init__(self, mascara):
        """
        Constructor
        """
        self._mascara = list(x for x in (mascara))
        self._campos = list(0 for x in range(0, len(self._mascara)))

    def parse(self, context, message):
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
            parser = ParserP(d["MASK"])
    elif tipo.startswith("TDI*GETDRIVER"):
        parser = ParserGETDRIVERINFO()
        
    log.info("<----- Fin")
    return parser

def parse(context, message):
    retval = None
    parser = parser_factory(context, message);
    if (parser != None):
        retval = parser.parse(context, message);
    return retval;

