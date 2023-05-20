--############# FUNCŢII "SERVER SIDE" ###################

--creare funcţie de adăugare în nomenclator
CREATE OR REPLACE FUNCTION logx.nom_add(_idcode_ text,_refteh_ 
text,_refcom_ text, _descr_ text)
RETURNS text AS
$$
DECLARE
f boolean;
ach text;
BEGIN
--testare existenţă idcode în nom
SELECT EXISTS(SELECT * FROM logx.nom WHERE idcode=_idcode_) INTO f;
IF f THEN
SELECT 'Există deja în nom.'||_idcode_||'-- refteh:'||refteh||' recom:'||
refcom||' Descriere:'||descr
 ||' User:'||utiliz||'-Data:'||data||'-Ora:'||ora 
 FROM logx.nom WHERE idcode=_idcode_ INTO ach;
return ach;
END IF;
INSERT INTO logx.nom(idcode, refteh, refcom, descr)
 VALUES (_idcode_, _refteh_, _refcom_, _descr_);
RETURN 'OK'; 
END
$$
LANGUAGE 'plpgsql';
---## BR NOU ##-------------
create or replace function logx.br_nou(_datain_ date DEFAULT 
CURRENT_DATE)
returns void as
$$
begin
insert into logx.br(nrbr,datain) VALUES ((select 
nextval('logx.br_seq')),_datain_);
end
$$
language 'plpgsql';




-----------## CONSTITUIRE ID NOU ##----------
CREATE OR REPLACE FUNCTION logx.id_nou(_dep_ text)
RETURNS text AS
$$
DECLARE
i int;
BEGIN
SELECT nextval('logx.id_seq') INTO i;
return _dep_||i::text;
END;
$$
LANGUAGE 'plpgsql';



----------------## VALIDARE BR ##-----------
CREATE OR REPLACE FUNCTION logx.valid_br(_nrbr_ int)
RETURNS text AS
$$
DECLARE
f boolean;
BEGIN
--verificare introducere itemcode
SELECT EXISTS(SELECT * FROM logx.br WHERE idcode IS NULL) INTO f;
IF f THEN return 'Introduceti itemcode!'; END IF;
--verificare introducere cantităţi
SELECT EXISTS(SELECT * FROM logx.br WHERE qty<1) INTO f;
IF f THEN return 'Introduceti cantitatea!'; END IF;
--verificare introducere datain
SELECT EXISTS(SELECT * FROM logx.br WHERE datain IS NULL) INTO f;
IF f THEN return 'Introduceti DATA!'; END IF;
--NOTA: funcţia se execută intr-o singura tranzitie
--adăugare în logx.inx
INSERT INTO logx.inx(
 id, nrbr, datain, idcode, po, status, supplier, serialno, 
 depinit, amplinit, qty, val)
SELECT logx.id_nou(depinit), nrbr, datain, idcode, po, status, supplier, 
serialno, depinit, amplinit, qty, val FROM logx.br WHERE nrbr=_nrbr_; 
--adaugă în stoc
INSERT INTO logx.stx(dep, ampl, id, qtyfiz, qtydisp)
 SELECT depinit,amplinit,id,qty,qty FROM logx.inx WHERE inx.nrbr=_nrbr_; 
--şterge din BR 
 DELETE FROM logx.br USING logx.inx WHERE inx.nrbr=br.nrbr; 
RETURN 'OK';
END;
$$
LANGUAGE 'plpgsql';


-----------## BP NOU ##----------
create or replace function logx.bp_nou(_destin_ text,_databp_ date 
DEFAULT CURRENT_DATE) returns void as
$$
begin
insert into logx.bp_(nrbp,databp,destin) VALUES ((select 
nextval('logx.bp_seq')), _databp_,_destin_);
end
$$
language 'plpgsql';


---------------## ADAUGARE LINIE _BP ##-------
CREATE OR REPLACE FUNCTION logx.add_bp_id(_nrbp_ integer,_id_ text,_dep_
text,_ampl_ text,_qtyrez_ int)
 RETURNS text AS
