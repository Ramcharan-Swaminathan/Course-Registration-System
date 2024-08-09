

#include <raygui.h>
#include "all_includes_and_macros.h"
#define RAYGUI_IMPLEMENTATION






int Labels_for_reg_courses_view(Course courses[],bool *already_retrieved,char reg_courses[][10],int reg_records,float pos_x,float pos_y,bool commands[],int student_id){
    //Course courses[30];
    if (*already_retrieved == false){
        reg_records = retrieve_course_array(reg_records,reg_courses,courses);
        *already_retrieved = true;
    }
    Section current_section;
    char sl_no[2];
    int total_cred;
    char total_credits[10];

    char credits[10];
    GuiSetStyle(DEFAULT, TEXT_SIZE, 40);

    DrawRectangle(pos_x-10,pos_y-10-60,100,60,SKYBLUE);
    GuiLabel((Rectangle){pos_x,pos_y-60,100,30},"S.No");
    DrawRectangleLines(pos_x-10,pos_y-10-60,100,60,BLACK);

    DrawRectangle(pos_x+100-10,pos_y-10-60,250,60,SKYBLUE);
    GuiLabel((Rectangle){pos_x+100,pos_y-60,250,30},"Course Code");
    DrawRectangleLines(pos_x-10+100,pos_y-10-60,250,60,BLACK);

    DrawRectangle(pos_x+350-10,pos_y-10-60,800,60,SKYBLUE);
    GuiLabel((Rectangle){pos_x+350,pos_y-60,800,30},"Course Name");
    DrawRectangleLines(pos_x-10+350,pos_y-10-60,800,60,BLACK);

    DrawRectangle(pos_x+1150-10,pos_y-10-60,250,60,SKYBLUE);
    GuiLabel((Rectangle){pos_x+1150,pos_y-60,250,30},"Section Code");
    DrawRectangleLines(pos_x-10+1150,pos_y-10-60,250,60,BLACK);

    DrawRectangle(pos_x+1400-10,pos_y-10-60,250,60,SKYBLUE);
    GuiLabel((Rectangle){pos_x+1400,pos_y-60,250,30},"Faculty Code");
    DrawRectangleLines(pos_x-10+1400,pos_y-10-60,250,60,BLACK);

    DrawRectangle(pos_x+1650-10,pos_y-10-60,200,60,SKYBLUE);
    GuiLabel((Rectangle){pos_x+1650,pos_y-60,200,30},"Credits");
    DrawRectangleLines(pos_x-10+1650,pos_y-10-60,200,60,BLACK);


    for (int i = 0; i < reg_records;i++){

        current_section = reg_sec_from_course_code(student_id,courses[i].Course_code);
        sprintf(sl_no,"%d",i+1);
        sprintf(credits,"%d",courses[i].Credits);
        total_cred += courses[i].Credits;

        GuiLabel((Rectangle){pos_x,pos_y,100,30},sl_no);
        DrawRectangleLines(pos_x-10,pos_y-10,100,60,BLACK);

        GuiLabel((Rectangle){pos_x+100,pos_y,250,30},courses[i].Course_code);
        DrawRectangleLines(pos_x-10+100,pos_y-10,250,60,BLACK);

        if (courses[i].mandatory == 1){
            DrawRectangle(pos_x+350-10,pos_y-10,800,60,(Color) {255, 249, 196, 225});}

        GuiLabel((Rectangle){pos_x+350,pos_y,800,30},courses[i].Course_Name);
        DrawRectangleLines(pos_x-10+350,pos_y-10,800,60,BLACK);

        GuiLabel((Rectangle){pos_x+1150,pos_y,250,30},current_section.Section_code);
        DrawRectangleLines(pos_x-10+1150,pos_y-10,250,60,BLACK);

        commands[i] = GuiButton((Rectangle){pos_x+1400,pos_y-5,220,50},current_section.Faculty_code);
        DrawRectangleLines(pos_x-10+1400,pos_y-10,250,60,BLACK);

        GuiLabel((Rectangle){pos_x+1650,pos_y,200,30},credits);
        DrawRectangleLines(pos_x-10+1650,pos_y-10,200,60,BLACK);

        pos_y = pos_y+60;
    }
    total_cred = calculate_total_credits(student_id);
    sprintf(total_credits,"%d",total_cred);
    DrawRectangle(pos_x+1400-10,pos_y-10,250,60,SKYBLUE);
    GuiLabel((Rectangle){pos_x+1400,pos_y,250,30},"Total");
    DrawRectangleLines(pos_x-10+1400,pos_y-10,250,60,BLACK);

    GuiLabel((Rectangle){pos_x+1650,pos_y,200,30},total_credits);
    DrawRectangleLines(pos_x-10+1650,pos_y-10,200,60,BLACK);
}




