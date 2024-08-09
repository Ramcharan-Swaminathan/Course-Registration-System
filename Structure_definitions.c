#ifndef STRUCTURE_DEFINITIONS_C_INCLUDED
#define STRUCTURE_DEFINITIONS_C_INCLUDED



typedef struct
{


    char Department[30];
    short int Semester ;
    char Course_code[10];
    char Course_Name[100];
    int Elective;
    char Section_1[10];
    char Section_2[10];
    char Section_3[10];
    short int Credits;
    char pre_requisite[50];
    int mandatory;



} Course;

typedef struct
{


    char Section_code[10];
    char Faculty_code[10];
    int Available_seats;
    char Registered_Students[1000];
    int waitlist_availability;
    char waitlist_Students[40];

} Section;



typedef struct
{

    int user_id;
    char password[10];
} LoginInfo;


typedef struct
{

    int student_id;
    char name[40];
    char Department[10];
    int Semester;
    float percent12th;
    char completed_courses[4000];
    char registered_courses[300];
    char registerd_sections[300];
    char waitlist_sections[200];
    float cgpa;
    char email_id[50];
    int admin_control;


} StudentInfo;


typedef struct {

    char faculty_code[10];
    char faculty_name[60];
    char gender[10];
    char designation[60];
    char email_id[45];


}FacultyInfo;




typedef struct{

    char Department[10];
    int Semester;
    char slot[10000];
    int al_slot1;
    char slot1[2500];
    int al_slot2;
    char slot2[2500];
    int al_slot3;
    char slot3[2500];
    int al_slot4;
    char slot4[2500];

}Slot;






typedef struct {
    int days;
    int hours;
    int minutes;
    int seconds;
} TimeDifference;



#endif

