# coding: utf-8
from sqlalchemy import BigInteger, Column, Date, DateTime, Float, ForeignKey, Integer, Numeric, String, text
from sqlalchemy.orm import relationship
from sqlalchemy.ext.declarative import declarative_base


Base = declarative_base()
metadata = Base.metadata


class Auftrage(Base):
    __tablename__ = 'auftrage'

    codigo = Column(BigInteger, primary_key=True, server_default=text("'0'"))
    auftragsnummer = Column(String(20), nullable=False, index=True)
    transportid = Column(Integer)
    datum = Column(DateTime)
    wewa = Column(String(80))
    werk = Column(String(80))
    relevanz = Column(String(80))
    gebiet = Column(String(80))
    transportbenne = Column(String(80), nullable=False)
    senderlocation = Column(String(80))
    empfangerlocation = Column(String(80))
    menge = Column(Float(asdecimal=True))


class Bewertung(Base):
    __tablename__ = 'bewertung'

    datum = Column(DateTime)
    auftragsnummer = Column(String(20), primary_key=True)
    relevanz = Column(String(80))
    wewa = Column(String(80))
    gebiet = Column(String(80))
    senderlocation = Column(String(80))
    empfangerlocation = Column(String(80))
    werk = Column(String(80))
    transportiste = Column(String(80))
    szenario = Column(String(80))
    menge = Column(Float(asdecimal=True))
    berechnetes = Column(Float(asdecimal=True))
    kosten = Column(Float(asdecimal=True))
    sammelgut = Column(Float(asdecimal=True))
    sammelgut_diesel = Column(Float(asdecimal=True))
    umschlag = Column(Float(asdecimal=True))
    hauptlauf = Column(Float(asdecimal=True))
    hauptlauf_diesel = Column(Float(asdecimal=True))
    peso = Column(Numeric(13, 2))
    volumen = Column(Numeric(13, 4))


class Doc(Base):
    __tablename__ = 'doc'

    doccod = Column(BigInteger, primary_key=True, server_default=text("'0'"))
    docrel = Column(String(20), nullable=False, server_default=text("''"))
    docexp = Column(ForeignKey(u'bewertung.auftragsnummer'), nullable=False, index=True, server_default=text("''"))
    docfec = Column(Date, nullable=False, server_default=text("'0001-01-01'"))
    docorgzon = Column(String(10), nullable=False, server_default=text("''"))
    docorgpob = Column(String(80), nullable=False, server_default=text("''"))
    docdeszon = Column(String(10), nullable=False, server_default=text("''"))
    docdespob = Column(String(80), nullable=False, server_default=text("''"))
    docflu = Column(String(5), nullable=False, server_default=text("''"))
    docfab = Column(String(20))
    docdun = Column(String(80))
    docpro = Column(String(80), nullable=False, server_default=text("''"))
    dockcc = Column(String(10), nullable=False, server_default=text("''"))
    docpes = Column(Numeric(13, 4), nullable=False, server_default=text("'0.0000'"))
    docvol = Column(Numeric(13, 4), nullable=False, server_default=text("'0.0000'"))
    docpef = Column(Numeric(13, 4), nullable=False, server_default=text("'0.0000'"))

    bewertung = relationship(u'Bewertung')


class Doc1(Base):
    __tablename__ = 'doc1'

    doccod = Column(BigInteger, primary_key=True, server_default=text("'0'"))
    docrel = Column(String(20), nullable=False, server_default=text("''"))
    docexp = Column(String(20), nullable=False, index=True, server_default=text("''"))
    docfec = Column(Date, nullable=False, server_default=text("'0001-01-01'"))
    docorgzon = Column(String(10), nullable=False, server_default=text("''"))
    docorgpob = Column(String(80), nullable=False, server_default=text("''"))
    docdeszon = Column(String(10), nullable=False, server_default=text("''"))
    docdespob = Column(String(80), nullable=False, server_default=text("''"))
    docflu = Column(String(5), nullable=False, server_default=text("''"))
    docfab = Column(String(20))
    docdun = Column(String(80))
    docpro = Column(String(80), nullable=False, server_default=text("''"))
    dockcc = Column(String(10), nullable=False, server_default=text("''"))
    docpes = Column(Numeric(13, 4), nullable=False, server_default=text("'0.0000'"))
    docvol = Column(Numeric(13, 4), nullable=False, server_default=text("'0.0000'"))
    docpef = Column(Numeric(13, 4), nullable=False, server_default=text("'0.0000'"))


