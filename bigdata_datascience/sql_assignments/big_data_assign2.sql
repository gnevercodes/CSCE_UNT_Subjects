Create database ganesh_bigdata_db;
use  ganesh_bigdata_db;
create table studentinbigdata(
student_name varchar(25),
students_present_age int,
course_enrolled_in char(25),
student_identification_number int
);

create table subjects_all_enrolled(
subject_name varchar(25),
course_code int,
course_name char(25)
);

alter table subjects_all_enrolled
modify course_name char(25) not null; 

INSERT INTO studentinbigdata (`student_name`, `students_present_age`, `course_enrolled_in`, `student_identification_number`)
VALUES ('ganesh', 23, 'big_data_sciene', 11700551),
       ('pranav', 23, 'big_data', 11700331),
       ('aryanth', 25, 'cyber_data', 1700222);

INSERT INTO subjects_all_enrolled (`subject_name`, `course_code`, `course_name`)
values ('big_data','5301','big-data-data-science'),
       ('computer_algo_jiang_beli','5507','algos-dsa'),
       ('fdb','5201','fundamentalsofdatabase');


select * from subjects_all_enrolled;

select * from studentinbigdata;

select * from studentinbigdata where student_identification_number=11700551;
select * from studentinbigdata where students_present_age=23;

select student_name from studentinbigdata where students_present_age=23;



select
    s.student_name,
    s.students_present_age,
    s.course_enrolled_in
from
    studentinbigdata s
join
    subjects_all_enrolled se ON s.course_enrolled_in = se.course_name;



