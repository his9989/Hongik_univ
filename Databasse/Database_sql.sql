create table Temp(
    pid integer,
    pname VARCHAR(20),
    Primary Key(pid));

insert into Temp VALUES (111, 'aaa');

select * from Temp;

update Temp set pname = 'ccc' where pid=111;

delete from Temp where pname='ccc';

/* Having은 그룹당 하나의 값만 나와야한다. */
/* ------------------------------------------------------------------- */
select * from Student;
select * from Class;
select * from Enrolled;
select * from Faculty;
/* 5.1 */
/* num1 */
select Distinct S.sname
from Student S, Faculty f, Class c, Enrolled E
where S.snum = E.snum And E.cname = C.name And C.fid = F.fid And S.standing = 'JR' And F.fname Like 'I%';

/* num2 */
select Max(S.age)
from Student S, Enrolled E, Class C, Faculty F
where S.major = 'History' Or (S.snum = E.snum And E.cname = C.name And C.fid = F.fid And F.fname like 'I%');

/* num3 */
select Distinct C.name
from Class C
where C.room = 'R128'
UNION
select Distinct C2.name
from class C2
where 5 < (select Count(E.snum)
           from Enrolled E
           where E.cname = C2.name);
           
/* num4 */
select Distinct S.sname
from Student S, Enrolled E1, Enrolled E2, Class C1, Class C2
where S.snum = E1.snum And E1.cname = C1.name And S.snum = E2.snum And E2.cname = C2.name
        And C1.name <> C2.name And C1.meets_at = C2.meets_at;

/* num5 */
select F.fname
from Faculty F
where Not EXISTS (select Distinct C.room
                  from Class C
                  Minus
                  select Distinct C2.room
                  from Class C2
                  where C2.fid = F.fid);

/* num6 */
select F.fname
from Faculty F
where 5 > (select Count(S.snum)
           from Student S, Class C, Enrolled E
           where S.snum = E.snum And E.cname = C.name And C.fid = F.fid);

/* num7 */
select S.Standing, AVG(S.age)
from Student S
Group By S.Standing;

/* num8 */
select S.standing, AVG(S.age)
from Student S
Group By S.standing
HAVING S.standing <> 'JR';

/* num9 */                  
select F.fname, Count(C.fid)
from Class C, Faculty F
where F.fid = C.fid And Not Exists (select Distinct C2.room
                   from Class C2
                   where C2.fid = F.fid
                   Minus
                   select Distinct C3.room
                   from Class C3
                   where C3.room = 'R128')
Group By F.fname;

/* num10 */
select Distinct Temp.name
from (select S.sname as name, count(E.cname) as cnt
          from Student S, Enrolled E
          where E.snum = S.snum
          Group By S.sname, S.snum) Temp
where Temp.cnt = (select Max(Temp.cnt)
                  from (select S.sname as name, count(E.cname) as cnt
                       from Student S, Enrolled E
                       where E.snum = S.snum
                       Group By S.sname, S.snum) Temp);
                       
/* num11 */
select Distinct S.sname
from Student S
where S.sname Not In (select S2.sname
                      from Student S2, Enrolled E
                      where E.snum = S2.snum);

/* num12 */
select S.age, S.standing
from Student S
Group By S.age, S.standing
Having S.standing In (select S2.standing
                      from Student S2
                      where S2.age = S.age
                      Group By S2.standing, S2.age
                      Having Count (*) >= All (select Count(*)
                                               from Student S3
                                               where S3.age = S.age
                                               Group By S3.standing, S3.age))
ORDER BY S.age;
             
/* ------------------------------------------------------------------- */
/* 5.2 */
select * from suppliers;
select * from Parts;
select * from Catalog;
/* num1 */
select P.pname
from Parts P, Catalog C
where C.pid = P.pid;

/* num2 */
select S.sname
from Suppliers S
where Not Exists (select P.pid
                  from Parts P
                  Minus
                  select P2.pid
                  from Parts P2, Catalog C
                  where S.sid = C.sid And C.pid = P2.pid);
                  
/* num3 */
select S.sname
from Suppliers S
where Not Exists (Select P.pid
                  from Parts P
                  where P.color = 'Red'
                  Minus
                  Select P2.pid
                  from Parts P2, Catalog C
                  where S.sid = C.sid And C.pid = P2.pid);

/* num4 */
select Distinct P.pname
from Parts P, Catalog C, Suppliers S
where S.sname = 'Acme Widget Suppliers' and S.sid = C.sid and C.pid = P.pid;

