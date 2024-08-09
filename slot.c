


#include <raygui.h>
#include <time.h>
#include "all_includes_and_macros.h"




//divided slots




void divide_slots() {
    StudentInfo student_datas[STU_DATASIZE];
    Slot slot_data[SLOT_DATASIZE];

    int slot_records = read_slot_data(slot_data, SLOT_DB);
    int student_records = read_Student_data(student_datas, STUDENT_DB);

    char id[10];
    int present = 0;
    for (int i = 0; i < student_records; i++) {
        for (int j = 0; j < slot_records; j++) {
            if (strcmp(student_datas[i].Department, slot_data[j].Department) == 0 &&
                student_datas[i].Semester == slot_data[j].Semester) {
                present = 1;
                break;
            }
        }

        if (present == 0) {
            strcpy(slot_data[slot_records].Department, student_datas[i].Department);
            slot_data[slot_records].Semester = student_datas[i].Semester;
            slot_records++;
        }
        present = 0;
    }

    for (int i = 0; i < student_records; i++) {
        for (int j = 0; j < slot_records; j++) {
            if (strcmp(student_datas[i].Department, slot_data[j].Department) == 0 &&
                student_datas[i].Semester == slot_data[j].Semester) {
                sprintf(id, "%d", student_datas[i].student_id);

                // Check if the ID is already present in the slot
                if (strstr(slot_data[j].slot, id) == NULL) {
                    // Only append the ID if it's not already present
                    if (strcmp(slot_data[j].slot, "") == 0) {
                        strcpy(slot_data[j].slot, id);
                    } else {
                        strcat(slot_data[j].slot, "|");
                        strcat(slot_data[j].slot, id);
                    }
                }
            }
        }
    }

    for (int i = 0; i < slot_records; i++) {
        sort_by_cgpa(slot_data[i].slot);
    }

    int s_records;
    char student_id[STU_DATASIZE][10];
    int no_of_slot = 4;
    for (int i = 0; i < slot_records; i++) {
        s_records = split_string(student_id, slot_data[i].slot, "|");
        int students_per_slot = s_records / no_of_slot;

        for (int j = 0; j < no_of_slot; j++) {
            int start_index = j * students_per_slot;
            int end_index = (j + 1) * students_per_slot;

            // If this is the last sub-slot, set the end index to the total number of students
            if (j == no_of_slot - 1) {
                end_index = s_records;
            }

            if (end_index < s_records) {
                while (end_index < s_records && strcmp(student_id[end_index], student_id[end_index - 1]) == 0) {
                    end_index++;
                }
            }

            for (int k = start_index; k < end_index && k < s_records; k++) {
                switch (j) {
                    case 0:
                        if (strstr(slot_data[i].slot1, student_id[k]) == NULL) {
                            if (strcmp(slot_data[i].slot1, "") == 0) {
                                strcpy(slot_data[i].slot1, student_id[k]);
                            } else {
                                strcat(slot_data[i].slot1, "|");
                                strcat(slot_data[i].slot1, student_id[k]);
                            }
                        }
                        break;
                    case 1:
                        if (strstr(slot_data[i].slot2, student_id[k]) == NULL) {
                            if (strcmp(slot_data[i].slot2, "") == 0) {
                                strcpy(slot_data[i].slot2, student_id[k]);
                            } else {
                                strcat(slot_data[i].slot2, "|");
                                strcat(slot_data[i].slot2, student_id[k]);
                            }
                        }
                        break;
                    case 2:
                        if (strstr(slot_data[i].slot3, student_id[k]) == NULL) {
                            if (strcmp(slot_data[i].slot3, "") == 0) {
                                strcpy(slot_data[i].slot3, student_id[k]);
                            } else {
                                strcat(slot_data[i].slot3, "|");
                                strcat(slot_data[i].slot3, student_id[k]);
                            }
                        }
                        break;
                    case 3:
                        if (strstr(slot_data[i].slot4, student_id[k]) == NULL) {
                            if (strcmp(slot_data[i].slot4, "") == 0) {
                                strcpy(slot_data[i].slot4, student_id[k]);
                            } else {
                                strcat(slot_data[i].slot4, "|");
                                strcat(slot_data[i].slot4, student_id[k]);
                            }
                        }
                        break;
                }
            }
        }
    }


    write_slot_data(slot_data, SLOT_DB, slot_records);
}


