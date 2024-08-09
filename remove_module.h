

#ifndef COURSE_REGISTRATION_REMOVE_MODULE_H
#define COURSE_REGISTRATION_REMOVE_MODULE_H
/*
#include <raylib.h>
#include "Structure_definitions.c"
*/
#include "all_includes_and_macros.h"


int retrieve_courses(int student_id,char reg_courses[][10]);

int remove_check_eligibilty(int student_id);

int Labels_for_courses(char reg_courses[][10],int reg_records,float pos_x,float pos_y,bool commands[]);

int remove_courses(int student_id,char course_code[10]);

int retrieve_waitlist_sections(int student_id,char waitlist_sections[][10]);

int Labels_for_waitlist_sections(char waitist_secctions[][10],int waitlist_records,float pos_x,float pos_y,bool commands[]);

int remove_from_waitlist(char section_code[],int student_id);

int retrieve_course_array(int reg_records,char reg_courses[][10],Course courses[]);

int get_course_from_sec(char section_code[10],Course *course);

int retrieve_non_mandatory_regcourses(int student_id,char reg_courses[][10]);
#endif //COURSE_REGISTRATION_REMOVE_MODULE_H