$BODY$
DECLARE
f boolean;
begin
--verificare existenţă linie deja adăugată
select exists (select * from logx._bp where _bp.nrbp=_nrbp_ AND 
_bp.id=_id_ AND _bp.dep=_dep_ AND _bp.ampl=_ampl_) INTO f;
if f then return 'Exisă deja un item de acest tip introdus în BP-ul 
curent!'; end if;
INSERT INTO logx._bp(nrbp,id,dep,ampl,qtyrez) 
VALUES(_nrbp_,_id_,_dep_,_ampl_,_qtyrez_);
UPDATE logx.stx set qtydisp=qtydisp-_bp.qtyrez FROM logx._bp WHERE 
_bp.id=stx.id AND _bp.dep=stx.dep AND _bp.ampl=stx.ampl AND 
_bp.nrbp=_nrbp_ AND _bp.id=_id_ AND _bp.dep=_dep_ AND _bp.ampl=_ampl_;
return 'OK';
end
$BODY$
 LANGUAGE plpgsql;



-------------## ŞTERGERE LINIE _BP ---------------
CREATE OR REPLACE FUNCTION logx.del_bp_id(_nrbp_ integer, _id_ text, 
_dep_ text, _ampl_ text) RETURNS text AS
$BODY$
DECLARE
f boolean;
begin
UPDATE logx.stx set qtydisp=qtydisp+_bp.qtyrez FROM logx._bp WHERE 
_bp.id=stx.id AND _bp.dep=stx.dep AND _bp.ampl=stx.ampl AND 
_bp.nrbp=_nrbp_ AND _bp.id=_id_ AND _bp.dep=_dep_ AND _bp.ampl=_ampl_;
DELETE FROM logx._bp WHERE _bp.nrbp=_nrbp_ AND _bp.id=_id_ AND 
_bp.dep=_dep_ AND _bp.ampl=_ampl_;
DELETE FROM tmpselst WHERE tmpselst.nrbp=_nrbp_ AND tmpselst.id=_id_ AND 
tmpselst.dep=_dep_ AND tmpselst.ampl=_ampl_;
return 'OK';
end
$BODY$ LANGUAGE plpgsql;


-----------## VALIDARE BP ##-------
create or replace function logx.valid_bp(_nrbp_ int)
returns text as
$$
DECLARE
f boolean;
BEGIN
select EXISTS(select * from logx._bp where _bp.nrbp=_nrbp_ and 
_bp.qtyconf>_bp.qtyrez) INTO f;
IF f THEN return 'Există cantitati confirmate mai mari decat cantitatile 
rezervate'; END IF;
-- adaugă în iesiri (tabelul outx ce contine borderourile de livrare)
INSERT INTO logx.outx(nrbl, destin, id, qtyliv, dep, ampl,dataout) 
 SELECT _bp.nrbp,bp_.destin,_bp.id,_bp.qtyrez,_bp.dep,_bp.ampl, 
bp_.databp 
 FROM logx.bp_,logx._bp WHERE bp_.nrbp=_bp.nrbp AND _bp.nrbp=_nrbp_;
--actualizare stoc -- identificarea se face pentru intreaga cheie primara din tabelul logx.stx
UPDATE logx.stx SET qtyfiz=stx.qtyfiz-_bp.qtyconf, 
qtydisp=stx.qtydisp+_bp.qtyrez-_bp.qtyconf 
 FROM logx._bp WHERE stx.dep=_bp.dep AND stx.ampl=_bp.ampl AND 
stx.id=_bp.id AND _bp.nrbp=_nrbp_;
--sterge linii ramase cu qtyfiz=0 din stoc
DELETE FROM logx.stx WHERE qtyfiz<1;
--sterge din BP
DELETE FROM logx._bp WHERE _bp.nrbp=_nrbp_;
DELETE FROM logx.bp_ WHERE bp_.nrbp=_nrbp_;
RETURN 'OK';
END
$$
language 'plpgsql';



----## VALIDARE BT ##-------------
CREATE OR replace function logx.bt_valid(_nrbt_ int)
RETURNS text AS
$$
DECLARE
f boolean;
BEGIN
--verifică dacă toate cantităţile ce urmează a fi transferate sunt disponibile
SELECT EXISTS(SELECT * FROM logx.stx,logx._bt 
WHERE stx.dep=_bt.dep_srs AND stx.ampl=_bt.ampl_srs AND 
stx.id=_bt.id AND stx.qtydisp<qtytr)INTO f;
IF f THEN RETURN 'Există cantităţi ce nu sunt disponibile ptr. tranfer!';
END IF;
--adaugă în tabelul cu transferurile efectuate
INSERT INTO logx.trx(nrbt, datatr, dep_srs, ampl_srs, dep_dest, 
ampl_dest, id, qtytr) 
SELECT bt_.nrbt, bt_.databt, _bt.dep_srs, _bt.ampl_srs, bt_.dep_dest, 
bt_.ampl_dest, _bt.id, _bt.qtytr FROM logx.bt_,logx._bt 
 WHERE _bt.nrbt=bt_.nrbt AND _bt.nrbt=_nrbt_; 
