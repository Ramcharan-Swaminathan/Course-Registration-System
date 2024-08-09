

#include "all_includes_and_macros.h"
#include "mail.h"

int check_credentials(int student_id, char password[]) {

    LoginInfo login_data[LOGIN_DATASIZE];
    int login_records = read_login_data(login_data,
                                        LOGIN_DB);

    for (int i = 0; i < login_records; i++) {
        if ((login_data[i].user_id == student_id) && (strcmp(login_data[i].password, password) == 0)) {
            return 1;
        }
    }

    return 0;

}


StudentInfo get_current_student(int student_id) {

    StudentInfo stu_details[STU_DATASIZE];
    int stu_records = read_Student_data(stu_details,
                                        STUDENT_DB);

    for (int i = 0; i < stu_records; i++) {
        if (stu_details[i].student_id == student_id) {
            return stu_details[i];
        }
    }

}


int gen_new_id() {

    int new_id = 0;
    FILE *fp = fopen(LAST_GEN_ID, "r");
    fscanf(fp, "%d", &new_id);
    new_id++;
    fclose(fp);
    fp = fopen(LAST_GEN_ID, "w");
    fprintf(fp, "%d", new_id);
    fclose(fp);
    return new_id;

}


int check_temp(int temp_id, char temp_pass[]) {

    LoginInfo temp_login_data[TEMP_DATASIZE];
    int temp_login_records = read_login_data(temp_login_data,
                                             TEMP_DB);

    for (int i = 0; i < temp_login_records; i++) {
        if (temp_login_data[i].user_id == temp_id && strcmp(temp_login_data[i].password, temp_pass) == 0) {
            return 1;
        }


    }
    return 0;
}


void add_new_details(int new_id, char name[], char department[], float percent12th, char email[]) {

    StudentInfo new_student;
    new_student.student_id = new_id;


    new_student.percent12th = percent12th;
    strcpy(new_student.Department, department);
    strcpy(new_student.name, name);
    strcpy(new_student.completed_courses, "NULL");
    strcpy(new_student.registered_courses, "NULL");
    strcpy(new_student.registerd_sections, "NULL");
    strcpy(new_student.waitlist_sections, "NULL");
    strcpy(new_student.email_id, email);
    new_student.cgpa = 0;
    new_student.Semester = 1;
    new_student.admin_control = 0;
    StudentInfo stu_details[STU_DATASIZE];
    int stu_records = read_Student_data(stu_details,
                                        STUDENT_DB);

    stu_details[stu_records] = new_student;
    write_student_data(stu_details,
                       STUDENT_DB,
                       stu_records + 1);
    divide_slots();
    if (if_slot_on(new_id, department, 1)) {
        admin_allow(new_id);
    }
    send_mail_if_registered(email, name, new_id, department, email, percent12th);
}

void add_to_login_db(int new_id, char new_password[]) {

    LoginInfo login_data[LOGIN_DATASIZE];
    int login_records = read_login_data(login_data,
                                        LOGIN_DB);

    login_data[login_records].user_id = new_id;
    strcpy(login_data[login_records].password, new_password);
    write_login_data(login_data,
                     LOGIN_DB,
                     login_records + 1);

}


void decrement_new_id() {

    int new_id;
    FILE *fp = fopen(LAST_GEN_ID, "r");
    fscanf(fp, "%d", &new_id);
    new_id--;
    fclose(fp);
    fp = fopen(LAST_GEN_ID, "w");
    fprintf(fp, "%d", new_id);
    fclose(fp);

}


int check_admin_credentials(int admin_id, char password[]) {

    LoginInfo admin_data[ADMIN_DATASIZE];
    int admin_records = read_login_data(admin_data,
                                        ADMIN_DB);

    for (int i = 0; i < admin_records; i++) {
        if ((admin_data[i].user_id == admin_id) && (strcmp(admin_data[i].password, password) == 0)) {
            return 1;
        }
    }

    return 0;

}


int if_present_in_terms(char student_id[10]) {

    int terms_records;
    char terms_details[TERMS_DATASIZE][10];
    terms_records = read_terms_data(terms_details, TERMS_ACCEPTED);
    if (strcmp(terms_details[0], "NULL") == 0) {
        return 0;
    } else {
        for (int i = 0; i < terms_records; i++) {
            if (strcmp(student_id, terms_details[i]) == 0) {
                return 1;
            }

        }

    }
    return 0;
}


int write_student_to_terms(char student_id[10]) {

    int terms_records;
    char terms_details[TERMS_DATASIZE][10];
    terms_records = read_terms_data(terms_details, TERMS_ACCEPTED);
    if (strcmp(terms_details[0], "NULL") == 0) {
        strcpy(terms_details[0], student_id);
    } else {
        strcpy(terms_details[terms_records], student_id);
    }

    write_terms_data(terms_details, TERMS_ACCEPTED, terms_records + 1);


}


int remove_temp_detail(int student_id) {

    LoginInfo temp_details[LOGIN_DATASIZE];
    int temp_records = read_login_data(temp_details, TEMP_DB);

    int index = 0;
    for (int i = 0; i < temp_records; i++) {
        if (student_id == temp_details[i].user_id) {
            index = i;
            break;
        }
    }
    for (int j = index; j < temp_records - 1; j++) {
        temp_details[j] = temp_details[j + 1];
    }
    temp_records--;
    write_login_data(temp_details, TEMP_DB, temp_records);
    return 0;

}






