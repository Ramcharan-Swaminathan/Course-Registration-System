

#ifndef COURSE_REGISTRATION_MODIFYING_FUNCTIONS_H
#define COURSE_REGISTRATION_MODIFYING_FUNCTIONS_H


int split_string(char [][10], char *, char *);

void list_to_str(char [][10],int ,char str[],char*);

void delete_element_in_array(char arr[][10],int* records,char element[]);

void delete_element_in_int_array(int arr[],int* records,int element);

//int if_already_in_course(char course_code[],char registered_courses[][10]);

void add_element_in_array(char arr[][10],int* records,char element[]);


#endif //COURSE_REGISTRATION_MODIFYING_FUNCTIONS_H