int check_admin_control(int student_id) {
    StudentInfo arr[STU_DATASIZE];
    int records = read_Student_data(arr, STUDENT_DB);

    for (int i = 0; i < records; i++) {
        if (arr[i].student_id == student_id) {
            return arr[i].admin_control;
        }
    }

    return -1;
}


int admin_allow(int student_id) {
    StudentInfo arr[STU_DATASIZE];
    int records = read_Student_data(arr, STUDENT_DB);
    for (int i = 0; i < records; i++) {
        if (arr[i].student_id == student_id) {
            arr[i].admin_control = 1;
            write_student_data(arr, STUDENT_DB, records);
            return 1;

        }

    }
    return -1;
}


int admin_block(int student_id) {
    StudentInfo arr[STU_DATASIZE];
    int records = read_Student_data(arr, STUDENT_DB);
    for (int i = 0; i < records; i++) {
        if (arr[i].student_id == student_id) {
            arr[i].admin_control = 0;
            write_student_data(arr, STUDENT_DB, records);
            return 1;
        }

    }
    return -1;
}


/*
int add_course(Course c) {
    Course arr[500];
    int records = read_course_data(arr, "databases\\Course_data.csv");
    arr[records] = c;
    write_course_data(arr, "databases\\Course_data.csv", records + 1);
    return 1;
}

int remove_course(char course_code[]) {
    Course arr[500];
    int records = read_course_data(arr, "databases\\Course_data.csv");
    for (int i = 0; i < records; i++) {
        if (strcmp(arr[i].Course_code, course_code) == 0) {
            for (int j = i; j < records - 1; j++) {
                arr[j] = arr[j + 1];
            }
            write_course_data(arr, "databases\\Course_data.csv", records - 1);
            return 1;
        }
    }
    return -1;
}
 */



int allow_slot(char slot[]) {
    Slot arr[SLOT_DATASIZE];
    char students[1000];
    char lis_students[500][10];
    int no_stu;
    int records = read_slot_data(arr, SLOT_DB);
    for (int i = 0; i < records; i++) {
        if (strcmp(slot, "slot1") == 0) {
            strcpy(students, arr[i].slot1);
            if (strcmp(students, "") == 0) {
                return -1;
            }
            no_stu = split_string(lis_students, students, "|");
            for (int j = 0; j < no_stu; j++) {
                admin_allow(atoi(lis_students[j]));


            }
            arr[i].al_slot1 = 1;

        } else if (strcmp(slot, "slot2") == 0) {
            strcpy(students, arr[i].slot2);
            if (strcmp(students, "") == 0) {
                return -1;
            }
            no_stu = split_string(lis_students, students, "|");
            for (int j = 0; j < no_stu; j++) {
                admin_allow(atoi(lis_students[j]));
            }
            arr[i].al_slot2 = 1;

        } else if (strcmp(slot, "slot3") == 0) {
            strcpy(students, arr[i].slot3);
            if (strcmp(students, "") == 0) {
                return -1;
            }
            no_stu = split_string(lis_students, students, "|");
            for (int j = 0; j < no_stu; j++) {
                admin_allow(atoi(lis_students[j]));
            }
            arr[i].al_slot3 = 1;
        } else if (strcmp(slot, "slot4") == 0) {
            strcpy(students, arr[i].slot4);
            if (strcmp(students, "") == 0) {
                return -1;
            }

            no_stu = split_string(lis_students, students, "|");
            for (int j = 0; j < no_stu; j++) {
                admin_allow(atoi(lis_students[j]));
            }
            arr[i].al_slot4 = 1;

        }


    }
    write_slot_data(arr, SLOT_DB, records);


}


