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

import logging
import pymongo

import dispositivos
import mensajes
import notificaciones

logging.basicConfig(level=logging.INFO, format="%(asctime)s %(levelname)s %(module)s.%(funcName)s %(message)s")
log = logging.getLogger(__name__)

#
#
#
class Context(object):
    
    def __init__(self, mq):
        """
        Constructor
        """
        self.client = pymongo.MongoClient("mongodb://localhost")
        self.mq = mq
        self.db = self.client.get_database(mq)
        self._dispositivos = []
        
    def close(self):
        """
        Cierre de recursos del contexto
        """
        self.client.close()
        
    def get_dispositivos(self):
        """
        Mantiene una lista de los dispositivos vinculados a la cola
        """
        if len(self._dispositivos) == 0:
            self._dispositivos = dict((d["ID_MOVIL"], d) for d in self.db.dispositivos.find())
        return self._dispositivos
        
#
#
#
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
