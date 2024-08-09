
#ifndef UNTITLED_TRIAL_SLOT_H
#define UNTITLED_TRIAL_SLOT_H

#include "all_includes_and_macros.h"


void divide_slots();

int admin_allow(int student_id);

int admin_block(int student_id);

int allow_slot(char slot[]);

int block_slot(char slot[]);

void check_if_allowed(int chec_arr[4]);

void DrawBarChart( char labels[][10], const int* counts, int labelCount, int chartWidth, int chartHeight, Vector2 position);

void dept_wise_bar(bool* dept_got,int width, int height, Vector2 position);

void sem_wise_bar(bool* sem_got,int width, int height, Vector2 position);

void get_data_reg_student_deptwise(char dept[][10], int dept_count[] , int* n);

void get_data_reg_student_semwise(int sems[], int sem_count[],int* n);

void reg_student_dept_wise_bar(bool *reg_dept_data_displayed,int width, int height, Vector2 position);

void reg_student_sem_wise_bar(bool *reg_sem_data_diaplayed,int width, int height, Vector2 position);

int check_admin_control(int student_id);

int if_slot_on(int student_id,char department[],int semester);

TimeDifference GetTimeDifference(time_t endTime);

time_t ParseDateTime(const char* dateTime);

void SaveEndTimeToFile(time_t endTime);

time_t LoadEndTimeFromFile();

void ResetEndTimeInFile();

int find_which_slot(int student_id);

Course get_max_reg_course(char dept[],int sem);

int check_eligibilty(StudentInfo current_student);
#endif //UNTITLED_TRIAL_SLOT_H
