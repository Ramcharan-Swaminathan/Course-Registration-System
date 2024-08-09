#include <stdio.h>
#include "Structure_definitions.c"


int read_course_data(Course lis[], const char *file_name) {

    FILE *fp;

    fp = fopen(file_name, "r");
    if (fp == NULL)
        return -1;

    if (ferror(fp) != 0)
        return -1;
    int records = 0;
    int read = 0;
    while (feof(fp) == 0) {

        read = fscanf(fp, "%[^,],%hd,%[^,],%[^,],%d,%[^,],%[^,],%[^,],%hd,%[^,],%d\n",

                      lis[records].Department,
                      &lis[records].Semester,
                      lis[records].Course_code,
                      lis[records].Course_Name,
                      &lis[records].Elective,
                      lis[records].Section_1,
                      lis[records].Section_2,
                      lis[records].Section_3,
                      &lis[records].Credits,
                      lis[records].pre_requisite,
                      &lis[records].mandatory);

        records++;


    }

    fclose(fp);

    return records;


}

int read_Section_data(Section lis[], const char *file_name) {

    FILE *fp;

    fp = fopen(file_name, "r");


    if (fp == NULL)
        return -1;

    if (ferror(fp) != 0)
        return -1;

    int records = 0;
    int read = 0;
    while (feof(fp) == 0) {


        read = fscanf(fp, "%[^,],%[^,],%d,%[^,],%d,%[^\n]\n",

                      lis[records].Section_code,
                      lis[records].Faculty_code,
                      &lis[records].Available_seats,
                      lis[records].Registered_Students,
                      &lis[records].waitlist_availability,
                      lis[records].waitlist_Students);

        records++;

    }

    fclose(fp);

    return records;


}

int read_Student_data(StudentInfo lis[], const char *file_name) {
    FILE *fp = fopen(file_name, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return -1;
    }

    int records = 0;

    while (fscanf(fp, "%d,%[^,],%[^,],%d,%f,%[^,],%[^,],%[^,],%[^,],%f,%[^,],%d\n",
                  &lis[records].student_id,
                  lis[records].name,
                  lis[records].Department,
                  &lis[records].Semester,
                  &lis[records].percent12th,
                  lis[records].completed_courses,
                  lis[records].registered_courses,
                  lis[records].registerd_sections,
                  lis[records].waitlist_sections,
                  &lis[records].cgpa,
                  lis[records].email_id,
                  &lis[records].admin_control) == 12) {
        records++;
    }


    fclose(fp);
    return records;
}

int read_login_data(LoginInfo lis[], const char *file_name) {

    FILE *log;

    log = fopen(file_name, "r");

    if (log == NULL) {

        return -1;
    }
    int read = 0;
    int records = 0;

    do {

        read = fscanf(log,
                      "%d,%s\n",
                      &lis[records].user_id,
                      lis[records].password);

        if (read == 2) records++;

        if (read != 2 && !feof(log)) {

            return -1;
        }
        if (ferror(log)) {

            return -1;
        }


    } while (!feof(log));

    fclose(log);
    return records;


}

int read_faculty_data(FacultyInfo lis[], const char *file_name) {

    FILE *fp;

    fp = fopen(file_name, "r");


    if (fp == NULL)
        return -1;

    if (ferror(fp) != 0)
        return -1;

    int records = 0;
    while (feof(fp) == 0) {

        fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
               lis[records].faculty_code,
               lis[records].faculty_name,
               lis[records].gender,
               lis[records].designation,
               lis[records].email_id);


        records++;

    }

    fclose(fp);

    return records;
}


int read_slot_data(Slot lis[], const char *file_name) {

    FILE *fp;

    fp = fopen(file_name, "r");

    if (fp == NULL)
        return -1;

    if (ferror(fp) != 0)
        return -1;

    int records = 0;
    while (feof(fp) == 0) {

        fscanf(fp, "%[^,],%d,%[^,],%d,%[^,],%d,%[^,],%d,%[^,],%d,%[^\n]\n",
               lis[records].Department,
               &lis[records].Semester,
               lis[records].slot,
               &lis[records].al_slot1,
               lis[records].slot1,
               &lis[records].al_slot2,
               lis[records].slot2,
               &lis[records].al_slot3,
               lis[records].slot3,
               &lis[records].al_slot4,
               lis[records].slot4);

        records++;

    }

    fclose(fp);

    return records;

}