int block_slot(char slot[]) {
    Slot arr[SLOT_DATASIZE];
    char students[1000];
    char lis_students[500][10];
    int no_stu;
    int records = read_slot_data(arr, SLOT_DB);
    for (int i = 0; i < records; i++) {
        if (strcmp(slot, "slot1") == 0) {
            strcpy(students, arr[i].slot1);
            if (strcmp(students, "") == 0) {
                return -1;
            }
            no_stu = split_string(lis_students, students, "|");
            for (int j = 0; j < no_stu; j++) {
                admin_block(atoi(lis_students[j]));
            }
            arr[i].al_slot1 = 0;

        } else if (strcmp(slot, "slot2") == 0) {
            strcpy(students, arr[i].slot2);
            if (strcmp(students, "") == 0) {
                return -1;
            }
            no_stu = split_string(lis_students, students, "|");
            for (int j = 0; j < no_stu; j++) {
                admin_block(atoi(lis_students[j]));
            }
            arr[i].al_slot2 = 0;

        } else if (strcmp(slot, "slot3") == 0) {
            strcpy(students, arr[i].slot3);
            if (strcmp(students, "") == 0) {
                return -1;
            }
            no_stu = split_string(lis_students, students, "|");
            for (int j = 0; j < no_stu; j++) {
                admin_block(atoi(lis_students[j]));
            }
            arr[i].al_slot3 = 0;

        } else if (strcmp(slot, "slot4") == 0) {
            strcpy(students, arr[i].slot4);
            if (strcmp(students, "") == 0) {
                return -1;
            }
            no_stu = split_string(lis_students, students, "|");
            for (int j = 0; j < no_stu; j++) {
                admin_block(atoi(lis_students[j]));
            }
            arr[i].al_slot4 = 0;

        }

    }
    write_slot_data(arr, SLOT_DB, records);


}


void check_if_allowed(int chec_arr[4]) {

    Slot arr[SLOT_DATASIZE];
    int records = read_slot_data(arr, SLOT_DB);
    for (int i = 0; i < records; i++) {
        if (arr[i].al_slot1 == 1) {
            chec_arr[0] = 1;
        } else {
            chec_arr[0] = 0;
        }
        if (arr[i].al_slot2 == 1) {
            chec_arr[1] = 1;
        } else {
            chec_arr[1] = 0;
        }
        if (arr[i].al_slot3 == 1) {
            chec_arr[2] = 1;
        } else {
            chec_arr[2] = 0;
        }
        if (arr[i].al_slot4 == 1) {
            chec_arr[3] = 1;
        } else {
            chec_arr[3] = 0;
        }
        break;

    }


}


void
DrawBarChart(char labels[][10], const int *counts, int labelCount, int chartWidth, int chartHeight, Vector2 position) {

    if (labelCount == 0) {
        GuiLabel((Rectangle) {position.x, position.y, 500, 20}, "No data to display");
    } else {
        // Calculate bar width and scaling factor
        int barWidth = chartWidth / labelCount;
        int maxCount = 0;
        for (int i = 0; i < labelCount; i++) {
            if (counts[i] > maxCount) {
                maxCount = counts[i];
            }
        }
        float scale = (float) chartHeight / maxCount;

        // Draw bars
        for (int i = 0; i < labelCount; i++) {
            int barHeight = counts[i] * scale;
            Rectangle bar = {position.x + i * barWidth, position.y + (chartHeight - barHeight), barWidth - 10,
                             barHeight};
            DrawRectangleRec(bar, BLUE);
            // Draw labels
            //DrawText(labels[i], position.x + i * barWidth + (barWidth / 2 - MeasureText(labels[i], 10) / 2), position.y + chartHeight + 10, 10, BLACK);
            GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
            GuiLabel((Rectangle) {position.x + i * barWidth + (barWidth / 2 - MeasureText(labels[i], 10) / 2) - 10,
                                  position.y + chartHeight + 10, 40, 10}, labels[i]);
            GuiSetStyle(DEFAULT, TEXT_SIZE, 40);
            // Draw count values

            char countText[10];
            sprintf(countText, "%d", counts[i]);
            //DrawText(countText, position.x + i * barWidth + (barWidth / 2 - MeasureText(countText, 10) / 2), position.y + (chartHeight - barHeight) - 20, 10, BLACK);
            GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
            GuiLabel((Rectangle) {position.x + i * barWidth + (barWidth / 2 - MeasureText(countText, 10) / 2) - 3,
                                  position.y + (chartHeight - barHeight) - 20, 30, 10}, countText);
            GuiSetStyle(DEFAULT, TEXT_SIZE, 40);

        }
        // Draw axes
        DrawLine(position.x, position.y, position.x, position.y + chartHeight, BLACK); // Y axis
        DrawLine(position.x, position.y + chartHeight, position.x + chartWidth, position.y + chartHeight,
                 BLACK); // X axis
    }
}


