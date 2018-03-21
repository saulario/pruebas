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
import parser

log = logging.getLogger(__name__)

#
#
#
def procesar(context):
    log.info("-----> Inicio")
    
    fuente = "%s/data/mq_%s.txt" % (context.base, context.mq)
    
    try:
        mensajes = open(fuente)
    except IOError:
        log.warn("<----- No se ha encontrado archivo de mensajes, saliendo...")
        return  
    
    for buffer in mensajes:
        procesar_mensaje(context, buffer)
        
    mensajes.close()  
    
    log.info("<----- Fin")
    
#
#
#
def enviar_mq(context, id):    
    pass
#
#
#    
def procesar_mensaje(context, buffer):
    log.info("-----> Inicio")
    log.info("\t(buffer): %s " % buffer)
    
    mensaje = parser.parse(context, buffer)
    if not mensaje is None:
        id = context.db.mensajes.insert_one(mensaje).inserted_id
        enviar_mq(context, id)
    
    log.info("<----- Fin")