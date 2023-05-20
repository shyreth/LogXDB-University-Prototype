--##### CREARE TABELE ###################
-- creare tabel NOM
DROP TABLE IF EXISTS logx.nom;
CREATE TABLE logx.nom(idcode varchar(20) PRIMARY KEY, refteh 
varchar(30),refcom varchar(20), descr varchar(100), utiliz varchar(30) 
DEFAULT CURRENT_USER, data date DEFAULT CURRENT_DATE, ora time DEFAULT 
CURRENT_TIME);
-- creare tabel LOC
DROP TABLE IF EXISTS logx.loc;
CREATE TABLE logx.loc(dep char(3), ampl varchar(10), CONSTRAINT loc_pk 
PRIMARY KEY(dep,ampl));
-- creare tabel BR 
DROP TABLE IF EXISTS logx.br;
CREATE TABLE logx.br(nrbr int,datain date DEFAULT CURRENT_DATE, idcode 
varchar(20), po varchar(10), status varchar(15), supplier varchar(50), 
serialno varchar(50), depinit char(3), amplinit varchar(10), qty int, val
numeric, idx serial PRIMARY KEY);
ALTER TABLE logx.br ADD CONSTRAINT br_f1 FOREIGN KEY (idcode) REFERENCES 
logx.nom (idcode); 
ALTER TABLE logx.br ADD CONSTRAINT br_f2 FOREIGN KEY (depinit,amplinit) 
REFERENCES logx.loc (dep,ampl); 
-- creare tabel INX
CREATE TABLE logx.inx(id varchar(11) PRIMARY KEY, nrbr int, datain date 
DEFAULT CURRENT_DATE, idcode varchar(20), po varchar(10), status 
varchar(15), supplier varchar(50), serialno varchar(50), depinit char(3),
amplinit varchar(10), qty int, val numeric);
ALTER TABLE logx.inx ADD CONSTRAINT in_f1 FOREIGN KEY (idcode) REFERENCES
logx.nom (idcode); 
ALTER TABLE logx.inx ADD CONSTRAINT in_f2 FOREIGN KEY (depinit,amplinit) 
REFERENCES logx.loc (dep,ampl); 
-- creare tabel STX
CREATE TABLE logx.stx(dep char(3),ampl varchar(10), id varchar(11), 
qtyfiz int, qtydisp int, CONSTRAINT st_pk PRIMARY KEY(dep,ampl,id));
ALTER TABLE logx.stx ADD CONSTRAINT st_f1 FOREIGN KEY (id) REFERENCES 
logx.inx (id); 
ALTER TABLE logx.stx ADD CONSTRAINT st_f2 FOREIGN KEY (dep,ampl) 
REFERENCES logx.loc (dep,ampl); 
-- creare tabele BT_ şi _BT
DROP TABLE IF EXISTS logx._bt; DROP TABLE IF EXISTS logx.bt_;
CREATE TABLE logx.bt_(nrbt int PRIMARY KEY, databt date, dep_dest 
char(3), ampl_dest varchar(10), CONSTRAINT f2_bt_ FOREIGN KEY(dep_dest,ampl_dest) REFERENCES logx.loc(dep,ampl));



CREATE TABLE logx._bt(nrbt int, id varchar(11), qtytr int DEFAULT 1, 
dep_srs varchar(3), ampl_srs varchar(10),
 CONSTRAINT k__bt PRIMARY KEY(nrbt,id,dep_srs,ampl_srs),
 CONSTRAINT f1__bt FOREIGN KEY(id) REFERENCES logx.inx(id) ,
 CONSTRAINT f2__bt FOREIGN KEY(dep_srs,ampl_srs) REFERENCES 
logx.loc(dep,ampl),
 CONSTRAINT f0__bt FOREIGN KEY(nrbt) REFERENCES logx.bt_(nrbt));
-- creare tabel TRX
CREATE TABLE logx.trx(nrbt int,datatr date,nrlin serial,dep_srs 
char(3),ampl_srs varchar(10),dep_dest char(3),ampl_dest varchar(10), id 
varchar(11), qtytr int, CONSTRAINT k_tr PRIMARY KEY(nrbt,nrlin));
ALTER TABLE logx.trx ADD CONSTRAINT tr_f1 FOREIGN KEY (id) REFERENCES 
logx.inx (id); 
ALTER TABLE logx.trx ADD CONSTRAINT tr_f21 FOREIGN KEY (dep_srs,ampl_srs)
REFERENCES logx.loc (dep,ampl); 
ALTER TABLE logx.trx ADD CONSTRAINT tr_f22 FOREIGN KEY 
(dep_dest,ampl_dest) REFERENCES logx.loc (dep,ampl); 
-- creare tabele BP_ şi _BP
CREATE TABLE logx.bp_(nrbp int PRIMARY KEY,databp date,destin 
varchar(30));
CREATE TABLE logx._bp(nrbp int,id varchar(11),qtyrez int DEFAULT 
0,qtyconf int DEFAULT 0,dep varchar(3), ampl varchar(10),
 CONSTRAINT k__bp PRIMARY KEY(nrbp,id,dep,ampl),
 CONSTRAINT f1__bp FOREIGN KEY(id) REFERENCES logx.inx(id) ,
 CONSTRAINT f2__bp FOREIGN KEY(dep,ampl) REFERENCES logx.loc(dep,ampl),
 CONSTRAINT f0__bp FOREIGN KEY(nrbp) REFERENCES logx.bp_(nrbp));
-- creare tabel ieşiri (INX)
CREATE TABLE logx.outx(nrbl int,destin varchar(30),id varchar(11),qtyliv
int,dep varchar(3), ampl varchar(10),dataout date,
 CONSTRAINT k_out PRIMARY KEY(nrbl,id,dep,ampl),
 CONSTRAINT f1__out FOREIGN KEY(id) REFERENCES logx.inx(id) ,
 CONSTRAINT f2__out FOREIGN KEY(dep,ampl) REFERENCES logx.loc(dep,ampl));
-- creare tabel acces (ACCES)
CREATE TABLE logx.acces(alias varchar(30) PRIMARY KEY, pw varchar(50), 
nume_utilizator varchar(100), date_contact varchar(200), dep varchar(100)
[]);


--############## CREARE CONTOARE ##############
-- creare secvenţa parte numerica ID
DROP SEQUENCE IF EXISTS logx.id_seq; CREATE SEQUENCE logx.id_seq
INCREMENT 1 MINVALUE 1 START 1;
--verificare index: select nextval('logx.id_seq');
-- creare secvenţa NUMĂR BR
DROP SEQUENCE IF EXISTS logx.br_seq; CREATE SEQUENCE logx.br_seq
INCREMENT 1 MINVALUE 1 START 10;
--verificare index: select nextval('logx.br_seq');
-- creare secvenţa NUMĂR BP
DROP SEQUENCE IF EXISTS logx.bp_seq; CREATE SEQUENCE logx.bp_seq
INCREMENT 1 MINVALUE 1 START 10;
--verificare index: select nextval('logx.bp_seq');




