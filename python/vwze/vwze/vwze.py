from datetime import *
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from sqlalchemy.sql.expression import *

import calcular
import generar

from model import *

#if __name__ == "__main__":
    
#    engine = create_engine("mysql://vwze:1111@localhost/vwze")
#    Session = sessionmaker(bind = engine)
#    sesion = Session()
    
#    t = datetime.now()
#    generar.todo(sesion)
    #calcular.todo(sesion)    
#    print datetime.now() - t
    
#    sesion.close()
    