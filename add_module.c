
#include <raygui.h>
#include "all_includes_and_macros.h"

#define RAYGUI_IMPLEMENTATION

int add_check_eligibilty(int student_id) {

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
    char reg_courses[10][10];
    int reg_records = split_string(reg_courses, current_student.registered_courses, "|");
    if (reg_records >= 6) {
        return 0;
    } else {
        return 1;
    }
}


int retrieve_sem_courses(int student_id, Course current_courses[]) {
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

    Course course_details[COURSE_DATASIZE];
    int course_records;
    int k = 0;
    course_records = read_course_data(course_details, COURSE_DB);
    for (int i = 0; i < course_records; i++) {
        if ((strcmp(current_student.Department, course_details[i].Department) == 0) &&
            (course_details[i].Semester == current_student.Semester)
            && !if_already_registered(current_student, course_details[i].Course_code)) {
            current_courses[k] = course_details[i];


            k++;
        }
    }

    return k;
}


int retrieve_non_mandatory_courses(int student_id, Course current_courses[]) {
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

    Course course_details[COURSE_DATASIZE];
    int course_records;
    int k = 0;
    course_records = read_course_data(course_details, COURSE_DB);
    for (int i = 0; i < course_records; i++) {
        if ((strcmp(current_student.Department, course_details[i].Department) == 0) &&
            (course_details[i].Semester == current_student.Semester)) {
            if (course_details[i].mandatory == 0) {
                current_courses[k] = course_details[i];
                k++;
            }


        }
    }
    return k;
}

int retrieve_non_mandatory_non_registered_courses(int student_id, Course current_courses[]) {
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

    Course course_details[COURSE_DATASIZE];
    int course_records;
    int k = 0;
    course_records = read_course_data(course_details, COURSE_DB);
    for (int i = 0; i < course_records; i++) {
        if ((strcmp(current_student.Department, course_details[i].Department) == 0) &&
            (course_details[i].Semester == current_student.Semester)) {
            if (course_details[i].mandatory == 0 &&
                !if_already_registered(current_student, course_details[i].Course_code)) {
                current_courses[k] = course_details[i];
                k++;
            }
        }
    }
    return k;
}


int Labels_for_sem_courses(Course courses[], int course_count, float pos_x, float pos_y, bool commands[]) {
    char credits[10];
    GuiSetStyle(DEFAULT, TEXT_SIZE, 40);

    DrawRectangle(pos_x - 10, pos_y - 10 - 60, 250, 60, SKYBLUE);
    GuiLabel((Rectangle) {pos_x, pos_y - 60, 250, 30}, "Course Code");
    DrawRectangleLines(pos_x - 10, pos_y - 10 - 60, 250, 60, BLACK);

    DrawRectangle(pos_x + 250 - 10, pos_y - 10 - 60, 900, 60, SKYBLUE);
    GuiLabel((Rectangle) {pos_x + 250, pos_y - 60, 900, 30}, "Course Name");
    DrawRectangleLines(pos_x + 250 - 10, pos_y - 10 - 60, 900, 60, BLACK);

    DrawRectangle(pos_x + 1150 - 10, pos_y - 10 - 60, 200, 60, SKYBLUE);
    GuiLabel((Rectangle) {pos_x + 1150, pos_y - 60, 200, 30}, "Credits");
    DrawRectangleLines(pos_x + 1150 - 10, pos_y - 10 - 60, 200, 60, BLACK);

    DrawRectangle(pos_x + 1350 - 10, pos_y - 10 - 60, 220, 60, SKYBLUE);
    GuiLabel((Rectangle) {pos_x + 1350, pos_y - 60, 220, 30}, "Select");
    DrawRectangleLines(pos_x + 1350 - 10, pos_y - 10 - 60, 220, 60, BLACK);


    for (int i = 0; i < course_count; i++) {
        sprintf(credits, "%d", courses[i].Credits);
        GuiLabel((Rectangle) {pos_x, pos_y, 250, 30}, courses[i].Course_code);
        DrawRectangleLines(pos_x - 10, pos_y - 10, 250, 60, BLACK);

        GuiLabel((Rectangle) {pos_x + 250, pos_y, 900, 30}, courses[i].Course_Name);
        DrawRectangleLines(pos_x + 250 - 10, pos_y - 10, 900, 60, BLACK);

        GuiLabel((Rectangle) {pos_x + 1150, pos_y, 200, 30}, credits);
        DrawRectangleLines(pos_x + 1150 - 10, pos_y - 10, 200, 60, BLACK);

        commands[i] = GuiButton((Rectangle) {pos_x + 1350, pos_y, 200, 45}, "Enter");

        DrawRectangleLines(pos_x + 1350 - 10, pos_y - 10, 220, 60, BLACK);

        pos_y = pos_y + 60;
    }
}