Section reg_sec_from_course_code(int student_id, char course_code[10]){

    Course course_detials[COURSE_DATASIZE];
    Course Current_course;
    int course_records = read_course_data(course_detials,COURSE_DB);
    for (int i = 0; i < course_records; i++){
        if (strcmp(course_detials[i].Course_code,course_code) ==0){
            Current_course = course_detials[i];
            break;
        }
    }

    StudentInfo student_detials[STU_DATASIZE];
    int student_records = read_Student_data(student_detials,STUDENT_DB);
    StudentInfo Current_student;
    for (int i = 0; i<student_records;i++){
        if (student_detials[i].student_id == student_id){
            Current_student = student_detials[i];
            break;
        }
    }


    int index = 0;
    char reg_courses[10][10];
    int num_reg_courses = split_string(reg_courses,Current_student.registered_courses,"|");
    for (int i = 0;i<num_reg_courses;i++){
        if (strcmp(reg_courses[i],course_code) == 0){
            index = i;
            break;
        }
    }

    char reg_sections[10][10];
    int  num_reg_sections = split_string(reg_sections,Current_student.registerd_sections,"|");
    char current_sec_id[10];
    strcpy(current_sec_id,reg_sections[index]);

    Section section_details[SECTION_DATASIZE];
    Section Current_section;
    int section_records = read_Section_data(section_details,SECTION_DB);
    for (int i = 0;i<section_records;i++){
        if (strcmp(section_details[i].Section_code,current_sec_id) == 0){
            return section_details[i];
        }
    }

}


int calculate_total_credits(int student_id){
    StudentInfo student_detials[STU_DATASIZE];
    int student_records = read_Student_data(student_detials,STUDENT_DB);
    StudentInfo Current_student;
    for (int i = 0; i<student_records;i++){
        if (student_detials[i].student_id == student_id){
            Current_student = student_detials[i];
            break;
        }
    }

    int index = 0;
    char reg_courses[10][10];
    int num_reg_courses = split_string(reg_courses,Current_student.registered_courses,"|");
    int total_credits = 0;
    Course course_details[COURSE_DATASIZE];
    int course_records = read_course_data(course_details,COURSE_DB);
    for (int i = 0; i<num_reg_courses;i++){
        for (int j = 0; j<course_records;j++){
            if (strcmp(reg_courses[i],course_details[j].Course_code) == 0){
                total_credits += course_details[j].Credits;
            }
        }
    }
    return total_credits;
}





int Labels_for_waitlist_sections_view(bool *wait_list_view_read,char waitist_secctions[][10],int waitlist_records,float pos_x,float pos_y,int student_id){

    static Course current_course;
    static Course course_arr[30];
    static int waitlist_pos[30];
    char index [3];
    if(*wait_list_view_read == false) {

        for (int i = 0; i < waitlist_records; i++) {
            get_course_from_sec(waitist_secctions[i], &current_course);
            course_arr[i] = current_course;
            waitlist_pos[i] = find_waitlist_position(student_id, waitist_secctions[i]);
        }
        *wait_list_view_read = true;
    }


    GuiSetStyle(DEFAULT, TEXT_SIZE, 40);


    DrawRectangle(pos_x-10-100,pos_y-10-60,100,60,SKYBLUE);
    GuiLabel((Rectangle){pos_x-100,pos_y-60,100,30},"S.No");
    DrawRectangleLines(pos_x-10-100,pos_y-10-60,100,60,BLACK);

    DrawRectangle(pos_x-10,pos_y-10-60,250,60,SKYBLUE);
    GuiLabel((Rectangle){pos_x,pos_y-60,250,30},"Course Code");
    DrawRectangleLines(pos_x-10,pos_y-10-60,250,60,BLACK);

    DrawRectangle(pos_x+250-10,pos_y-10-60,800,60,SKYBLUE);
    GuiLabel((Rectangle){pos_x+250,pos_y-60,800,30},"Course Name");
    DrawRectangleLines(pos_x+250-10,pos_y-10-60,800,60,BLACK);

    DrawRectangle(pos_x+1050-10,pos_y-10-60,250,60,SKYBLUE);
    GuiLabel((Rectangle){pos_x+1050,pos_y-60,250,30},"Section Code");
    DrawRectangleLines(pos_x+1050-10,pos_y-10-60,250,60,BLACK);

    DrawRectangle(pos_x+1300-10,pos_y-10-60,300,60,SKYBLUE);
    GuiLabel((Rectangle){pos_x+1300,pos_y-60,300,30},"Waitlist Position");
    DrawRectangleLines(pos_x+1300-10,pos_y-10-60,300,60,BLACK);


    for (int i = 0;i<waitlist_records;i++) {

        sprintf(index,"%d",i+1);

        GuiLabel((Rectangle) {pos_x-100, pos_y, 100, 30}, index);
        DrawRectangleLines(pos_x - 10 -100, pos_y - 10, 100, 60, BLACK);

        GuiLabel((Rectangle) {pos_x, pos_y, 250, 30}, course_arr[i].Course_code);
        DrawRectangleLines(pos_x - 10, pos_y - 10, 250, 60, BLACK);

        GuiLabel((Rectangle) {pos_x + 250, pos_y, 800, 30}, course_arr[i].Course_Name);
        DrawRectangleLines(pos_x + 250 - 10, pos_y - 10, 800, 60, BLACK);

        GuiLabel((Rectangle) {pos_x + 1050, pos_y, 250, 30}, waitist_secctions[i]);
        DrawRectangleLines(pos_x + 1050 - 10, pos_y - 10, 250, 60, BLACK);

        sprintf(index,"%d",waitlist_pos[i]+1);
        GuiLabel((Rectangle) {pos_x + 1300, pos_y, 300, 30}, index);
        DrawRectangleLines(pos_x + 1300 - 10, pos_y - 10, 300, 60, BLACK);

        pos_y = pos_y + 60;
    }

}





