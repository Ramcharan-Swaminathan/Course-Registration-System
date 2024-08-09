
#include <raygui.h>
#include "all_includes_and_macros.h"

#define RAYGUI_IMPLEMENTATION

#include "mail.h"


int retrieve_courses(int student_id, char reg_courses[][10]) {
    StudentInfo stu_details[STU_DATASIZE];
    StudentInfo current_student;
    int records;
    records = read_Student_data(stu_details, STUDENT_DB);
    for (int i = 0; i < records; i++) {
        if (stu_details[i].student_id == student_id) {
            current_student = stu_details[i];
            break;
        }
    }
    if (strcmp(current_student.registered_courses, "NULL") != 0) {
        int reg_records = split_string(reg_courses, current_student.registered_courses, "|");
        return reg_records;
    } else {
        return 0;
    }
}

int retrieve_non_mandatory_regcourses(int student_id, char reg_courses[][10]) {
    StudentInfo stu_details[STU_DATASIZE];
    StudentInfo current_student;
    int records;
    records = read_Student_data(stu_details, STUDENT_DB);
    for (int i = 0; i < records; i++) {
        if (stu_details[i].student_id == student_id) {
            current_student = stu_details[i];
            break;
        }
    }
    Course course_details[10];
    int course_records;
    course_records = retrieve_non_mandatory_courses(student_id, course_details);
    int k = 0;
    char all_reg_courses[20][10];
    int all_reg_records = split_string(all_reg_courses, current_student.registered_courses, "|");
    for (int i = 0; i < course_records; i++) {
        int flag = 0;
        for (int j = 0; j < all_reg_records; j++) {
            if (strcmp(course_details[i].Course_code, all_reg_courses[j]) == 0) {
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            strcpy(reg_courses[k], course_details[i].Course_code);
            k++;
        }
    }
    return k;

}


int retrieve_course_array(int reg_records, char reg_courses[][10], Course courses[30]) {
    Course course_details[COURSE_DATASIZE];
    int course_records;
    int k = 0;
    course_records = read_course_data(course_details, COURSE_DB);
    for (int i = 0; i < reg_records; i++) {
        for (int j = 0; j < course_records; j++) {
            if (strcmp(course_details[j].Course_code, reg_courses[i]) == 0) {
                courses[k] = course_details[j];
                k++;
                break;
            }
        }
    }
}

int Labels_for_courses(char reg_courses[][10], int reg_records, float pos_x, float pos_y, bool commands[]) {
    Course courses[COURSE_DATASIZE];
    retrieve_course_array(reg_records, reg_courses, courses);

    char credits[10];
    GuiSetStyle(DEFAULT, TEXT_SIZE, 40);

    DrawRectangle(pos_x - 10, pos_y - 10 - 60, 250, 60, SKYBLUE);
    GuiLabel((Rectangle) {pos_x, pos_y - 60, 250, 30}, "Course Code");
    DrawRectangleLines(pos_x - 10, pos_y - 10 - 60, 250, 60, BLACK);

    DrawRectangle(pos_x + 250 - 10, pos_y - 10 - 60, 800, 60, SKYBLUE);
    GuiLabel((Rectangle) {pos_x + 250, pos_y - 60, 800, 30}, "Course Name");
    DrawRectangleLines(pos_x + 250 - 10, pos_y - 10 - 60, 800, 60, BLACK);

    DrawRectangle(pos_x + 1050 - 10, pos_y - 10 - 60, 200, 60, SKYBLUE);
    GuiLabel((Rectangle) {pos_x + 1050, pos_y - 60, 200, 30}, "Credits");
    DrawRectangleLines(pos_x + 1050 - 10, pos_y - 10 - 60, 200, 60, BLACK);

    DrawRectangle(pos_x + 1250 - 10, pos_y - 10 - 60, 220, 60, SKYBLUE);
    GuiLabel((Rectangle) {pos_x + 1250, pos_y - 60, 220, 30}, "Select");
    DrawRectangleLines(pos_x + 1250 - 10, pos_y - 10 - 60, 220, 60, BLACK);


    for (int i = 0; i < reg_records; i++) {
        sprintf(credits, "%d", courses[i].Credits);
        GuiLabel((Rectangle) {pos_x, pos_y, 250, 30}, courses[i].Course_code);
        DrawRectangleLines(pos_x - 10, pos_y - 10, 250, 60, BLACK);

        GuiLabel((Rectangle) {pos_x + 250, pos_y, 800, 30}, courses[i].Course_Name);
        DrawRectangleLines(pos_x + 250 - 10, pos_y - 10, 800, 60, BLACK);

        GuiLabel((Rectangle) {pos_x + 1050, pos_y, 200, 30}, credits);
        DrawRectangleLines(pos_x + 1050 - 10, pos_y - 10, 200, 60, BLACK);

        commands[i] = GuiButton((Rectangle) {pos_x + 1250, pos_y, 200, 45}, "Remove");

        DrawRectangleLines(pos_x + 1250 - 10, pos_y - 10, 220, 60, BLACK);

        pos_y = pos_y + 60;
    }
}


int remove_check_eligibilty(int student_id) {

    StudentInfo stu_details[STU_DATASIZE];
    StudentInfo current_student;
    int records, reg_records;
    records = read_Student_data(stu_details, STUDENT_DB);
    for (int i = 0; i < records; i++) {
        if (stu_details[i].student_id == student_id) {
            current_student = stu_details[i];
            break;
        }
    }
    char reg_courses[20][10];
    if (strcmp(current_student.registered_courses, "NULL") == 0) {
        return 0;
    } else {
        reg_records = split_string(reg_courses, current_student.registered_courses, "|");

        if (reg_records > 4) {
            return 1;
        } else {
            return 0;
        }
    }
}


int remove_courses(int student_id, char course_code[10]) {

    int stu_records;
    StudentInfo stu_details[STU_DATASIZE];
    StudentInfo current_student;
    stu_records = read_Student_data(stu_details, STUDENT_DB);
    for (int i = 0; i < stu_records; i++) {
        if (student_id == stu_details[i].student_id) {
            current_student = stu_details[i];
            break;
        }
    }

    int course_records;
    Course choosen_course;
    Course course_detials[COURSE_DATASIZE];
    course_records = read_course_data(course_detials, COURSE_DB);
    for (int i = 0; i < course_records; i++) {
        if (strcmp(course_detials[i].Course_code, course_code) == 0) {
            choosen_course = course_detials[i];
            break;
        }
    }


    char reg_sections[20][10];
    int reg_section_records = split_string(reg_sections, current_student.registerd_sections, "|");
    char current_section_code[10];

    for (int i = 0; i < reg_section_records; i++) {
        if (strcmp(reg_sections[i], choosen_course.Section_2) == 0 ||
            strcmp(reg_sections[i], choosen_course.Section_1) == 0 ||
            strcmp(reg_sections[i], choosen_course.Section_3) == 0) {
            strcpy(current_section_code, reg_sections[i]);
            break;
        }
    }

    int section_records;
    Section section_details[SECTION_DATASIZE];
    section_records = read_Section_data(section_details, SECTION_DB);
    Section current_section;
    for (int i = 0; i < section_records; i++) {
        if (strcmp(section_details[i].Section_code, current_section_code) == 0) {
            current_section = section_details[i];
            break;
        }
    }

    //removing from student
    char registered_courses[20][10];
    int reg_course_records = split_string(registered_courses, current_student.registered_courses, "|");
    delete_element_in_array(registered_courses, &reg_course_records, course_code);
    if (reg_course_records == 0) {
        strcpy(current_student.registered_courses, "NULL");
    } else {
        list_to_str(registered_courses, reg_course_records, current_student.registered_courses, "|");
    }

    char registered_sections[20][10];
    int regis_section_records = split_string(registered_sections, current_student.registerd_sections, "|");
    delete_element_in_array(registered_sections, &regis_section_records, current_section_code);
    if (regis_section_records == 0) {
        strcpy(current_student.registerd_sections, "NULL");
    } else {
        list_to_str(registered_sections, regis_section_records, current_student.registerd_sections, "|");
    }
    for (int i = 0; i < stu_records; i++) {
        if (student_id == stu_details[i].student_id) {
            stu_details[i] = current_student;
            break;
        }
    }
    //end removing from studenet


    //remving from section
    char reg_students[40][10];

    int reg_student_records = split_string(reg_students, current_section.Registered_Students, "|");
    char current_student_id[10];
    sprintf(current_student_id, "%d", student_id);


    delete_element_in_array(reg_students, &reg_student_records, current_student_id);


    current_section.Available_seats++;
    if (reg_student_records == 0) {

        strcpy(current_section.Registered_Students, "NULL");
    } else {
        list_to_str(reg_students, reg_student_records, current_section.Registered_Students, "|");

    }

    for (int i = 0; i < section_records; i++) {
        if (strcmp(section_details[i].Section_code, current_section_code) == 0) {
            section_details[i] = current_section;

            break;
        }
    }
    //end removing from section

    //allot first student in waitlist
    write_student_data(stu_details, STUDENT_DB, stu_records);
    write_section_data(section_details, SECTION_DB, section_records);


    char wait_list_students[20][10];
    char first_waitlist_student[10];
    int first_waitlist_student_id;


    StudentInfo first_waitlist_student_struct;
    int stu_records1 = read_Student_data(stu_details, STUDENT_DB);


    if (strcmp(current_section.waitlist_Students, "NULL") != 0) {
        int waitlist_records = split_string(wait_list_students, current_section.waitlist_Students, "|");

        if (waitlist_records != 0) {

            int temp_waitllist_records = waitlist_records;
            for (int i = 0; i < temp_waitllist_records; i++) {
                first_waitlist_student_id = atoi(wait_list_students[i]);

                remove_from_waitlist(current_section.Section_code, first_waitlist_student_id);

                if (add_check_eligibilty(first_waitlist_student_id)) {
                    for (int i = 0; i < stu_records1; i++) {
                        if (stu_details[i].student_id == first_waitlist_student_id) {
                            first_waitlist_student_struct = stu_details[i];
                            break;
                        }
                    }
                    allot_section(first_waitlist_student_id, current_section.Section_code, course_code);
                    send_mail_waitlist_allotted(first_waitlist_student_struct.email_id, first_waitlist_student_struct,
                                                choosen_course, current_section);

                    break;
                }

            }

        }
    }


}


int retrieve_waitlist_sections(int student_id, char waitlist_sections[][10]) {
    StudentInfo stu_details[STU_DATASIZE];
    StudentInfo current_student;
    int records;
    records = read_Student_data(stu_details, STUDENT_DB);
    for (int i = 0; i < records; i++) {
        if (stu_details[i].student_id == student_id) {
            current_student = stu_details[i];
            break;
        }
    }
    if (strcmp(current_student.waitlist_sections, "NULL") == 0) {
        return 0;
    }
    int reg_records = split_string(waitlist_sections, current_student.waitlist_sections, "|");
    return reg_records;
}

int get_course_from_sec(char section_code[10], Course *course) {
    Course course_details[COURSE_DATASIZE];
    int course_records;
    course_records = read_course_data(course_details, COURSE_DB);
    for (int i = 0; i < course_records; i++) {
        if (strcmp(course_details[i].Section_1, section_code) == 0 ||
            strcmp(course_details[i].Section_2, section_code) == 0 ||
            strcmp(course_details[i].Section_3, section_code) == 0) {
            *course = course_details[i];
            break;
        }
    }
}


int Labels_for_waitlist_sections(char waitist_secctions[][10], int waitlist_records, float pos_x, float pos_y,
                                 bool commands[]) {

    Course current_course;
    Course course_arr[30];
    for (int i = 0; i < waitlist_records; i++) {
        get_course_from_sec(waitist_secctions[i], &current_course);
        course_arr[i] = current_course;
    }
    GuiSetStyle(DEFAULT, TEXT_SIZE, 40);

    DrawRectangle(pos_x - 10, pos_y - 10 - 60, 250, 60, SKYBLUE);
    GuiLabel((Rectangle) {pos_x, pos_y - 60, 250, 30}, "Course Code");
    DrawRectangleLines(pos_x - 10, pos_y - 10 - 60, 250, 60, BLACK);

    DrawRectangle(pos_x + 250 - 10, pos_y - 10 - 60, 800, 60, SKYBLUE);
    GuiLabel((Rectangle) {pos_x + 250, pos_y - 60, 800, 30}, "Course Name");
    DrawRectangleLines(pos_x + 250 - 10, pos_y - 10 - 60, 800, 60, BLACK);

    DrawRectangle(pos_x + 1050 - 10, pos_y - 10 - 60, 250, 60, SKYBLUE);
    GuiLabel((Rectangle) {pos_x + 1050, pos_y - 60, 250, 30}, "Section Code");
    DrawRectangleLines(pos_x + 1050 - 10, pos_y - 10 - 60, 250, 60, BLACK);

    DrawRectangle(pos_x + 1300 - 10, pos_y - 10 - 60, 220, 60, SKYBLUE);
    GuiLabel((Rectangle) {pos_x + 1300, pos_y - 60, 220, 30}, "Select");
    DrawRectangleLines(pos_x + 1300 - 10, pos_y - 10 - 60, 220, 60, BLACK);

    for (int i = 0; i < waitlist_records; i++) {
        GuiLabel((Rectangle) {pos_x, pos_y, 250, 30}, course_arr[i].Course_code);
        DrawRectangleLines(pos_x - 10, pos_y - 10, 250, 60, BLACK);

        GuiLabel((Rectangle) {pos_x + 250, pos_y, 800, 30}, course_arr[i].Course_Name);
        DrawRectangleLines(pos_x + 250 - 10, pos_y - 10, 800, 60, BLACK);

        GuiLabel((Rectangle) {pos_x + 1050, pos_y, 250, 30}, waitist_secctions[i]);
        DrawRectangleLines(pos_x + 1050 - 10, pos_y - 10, 250, 60, BLACK);

        commands[i] = GuiButton((Rectangle) {pos_x + 1300, pos_y, 200, 45}, "Remove");
        DrawRectangleLines(pos_x + 1300 - 10, pos_y - 10, 220, 60, BLACK);
        pos_y = pos_y + 60;
    }

}


int remove_from_waitlist(char section_code[], int student_id) {

    StudentInfo stu_details[STU_DATASIZE];
    StudentInfo current_student;
    int records;
    records = read_Student_data(stu_details, STUDENT_DB);
    Section section_details[SECTION_DATASIZE];
    Section current_section;
    int sec_records = read_Section_data(section_details, SECTION_DB);

    for (int i = 0; i < records; i++) {
        if (stu_details[i].student_id == student_id) {

            current_student = stu_details[i];
            break;
        }
    }

    char waitlist_sections[20][10];
    int waitlist_records = split_string(waitlist_sections, current_student.waitlist_sections, "|");
    delete_element_in_array(waitlist_sections, &waitlist_records, section_code);

    if (waitlist_records == 0) {
        strcpy(current_student.waitlist_sections, "NULL");
    } else {
        list_to_str(waitlist_sections, waitlist_records, current_student.waitlist_sections, "|");
    }


    for (int i = 0; i < records; i++) {
        if (current_student.student_id == stu_details[i].student_id) {
            stu_details[i] = current_student;
            break;
        }
    }


    for (int i = 0; i < sec_records; i++) {
        if (strcmp(section_details[i].Section_code, section_code) == 0) {
            current_section = section_details[i];
            break;
        }
    }


    char waitlist_students[20][10];
    int waitlist_student_records = split_string(waitlist_students, current_section.waitlist_Students, "|");
    char current_student_id[10];
    sprintf(current_student_id, "%d", student_id);
    delete_element_in_array(waitlist_students, &waitlist_student_records, current_student_id);
    current_section.waitlist_availability++;
    if (waitlist_student_records == 0) {

        strcpy(current_section.waitlist_Students, "NULL");
    } else {
        list_to_str(waitlist_students, waitlist_student_records, current_section.waitlist_Students, "|");
    }

    for (int i = 0; i < sec_records; i++) {
        if (strcmp(section_details[i].Section_code, section_code) == 0) {
            section_details[i] = current_section;
            break;
        }
    }


    write_student_data(stu_details, STUDENT_DB, records);
    write_section_data(section_details, SECTION_DB, sec_records);

}













