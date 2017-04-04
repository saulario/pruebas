from comun import *
from model import *

from sqlalchemy.sql.expression import *
from sqlalchemy.sql.functions import max

#---------------------------------------------------------------------------------------------------
#
def borrar_tipo(sesion, tipo, flujo):  
    stmt = delete(Dof).where(Dof.doftip == tipo).where(Dof.dofflu == flujo)
    result = sesion.connection().execute(stmt)

    stmt = delete(Doe).where(Doe.doetip == tipo).where(Doe.doeflu == flujo)
    result = sesion.connection().execute(stmt)
    
    sesion.commit()

#---------------------------------------------------------------------------------------------------
#    
def obtener_dodcod(sesion):    
    dodcod = sesion.query(max(Dod.dodcod)).scalar()
    if (dodcod is None):
        dodcod = 0
    return dodcod



#---------------------------------------------------------------------------------------------------
#     
def inbound_recogida(sesion):
    
    tipo = 1
    flujo = "WE"
    borrar_tipo(sesion, tipo, flujo)
    
    zonas = cargar_zonas(sesion)
    
    doecod = obtener_doecod(sesion)
    dofcod = obtener_dofcod(sesion)
    
    qry = sesion.query(Doc).filter(Doc.docflu == flujo)\
        .order_by(Doc.docrel, Doc.docfec, Doc.docdun, Doc.docorgzon)\
        .limit(10)

    get_token = lambda doc: doc.docrel + ":" + doc.docfec.strftime("%Y%m%d")\
        + ":" + doc.docdun + ":" + doc.docorgzon

    primero = True
    doe = Doe()
    doe.doepes = 0
    doe.doevol = 0
    doe.doecnt = 0
    dofs = list()
    
    token = ""
    for doc in qry.all():
        
        if (primero):
            token = get_token(doc)
            primero = False
            
        print doc.docexp
        if (token != get_token(doc)):
            print "----->", token
            doecod = doecod + 1
            doe.doecod = doecod
            doe.doerel = doc.docrel
            doe.doeexp = doc.docexp
            doe.doetip = 1
            doe.doefec = doc.docfec
            doe.doeorgzon = doc.docorgzon
            doe.doeorgpob = doc.docorgpob
            
            zon = zonas.get(doe.doeorgzon)
            doe.doedeszon = zon.zoncod
            doe.doedespob = zon.zondes
            
            doe.doeflu = doc.docflu
            doe.doefab = doc.docfab
            doe.doedun = doc.docdun
            doe.doepro = doc.docpro
            
            pef = doe.doevol * 250
            if (pef > doe.doepes):
                doe.doepef = pef
            else:
                doe.doepef = doe.doepes
                
            sesion.add(doe)                
                
            for dof in dofs:
                dof.dofdoecod = doe.doecod
                sesion.add(dof)
                
            sesion.commit()
            
            doe = Doe()
            doe.doepes = 0
            doe.doevol = 0
            doe.doecnt = 0
            dofs = list()
        
        doe.doepes = doe.doepes + doc.docpes
        doe.doevol = doe.doevol + doc.docvol
        doe.doecnt = doe.doecnt + 1
        
        dofcod = dofcod + 1
        dof = Dof()
        dof.dofcod = dofcod
        dof.doftip = 1
        dof.doe = doe;
        dof.dofexp = doc.docexp
        dof.dofflu = doc.docflu
        
        dofs.append(dof)
        
        token = get_token(doc)
        
        #filas = filas + 1
        #if ((filas % 1000) == 0):
        #    sesion.commit()

    if (len(dofs) != 0):
        doecod = doecod + 1
        doe.doecod = doecod
        sesion.add(doe)                

        for dof in dofs:
            dof.dofdoecod = doe.doecod
            sesion.add(dof)
        
        sesion.commit()

#---------------------------------------------------------------------------------------------------
#
def inbound_manipulacion(sesion):    
    borrar_tipo(sesion, 0, "WE")

def inbound_transporte(sesion):
    borrar_tipo(sesion, 2, "WE")

def retorno_transporte(sesion):
    borrar_tipo(sesion, -2, "WA")
    
def retorno_manipulacion(sesion):
    borrar_tipo(sesion, 0, "WA")

def retorno_entrega(sesion):
    borrar_tipo(sesion, -1, "WA")   

def todo(sesion):
    inbound_recogida(sesion)
    inbound_manipulacion(sesion)
    inbound_transporte(sesion)
    retorno_transporte(sesion)
    retorno_manipulacion(sesion)
    retorno_entrega(sesion)