/* num5 */
select C.sid
from Catalog C
where c.cost > (select Avg(C2.cost)
                from Catalog C2
                where c.pid = C2.pid);

/* num6 */
select C.pid, Max(C.cost)
from Catalog C
Group By C.pid
Order By C.pid;

/* num7 */
select S.sid
from Suppliers S
where Not Exists (select P.pid
                  from Parts P, Catalog C
                  where P.pid = C.pid And S.sid = C.sid
                  Minus
                  select P2.pid
                  from Parts P2
                  where P2.color = 'Red');

/* num8 */
select S.sid
from Suppliers S
where S.sid In (select C.sid
                from Catalog C, Parts P
                where C.pid = P.pid and P.color = 'Red')
Intersect
select S2.sid
from Suppliers S2
where S2.sid in (select C2.sid
                 from Catalog C2, Parts P2
                 where C2.pid = P2.pid and P2.color = 'Green');

/* num9 */
select S.sid
from Suppliers S
where S.sid In (select C.sid
                from Catalog C, Parts P
                where C.pid = P.pid and P.color = 'Red')
Union
select S2.sid
from Suppliers S2
where S2.sid in (select C2.sid
                 from Catalog C2, Parts P2
                 where C2.pid = P2.pid and P2.color = 'Green');

/* num10 */ /* Not in, Not Exists 뭘 사용하든 상관없다 */
select Distinct S.sname, Count(C3.pid)
from Suppliers S, Catalog C3
where S.sid = C3.sid And
    S.sid Not IN (select C.sid
                    from Catalog C, Parts P
                    where C.pid = P.pid And C.sid = S.sid
                    Minus
                    select C2.sid
                    from Catalog C2, Parts P2
                    where C2.pid = P2.pid And P2.color = 'Green')
Group By S.sname, S.sid;

select Distinct S.sname, Count(C3.pid)
from Suppliers S, Catalog C3
where S.sid = C3.sid And
      Not Exists (select C.sid
                  from Catalog C, Parts P
                  where C.pid = P.pid And C.sid = S.sid
                  Minus
                  select C2.sid
                  from Catalog C2, Parts P2
                  where C2.pid = P2.pid And P2.color = 'Green')
Group By S.sname, S.sid;

/* num11 */
select S.sname, Max(C.cost)
from Suppliers S, Catalog C
where S.sid = C.sid
      and S.sid in ( select C2.sid
                     from Catalog C2, Parts P2
                     where C2.pid = P2.pid And P2.color = 'Red'
                     Intersect
                     select C3.sid
                     from Catalog C3, Parts P3
                     where C3.pid = P3.pid And P3.color = 'Green')
Group By S.sname, S.sid;

/* ------------------------------------------------------------------- */
/* 5.3 Data set */
select * from Flights;
select * from Aircraft;
select * from Certified;
select * from Employees;
/* num1 */
select Distinct A.aname
from Aircraft A, Certified C, Employees E
where C.aid = A.aid and C.eid = E.eid
    and E.eid not in ( select E2.eid
                       from Employees E2
                       where E2.salary < 80000);

/* num2 */
select E.eid, Max(A.crusingrange)
from Employees E, Aircraft A, Certified C
where C.eid = E.eid and C.aid = A.aid
    and 3 < (select Count(C2.aid)
             from Certified C2
             where C2.eid = E.eid)
group by E.eid;

/* num3 */
select E.ename
from Employees E
where E.salary < (select min(F.price)
                  from Flights F
                  where F.origin = 'Los Angeles' and f.destination = 'Honolulu');

/* num4 */
select A.aname, AVG(E.salary)
from Aircraft A, Certified C, Employees E
where a.crusingrange > 1000 and A.aid = C.aid and C.eid = E.eid
Group By A.aname, A.aid;

/* num5 */
select Distinct E.ename
from Employees E, Certified C, Aircraft A
where C.eid = E.eid and C.aid = A.aid and A.aname like 'Boeing%';

/* num6 */
select A.aid
from Aircraft A, Flights F
where F.origin = 'Los Angeles' and F.destination = 'Chicago' and F.distance < a.crusingrange;

/* num7 */
select Distinct F.flno
from Flights F, Employees E, Aircraft A, Certified C
where E.salary > 100000 and E.eid = C.eid and C.aid = A.aid and A.crusingrange > F.distance;

/* num8 */
select Distinct E.ename
from Employees E, Certified C, Aircraft A
where E.eid = C.eid and C.aid = A.aid and
    Not Exists (select A2.aid
                  from Aircraft A2, Certified C2
                  where A2.aid = C2.aid and C2.eid = E.eid
                  Minus
                  select A3.aid
                  from Aircraft A3
                  where A3.aname <> 'Boeing%')