int check_eligibilty(StudentInfo current_student) {

    char regis_courses[20][10];
    if (strcmp(current_student.registered_courses, "NULL") == 0) {
        return 0;
    } else {
        int regis_records = split_string(regis_courses, current_student.registered_courses, "|");
        if (regis_records >= 4) {
            return 1;
        } else {
            return 0;
        }
    }
}


int str_if_already_in_arr(char arr[][10], char str[], int n) {
    for (int i = 0; i < n; i++) {
        if (strcmp(arr[i], str) == 0) {

            return 1;
        }
    }
    return 0;
}


int int_if_already_in_arr(int arr[], int num, int n) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == num) {
            return 1;
        }
    }
    return 0;
}

void int_arr_to_str_arr(int arr[], char str_arr[][10], int n) {
    for (int i = 0; i < n; i++) {
        sprintf(str_arr[i], "%d", arr[i]);
    }
}


int get_data_dept_wise(char dept[][10], int dept_count[], int *n) {
    StudentInfo arr[STU_DATASIZE];
    int records = read_Student_data(arr, STUDENT_DB);

    for (int i = 0; i < records; i++) {
        if (str_if_already_in_arr(dept, arr[i].Department, *n) == 0) {
            strcpy(dept[*n], arr[i].Department);
            dept_count[*n] = 1;
            (*n)++;
        } else {
            for (int j = 0; j < *n; j++) {
                if (strcmp(dept[j], arr[i].Department) == 0) {
                    dept_count[j]++;
                }
            }
        }
    }


}

int get_data_sem_wise(int sems[], int sem_count[], int *n) {
    StudentInfo arr[STU_DATASIZE];
    int records = read_Student_data(arr, STUDENT_DB);
    for (int i = 0; i < records; i++) {
        if (int_if_already_in_arr(sems, arr[i].Semester, *n) == 0) {
            sems[*n] = arr[i].Semester;
            sem_count[*n] = 1;
            (*n)++;
        } else {
            for (int j = 0; j < *n; j++) {
                if (sems[j] == arr[i].Semester) {
                    sem_count[j]++;
                }
            }
        }

    }


}


void dept_wise_bar(bool *dept_got, int width, int height, Vector2 position) {
    static char dept[500][10];
    static int dept_count[500];
    static int n = 0;
    if (!(*dept_got)) {
        n = 0;
        get_data_dept_wise(dept, dept_count, &n);
        *dept_got = true;
    }
    DrawBarChart(dept, dept_count, n, width, height, position);

}

void sem_wise_bar(bool *sem_got, int width, int height, Vector2 position) {
    static int sems[10];
    static int sem_count[500];
    static int n = 0;
    if (!(*sem_got)) {
        n = 0;
        get_data_sem_wise(sems, sem_count, &n);
        *sem_got = true;
    }
    char sems_str[10][10];
    int_arr_to_str_arr(sems, sems_str, n);

    DrawBarChart(sems_str, sem_count, n, width, height, position);

}


void get_data_reg_student_deptwise(char dept[][10], int dept_count[], int *n) {
    StudentInfo arr[STU_DATASIZE];
    int records = read_Student_data(arr, STUDENT_DB);
    StudentInfo current_student;
    for (int i = 0; i < records; i++) {
        current_student = arr[i];
        if (check_eligibilty(current_student) == 1) {
            if (str_if_already_in_arr(dept, current_student.Department, *n) == 0) {
                strcpy(dept[*n], current_student.Department);
                dept_count[*n] = 1;
                *n = *n + 1;
            } else {
                for (int j = 0; j < *n; j++) {
                    if (strcmp(dept[j], current_student.Department) == 0) {
                        dept_count[j]++;
                    }
                }
            }
        }

    }

}

