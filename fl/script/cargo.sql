
drop table if exists tca;

drop table if exists tta;

drop table if exists cto;
DROP TABLE IF EXISTS cyp;
DROP TABLE IF EXISTS emp;
DROP TABLE IF EXISTS seq;
drop table if exists tea;
drop table if exists teo;
DROP TABLE IF EXISTS usu;

create table cto (
    version     bigint unsigned not null default '0'                            comment 'Version',
    ctocod      varchar(5) NOT NULL DEFAULT ''                                  comment 'Código',
    ctodes      varchar(80) NOT NULL DEFAULT ''                                 COMMENT 'Descripción',    
    ctoest      smallint unsigned not null default '0'                          comment 'Estado baja',
    primary key (ctocod)
) comment 'Conceptos a cobrar/pagar';

CREATE TABLE cyp (
    version     bigint unsigned not null default '0'                            comment 'Version',
    cypcod      bigint unsigned NOT NULL DEFAULT '0'                            COMMENT 'Codigo interno',
    cypraz      varchar(80) NOT NULL DEFAULT ''                                 COMMENT 'Razón social',
    cypidf      varchar(20) NOT NULL DEFAULT ''                                 COMMENT 'Identificación fiscal',
    cyptkr      varchar(5) NOT NULL DEFAULT ''                                  COMMENT 'Ticker',
    PRIMARY KEY (cypcod)
) comment 'Clientes y proveedores';

CREATE TABLE emp (
    version     bigint unsigned not null default '0'                            comment 'Version',
    empcod      bigint unsigned NOT NULL DEFAULT '0'                            COMMENT 'Codigo interno',
    empraz      varchar(80) NOT NULL DEFAULT ''                                 COMMENT 'Razón social',
    empidf      varchar(20) NOT NULL DEFAULT ''                                 COMMENT 'Identificación fiscal',
    PRIMARY KEY (empcod)
) comment 'Empresas';

CREATE TABLE seq (
    version     bigint unsigned not null default '0'                            comment 'Version',
    seqcod      varchar(20) NOT NULL DEFAULT ''                                 COMMENT 'Secuencia',
    seqdes      varchar(80) NOT NULL DEFAULT ''                                 COMMENT 'Descripción',
    segnxt      bigint unsigned NOT NULL DEFAULT '0'                            COMMENT 'Siguiente valor',
    PRIMARY KEY (seqcod)
) comment 'Secuencias';

create table tea (
    version     bigint unsigned not null default '0'                            comment 'Version',
    teacod      varchar(5) not null default ''                                  comment 'Código',
    teades      varchar(80) not null default ''                                 comment 'Descripción',
    teadef      smallint unsigned not null default '0'                          comment 'Valor por defecto',
    primary key (teacod)
) comment 'Estados administrativos';

create table teo (
    version     bigint unsigned not null default '0'                            comment 'Version',
    teocod      varchar(5) not null default ''                                  comment 'Código',
    teodes      varchar(80) not null default ''                                 comment 'Descripción',
    teodef      smallint unsigned not null default '0'                          comment 'Valor por defecto',
    primary key (teocod)
) comment 'Estados operativos';

create table usu (
    version     bigint unsigned not null default '0'                            comment 'Version',
    usucod      bigint unsigned not null default '0'                            comment 'Código interno',
    usuusr      varchar(10) not null default ''                                 comment 'Usuario',
    usueml      varchar(200) not null default ''                                comment 'Correo electrónico',
    usunom      varchar(200) not null default ''                                comment 'Nombre',
    usupwd      varchar(200) not null default ''                                comment 'Contraseña',
    primary key (usucod)
) comment 'Usuarios';

insert into usu values(1, 0, 'root', 'root@flcargo.org', 'Usuario administrador', 'passwd');

create table tca (
    version     bigint unsigned not null default '0'                            comment 'Version',
    tcacod      bigint unsigned NOT NULL DEFAULT '0'                            COMMENT 'Codigo interno',
    tcaloc      varchar(20) NOT NULL DEFAULT ''                                 COMMENT 'Localizador',

    tcacypcod   bigint unsigned NOT NULL DEFAULT '0'                            COMMENT 'Codigo cliente',
    tcacypraz   varchar(80) NOT NULL DEFAULT ''                                 COMMENT 'Razón social',
    tcacypidf   varchar(20) NOT NULL DEFAULT ''                                 COMMENT 'Identificación fiscal',
    tcacyptkr   varchar(5) NOT NULL DEFAULT ''                                  COMMENT 'Ticker',

    tcateocod   varchar(5) not null default ''                                  comment 'Estado operativo',

    primary key(tcacod),
    foreign key (tcacypcod) references cyp(cypcod),
    foreign key (tcateocod) references teo(teocod)
) comment 'Órdenes de carga';

create table tta (
    version     bigint unsigned not null default '0'                            comment 'Version',
    ttacod bigint unsigned NOT NULL DEFAULT '0'                                 COMMENT 'Codigo interno',
    ttaloc varchar(20) NOT NULL DEFAULT ''                                      COMMENT 'Localizador',

    ttacypcod   bigint unsigned NOT NULL DEFAULT '0'                            COMMENT 'Codigo proveedor',
    ttacypraz   varchar(80) NOT NULL DEFAULT ''                                 COMMENT 'Razón social',
    ttacypidf   varchar(20) NOT NULL DEFAULT ''                                 COMMENT 'Identificación fiscal',
    ttacyptkr   varchar(5) NOT NULL DEFAULT ''                                  COMMENT 'Ticker',

    ttateocod   varchar(5) not null default ''                                  comment 'Código estado operativo',

    primary key(ttacod),
    foreign key (ttacypcod) references cyp(cypcod),
    foreign key (ttateocod) references teo(teocod)
) comment 'Órdenes de trabajo';