Intersect
select Distinct E4.ename
from Employees E4, Certified C4, Aircraft A4
where E4.eid = C4.eid and C4.aid = A4.aid and A4.crusingrange > 3000;

/* num9 */
/* 도착시간 value가 시간으로 딱 떨어지지 않으므로 쿼리로는 짜기 힘듬 */
/* 아래 쿼리는 논리적 구조 */
select F1.departs
from Flights F1, Flights F2
where F1.origin = 'Madison' and F1.Destination = F2.origin and F2.destination = 'New York' and F2.arrives < '18PM'
Union
select F3.departs
from Flights F3, Flights F4, Flights F5
where F3.origin = 'Madison' and F3.Destination = F4.origin and F4.destination = F5.origin and F5.destination = 'New York' and F5.arrives < '18PM';

/* num10 */
select AVG(E.salary)-AVG(E2.salary)
from Employees E, Certified C, Aircraft A, Employees E2
where E.eid = C.eid and C.aid = A.aid;

/* num11 */
select Distinct E.ename, E.salary
from Employees E, certified C,
    (select AVG(E2.salary) avgsalary
     from Certified C2, Aircraft A2, Employees E2
     where C2.eid = E2.eid and C2.aid = A2.aid)Temp
where E.eid <> C.eid and E.salary > Temp.avgsalary
Group By E.ename, E.salary, E.eid;

/* num12 */
select E.ename
from Employees E
where E.eid Not In (select C.eid
                    from Certified C, Aircraft A
                    where C.aid = A.aid and A.crusingrange < 1000);
                    
/* num13 */
select E.ename
from Employees E
where E.eid Not In (select C.eid
                    from Certified C, Aircraft A
                    where C.aid = A.aid and A.crusingrange < 1000)
Intersect
select E2.ename
from Employees E2
where 2 <= (select count(C2.aid)
            from Certified C2
            where C2.eid = E2.eid);

/* num14 */
select Distinct E.ename
from Employees E
where E.eid not in (select C.eid
                    from Certified C, Aircraft A
                    where C.aid = A.aid and A.crusingrange < 1000)
Minus
select Distinct E2.ename
from Employees E2
where E2.eid Not In (select C2.eid
                     from Certified C2, Aircraft A2
                     where C2.aid = A2.aid and A2.aname = 'Boeing%');

/* ------------------------------------------------------------------- */
/* 5.4 Data set */
select * from dept;
select * from works;
select * from Emp;

/* 1번 */
select E.ename, E.age
from Emp E, Works W1, Works W2, Dept D1, Dept D2
where E.eid = W1.eid And W1.did = D1.did And D1.dname = 'Hardware'
    AND E.eid = W2.eid And W2.did = D2.did And D2.dname = 'Software';

/* 2번 */
select W.did, Count(W.eid)
from Works W
Group By W.did
Having Sum(w.pct_time) > 2000;

/* 2번 전일제가 20명 이상인 경우 */
select W.did, Count(W.eid)
from Works W
where w.pct_time = 100
Group By W.did
Having Count(W.eid)>20;

/* 3번 */
select E.ename
from Emp E, Works W, Dept D
where E.eid = W.eid And W.did = D.did And (E.salary > All(D.budget));

/* 4번 */
select D.managerid
from Dept D
where Not EXISTS (select D2.did
                  from Dept D2
                  where D2.managerid = D.managerid
                  MINUS
                  select D3.did
                  from Dept D3
                  where D3.budget>1000000);

/* 5번 */
select E.ename
from emp E, dept D
where D.managerid = E.eid And D.budget = (Select MAX(D2.budget)
                                          from dept D2);

/* 6번 */
select Distinct D.managerid
from Dept D
where 5000000 < (select sum(D2.budget)
                 from Dept D2
                 where D2.managerid = D.managerid);

/* 7번 */
select D.managerid
from Dept D
where D.budget in (select Max(D2.budget)
                   from  Dept D2);

/* 8번 */
select Distinct E.ename
from Dept D, Emp E
where D.managerid = E.eid
    and D.did in (select D2.did
                from Dept D2
                where Not Exists (select D3.did
                                  from Dept D3
                                  where D3.managerid = D2.managerid
                                  minus
                                  select D4.did
                                  from Dept D4
                                  where D4.budget > 1000000)
                Intersect
                select D5.did
                from Dept D5
                where 1 <= (select Count(D6.did)
                            from Dept D6
                            where D6.did = D5.did and D6.budget < 5000000));


           