int retrieve_section(Course current_cours, Section section_details[]) {
    Section sec_details[SECTION_DATASIZE];
    int sec_records;
    sec_records = read_Section_data(sec_details, SECTION_DB);


    int k = 0;
    for (int i = 0; i < sec_records; i++) {
        if (strcmp(current_cours.Section_1, sec_details[i].Section_code) == 0
            || strcmp(current_cours.Section_2, sec_details[i].Section_code) == 0
            || strcmp(current_cours.Section_3, sec_details[i].Section_code) == 0) {
            section_details[k] = sec_details[i];
            k++;
        }
    }


    return k;


}


int Labels_for_section(Section sections[], int section_count, float pos_x, float pos_y,
                       bool faculty_coommands[], bool allot_commands[], bool waitlist_commands[], int student_id) {

    char available_seats_section[4];
    char available_seats_waitlist[4];
    GuiSetStyle(DEFAULT, TEXT_SIZE, 40);

    DrawRectangle(pos_x - 10, pos_y - 10 - 60, 260, 60, SKYBLUE);
    GuiLabel((Rectangle) {pos_x, pos_y - 60, 260, 30}, "Section Code");
    DrawRectangleLines(pos_x - 10, pos_y - 10 - 60, 260, 60, BLACK);

    DrawRectangle(pos_x + 260 - 10, pos_y - 10 - 60, 260, 60, SKYBLUE);
    GuiLabel((Rectangle) {pos_x + 260, pos_y - 60, 260, 30}, "Faculty Code");
    DrawRectangleLines(pos_x + 260 - 10, pos_y - 10 - 60, 260, 60, BLACK);

    DrawRectangle(pos_x + 520 - 10, pos_y - 10 - 60, 300, 60, SKYBLUE);
    GuiLabel((Rectangle) {pos_x + 520, pos_y - 60, 300, 30}, "Available Seats");
    DrawRectangleLines(pos_x + 520 - 10, pos_y - 10 - 60, 300, 60, BLACK);

    DrawRectangle(pos_x + 820 - 10, pos_y - 10 - 60, 280, 60, SKYBLUE);
    GuiLabel((Rectangle) {pos_x + 820, pos_y - 60, 280, 30}, "Allot Section");
    DrawRectangleLines(pos_x + 820 - 10, pos_y - 10 - 60, 280, 60, BLACK);

    DrawRectangle(pos_x + 1100 - 10, pos_y - 10 - 60, 300, 60, SKYBLUE);
    GuiLabel((Rectangle) {pos_x + 1100, pos_y - 60, 300, 30}, "Available Waitlist");
    DrawRectangleLines(pos_x + 1100 - 10, pos_y - 10 - 60, 300, 60, BLACK);

    DrawRectangle(pos_x + 1400 - 10, pos_y - 10 - 60, 260, 60, SKYBLUE);
    GuiLabel((Rectangle) {pos_x + 1400, pos_y - 60, 260, 30}, "Allot Waitlist");
    DrawRectangleLines(pos_x + 1400 - 10, pos_y - 10 - 60, 260, 60, BLACK);


    for (int i = 0; i < section_count; i++) {

        sprintf(available_seats_section, "%d", sections[i].Available_seats);
        sprintf(available_seats_waitlist, "%d", sections[i].waitlist_availability);

        GuiLabel((Rectangle) {pos_x, pos_y, 260, 30}, sections[i].Section_code);
        DrawRectangleLines(pos_x - 10, pos_y - 10, 260, 60, BLACK);

        faculty_coommands[i] = GuiButton((Rectangle) {pos_x + 260, pos_y, 240, 45}, sections[i].Faculty_code);
        DrawRectangleLines(pos_x + 260 - 10, pos_y - 10, 260, 60, BLACK);

        GuiLabel((Rectangle) {pos_x + 520, pos_y, 300, 30}, available_seats_section);
        DrawRectangleLines(pos_x + 520 - 10, pos_y - 10, 300, 60, BLACK);
        if (sections[i].Available_seats != 0) {
            allot_commands[i] = GuiButton((Rectangle) {pos_x + 820, pos_y, 250, 45}, "Allot");
            GuiLabel((Rectangle) {pos_x + 1400, pos_y, 260, 45}, "Not Available");

        } else {
            //GuiLabel((Rectangle){pos_x+820,pos_y,280,45},"Full");
            if (sections[i].waitlist_availability != 0) {
                if (!if_already_in_waitlist(student_id, sections[i].Section_code)) {
                    waitlist_commands[i] = GuiButton((Rectangle) {pos_x + 1400, pos_y, 250, 45}, "Allot");
                    GuiLabel((Rectangle) {pos_x + 820, pos_y, 250, 45}, "Full");

                } else if (if_already_in_waitlist(student_id, sections[i].Section_code)) {
                    GuiLabel((Rectangle) {pos_x + 1400, pos_y, 260, 45}, "In queue");
                    GuiLabel((Rectangle) {pos_x + 820, pos_y, 250, 45}, "Full");

                }

            } else {

                if (if_already_in_waitlist(student_id, sections[i].Section_code)) {
                    GuiLabel((Rectangle) {pos_x + 1400, pos_y, 260, 45}, "In queue");
                    GuiLabel((Rectangle) {pos_x + 820, pos_y, 250, 45}, "Full");

                } else {
                    GuiLabel((Rectangle) {pos_x + 1400, pos_y, 260, 45}, "Full");
                    GuiLabel((Rectangle) {pos_x + 820, pos_y, 250, 45}, "Full");

                }
            }
        }
        DrawRectangleLines(pos_x + 820 - 10, pos_y - 10, 280, 60, BLACK);

        GuiLabel((Rectangle) {pos_x + 1100, pos_y, 300, 30}, available_seats_waitlist);
        DrawRectangleLines(pos_x + 1100 - 10, pos_y - 10, 300, 60, BLACK);

        DrawRectangleLines(pos_x + 1400 - 10, pos_y - 10, 260, 60, BLACK);

        pos_y = pos_y + 60;
    }

}