--dacă există înregistrări le actualizează cu noile cantităţi
UPDATE logx.stx SET qtyfiz=qtyfiz+_bt.qtytr, qtydisp=qtydisp+_bt.qtytr 
 FROM logx._bt,logx.bt_ WHERE bt_.dep_dest=stx.dep AND 
bt_.ampl_dest=stx.ampl 
 AND _bt.id=stx.id AND _bt.nrbt=bt_.nrbt AND _bt.nrbt=_nrbt_;
--dacă nu există înregistrarile noi (dep,loc,id) le adaugă DOAR pe cele care NU se regăsesc în stoc(dep,ampl,id)
INSERT INTO logx.stx(dep, ampl, id, qtyfiz, qtydisp) 
 SELECT par.dep,par.ampl,par.id, _bt.qtytr, _bt.qtytr FROM
 (SELECT bt_.dep_dest as dep, bt_.ampl_dest as ampl, _bt.id 
 FROM logx._bt,logx.bt_ WHERE _bt.nrbt=bt_.nrbt AND _bt.nrbt=_nrbt_
 EXCEPT
 SELECT stx.dep,stx.ampl,stx.id FROM logx.stx,logx.bt_ WHERE 
bt_.dep_dest=stx.dep AND bt_.ampl_dest=stx.ampl
-- se poate şi fără ultima condiţie dar poate creşte timpul de interogare
 )par,logx._bt,logx.bt_ 
 WHERE _bt.id=par.id AND bt_.dep_dest=par.dep AND bt_.ampl_dest=par.ampl
 AND _bt.nrbt=bt_.nrbt AND _bt.nrbt=_nrbt_;
--ATENŢIE: se va realiza mai intâi UPDATE şi apoi INSERT altfel cantităţile se pot dubla
  
-- SE realizează scăderea din stoc (pentru SURSA)
UPDATE logx.stx SET qtyfiz=qtyfiz-_bt.qtytr, qtydisp=qtydisp-_bt.qtytr 
 FROM logx._bt WHERE _bt.dep_srs=stx.dep AND _bt.ampl_srs=stx.ampl 
 AND _bt.id=stx.id AND _bt.nrbt=_nrbt_;
-- dacă în urma scăderii qtyfiz =0 aceste linii se vor şterge
DELETE FROM logx.stx WHERE qtyfiz=0;
--şterge liniile din tabelele master-slave (bt_ şi _bt) corespunzatoare _nrbt_
DELETE FROM logx._bt WHERE nrbt=_nrbt_;
DELETE FROM logx.bt_ WHERE nrbt=_nrbt_;
RETURN 'OK'; 
END
$$ language plpgsql;

  -------------## INTEROGARE GENERALĂ ##-----------------
-- Function: logx.q_x(text, smallint, text[], text[], boolean[], boolean[], text[], text[], text)
CREATE OR REPLACE FUNCTION logx.q_x(_tipq_ text, _nr_ smallint, _nume_ 
text[], _tip_ text[], _a_ boolean[], _s_ boolean[], _val1_ text[], _val2_
text[], _ord_ text)
 RETURNS text AS $BODY$
DECLARE
vald1_ date[];
vald2_ date[];
valn1_ numeric[];
valn2_ numeric[];
valAC_ text[];
valb_ boolean[]; 
exeQ text; -- conţine şirul final pe baza căruia se realizează interogarea (comanda SQL finala)
codR text; -- răspunsul funcţiei : OK - ieşire cu execuţie până la capata interogarii
achA text; -- şirul format pentru alcătuirea exeQ ce conţine partea de afişare a coloanelor/câmpurilor din cda SQL
achS text; -- şirul format pentru alcătuirea exeQ ce conţine partea cu condițiile de selecţie din cda SQL
achG text; -- şirul format pentru alcătuirea exeQ ce conţine partea cu GRUPUL din cadrul czii SQL
achO text; -- şirul format pentru alcătuirea exeQ ce conţine partea cu ORDER BY din cadrul czii SQL
achLegTab text; --inner join
achFROM text;
achTmpTable text;--nume tabel rezultat
i int; f boolean; r int; ach text;
BEGIN
-- REZULTATUL interogarii va fi pus în tabelul TEMPORAR dat de achTmpTable
 achA:='';achS:='';achG:='#';achO:='';codR:='OK';f:=false;
