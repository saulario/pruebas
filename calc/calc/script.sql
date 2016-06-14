
drop table if exists doc;
drop table if exists pro;
drop table if exists zoo;
drop table if exists zon;

create table zon (
    zoncod      varchar(10) not null default '',
    zondes      varchar(40) not null default '',
    zonman      decimal(13,4) not null default '0.0000',
    primary key (zoncod)
);

insert into zon values ('DE38','ZONA 1 Hannover',0);
insert into zon values ('DE74','ZONA 2 Ilsfeld',0);
insert into zon values ('DE59','ZONA 3 Bonnen',0);

create table zoo (
    zoocod      bigint not null default '0',
    zoozoncod   varchar(10) not null default '',
    zoopcp      varchar(10) not null default '',
    primary key (zoocod),
    constraint fk_zoo_zon foreign key (zoozoncod) references zon(zoncod)
);

insert into zoo values(1, 'DE38','DE20');
insert into zoo values(2, 'DE38','DE21');
insert into zoo values(3, 'DE38','DE22');
insert into zoo values(4, 'DE38','DE23');
insert into zoo values(5, 'DE38','DE24');
insert into zoo values(6, 'DE38','DE25');
insert into zoo values(7, 'DE38','DE26');
insert into zoo values(8, 'DE38','DE27');
insert into zoo values(9, 'DE38','DE28');
insert into zoo values(10,'DE38','DE29');
insert into zoo values(11,'DE38','DE30');
insert into zoo values(12,'DE38','DE31');
insert into zoo values(13,'DE38','DE32');
insert into zoo values(14,'DE38','DE33');
insert into zoo values(15,'DE38','DE37');
insert into zoo values(16,'DE38','DE38');
insert into zoo values(17,'DE38','DE49');

insert into zoo values(21,'DE74','DE63');
insert into zoo values(22,'DE74','DE64');
insert into zoo values(23,'DE74','DE66');
insert into zoo values(24,'DE74','DE67');
insert into zoo values(25,'DE74','DE68');
insert into zoo values(26,'DE74','DE69');
insert into zoo values(27,'DE74','DE70');
insert into zoo values(28,'DE74','DE71');
insert into zoo values(29,'DE74','DE72');
insert into zoo values(30,'DE74','DE73');
insert into zoo values(31,'DE74','DE74');
insert into zoo values(32,'DE74','DE75');
insert into zoo values(33,'DE74','DE76');
insert into zoo values(34,'DE74','DE77');
insert into zoo values(35,'DE74','DE97');
insert into zoo values(36,'DE74','FR57');
insert into zoo values(37,'DE74','DE67');

insert into zoo values(41,'DE59','DE34');
insert into zoo values(42,'DE59','DE35');
insert into zoo values(43,'DE59','DE36');

insert into zoo values(45,'DE59','DE40');
insert into zoo values(46,'DE59','DE41');
insert into zoo values(47,'DE59','DE42');
insert into zoo values(48,'DE59','DE43');
insert into zoo values(49,'DE59','DE44');
insert into zoo values(50,'DE59','DE45');
insert into zoo values(51,'DE59','DE46');
insert into zoo values(52,'DE59','DE47');
insert into zoo values(53,'DE59','DE48');

insert into zoo values(55,'DE59','DE50');
insert into zoo values(56,'DE59','DE51');
insert into zoo values(57,'DE59','DE52');
insert into zoo values(58,'DE59','DE53');
insert into zoo values(59,'DE59','DE54');
insert into zoo values(60,'DE59','DE55');
insert into zoo values(61,'DE59','DE56');
insert into zoo values(62,'DE59','DE57');
insert into zoo values(63,'DE59','DE58');
insert into zoo values(64,'DE59','DE59');

insert into zoo values(65,'DE59','DE60');
insert into zoo values(66,'DE59','DE61');
insert into zoo values(67,'DE59','DE62');
insert into zoo values(68,'DE59','DE65');

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
    docpes      decimal(13,4) not null default '0.0000',
    docvol      decimal(13,4) not null default '0.0000',
    docpef      decimal(13,4) not null default '0.0000',
    primary key (doccod)
);

create table dod (
    dodcod      bigint not null default '0',
    dodrel      varchar(20) not null default '',
    dodexp      varchar(20) not null default '',
    dodfec      date not null default '0001-01-01',
    dodorgzon   varchar(10) not null default '',
    dodorgpob   varchar(80) not null default '',
    doddeszon   varchar(10) not null default '',
    doddespob   varchar(80) not null default '',
    dodflu      varchar(5) not null default '',
    dodfab      varchar(5) not null default '',
    doddun      varchar(20) not null default '',
    dodpro      varchar(80) not null default '',
    dodpes      decimal(13,4) not null default '0.0000',
    dodvol      decimal(13,4) not null default '0.0000',
    dodpef      decimal(13,4) not null default '0.0000',
    primary key (dodcod)
);