int allot_section(int student_id, char section_code[], char course_code[]) {
    char stu_id_in_ch[10];
    sprintf(stu_id_in_ch, "%d", student_id);
    StudentInfo stu_details[STU_DATASIZE];
    StudentInfo current_student;
    Course course_details[COURSE_DATASIZE];
    Course Current_course;
    int course_records;
    course_records = read_course_data(course_details, COURSE_DB);
    for (int i = 0; i < course_records; i++) {
        if (strcmp(course_code, course_details[i].Course_code) == 0) {
            Current_course = course_details[i];
            break;
        }
    }
    if (if_already_in_waitlist(student_id, Current_course.Section_1)) {
        remove_from_waitlist(Current_course.Section_1, student_id);
    }
    if (if_already_in_waitlist(student_id, Current_course.Section_2)) {
        remove_from_waitlist(Current_course.Section_2, student_id);
    }
    if (if_already_in_waitlist(student_id, Current_course.Section_3)) {
        remove_from_waitlist(Current_course.Section_3, student_id);
    }


    int student_records;
    student_records = read_Student_data(stu_details, STUDENT_DB);

    for (int i = 0; i < student_records; i++) {
        if (stu_details[i].student_id == student_id) {
            if (strcmp(stu_details[i].registered_courses, "NULL") == 0) {
                strcpy(stu_details[i].registered_courses, course_code);
            } else {
                strcat(stu_details[i].registered_courses, "|");
                strcat(stu_details[i].registered_courses, course_code);
            }

            if (strcmp(stu_details[i].registerd_sections, "NULL") == 0) {
                strcpy(stu_details[i].registerd_sections, section_code);
            } else {
                strcat(stu_details[i].registerd_sections, "|");
                strcat(stu_details[i].registerd_sections, section_code);
            }
            break;
        }
    }

    write_student_data(stu_details, STUDENT_DB, student_records);

    Section sec_details[SECTION_DATASIZE];
    int sec_records;
    sec_records = read_Section_data(sec_details, SECTION_DB);
    for (int i = 0; i < sec_records; i++) {

        if (strcmp(section_code, sec_details[i].Section_code) == 0) {
            if (strcmp(sec_details[i].Registered_Students, "NULL") == 0) {
                strcpy(sec_details[i].Registered_Students, stu_id_in_ch);
                sec_details[i].Available_seats--;
            } else {
                strcat(sec_details[i].Registered_Students, "|");
                strcat(sec_details[i].Registered_Students, stu_id_in_ch);
                sec_details[i].Available_seats--;
            }
            break;
        }

    }
    write_section_data(sec_details, SECTION_DB, sec_records);

}


