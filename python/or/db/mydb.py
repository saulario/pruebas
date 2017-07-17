# coding: utf-8
from sqlalchemy import BigInteger, Column, ForeignKey, SmallInteger, String, text
from sqlalchemy.orm import relationship
from sqlalchemy.ext.declarative import declarative_base


Base = declarative_base()
metadata = Base.metadata


class Cli(Base):
    __tablename__ = 'cli'

    clicod = Column(BigInteger, primary_key=True, server_default=text("'0'"))
    cliraz = Column(String(40), nullable=False, server_default=text("''"))


class Cto(Base):
    __tablename__ = 'cto'

    version = Column(BigInteger, nullable=False, server_default=text("'0'"))
    ctocod = Column(String(5), primary_key=True, server_default=text("''"))
    ctodes = Column(String(80), nullable=False, server_default=text("''"))
    ctoest = Column(SmallInteger, nullable=False, server_default=text("'0'"))


class Cyp(Base):
    __tablename__ = 'cyp'

    version = Column(BigInteger, nullable=False, server_default=text("'0'"))
    cypcod = Column(BigInteger, primary_key=True, server_default=text("'0'"))
    cypraz = Column(String(80), nullable=False, server_default=text("''"))
    cypidf = Column(String(20), nullable=False, server_default=text("''"))
    cyptkr = Column(String(5), nullable=False, server_default=text("''"))


class Emp(Base):
    __tablename__ = 'emp'

    version = Column(BigInteger, nullable=False, server_default=text("'0'"))
    empcod = Column(BigInteger, primary_key=True, server_default=text("'0'"))
    empraz = Column(String(80), nullable=False, server_default=text("''"))
    empidf = Column(String(20), nullable=False, server_default=text("''"))


class Seq(Base):
    __tablename__ = 'seq'

    version = Column(BigInteger, nullable=False, server_default=text("'0'"))
    seqcod = Column(String(20), primary_key=True, server_default=text("''"))
    seqdes = Column(String(80), nullable=False, server_default=text("''"))
    segnxt = Column(BigInteger, nullable=False, server_default=text("'0'"))


class Tca(Base):
    __tablename__ = 'tca'

    version = Column(BigInteger, nullable=False, server_default=text("'0'"))
    tcacod = Column(BigInteger, primary_key=True, server_default=text("'0'"))
    tcaloc = Column(String(20), nullable=False, server_default=text("''"))
    tcacypcod = Column(ForeignKey(u'cyp.cypcod'), nullable=False, index=True, server_default=text("'0'"))
    tcacypraz = Column(String(80), nullable=False, server_default=text("''"))
    tcacypidf = Column(String(20), nullable=False, server_default=text("''"))
    tcacyptkr = Column(String(5), nullable=False, server_default=text("''"))
    tcateocod = Column(ForeignKey(u'teo.teocod'), nullable=False, index=True, server_default=text("''"))

    cyp = relationship(u'Cyp')
    teo = relationship(u'Teo')


class Tea(Base):
    __tablename__ = 'tea'

    version = Column(BigInteger, nullable=False, server_default=text("'0'"))
    teacod = Column(String(5), primary_key=True, server_default=text("''"))
    teades = Column(String(80), nullable=False, server_default=text("''"))
    teadef = Column(SmallInteger, nullable=False, server_default=text("'0'"))


class Teo(Base):
    __tablename__ = 'teo'

    version = Column(BigInteger, nullable=False, server_default=text("'0'"))
    teocod = Column(String(5), primary_key=True, server_default=text("''"))
    teodes = Column(String(80), nullable=False, server_default=text("''"))
    teodef = Column(SmallInteger, nullable=False, server_default=text("'0'"))


class Tta(Base):
    __tablename__ = 'tta'

    version = Column(BigInteger, nullable=False, server_default=text("'0'"))
    ttacod = Column(BigInteger, primary_key=True, server_default=text("'0'"))
    ttaloc = Column(String(20), nullable=False, server_default=text("''"))
    ttacypcod = Column(ForeignKey(u'cyp.cypcod'), nullable=False, index=True, server_default=text("'0'"))
    ttacypraz = Column(String(80), nullable=False, server_default=text("''"))
    ttacypidf = Column(String(20), nullable=False, server_default=text("''"))
    ttacyptkr = Column(String(5), nullable=False, server_default=text("''"))
    ttateocod = Column(ForeignKey(u'teo.teocod'), nullable=False, index=True, server_default=text("''"))

    cyp = relationship(u'Cyp')
    teo = relationship(u'Teo')


class Usu(Base):
    __tablename__ = 'usu'

    version = Column(BigInteger, nullable=False, server_default=text("'0'"))
    usucod = Column(BigInteger, primary_key=True, server_default=text("'0'"))
    usuusr = Column(String(10), nullable=False, server_default=text("''"))
    usueml = Column(String(200), nullable=False, server_default=text("''"))
    usunom = Column(String(200), nullable=False, server_default=text("''"))
    usupwd = Column(String(200), nullable=False, server_default=text("''"))