void sort_by_cgpa(char student[]) {
    char splited_std[100][10];
    char student_s[strlen(student) + 1];
    strcpy(student_s, student);
    int student_count = split_string(splited_std, student_s, "|");

    float remp[100][3];
    for(int i=0;i<student_count;i++){
        remp[i][1]= atof(splited_std[i]);
    }

    StudentInfo arr[STU_DATASIZE];
    int records = read_Student_data(arr, STUDENT_DB);

    for(int i=0;i<records;i++){
        for(int j=0;j<student_count;j++){
            if(arr[i].student_id==remp[j][1]){
                remp[j][0]=arr[i].cgpa;
                remp[j][2] = arr[i].percent12th;
            }
        }
    }

    int n=student_count;

    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(remp[j][0]<remp[j+1][0]){
                float ele=remp[j][0];
                remp[j][0]=remp[j+1][0];
                remp[j+1][0]=ele;
                ele=remp[j][1];
                remp[j][1]=remp[j+1][1];
                remp[j+1][1]=ele;
                ele=remp[j][2];
                remp[j][2]=remp[j+1][2];
                remp[j+1][2]=ele;
            }
            else if(remp[j][0] == remp[j+1][0]){
                if(remp[j][2]<remp[j+1][2]){
                    float elp_hsc = remp[j][2];
                    remp[j][2] = remp[j+1][2];
                    remp[j+1][2] = elp_hsc;
                    elp_hsc =remp[j][1];
                    remp[j][1]=remp[j+1][1];
                    remp[j+1][1]=elp_hsc;
                    elp_hsc =remp[j][0];
                    remp[j][0]=remp[j+1][0];
                    remp[j+1][0]=elp_hsc;
                }
            }
        }
    }

    char sorted_stu_ids[500][10];
    char temp_stu_id[10];
    for (int i = 0;i<student_count;i++){
        sprintf(temp_stu_id,"%d",(int)remp[i][1]);
        strcpy(sorted_stu_ids[i],temp_stu_id);
    }

    list_to_str(sorted_stu_ids, student_count, student, "|");
}




void sort_waitlist(){


    Section section_details[SECTION_DATASIZE];
    int section_records = read_Section_data(section_details,SECTION_DB);

    for (int i = 0;i<section_records;i++){
        if (strcmp(section_details[i].waitlist_Students,"NULL") != 0) {
            sort_by_cgpa(section_details[i].waitlist_Students);
        }
    }

    write_section_data(section_details,SECTION_DB,section_records);



}




int find_waitlist_position(int student_id, char section_code[10]){

    Section section_details[SECTION_DATASIZE];
    int section_records = read_Section_data(section_details,SECTION_DB);

    for (int i = 0;i<section_records;i++){
        if (strcmp(section_details[i].Section_code,section_code) == 0){
            char waitlist_students[100][10];
            int num_waitlist_students = split_string(waitlist_students,section_details[i].waitlist_Students,"|");
            for (int j = 0;j<num_waitlist_students;j++){
                if (atoi(waitlist_students[j]) == student_id){
                    return j;
                }
            }
        }
    }
    return -1;
}












