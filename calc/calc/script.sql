
drop table if exists doc;
drop table if exists pro;
drop table if exists zoo;
drop table if exists zon;

create table zon (
    zoncod varchar(10) not null default '',
    zondes varchar(40) not null default '',
    primary key (zoncod)
);

create table zoo (
    zoocod      bigint not null default '0',
    zoozoncod   varchar(10) not null default '',
    zoopcp      varchar(10) not null default '',
    primary key (zoocod),
	constraint fk_zoo_zon foreign key (zoozoncod) references zon(zoncod)
);

create table pro (
    produn varchar(20) not null default '',
    proraz varchar(80) not null default '',
    primary key(produn)
);

create table doc (
    doccod      bigint not null default '0',
    docrel      varchar(20) not null default '',
    docexp      varchar(20) not null default '',
    docfec      date not null default '0001-01-01',
    docorgzon   varchar(10) not null default '',
    docorgpob   varchar(80) not null default '',
    docdeszon   varchar(10) not null default '',
    docdespob   varchar(80) not null default '',
    docflu      varchar(5) not null default '',
    docfab      varchar(5) not null default '',
    docdun      varchar(20) not null default '',
    docpro      varchar(80) not null default '',
    primary key (doccod)
);