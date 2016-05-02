
drop table if exists oca;

drop table if exists ota;

drop table if exists cto;
drop table if exists gcl;
drop table if exists gem;
drop table if exists gpr;
drop table if exists gse;
drop table if exists oeo;
drop table if exists gus;

create table cto (
    version     bigint unsigned not null default '0'                            comment 'Version',
    ctocod      varchar(5) not null default ''                                  comment 'Código',
    ctoeid      varchar(20) not null default ''                                 comment 'Identificación externo',
    ctodes      varchar(80) not null default ''                                 comment 'Descripción',    
    ctoest      smallint unsigned not null default '0'                          comment 'Estado baja',
    primary key (ctocod)
) comment 'Conceptos a cobrar/pagar';

create table gcl (
    version     bigint unsigned not null default '0'                            comment 'Version',
    gclcod      bigint unsigned not null default '0'                            comment 'Codigo interno',
    gclraz      varchar(80) not null default ''                                 comment 'Razón social',
    gcleid      varchar(20) not null default ''                                 comment 'Identificación externo',
    gclidf      varchar(20) not null default ''                                 comment 'Identificación fiscal',
    gcltkr      varchar(5) not null default ''                                  comment 'Ticker',
    gclimg      blob                                                            comment 'Imagen',
    primary key (gclcod)
) comment 'Clientes';

create table gpr (
    version     bigint unsigned not null default '0'                            comment 'Version',
    gprcod      bigint unsigned not null default '0'                            comment 'Codigo interno',
    gprraz      varchar(80) not null default ''                                 comment 'Razón social',
    gpreid      varchar(20) not null default ''                                 comment 'Identificación externo',
    gpridf      varchar(20) not null default ''                                 comment 'Identificación fiscal',
    gprtkr      varchar(5) not null default ''                                  comment 'Ticker',
    gprimg      blob                                                            comment 'Imagen',
    primary key (gprcod)
) comment 'Proveedores';

create table gem (
    version     bigint unsigned not null default '0'                            comment 'Version',
    gemcod      bigint unsigned not null default '0'                            comment 'Codigo interno',
    gemraz      varchar(80) not null default ''                                 comment 'Razón social',
    gemidf      varchar(20) not null default ''                                 comment 'Identificación fiscal',
    gemtkr      varchar(5) not null default ''                                  comment 'Ticker',
    primary key (gemcod)
) comment 'Empresas';

create table gse (
    version     bigint unsigned not null default '0'                            comment 'Version',
    gsecod      varchar(20) not null default ''                                 comment 'Secuencia',
    gsedes      varchar(80) not null default ''                                 comment 'Descripción',
    gsenxt      bigint unsigned not null default '0'                            comment 'Siguiente valor',
    primary key (gsecod)
) comment 'Secuencias';

create table oeo (
    version     bigint unsigned not null default '0'                            comment 'Version',
    oeocod      varchar(5) not null default ''                                  comment 'Código',
    oeodes      varchar(80) not null default ''                                 comment 'Descripción',
    oeodef      smallint unsigned not null default '0'                          comment 'Valor por defecto',
    oeofin      smallint unsigned not null default '0'                          comment 'Valor por defecto',
    primary key (oeocod)
) comment 'Estados operativos';

create table gus (
    version     bigint unsigned not null default '0'                            comment 'Version',
    guscod      bigint unsigned not null default '0'                            comment 'Código interno',
    gususr      varchar(10) not null default ''                                 comment 'Usuario',
    guseml      varchar(200) not null default ''                                comment 'Correo electrónico',
    gusnom      varchar(200) not null default ''                                comment 'Nombre',
    guspwd      varchar(200) not null default ''                                comment 'Contraseña',
    primary key (guscod)
) comment 'Usuarios';

insert into gus values(1, 1, 'root', 'root@cargo.org', 'Usuario administrador', 'passwd');

create table oca (
    version     bigint unsigned not null default '0'                            comment 'Version',
    ocacod      bigint unsigned not null default '0'                            comment 'Codigo interno',
    ocaloc      varchar(20) not null default ''                                 comment 'Localizador',

    ocagclcod   bigint unsigned not null default '0'                            comment 'Codigo cliente',
    ocagclraz   varchar(80) not null default ''                                 comment 'Razón social',
    ocagclidf   varchar(20) not null default ''                                 comment 'Identificación fiscal',
    ocagcltkr   varchar(5) not null default ''                                  comment 'Ticker',

    ocaoeocod   varchar(5) not null default ''                                  comment 'Estado operativo',

    primary key(ocacod),
    foreign key (ocagclcod) references gcl(gclcod),
    foreign key (ocaoeocod) references oeo(oeocod)
) comment 'Órdenes de carga';

create table ota (
    version     bigint unsigned not null default '0'                            comment 'Version',
    otacod bigint unsigned not null default '0'                                 comment 'Codigo interno',
    otaloc varchar(20) not null default ''                                      comment 'Localizador',

    otagprcod   bigint unsigned not null default '0'                            comment 'Codigo proveedor',
    otagprraz   varchar(80) not null default ''                                 comment 'Razón social',
    otagpridf   varchar(20) not null default ''                                 comment 'Identificación fiscal',
    otagprtkr   varchar(5) not null default ''                                  comment 'Ticker',

    otaoeocod   varchar(5) not null default ''                                  comment 'Código estado operativo',

    primary key(otacod),
    foreign key (otagprcod) references gpr(gprcod),
    foreign key (otaoeocod) references oeo(oeocod)
) comment 'Órdenes de trabajo';

