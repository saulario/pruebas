
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
    procod bigint not null default '0',
    produn varchar(20) not null default '',
    proraz varchar(80) not null default '',
    primary key(procod)
);

create table doc (
    doccod      bigint not null default '0',



    primary key (doccod)
);