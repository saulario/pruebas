from model import *

#---------------------------------------------------------------------------------------------------
#
def obtener_doecod(sesion):    
    doecod = sesion.query(max(Doe.doecod)).scalar()
    if (doecod is None):
        doecod = 0
    return doecod

#---------------------------------------------------------------------------------------------------
#
def obtener_dofcod(sesion):    
    dofcod = sesion.query(max(Dof.dofcod)).scalar()
    if (dofcod is None):
        dofcod = 0
    return dofcod

#---------------------------------------------------------------------------------------------------
#    
def cargar_zonas(sesion):    
    codigos = dict()
    for d in sesion.query(Zoo).order_by(Zoo.zoopcp).all():
        codigos[d.zoopcp] = d.zon
    return codigos
