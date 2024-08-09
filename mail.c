#include <stdbool.h>
#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include "Structure_definitions.c"
#include "file_functions.h"
#define GMAIL_SMTP_SERVER "smtp://smtp.gmail.com:587"
#define GMAIL_USERNAME "srsuniversity3@gmail.com"
#define GMAIL_PASSWORD "vjvb hbqa auef vdck"

struct upload_status {
    int lines_read;
    const char **payload_text;
};

static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp) {
    struct upload_status *upload_ctx = (struct upload_status *)userp;
    const char *data;

    if ((size == 0) || (nmemb == 0) || ((size * nmemb) < 1)) {
        return 0;
    }

    data = upload_ctx->payload_text[upload_ctx->lines_read];

    if (data) {
        size_t len = strlen(data);
        memcpy(ptr, data, len);
        upload_ctx->lines_read++;
        return len;
    }

    return 0;
}

void send_email(const char *to, const char *subject, const char *body) {
    CURL *curl;
    CURLcode res = CURLE_OK;
    struct curl_slist *recipients = NULL;
    struct upload_status upload_ctx;
    const char *payload_text[6];

    // Construct payload
    char to_header[256];
    char from_header[256];
    char subject_header[256];
    snprintf(to_header, sizeof(to_header), "To: %s\r\n", to);
    snprintf(from_header, sizeof(from_header), "From: %s\r\n", GMAIL_USERNAME);
    snprintf(subject_header, sizeof(subject_header), "Subject: %s\r\n", subject);

    payload_text[0] = to_header;
    payload_text[1] = from_header;
    payload_text[2] = subject_header;
    payload_text[3] = "\r\n";  // Empty line to separate headers from body
    payload_text[4] = body;
    payload_text[5] = NULL;  // NULL termination

    upload_ctx.lines_read = 0;
    upload_ctx.payload_text = payload_text;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, GMAIL_SMTP_SERVER);
        curl_easy_setopt(curl, CURLOPT_USERNAME, GMAIL_USERNAME);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, GMAIL_PASSWORD);
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, GMAIL_USERNAME);

        recipients = curl_slist_append(recipients, to);
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }
}

#define FACULTY_DATASIZE 500
#define FACULTY_DB "databases\\staff.csv"


FacultyInfo get_fac_detials_mail_version(char faculty_code[]){

    FacultyInfo fac_details[FACULTY_DATASIZE];
    int fac_records;
    fac_records = read_faculty_data(fac_details,FACULTY_DB);

    for (int i = 0; i < fac_records; i++) {
        if (strcmp(fac_details[i].faculty_code,faculty_code)==0){
            return fac_details[i];
        }
    }

}

int send_mail_waitlist_allotted(char *to,StudentInfo current_studnet,Course course,Section section) {


    FacultyInfo faculty = get_fac_detials_mail_version(section.Faculty_code);

    char subject[256] = "Enrollment Update: Successful Allotment to Waitlisted Section";
    char body[1024];



    snprintf(body, sizeof(body),
          "Dear %s,\r\n     We are pleased to inform you that you have been successfully allotted a seat in the waitlisted section for your course. Below are the details of your enrollment:\r\n\nCourse Details:\r\n - Course Code: %s\r\n- Course Name: %s\r\n- Credits: %d\r\n\nSection Details:\r\n- Section Code: %s\r\n- Faculty Name: %s\r\n- Faculty Email: %s\r\n\n If you have any questions or concerns, please do not hesitate to reach out to %s at %s .\r\n\nWe are excited to have you in this section and wish you a successful semester ahead.\r\n\nBest regards,\r\n\nAdmin \r\nPh no: +91 93425 48204 \r\nSRS University\r\nChennai - 600 001.\r\n",
          current_studnet.name,course.Course_code,
          course.Course_Name,course.Credits,
          section.Section_code,
          faculty.faculty_name,faculty.email_id,
          faculty.faculty_name,faculty.email_id);



    send_email(to, subject, (const char*)body);



    return 0;
}








int send_mail_if_registered(char* to,char*Name,int student_id,char* department,char*email_id,float percent12th){

    char subject[256] = "Welcome to SRS University! Your Registration is Complete";
    char body[1024];
    snprintf(body,sizeof (body),

    "Dear %s,\r\n"
    "\n"
    "Welcome to SRS University!\r\n"
    "\n"
    "We are delighted to inform you that your registration has been successfully completed. Here are your registration details:\r\n"
    "\n"
    "Registration Details:\r\n"
    "- Student ID: %d\r\n"
    "- Name: %s\r\n"
    "- Email: %s\r\n"
    "- HSC percentage: %f\r\n"
    "- Department: %s\r\n"
    "- Semester: 1\r\n"
    "\n"
    "Please keep your Student ID safe as you will need it to access various university services and resources.\r\n"
    "\n"
    "We kindly ask you to review your registration details carefully. If you find any discrepancies or if any of the information needs to be updated, please reply to this email as soon as possible so we can make the necessary corrections.\r\n"
    "\n"
    "We are excited to have you as part of our academic community and look forward to supporting you throughout your educational journey.\r\n"
    "\n"
    "Best regards,\r\n"
    "\n"
    "Admin  \r\n"
    "Ph no: +91 93425 48204 \r\n"
    "SRS University\r\n"
    "Chennai - 600 001.\r\n",


    Name,student_id,Name,email_id,percent12th,department);

    send_email(to, subject, (const char*)body);

}



bool IsInternetAvailable() {
    CURL *curl;
    CURLcode res;
    bool isConnected = false;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://www.google.com");
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

        res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            isConnected = true;
        }

        curl_easy_cleanup(curl);
    }

    return isConnected;
}