int allot_waitlist(int student_id, char course_code[], char section_code[]) {

    char stu_id_in_ch[10];
    sprintf(stu_id_in_ch, "%d", student_id);

    StudentInfo stu_details[STU_DATASIZE];
    int student_records;
    student_records = read_Student_data(stu_details, STUDENT_DB);

    for (int i = 0; i < student_records; i++) {
        if (stu_details[i].student_id == student_id) {

            if (strcmp(stu_details[i].waitlist_sections, "NULL") == 0) {
                strcpy(stu_details[i].waitlist_sections, section_code);
            } else {
                strcat(stu_details[i].waitlist_sections, "|");
                strcat(stu_details[i].waitlist_sections, section_code);
            }
            break;
        }
    }
    write_student_data(stu_details, STUDENT_DB, student_records);

    Section sec_details[SECTION_DATASIZE];
    int sec_records;
    sec_records = read_Section_data(sec_details, SECTION_DB);

    for (int i = 0; i < sec_records; i++) {
        if (strcmp(section_code, sec_details[i].Section_code) == 0) {
            if (strcmp(sec_details[i].waitlist_Students, "NULL") == 0) {
                strcpy(sec_details[i].waitlist_Students, stu_id_in_ch);
                sec_details[i].waitlist_availability--;
            } else {
                strcat(sec_details[i].waitlist_Students, "|");
                strcat(sec_details[i].waitlist_Students, stu_id_in_ch);
                sec_details[i].waitlist_availability--;
            }
            break;
        }
    }

    write_section_data(sec_details, SECTION_DB, sec_records);
    sort_waitlist();

}

int pre_requisites(Course *Current_course_, int student_id) {


    char course_pre_req[30][10];
    char complete_pre_req[STU_DATASIZE][10];
    StudentInfo stu_details[STU_DATASIZE];
    StudentInfo Current_student;
    int stu_records = read_Student_data(stu_details, STUDENT_DB);
    for (int i = 0; i < stu_records; i++) {
        if (stu_details[i].student_id == student_id) {
            Current_student = stu_details[i];
            break;
        }
    }

    char pre_req[strlen(Current_course_->pre_requisite) + 1];
    strcpy(pre_req, Current_course_->pre_requisite);

    char comp_pre[strlen(Current_student.completed_courses) + 1];
    strcpy(comp_pre, Current_student.completed_courses);


    int pre_req_count = split_string(course_pre_req, pre_req, "|");
    int completed_count = split_string(complete_pre_req, comp_pre, "|");

    if (strcmp(course_pre_req[0], "NULL") == 0) {
        return 1;
    } else {
        for (int i = 0; i < pre_req_count; i++) {
            int found = 0;
            for (int j = 0; j < completed_count; j++) {
                if (strcmp(course_pre_req[i], complete_pre_req[j]) == 0) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                return 0;
            }
        }
        return 1;
    }

}


FacultyInfo get_fac_detials(char faculty_code[]) {

    FacultyInfo fac_details[FACULTY_DATASIZE];
    int fac_records;
    fac_records = read_faculty_data(fac_details, FACULTY_DB);

    for (int i = 0; i < fac_records; i++) {
        if (strcmp(fac_details[i].faculty_code, faculty_code) == 0) {
            return fac_details[i];
        }
    }

}


int if_already_registered(StudentInfo student, char course_code[]) {

    char courses[10][10];
    int records = split_string(courses, student.registered_courses, "|");
    for (int i = 0; i < records; i++) {
        if (strcmp(courses[i], course_code) == 0) {
            return 1;
        }
    }
    return 0;
}


int if_already_in_waitlist(int student_id, char section_code[]) {

    StudentInfo stu_details[STU_DATASIZE];
    StudentInfo current_student;
    int records = read_Student_data(stu_details, STUDENT_DB);
    for (int i = 0; i < records; i++) {
        if (stu_details[i].student_id == student_id) {
            current_student = stu_details[i];
            break;
        }
    }
    char waitlist_sections[15][10];
    int waitlist_records = split_string(waitlist_sections, current_student.waitlist_sections, "|");
    for (int i = 0; i < waitlist_records; i++) {
        if (strcmp(waitlist_sections[i], section_code) == 0) {
            return 1;
        }
    }
    return 0;

}