void get_data_reg_student_semwise(int sems[], int sem_count[], int *n) {
    StudentInfo arr[STU_DATASIZE];
    int records = read_Student_data(arr, STUDENT_DB);
    StudentInfo current_student;
    for (int i = 0; i < records; i++) {
        current_student = arr[i];
        if (check_eligibilty(current_student) == 1) {
            if (int_if_already_in_arr(sems, arr[i].Semester, *n) == 0) {
                sems[*n] = arr[i].Semester;
                sem_count[*n] = 1;
                (*n)++;
            } else {
                for (int j = 0; j < *n; j++) {
                    if (sems[j] == arr[i].Semester) {
                        sem_count[j]++;
                    }
                }
            }

        }
    }
}


void reg_student_dept_wise_bar(bool *reg_dept_data_displayed, int width, int height, Vector2 position) {
    static char dept[500][10];
    static int dept_count[500];
    static int n = 0;
    if (!(*reg_dept_data_displayed)) {
        n = 0;
        get_data_reg_student_deptwise(dept, dept_count, &n);
        *reg_dept_data_displayed = true;
    }
    if (n == 0) {
        GuiLabel((Rectangle) {position.x, position.y, 500, 20}, "No data to display");
    } else {
        DrawBarChart(dept, dept_count, n, width, height, position);
    }

}

void reg_student_sem_wise_bar(bool *reg_sem_data_diaplayed, int width, int height, Vector2 position) {
    static int sems[10];
    static int sem_count[500];
    static int n = 0;
    if (!(*reg_sem_data_diaplayed)) {
        n = 0;
        get_data_reg_student_semwise(sems, sem_count, &n);
        *reg_sem_data_diaplayed = true;
    }
    if (n == 0) {
        GuiLabel((Rectangle) {position.x, position.y, 500, 20}, "No data to display");
    } else {
        char sems_str[10][10];
        int_arr_to_str_arr(sems, sems_str, n);

        DrawBarChart(sems_str, sem_count, n, width, height, position);
    }
}


int if_slot_on(int student_id, char department[], int semester) {
    Slot arr[SLOT_DATASIZE];
    int records = read_slot_data(arr, SLOT_DB);
    for (int i = 0; i < records; i++) {
        if (strcmp(arr[i].Department, department) == 0 && arr[i].Semester == semester) {
            for (int j = 0; j < 4; j++) {
                char students[1000];
                char lis_students[500][10];
                int no_stu;
                if (j == 0) {
                    strcpy(students, arr[i].slot1);
                } else if (j == 1) {
                    strcpy(students, arr[i].slot2);
                } else if (j == 2) {
                    strcpy(students, arr[i].slot3);
                } else if (j == 3) {
                    strcpy(students, arr[i].slot4);
                }
                no_stu = split_string(lis_students, students, "|");
                for (int k = 0; k < no_stu; k++) {
                    if (atoi(lis_students[k]) == student_id) {
                        // Check if the slot is allowed
                        if ((j == 0 && arr[i].al_slot1 == 1) ||
                            (j == 1 && arr[i].al_slot2 == 1) ||
                            (j == 2 && arr[i].al_slot3 == 1) ||
                            (j == 3 && arr[i].al_slot4 == 1)) {
                            return 1;
                        } else {
                            return 0;
                        }
                    }
                }
            }
        }
    }
    return 0;  // Return 0 if no matching slot is found
}


TimeDifference GetTimeDifference(time_t endTime) {
    time_t currentTime = time(NULL);
    double secondsLeft = difftime(endTime, currentTime);

    TimeDifference diff;
    diff.days = (int) (secondsLeft / (60 * 60 * 24));
    secondsLeft -= diff.days * 60 * 60 * 24;
    diff.hours = (int) (secondsLeft / (60 * 60));
    secondsLeft -= diff.hours * 60 * 60;
    diff.minutes = (int) (secondsLeft / 60);
    diff.seconds = (int) (secondsLeft - diff.minutes * 60);

    return diff;
}