int read_setted_time(char time[], const char *file_name) {


    FILE *fp;

    fp = fopen(file_name, "r");

    if (fp == NULL)
        return -1;

    if (ferror(fp) != 0)
        return -1;

    int records = 0;
    while (feof(fp) == 0) {

        fscanf(fp, "%[^\n]\n",
               time);

        records++;

    }

    fclose(fp);

    return records;

}

int write_setted_time(char time[], const char *file_name) {

    FILE *fp;

    fp = fopen(file_name, "w");

    fprintf(fp, "%s\n", time);

    fclose(fp);

    return 1;

}


int write_course_data(Course lis[], const char *file_name, int records) {

    FILE *fp;

    fp = fopen(file_name, "w");

    for (int i = 0; i < records; i++) {

        fprintf(fp, "%s,%d,%s,%s,%d,%s,%s,%s,%hd,%s,%d\n",

                lis[i].Department,
                lis[i].Semester,
                lis[i].Course_code,
                lis[i].Course_Name,
                lis[i].Elective,
                lis[i].Section_1,
                lis[i].Section_2,
                lis[i].Section_3,
                lis[i].Credits,
                lis[i].pre_requisite,
                lis[i].mandatory);
        if (ferror(fp) != 0)
            return -1;
    }
    if (ferror(fp))
        return -1;
    fclose(fp);

    return 1;

}

int write_section_data(Section lis[], const char *file_name, int records) {

    FILE *fp;

    fp = fopen(file_name, "w");


    for (int i = 0; i < records; i++) {


        fprintf(fp, "%s,%s,%d,%s,%d,%s\n",
                lis[i].Section_code,
                lis[i].Faculty_code,
                lis[i].Available_seats,
                lis[i].Registered_Students,
                lis[i].waitlist_availability,
                lis[i].waitlist_Students);
    }

    if (ferror(fp))
        return -1;
    fclose(fp);

    return 1;


}

int write_student_data(StudentInfo lis[], const char *file_name, int records) {

    FILE *fp;

    fp = fopen(file_name, "w");
    for (int i = 0; i < records; i++) {

        fprintf(fp, "%d,%s,%s,%d,%f,%s,%s,%s,%s,%f,%s,%d\n",
                lis[i].student_id,
                lis[i].name,
                lis[i].Department,
                lis[i].Semester,
                lis[i].percent12th,
                lis[i].completed_courses,
                lis[i].registered_courses,
                lis[i].registerd_sections,
                lis[i].waitlist_sections,
                lis[i].cgpa,
                lis[i].email_id,
                lis[i].admin_control);
    }

    fclose(fp);


    return 1;


}

int write_login_data(LoginInfo lis[], const char *file_name, int records) {

    FILE *fp;

    fp = fopen(file_name, "w");

    for (int i = 0; i < records; i++) {

        fprintf(fp, "%d,%s\n",
                lis[i].user_id,
                lis[i].password);
    }
    fclose(fp);

    return 1;

}


int write_slot_data(Slot lis[], const char *file_name, int records) {

    FILE *fp;

    fp = fopen(file_name, "w");

    for (int i = 0; i < records; i++) {

        fprintf(fp, "%s,%d,%s,%d,%s,%d,%s,%d,%s,%d,%s\n",
                lis[i].Department,
                lis[i].Semester,
                lis[i].slot,
                lis[i].al_slot1,
                lis[i].slot1,
                lis[i].al_slot2,
                lis[i].slot2,
                lis[i].al_slot3,
                lis[i].slot3,
                lis[i].al_slot4,
                lis[i].slot4);
    }
    fclose(fp);

    return 1;

}


int read_terms_data(char lis[][10], const char *file_name) {

    FILE *fp;

    fp = fopen(file_name, "r");
    if (fp == NULL)
        return -1;

    if (ferror(fp) != 0)
        return -1;
    int records = 0;
    int read = 0;
    while (feof(fp) == 0) {

        fscanf(fp, "%[^\n]\n",

               lis[records]);
        records++;


    }

    fclose(fp);

    return records;

}

int write_terms_data(char lis[][10], const char *file_name, int records) {
    FILE *fp;
    fp = fopen(file_name, "w");
    for (int i = 0; i < records; i++) {

        fprintf(fp, "%s\n",
                lis[i]);
    }
    fclose(fp);
    return 1;
}



