from comun import *
from model import *

from sqlalchemy.sql.expression import delete

def borrar_dods(sesion):
    stmt = delete(Dod)
    result = sesion.connection().execute(stmt)
    sesion.commit()

def generar_wa(sesion, doc):
    pass

def generar_we(sesion, doc):
    pass

def todo(sesion):
    borrar_dods(sesion)
    for doc in sesion.query(Doc).limit(1000).all():
        if ("WA" == doc.docflu):
            generar_wa(sesion, doc)
        elif ("WE" == doc.docflu):
            generar_we(sesion, doc)
        else:
            print "Documento %s no reconocido" % doc.docexp
