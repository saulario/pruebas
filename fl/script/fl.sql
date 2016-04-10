
drop table if exists tc0;

drop table if exists tt0;

drop table if exists cto;
DROP TABLE IF EXISTS cyp;
DROP TABLE IF EXISTS emp;
DROP TABLE IF EXISTS seq;
drop table if exists tea;
drop table if exists teo;
DROP TABLE IF EXISTS usu;

create table cto (
    ctocod      varchar(5) NOT NULL DEFAULT ''                                  comment 'Código',
    ctodes      varchar(80) NOT NULL DEFAULT ''                                 COMMENT 'Descripción',    
    ctoest      smallint unsigned not null default '0'                          comment 'Estado baja',
    primary key (ctocod)
) comment 'Conceptos a cobrar/pagar';

CREATE TABLE cyp (
    cypcod      bigint unsigned NOT NULL DEFAULT '0'                            COMMENT 'Codigo interno',
    cypraz      varchar(80) NOT NULL DEFAULT ''                                 COMMENT 'Razón social',
    cypidf      varchar(20) NOT NULL DEFAULT ''                                 COMMENT 'Identificación fiscal',
    cyptkr      varchar(5) NOT NULL DEFAULT ''                                  COMMENT 'Ticker',
    PRIMARY KEY (cypcod)
) comment 'Clientes y proveedores';

CREATE TABLE emp (
    empcod      bigint unsigned NOT NULL DEFAULT '0'                            COMMENT 'Codigo interno',
    empraz      varchar(80) NOT NULL DEFAULT ''                                 COMMENT 'Razón social',
    empidf      varchar(20) NOT NULL DEFAULT ''                                 COMMENT 'Identificación fiscal',
    PRIMARY KEY (empcod)
) comment 'Empresas';

CREATE TABLE seq (
    seqcod      varchar(20) NOT NULL DEFAULT ''                                 COMMENT 'Secuencia',
    seqdes      varchar(80) NOT NULL DEFAULT ''                                 COMMENT 'Descripción',
    segnxt      bigint unsigned NOT NULL DEFAULT '0'                            COMMENT 'Siguiente valor',
    PRIMARY KEY (seqcod)
) comment 'Secuencias';

create table tea (
    teacod      varchar(5) not null default ''                                  comment 'Código',
    teades      varchar(80) not null default ''                                 comment 'Descripción',
    teadef      smallint unsigned not null default '0'                          comment 'Valor por defecto',
    primary key (teacod)
) comment 'Estados administrativos';

create table teo (
    teocod      varchar(5) not null default ''                                  comment 'Código',
    teodes      varchar(80) not null default ''                                 comment 'Descripción',
    teodef      smallint unsigned not null default '0'                          comment 'Valor por defecto',
    primary key (teocod)
) comment 'Estados operativos';

create table usu (
    usucod      bigint unsigned not null default '0'                            comment 'Código interno',
    usuusr      varchar(10) not null default ''                                 comment 'Usuario',
    usueml      varchar(200) not null default ''                                comment 'Correo electrónico',
    usupwd      varchar(200) not null default ''                                comment 'Contraseña',
    primary key (usucod)
) comment 'Usuarios';

create table tc0 (
    tc0cod      bigint unsigned NOT NULL DEFAULT '0'                            COMMENT 'Codigo interno',
    tc0loc      varchar(20) NOT NULL DEFAULT ''                                 COMMENT 'Localizador',

    tc0cypcod   bigint unsigned NOT NULL DEFAULT '0'                            COMMENT 'Codigo cliente',
    tc0cypraz   varchar(80) NOT NULL DEFAULT ''                                 COMMENT 'Razón social',
    tc0cypidf   varchar(20) NOT NULL DEFAULT ''                                 COMMENT 'Identificación fiscal',
    tc0cyptkr   varchar(5) NOT NULL DEFAULT ''                                  COMMENT 'Ticker',

    tc0teocod   varchar(5) not null default ''                                  comment 'Código estado operativo',
    tc0teacod   varchar(5) not null default ''                                  comment 'Código estado administrativo',

    primary key(tc0cod),
    foreign key (tc0cypcod) references cyp(cypcod),
    foreign key (tc0teocod) references teo(teocod),
    foreign key (tc0teacod) references tea(teacod)
) comment 'Órdenes de carga';

create table tt0 (
    tt0cod bigint unsigned NOT NULL DEFAULT '0'                                 COMMENT 'Codigo interno',
    tt0loc varchar(20) NOT NULL DEFAULT ''                                      COMMENT 'Localizador',

    tt0cypcod   bigint unsigned NOT NULL DEFAULT '0'                            COMMENT 'Codigo proveedor',
    tt0cypraz   varchar(80) NOT NULL DEFAULT ''                                 COMMENT 'Razón social',
    tt0cypidf   varchar(20) NOT NULL DEFAULT ''                                 COMMENT 'Identificación fiscal',
    tt0cyptkr   varchar(5) NOT NULL DEFAULT ''                                  COMMENT 'Ticker',

    tt0teocod   varchar(5) not null default ''                                  comment 'Código estado operativo',
    tt0teacod   varchar(5) not null default ''                                  comment 'Código estado administrativo',

    primary key(tt0cod),
    foreign key (tt0cypcod) references cyp(cypcod),
    foreign key (tt0teocod) references teo(teocod),
    foreign key (tt0teacod) references tea(teacod)
) comment 'Órdenes de trabajo';