-- testare existenţă date pentru filtru selecţie
 FOR i IN 1.._nr_
 LOOP
 IF _s_[i] AND (_val1_[i] IS NULL OR _val1_[i]='NULL') THEN 
codR='Selectie fara valoare pentru '||_nume_[i]||'!'; RETURN codR; END 
IF;
 IF _s_[i] AND (_tip_[i]='N2' OR _tip_[i]='D2') AND (_val2_[i] IS NULL 
OR _val2_[i]='NULL') THEN codR='Selectie fara valoare pentru '||
_nume_[i]||'!'; RETURN codR; END IF;
 IF _a_[i] AND _nume_[i]=_ord_ THEN f:=true; END IF; IF _ord_='---' 
THEN f:=true; END IF;
 END LOOP;
  IF NOT f THEN codR:='Câmpul dupa care se realizeaza ordonarea trebuie 
să se regaseasca în optiunile de afisare pentru coloane !'; RETURN codR; 
END IF;
--conversie date
 FOR i IN 1.._nr_
 LOOP
 IF _val1_[i]='NULL' THEN CONTINUE; END IF;
 IF _tip_[i]='D1' THEN vald1_[i]:=_val1_[i];END IF;
 IF _tip_[i]='D2' THEN vald1_[i]:=_val1_[i];vald2_[i]:=_val2_[i];END IF;
 IF _tip_[i]='N1' THEN valn1_[i]:=_val1_[i];END IF;
 IF _tip_[i]='N2' THEN valn1_[i]:=_val1_[i];valn2_[i]:=_val2_[i];END IF;
 IF _tip_[i]='B' THEN valb_[i]:=_val1_[i];END IF;
 IF _tip_[i]='A' OR _tip_[i]='C' THEN valAC_[i]:=_val1_[i];END IF;
 END LOOP;
-- constructie cda SQL 
 FOR i IN 1.._nr_
 LOOP
 IF _a_[i] THEN 
achA := achA ||','|| _nume_[i]; --intai va fi sum(qty)
if achG='#' then achG:=''; ELSE achG := achG ||','; end if;
achG := achG || _nume_[i]; 
 END IF;
 IF _s_[i] AND _tip_[i]='A' THEN achS:=achS||' AND '||_nume_[i]||' 
