'''
Created on 27 nov. 2017

@author: saulario
'''

class ParserGETDRIVERINFO():
    def __init__(self):
        pass
    
    def parse(self, context, message):
        return None
    

class ParserP():
    '''
    classdocs
    '''   

    def __init__(self, mascara):
        '''
        Constructor
        '''
        self._mascara = list(x for x in (mascara))
        self._campos = list(0 for x in range(0, len(self._mascara)))

    def parse(self, context, message):
        self.fields = message.split(',')
        self.retval = {}
        self.retval['medio'] = self.fields[0]
        self.retval['origen'] = int(self.fields[1])
        self.retval['mensaje'] = self.fields[2]
        return self.retval
        
        
def parser_factory(context, message):
    parser = None
    fields = message.split(',')
    tipo = fields[2]
    if tipo.startswith('TDI*P'):
        device = int(fields[1])
        if device in context.get_devices():
            d = context.get_devices()[device]
            parser = ParserP(d['MASK'])
    elif tipo.startswith('TDI*GETDRIVER'):
        parser = ParserGETDRIVERINFO()
    return parser

def parse(context, message):
    retval = None
    parser = parser_factory(context, message);
    if (parser != None):
        retval = parser.parse(context, message);
    return retval;