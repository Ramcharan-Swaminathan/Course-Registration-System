
#ifndef UNTITLED_TRIAL_VIEW_MODULE_H
#define UNTITLED_TRIAL_VIEW_MODULE_H

#include "all_includes_and_macros.h"


int calculate_total_credits(int student_id);

Section reg_sec_from_course_code(int student_id, char course_code[10]);
int Labels_for_reg_courses_view(Course courses[],bool *already_retrieved,char reg_courses[][10],int reg_records,float pos_x,float pos_y,bool commands[],int student_id);
int Labels_for_waitlist_sections_view(bool *wait_list_view_read,char waitist_secctions[][10],int waitlist_records,float pos_x,float pos_y,int student_id);


void sort_by_cgpa(char student[]);

void sort_waitlist();

int find_waitlist_position(int student_id, char section_code[10]);


#endif //UNTITLED_TRIAL_VIEW_MODULE_H
