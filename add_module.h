

#ifndef COURSE_REGISTRATION_ADD_MODULE_H
#define COURSE_REGISTRATION_ADD_MODULE_H

#include <raylib.h>
#include "all_includes_and_macros.h"


int retrieve_sem_courses(int student_id,Course current_courses[]);

int add_check_eligibilty(int student_id);


int Labels_for_section(Section sections[],int section_count,float pos_x,float pos_y,
                       bool faculty_coommands[],bool allot_commands[],bool waitlist_commands[],int student_id);


int retrieve_section(Course current_cours,Section section_details[]);


int Labels_for_sem_courses(Course courses[],int course_count,float pos_x,float pos_y,bool commands[]);

int pre_requisites(Course *Current_course_,int  student_id);


FacultyInfo get_fac_detials(char faculty_code[]);

int allot_section(int student_id,char section_code[],char course_code[]);
int allot_waitlist(int student_id,char course_code[],char section_code[]);

int if_already_registered(StudentInfo student, char course_code[]);
int if_already_in_waitlist(int  student_id, char section_code[]);
int if_student_registered_mandatory(StudentInfo student);

int retrieve_non_mandatory_courses(int student_id,Course current_courses[]);

int not_registered_mandatory(StudentInfo student,Course mandatory_courses[]);


int retrieve_non_mandatory_non_registered_courses(int student_id,Course current_courses[]);

void allot_all_students();

#endif