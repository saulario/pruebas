#!/usr/bin/python
#    Copyright (C) from 2017 onwards Saul Correas Subias (saul dot correas at gmail dot com)
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.

import datetime
import logging

import gis

log = logging.getLogger(__name__)

#
#
#
class Mensaje(object):
    """
    Clase base para todos los mensajes recibidos
    """
    def __init__(self, id_movil, registro):
        self.id_movil = id_movil
        self.registro = registro
    
#
# Parser nulo
#
class ParserNULL(object):
    """
    OTROS
    """
    
    def parse(self, mensaje):
        return None

#
# TDI*GETDRIVERINFO
#
class ParserGETDRIVERINFO(object):
    """
    TDI*GETDRIVERINFO
    """
    
    def __init(self, context):
        self._context = context
    
    def parse(self, message):
        return None   

#
# TDI*P
#
class ParserP(object):
    """
    TDI *P
    """
    cc = None   

    def __init__(self, context, dispositivo):
        """
        Constructor
        """
        self._context = context
        self._dispositivo = dispositivo
        self._mascara = list(x for x in (dispositivo["MASK"]))
        
    def _eliminar_campos(self, cc):
        cc.pop(0)
        cc.pop(0) 
        
    def _bit01(self, mm, campos, mensaje):
        current = int(mm.pop(0))
        if (not current):
            return
        campos.pop(0)
         
    def _bit02(self, mm, campos, mensaje):
        current = int(mm.pop(0))
        if (not current):
            return
        self._aux = ("%s %s" % (campos.pop(0), campos.pop(0)))
        mensaje["dateTime"] = datetime.datetime.strptime(self._aux, "%d/%m/%Y %H:%M:%S")
        
    def _bit03(self, mm, campos, mensaje):
        current = int(mm.pop(0))
        if (not current):
            return
        self._aux = ("%s %s" % (campos.pop(0), campos.pop(0)))
        mensaje["dateTime1"] = datetime.datetime.strptime(self._aux, "%d/%m/%Y %H:%M:%S")

    def _bit04(self, mm, campos, mensaje):
        current = int(mm.pop(0))
        if (not current):
            return
        self._datosGPS = {}
        
        self._datosGPS["position"] = gis.convertir_coordenada_GPS(campos.pop(0), campos.pop(0))
        self._datosGPS["altitude"] = float(campos.pop(0))
        self._datosGPS["speed"] = float(campos.pop(0))
        self._datosGPS["bearing"] = int(campos.pop(0))
        self._datosGPS["satellites"] = int(campos.pop(0))
        self._datosGPS["kilometers"] = float(campos.pop(0))
        self._datosGPS["digitalInputs"] = int(campos.pop(0), 16)
        mensaje["GPSData"] = self._datosGPS

    def parse(self, buffer):
        self._campos = buffer.split(",")
        self._mensaje = {}
        self._mensaje["idMovil"] = self._dispositivo["ID_MOVIL"]
        self._mensaje["registration"] = self._dispositivo["REGISTRATION"]
        self._mensaje["message"] = "TDI*P"
        
        self._mm = self._mascara       
        self._eliminar_campos(self._campos)
        self._bit01(self._mm, self._campos, self._mensaje)
        self._bit02(self._mm, self._campos, self._mensaje)
        self._bit03(self._mm, self._campos, self._mensaje)
        self._bit04(self._mm, self._campos, self._mensaje)
        
        
        
        
        
        return self._mensaje
        
#
#
#       
def parser_factory(context, buffer):
    """Instancia el Parser en funcion del tipo de mensaje recibido
    """
    log.info("-----> Inicio")
    log.info("\t(buffer): %s" % buffer)
    
    parser = ParserNULL()
    campos = buffer.split(",")
    
    if len(campos) < 3:
        log.warn("<----- Mensaje aparentemente incorrecto, saliendo...")
        return parser
    
    id_dev = int(campos[1])
    if not id_dev in context.get_dispositivos():
        log.warn("<----- Dispositivo %d no encontrado, saliendo..." % id_dev)
        return parser
        
    dispositivo = context.get_dispositivos()[id_dev]
    tipo = campos[2]
    
    if tipo.startswith("TDI*P"):
        parser = ParserP(context, dispositivo)
    elif tipo.startswith("TDI*GETDRIVER"):
        parser = ParserGETDRIVERINFO(context)
        
    log.info("<----- Fin")
    return parser

#
#
#
def parse(context, buffer):
    """Parsea el buffer y devuelve un mensaje para insertar en base de datos
    """
    log.info("-----> Inicio")
    log.info("\t(buffer): %s" % buffer)
    
    mensaje = parser_factory(context, buffer).parse(buffer);
        
    log.info("<----- Fin")        
    return mensaje


