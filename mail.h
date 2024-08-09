//
// Created by Ramcharan on 17-06-2024.
//

#ifndef UNTITLED_TRIAL_MAIL_H
#define UNTITLED_TRIAL_MAIL_H



void send_email();
int send_mail_waitlist_allotted(char *to,StudentInfo current_studnet,Course course,Section section) ;
int send_mail_if_registered(char* to,char*Name,int student_id,char* department,char*email_id,float percent12th);
bool IsInternetAvailable();

#endif //UNTITLED_TRIAL_MAIL_H