int get_mandatory_courses(StudentInfo student, Course mandatory_courses[]) {

    Course course_details[COURSE_DATASIZE];
    int course_records = read_course_data(course_details, COURSE_DB);
    int manda_count = 0;

    for (int i = 0; i < course_records; i++) {
        if (strcmp(course_details[i].Department, student.Department) == 0 &&
            course_details[i].Semester == student.Semester) {
            if (course_details[i].mandatory == 1) {
                mandatory_courses[manda_count] = course_details[i];
                manda_count++;
            }
        }
    }
    return manda_count;
}

int not_registered_mandatory(StudentInfo student, Course mandatory_courses[]) {

    Course course_details[COURSE_DATASIZE];
    int manda_count = 0;
    Course all_man_courses[10];
    manda_count = get_mandatory_courses(student, all_man_courses);
    int k = 0;
    char registered_courses[10][10];
    int reg_count = split_string(registered_courses, student.registered_courses, "|");
    for (int i = 0; i < manda_count; i++) {
        int found = 0;
        for (int j = 0; j < reg_count; j++) {
            if (strcmp(all_man_courses[i].Course_code, registered_courses[j]) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            mandatory_courses[k] = all_man_courses[i];
            k++;
        }
    }
    return k;
}


int if_student_registered_mandatory(StudentInfo student) {

    Course course_details[COURSE_DATASIZE];
    Course mandatory_courses[10];
    int manda_count = 0;

    manda_count = get_mandatory_courses(student, mandatory_courses);

    char registered_courses[10][10];
    int reg_count = split_string(registered_courses, student.registered_courses, "|");
    for (int i = 0; i < manda_count; i++) {
        int found = 0;
        for (int j = 0; j < reg_count; j++) {
            if (strcmp(mandatory_courses[i].Course_code, registered_courses[j]) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            return 0;
        }
    }

    return 1;
}


Section least_section_for_given_courses(Course courses[], int course_count) {
    Section sec_details[25];
    Section least_section = (Section) {"NULL", "NULL", 1000, "NULL", 40};
    Section three_sections[3];
    int th_count;
    for (int i = 0; i < course_count; i++) {
        th_count = retrieve_section(courses[i], three_sections);
        for (int j = 0; j < th_count; j++) {
            if (three_sections[j].Available_seats <= least_section.Available_seats) {
                if (three_sections[j].Available_seats > 0) {
                    least_section = three_sections[j];
                }
            }
        }
    }
    return least_section;
}

void allot_all_students() {

    StudentInfo stu_details[STU_DATASIZE];
    Course course_details[COURSE_DATASIZE];
    Section sec_details[SECTION_DATASIZE];
    int stu_records = read_Student_data(stu_details, STUDENT_DB);
    int course_records = read_course_data(course_details, COURSE_DB);
    int sec_records = read_Section_data(sec_details, SECTION_DB);

    Course mandatory_courses[10];
    Course non_mandatory_courses[10];
    int manda_count;
    int non_manda_count;
    Course Alloting_courses;
    Section Alloting_section;
    for (int i = 0; i < stu_records; i++) {
        while (!check_eligibilty(stu_details[i])) {

            if (if_student_registered_mandatory(stu_details[i])) {
                non_manda_count = retrieve_non_mandatory_non_registered_courses(stu_details[i].student_id,
                                                                                non_mandatory_courses);

                //least section from non-mandatory courses
                Alloting_section = least_section_for_given_courses(non_mandatory_courses, non_manda_count);

                get_course_from_sec(Alloting_section.Section_code, &Alloting_courses);
                //alloting non-mandatory sections
                allot_section(stu_details[i].student_id, Alloting_section.Section_code, Alloting_courses.Course_code);


            } else {
                // registering mandatory courses
                manda_count = not_registered_mandatory(stu_details[i], mandatory_courses);
                //lest section from non-registered mandatory courses

                Alloting_section = least_section_for_given_courses(mandatory_courses, manda_count);
                get_course_from_sec(Alloting_section.Section_code, &Alloting_courses);
                //alloting mandatory sections
                allot_section(stu_details[i].student_id, Alloting_section.Section_code, Alloting_courses.Course_code);


            }
            read_Student_data(stu_details, STUDENT_DB);

        }

    }
}