time_t ParseDateTime(const char *dateTime) {
    struct tm tm = {0};
    int year, month, day, hour, minute, second;

    if (sscanf(dateTime, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second) == 6) {
        tm.tm_year = year - 1900;
        tm.tm_mon = month - 1;
        tm.tm_mday = day;
        tm.tm_hour = hour;
        tm.tm_min = minute;
        tm.tm_sec = second;
        return mktime(&tm);
    }
    return (time_t) -1;
}

void SaveEndTimeToFile(time_t endTime) {
    FILE *file = fopen(FILENAME, "w");
    if (file) {
        struct tm *tm = localtime(&endTime);
        fprintf(file, "%04d-%02d-%02d %02d:%02d:%02d\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
                tm->tm_hour, tm->tm_min, tm->tm_sec);
        fclose(file);
    }
}

time_t LoadEndTimeFromFile() {
    FILE *file = fopen(FILENAME, "r");
    if (file) {
        char dateTime[64];
        if (fgets(dateTime, sizeof(dateTime), file)) {
            fclose(file);
            return ParseDateTime(dateTime);
        }
        fclose(file);
    }
    return (time_t) -1;
}

void ResetEndTimeInFile() {
    FILE *file = fopen(FILENAME, "w");
    if (file) {
        fprintf(file, "0000-00-00 00:00:00\n");
        fclose(file);
    }
}


int find_which_slot(int student_id) {
    Slot arr[SLOT_DATASIZE];
    int records = read_slot_data(arr, SLOT_DB);
    char stud_id[10];
    sprintf(stud_id, "%d", student_id);
    for (int i = 0; i < records; i++) {
        if (strstr(arr[i].slot1, stud_id) != NULL) {
            return 1;
        } else if (strstr(arr[i].slot2, stud_id) != NULL) {
            return 2;
        } else if (strstr(arr[i].slot3, stud_id) != NULL) {
            return 3;
        } else if (strstr(arr[i].slot4, stud_id) != NULL) {
            return 4;
        }
    }
    return -1;
}


int get_regestered_count(Course course) {

    Section section_details[SECTION_DATASIZE];
    int section_records = read_Section_data(section_details, SECTION_DB);
    int count = 0;
    char reg_students[700];
    char lis_students[60][10];

    for (int i = 0; i < section_records; i++) {

        if (strcmp(section_details[i].Section_code, course.Section_1) == 0) {
            if (strcmp(section_details[i].Registered_Students, "NULL") != 0) {

                count += split_string(lis_students, section_details[i].Registered_Students, "|");
            }

        } else if (strcmp(section_details[i].Section_code, course.Section_2) == 0) {
            if (strcmp(section_details[i].Registered_Students, "NULL") != 0) {
                count += split_string(lis_students, section_details[i].Registered_Students, "|");
            }

        } else if (strcmp(section_details[i].Section_code, course.Section_3) == 0) {
            if (strcmp(section_details[i].Registered_Students, "NULL") != 0) {
                count += split_string(lis_students, section_details[i].Registered_Students, "|");
            }

        }


    }
    return count;


}


Course get_max_reg_course(char dept[], int sem) {

    Course course_deatils[COURSE_DATASIZE];
    int course_records = read_course_data(course_deatils, COURSE_DB);
    Course max_course;
    bool got_inside;

    for (int i = 0; i < course_records; i++) {
        if (strcmp(course_deatils[i].Department, dept) == 0 && course_deatils[i].Semester == sem &&
            course_deatils[i].mandatory == 0) {
            if (!got_inside) {
                max_course = course_deatils[i];
                got_inside = true;
            } else if (get_regestered_count(course_deatils[i]) > get_regestered_count(max_course)) {
                max_course = course_deatils[i];
            }
        }
    }
    return max_course;
}




