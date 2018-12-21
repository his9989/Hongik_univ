/* create Pitchers table */
CREATE TABLE  Pitchers(
    pid VARCHAR(20),
    name VARCHAR(20),
    salary integer,
    PRIMARY KEY (pid));
    
/* create Teams table */
CREATE TABLE Teams(
    tid VARCHAR(20),
    location VARCHAR(20),
    manager VARCHAR(20),
    PRIMARY KEY (tid));
        
/* create Records table */
CREATE TABLE Records (
    rid VARCHAR(20),
    home_team_id VARCHAR(20),
    visiting_team_id VARCHAR(20),
    starting_pitcher_home VARCHAR(20),
    starting_pitcher_away VARCHAR(20),
    PRIMARY KEY(rid),
    FOREIGN KEY (visiting_team_id) REFERENCES Teams,
    FOREIGN KEY (home_team_id) REFERENCES Teams,
    FOREIGN KEY (starting_pitcher_home) REFERENCES Pitchers,
    FOREIGN KEY (starting_pitcher_away) REFERENCES Pitchers);
    
/* insert Pitchers data */
insert INTO pitchers VALUES ('p1', 'player1', 6000);
insert INTO pitchers VALUES ('p2', 'player2', 6000);
insert INTO pitchers VALUES ('p3', 'player3', 4000);
insert INTO pitchers VALUES ('p4', 'player4', 4000);
insert INTO pitchers VALUES ('p5', 'player5', 2000);
insert INTO pitchers VALUES ('p6', 'player6', 2000);
insert INTO pitchers VALUES ('p7', 'player7', 8000);
insert INTO pitchers VALUES ('p8', 'player8', 8000);
insert INTO pitchers VALUES ('p9', 'player9', 10000);
insert INTO pitchers VALUES ('p10', 'player10', 10000);
insert INTO pitchers VALUES ('p11', 'player11', 9000);

/* insert Teams data */
INSERT INTO Teams VALUES ('team1', 'seoul', 'park');
INSERT INTO Teams VALUES ('team2', 'busan', 'Han');
INSERT INTO Teams VALUES ('team3', 'tokyo', 'Kim');
INSERT INTO Teams VALUES ('team4', 'newyork', 'Yoon');
INSERT INTO Teams VALUES ('team5', 'Beijing', 'li');

/* insert Records data */
INSERT INTO Records VALUES ('record1', 'team2', 'team1', 'p3', 'p1');
INSERT INTO Records VALUES ('record2', 'team3', 'team1', 'p5', 'p1');
INSERT INTO Records VALUES ('record3', 'team4', 'team1', 'p7', 'p1');
INSERT INTO Records VALUES ('record4', 'team5', 'team1', 'p9', 'p1');

INSERT INTO Records VALUES ('record5', 'team1', 'team3', 'p1', 'p5');
INSERT INTO Records VALUES ('record6', 'team2', 'team3', 'p3', 'p5');
INSERT INTO Records VALUES ('record7', 'team4', 'team3', 'p7', 'p5');
INSERT INTO Records VALUES ('record8', 'team5', 'team3', 'p9', 'p5');

INSERT INTO Records VALUES ('record9', 'team2', 'team1', 'p4', 'p2');
INSERT INTO Records VALUES ('record10', 'team3', 'team1', 'p6', 'p2');
INSERT INTO Records VALUES ('record11', 'team5', 'team1', 'p10', 'p2');

/* query1. 가)1번 */
select p1.name
from pitchers p1
where p1.salary = (select  min(p2.salary)
                   from pitchers p2
                   where 1 = ( select count(DISTINCT(t1.tid))
                               from teams t1
                               where t1.tid IN (select t2.tid
                                                from teams t2
                                                MINUS
                                                select r1.home_team_id
                                                from records r1
                                                where r1.starting_pitcher_away = p2.pid)))
INTERSECT
select p3.name
from pitchers p3
where p3.pid IN ( select  p4.pid
                from pitchers p4
                where 1 = ( select count(DISTINCT(t3.tid))
                            from teams t3
                            where t3.tid IN (select t4.tid
                                             from teams t4
                                             MINUS
                                             select r3.home_team_id
                                             from records r3
                                             where r3.starting_pitcher_away = p4.pid)));

/* query2. 가)2번 */
select p1.name
from pitchers p1
where p1.salary = (select max(p2.salary)
                   from pitchers p2
                   where NOT EXISTS (select r1.rid
                                     from records r1
                                     MINUS
                                     select r2.rid
                                     from records r2
                                     where r2.starting_pitcher_away <> p2.pid and r2.starting_pitcher_home <> p2.pid))
INTERSECT
select p3.name
from pitchers p3
where p3.pid IN (select p4.pid
                   from pitchers p4
                   where NOT EXISTS (select r3.rid
                                     from records r3
                                     MINUS
                                     select r4.rid
                                     from records r4
                                     where r4.starting_pitcher_away <> p4.pid and r4.starting_pitcher_home <> p4.pid));