ILIKE ''%'||valAC_[i]||'%'''; END IF; 
 IF _s_[i] AND _tip_[i]='C' THEN achS:=achS||' AND '||_nume_[i]||' = 
'||quote_literal(valAC_[i]); END IF; 
 IF _s_[i] AND _tip_[i]='B' THEN achS:=achS||' AND '||_nume_[i]||' IS 
'||_valb_[i]; END IF; 
 IF _s_[i] AND _tip_[i]='N1' THEN achS:=achS||' AND '||_nume_[i]||' = 
'||valn1_[i]; END IF; 
 IF _s_[i] AND _tip_[i]='N2' THEN achS:=achS||' AND '||_nume_[i]||' >= 
'||valn1_[i]||' AND '||_nume_[i]||' <= '||valn2_[i]; END IF; 
 IF _s_[i] AND _tip_[i]='D1' THEN achS:=achS||' AND '||_nume_[i]||' = 
to_date('||quote_literal(vald1_[i])||','||
quote_literal('dd.mm.yyyy')||')';END IF; 
 IF _s_[i] AND _tip_[i]='D2' THEN achS:=achS||' AND '||_nume_[i]||' >= 
to_date('||quote_literal(vald1_[i])||','||quote_literal('dd.mm.yyyy')||')
 AND '||_nume_[i]||' <= to_date('||quote_literal(vald2_[i])||','||
quote_literal('dd.mm.yyyy')||')';END IF; 
 END LOOP; 
--creare tabele sursă şi tabele de legătură
-- utilizatorii pot vedea doar anumite magazii --- DOAR MAGAZIILE/DEPOZITELE cu drepturi de acces valide vor fi luate în
-- rezultatul interogarii (tmpacc)!
 DROP TABLE IF EXISTS tmpacc; CREATE TEMP TABLE tmpacc AS SELECT dep[s] 
FROM (select acces.*, generate_subscripts(dep,1) as s from 
logx.acces)par;
 IF _tipQ_ ='IN' THEN achTmpTable:='q_tmp_in'; achFROM:=' FROM 
logx.inx,logx.nom,tmpacc '; achLegTab:=' nom.idcode=inx.idcode AND 
depinit=tmpacc.dep'; END IF;
 IF _tipQ_ ='ST' OR _tipQ_ ='STL' THEN achTmpTable:='q_tmp_st'; 
achFROM:=' FROM logx.inx,logx.nom,logx.stx,tmpacc '; achLegTab:=' 
nom.idcode=inx.idcode AND inx.id=stx.id AND stx.dep=tmpacc.dep'; END IF;
 IF _tipQ_ ='OUT' THEN achTmpTable:='q_tmp_out';achFROM:=' FROM 
logx.inx,logx.nom,logx.outx,tmpacc '; achLegTab:=' nom.idcode=inx.idcode 
AND inx.id=outx.id AND outx.dep=tmpacc.dep'; END IF;
 IF _tipQ_ ='TR' THEN achTmpTable:='q_tmp_tr';achFROM:=' FROM 
logx.inx,logx.nom,logx.trx,tmpacc '; achLegTab:=' nom.idcode=inx.idcode 
AND inx.id=tr.id AND trx.dep_srs=tmpacc.dep AND trx.dep_dest=tmpacc.dep';
END IF;
 
 IF achG !='#' THEN achG:=' GROUP BY '||achG; ELSE achG:=''; END IF;
 achS:=' WHERE '||achLegTab||achS;
 IF _tipQ_ ='STL' THEN achS:=achS||' AND stx.qtydisp>0 '; END IF;
 IF _ord_!='---' THEN achO:=' ORDER BY '||_ord_; ELSE achO:=''; END IF;
 IF _tipQ_ = 'ST' OR _tipQ_ ='STL' THEN ach:= ' AS SELECT SUM(qtyfiz) as
qtyfiz, SUM(qtydisp) as qtydisp '; ELSE ach:= ' AS SELECT SUM(qty) as qty
';END IF; 
 exeQ:='DROP TABLE IF EXISTS '||achTmpTable||' ;
 CREATE TEMPORARY TABLE '||achTmpTable||ach||achA||
 achFROM||achS||achG||achO||';';
 RAISE NOTICE 'Interogarea: % ',exeQ;
 EXECUTE exeQ;
 GET DIAGNOSTICS r := ROW_COUNT; RAISE NOTICE 'Rez: %: % inregistrari', 
achTmpTable, r; 
 RETURN codR;
 END
$BODY$
 LANGUAGE plpgsql VOLATILE
 COST 100;
ALTER FUNCTION logx.q_x(text, smallint, text[], text[], boolean[], 
boolean[], text[], text[], text)
 OWNER TO postgres;
COMMENT ON FUNCTION logx.q_x(text, smallint, text[], text[], boolean[],
							 boolean[], text[], text[], text) IS '
© 2023, Stefan Iancu, Universitatea Hyperion din Bucuresti, v.001';



--########### POPULAREA CU DATE DE TEST ###############
INSERT INTO logx.acces(alias, pw, dep) 
VALUES('u1','0',ARRAY['DP1','DP2']),('u2','abc',ARRAY['DP2','DP3']);
INSERT INTO logx.nom(idcode,descr) VALUES 
('A1','DescrA1'),('A2','DescrA2'),('B1','DescrB1'),('B2','DescrZ2'),
('C1','DescrC1'),('C2','DescrC2');
INSERT INTO logx.loc(dep, ampl) VALUES ('DP1','AA1'),('DP1','AA2'),
('DP2','AA1'),('DP2','AB1'),('DP2','AC1'),('DP2','AA2'),('DP3','AA1'),
('DP3','AA2');
INSERT INTO logx.br(nrbr, datain, idcode, status, supplier, serialno, 
qty,depinit,amplinit) VALUES
(1,'2012-04-17','A1','functional','Furniz1','SS1',1,'DP1','AA1'),
(1,'2012-04-17','A2','rebut','Furniz1','SS2',1,'DP1','AA1'),
(1,'2012-04-17','B2','functional','Furniz1',NULL,10,'DP1','AA1'),
(2,'2012-04-18','B2','incert','Furniz1',NULL,15,'DP2','AA1'),
(2,'2012-04-18','C1','defect','Furniz1','SS3',1,'DP2','AA1'),
(3,'2012-04-18','C1','defect','Furniz1','SS3',1,'DP3','AA1'),
(3,'2012-04-18','B2','functional','Furniz2',NULL,25,'DP3','AA1');
-- select logx.valid_br(1) as rez;



--########## DREPTURI DE ACCES ########################
--pentru a putea şterge utilizatorii şi drepturile de acces trebuie să 
-- ne asigurăm că nu mai există obiecte create de aceştia, obiectele sunt 
-- trecute în posesia utilizatorului postgres
--DROP OWNED BY "LOGX";-- LA A DOUA RULARE A FIŞIERULUI SE VA ŞTERGE 
-- COMENTARIUL !!!
DROP ROLE IF EXISTS logx_sw ; DROP ROLE IF EXISTS "LOGX";
CREATE ROLE logx_sw LOGIN PASSWORD 'gugu' SUPERUSER INHERIT NOCREATEDB 
CREATEROLE; COMMENT ON ROLE logx_sw IS 'supervizor logx';
--se crează GRUPUL DE ACCES LOGX
CREATE ROLE "LOGX";
-- se oferă acces utlizatorului logx_sw la grupul LOGX
GRANT logx_sw TO "LOGX";
--asignări acces
GRANT CONNECT, TEMPORARY ON DATABASE picdb TO GROUP "LOGX";
GRANT ALL ON SCHEMA logx TO "LOGX";
GRANT EXECUTE ON FUNCTION logx.add_bp_id(integer, text, text, text, 
integer) TO GROUP "LOGX";
GRANT EXECUTE ON FUNCTION logx.bp_nou(text, date) TO GROUP "LOGX";
GRANT EXECUTE ON FUNCTION logx.br_nou(date) TO GROUP "LOGX";
GRANT EXECUTE ON FUNCTION logx.bt_valid(integer) TO GROUP "LOGX";
GRANT EXECUTE ON FUNCTION logx.del_bp_id(integer, text, text, text) TO 
GROUP "LOGX";
GRANT EXECUTE ON FUNCTION logx.id_nou(text) TO GROUP "LOGX";
GRANT EXECUTE ON FUNCTION logx.nom_add(text, text, text, text) TO GROUP 
"LOGX";
GRANT EXECUTE ON FUNCTION logx.q_x(text, smallint, text[], text[], 
boolean[], boolean[], text[], text[], text) TO GROUP "LOGX";
GRANT EXECUTE ON FUNCTION logx.valid_bp(integer) TO GROUP "LOGX";
GRANT EXECUTE ON FUNCTION logx.valid_br(integer) TO GROUP "LOGX";
GRANT ALL ON SEQUENCE logx.bp_seq TO GROUP "LOGX";
GRANT ALL ON SEQUENCE logx.br_idx_seq TO GROUP "LOGX";
GRANT ALL ON SEQUENCE logx.br_seq TO GROUP "LOGX";
GRANT ALL ON SEQUENCE logx.id_seq TO GROUP "LOGX";
GRANT ALL ON SEQUENCE logx.trx_nrlin_seq TO GROUP "LOGX";
GRANT ALL ON TABLE logx._bp TO GROUP "LOGX";
GRANT ALL ON TABLE logx._bt TO GROUP "LOGX";
GRANT ALL ON TABLE logx.acces TO GROUP "LOGX";
GRANT ALL ON TABLE logx.bp_ TO GROUP "LOGX";
GRANT ALL ON TABLE logx.br TO GROUP "LOGX";
GRANT ALL ON TABLE logx.bt_ TO GROUP "LOGX";
GRANT ALL ON TABLE logx.inx TO GROUP "LOGX";
GRANT ALL ON TABLE logx.loc TO GROUP "LOGX";
GRANT ALL ON TABLE logx.nom TO GROUP "LOGX";
GRANT ALL ON TABLE logx.outx TO GROUP "LOGX";
GRANT ALL ON TABLE logx.stx TO GROUP "LOGX";
GRANT ALL ON TABLE logx.trx TO GROUP "LOGX";
-- drepturile de acces de tip public se pot şterge şi manual din pgAdmin IV
--############################# 