class Dod(Base):
    __tablename__ = 'dod'

    dodcod = Column(BigInteger, primary_key=True, server_default=text("'0'"))
    dodrel = Column(String(20), nullable=False, server_default=text("''"))
    dodexp = Column(ForeignKey(u'bewertung.auftragsnummer'), nullable=False, index=True, server_default=text("''"))
    dodtip = Column(Integer, nullable=False, server_default=text("'0'"))
    dodfec = Column(Date, nullable=False, server_default=text("'0001-01-01'"))
    dodorgzon = Column(String(10), nullable=False, server_default=text("''"))
    dodorgpob = Column(String(80), nullable=False, server_default=text("''"))
    doddeszon = Column(String(10), nullable=False, server_default=text("''"))
    doddespob = Column(String(80), nullable=False, server_default=text("''"))
    dodflu = Column(String(5), nullable=False, server_default=text("''"))
    dodfab = Column(String(20))
    doddun = Column(String(80))
    dodpro = Column(String(80), nullable=False, server_default=text("''"))
    dodpes = Column(Numeric(13, 4), nullable=False, server_default=text("'0.0000'"))
    dodvol = Column(Numeric(13, 4), nullable=False, server_default=text("'0.0000'"))
    dodpef = Column(Numeric(13, 4), nullable=False, server_default=text("'0.0000'"))

    bewertung = relationship(u'Bewertung')


class Doe(Base):
    __tablename__ = 'doe'

    doecod = Column(BigInteger, primary_key=True, server_default=text("'0'"))
    doetip = Column(Integer, nullable=False, server_default=text("'0'"))
    doefec = Column(Date, nullable=False, server_default=text("'0001-01-01'"))
    doeorgzon = Column(String(10), nullable=False, server_default=text("''"))
    doeorgpob = Column(String(80), nullable=False, server_default=text("''"))
    doedeszon = Column(String(10), nullable=False, server_default=text("''"))
    doedespob = Column(String(80), nullable=False, server_default=text("''"))
    doeflu = Column(String(5), nullable=False, server_default=text("''"))
    doeexp = Column(String(20), nullable=False, server_default=text("''"))
    doedun = Column(String(80))
    doepro = Column(String(80), nullable=False, server_default=text("''"))
    doepes = Column(Numeric(13, 4), nullable=False, server_default=text("'0.0000'"))
    doevol = Column(Numeric(13, 4), nullable=False, server_default=text("'0.0000'"))
    doepef = Column(Numeric(13, 4), nullable=False, server_default=text("'0.0000'"))
    doecnt = Column(Integer, nullable=False, server_default=text("'0'"))
    doepun = Column(Numeric(13, 4), nullable=False, server_default=text("'0.0000'"))
    doetot = Column(Numeric(13, 2), nullable=False, server_default=text("'0.00'"))


class Dof(Base):
    __tablename__ = 'dof'

    dofcod = Column(BigInteger, primary_key=True, server_default=text("'0'"))
    doftip = Column(Integer, nullable=False, server_default=text("'0'"))
    dofdoecod = Column(ForeignKey(u'doe.doecod'), nullable=False, index=True, server_default=text("'0'"))
    dofexp = Column(String(20), nullable=False, index=True, server_default=text("''"))
    dofflu = Column(String(5), nullable=False, server_default=text("''"))

    doe = relationship(u'Doe')


class Pro(Base):
    __tablename__ = 'pro'

    produn = Column(String(20), primary_key=True, server_default=text("''"))
    proraz = Column(String(80), nullable=False, server_default=text("''"))


class Rfc(Base):
    __tablename__ = 'rfc'

    rfccod = Column(BigInteger, primary_key=True, server_default=text("'0'"))
    rfcrul = Column(String(40), nullable=False, server_default=text("''"))
    rfcmin = Column(Numeric(13, 2), nullable=False, server_default=text("'0.00'"))
    rfckmt = Column(Integer, nullable=False, server_default=text("'0'"))
    rfczon = Column(String(10), nullable=False, server_default=text("''"))


class Rfd(Base):
    __tablename__ = 'rfd'

    rfdcod = Column(BigInteger, primary_key=True, server_default=text("'0'"))
    rfdrfccod = Column(ForeignKey(u'rfc.rfccod'), nullable=False, index=True, server_default=text("'0'"))
    rfdmin = Column(Numeric(13, 2), nullable=False, server_default=text("'0.00'"))
    rfdmef = Column(Numeric(13, 2), nullable=False, server_default=text("'0.00'"))
    rfdpun = Column(Numeric(13, 2), nullable=False, server_default=text("'0.00'"))

    rfc = relationship(u'Rfc')


class Zon(Base):
    __tablename__ = 'zon'

    zoncod = Column(String(10), primary_key=True, server_default=text("''"))
    zondes = Column(String(40), nullable=False, server_default=text("''"))
    zonman = Column(Numeric(13, 4), nullable=False, server_default=text("'0.0000'"))
    zontte = Column(Numeric(13, 4), nullable=False, server_default=text("'0.0000'"))


class Zoo(Base):
    __tablename__ = 'zoo'

    zoocod = Column(BigInteger, primary_key=True, server_default=text("'0'"))
    zoozoncod = Column(ForeignKey(u'zon.zoncod'), nullable=False, index=True, server_default=text("''"))
    zoopcp = Column(String(10), nullable=False, server_default=text("''"))

    zon = relationship(u'Zon')
