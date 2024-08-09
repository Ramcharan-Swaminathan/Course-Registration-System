

#ifndef FILE_FUNCTIONS_H_INCLUDED
#define FILE_FUNCTIONS_H_INCLUDED

#include "Structure_definitions.c"



int read_course_data(Course lis[],const char *);

int read_Section_data(Section lis[],const char * );

int read_Student_data(StudentInfo lis[],const char * );

int read_faculty_data(FacultyInfo lis[],const char * );

int read_login_data(LoginInfo lis[],const char * );

int read_slot_data(Slot lis[],const char *file_name);

int read_setted_time(char time[],const char * file_name);

int write_setted_time(char time[],const char * file_name);

int write_course_data(Course lis[],const char * ,int );

int write_section_data(Section lis[],const char * ,int );

int write_student_data(StudentInfo lis[],const char * ,int );

int write_login_data(LoginInfo lis[],const char * ,int );

int write_slot_data(Slot lis[],const char * file_name,int records);

int read_terms_data(char lis[][10],const char * file_name);

int write_terms_data(char lis[][10],const char * file_name , int records);

#endif // FILE_FUNCTIONS_H_INCLUDED
