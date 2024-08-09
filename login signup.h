//
// Created by Ramcharan on 20-05-2024.
//

#ifndef COURSE_REGISTRATION_LOGIN_SIGNUP_H
#define COURSE_REGISTRATION_LOGIN_SIGNUP_H

#include "all_includes_and_macros.h"


int check_credentials(int student_id, char password[]);

int check_temp(int temp_id, char temp_pass[]);

int gen_new_id();

StudentInfo get_current_student(int student_id);

void add_new_details(int new_id,char name[],char department[],float percent12th,char email[]);

int signup();

void add_to_login_db(int new_id, char new_password[]);
void decrement_new_id();

int check_admin_credentials(int admin_id, char password[]);

int if_present_in_terms(char student_id[10]);

int write_student_to_terms(char student_id[10]);

int remove_temp_detail(int  student_id);




#endif //COURSE_REGISTRATION_LOGIN_SIGNUP_H
