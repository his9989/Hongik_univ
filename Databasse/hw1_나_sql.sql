/* create table */
create table suppliers(
    sid VARCHAR(20),
    sname VARCHAR(20),
    address VARCHAR(20),
    PRIMARY KEY(sid));
    
create table parts(
    pid VARCHAR(20),
    pname VARCHAR(20),
    color VARCHAR(20),
    PRIMARY KEY (pid));
    
create table Catalog(
    sid VARCHAR(20),
    pid VARCHAR(20),
    cost real,
    PRIMARY KEY(sid, pid),
    FOREIGN KEY (sid) REFERENCES suppliers,
    FOREIGN KEY (pid) REFERENCES parts);
    
/* insert data */
insert INTO parts VALUES ('part1_pid', 'part1_pname', 'red');
insert INTO parts VALUES ('part2_pid', 'part2_pname', 'red');
insert INTO parts VALUES ('part3_pid', 'part3_pname', 'red');
insert INTO parts VALUES ('part4_pid', 'part4_pname', 'green');
insert INTO parts VALUES ('part5_pid', 'part5_pname', 'green');
insert INTO parts VALUES ('part6_pid', 'part6_pname', 'blue');

insert INTO Suppliers Values ('supp1_sid', 'supp1_sname', 'add1');
insert INTO Suppliers Values ('supp2_sid', 'supp2_sname', 'add2');
insert INTO Suppliers Values ('supp3_sid', 'supp3_sname', 'add3');
insert INTO Suppliers Values ('supp4_sid', 'supp4_sname', 'add4');

insert INTO Catalog values ('supp1_sid', 'part1_pid', 100);
insert INTO Catalog values ('supp1_sid', 'part4_pid', 200);
insert INTO Catalog values ('supp1_sid', 'part6_pid', 300);
insert INTO Catalog values ('supp2_sid', 'part1_pid', 150);
insert INTO Catalog values ('supp2_sid', 'part2_pid', 200);
insert INTO Catalog values ('supp2_sid', 'part4_pid', 250);
insert INTO Catalog values ('supp3_sid', 'part3_pid', 300);
insert INTO Catalog values ('supp3_sid', 'part5_pid', 400);
insert INTO Catalog values ('supp4_sid', 'part5_pid', 500);
insert INTO Catalog values ('supp4_sid', 'part6_pid', 600);

/* query3. 나)1번 */
select c1.pid, s.sname
from Catalog c1, suppliers s
where c1.sid = s.sid and c1.cost = (select MAX(c2.cost)
                                    from catalog c2
                                    where c1.pid = c2.pid);

/* query4. 나)2번 */
select c.sid
from Catalog c, Parts p
where c.pid = p.pid and p.color = 'red'
INTERSECT
select c2.sid
from Catalog c2, parts p2
where c2.pid = p2.pid and p2.color = 'green';
