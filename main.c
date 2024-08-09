
// Created by: SRS-University - Course Registration System

#include "all_includes_and_macros.h"
#include <time.h>

#define RAYGUI_IMPLEMENTATION

#include "raylib.h"
#include "raygui.h"
#include "mail.h"


#define SPLASH_TIME 3.0f
#define MY_BLUE (Color){22,100,225,225}

void DrawMultiLineTextWrapped(const char *text, Rectangle rec, int lineSpacing, Color color, Font font,int scrollOffsetY);
void ShowSplashScreen();

int main(void) {
    ShowSplashScreen();


    InitWindow(450, 350, "SRS-University"); // Initialize window with temporary values

    const int screenWidth = GetMonitorWidth(0);
    const int screenHeight = GetMonitorHeight(0) - 35;

    SetWindowSize(screenWidth, screenHeight);

    SetWindowPosition(0, 35);


    bool Login_page = true;
    bool Sign_up_page = false;
    bool Reg_page = false;
    bool Terms_page = false;

    const char *termsText = "Please read the following terms and conditions carefully before proceeding with the course registration process.\n\n"

                            "1.Students will be allocated slots based on their Cumulative Grade Point Average (CGPA) and Higher Secondary Certificate (HSC) percentage.\n"
                            "Students must enroll within the given time frame. Late enrollments will not be entertained.\n"
                            "\n"
                            "2.Students can add up to 6 courses, including mandatory courses.\n"
                            "Enrollment in elective courses is allowed only after the mandatory courses have been enrolled.\n"
                            "\n"
                            "3.Students have the option to drop a course. If a course is dropped, the first student on the waitlist will be allocated the seat.\n"
                            "The waitlist is sorted based on CGPA and HSC percentage.\n"
                            "\n"
                            "4.Students will receive an email notification if they are allocated a seat from the waitlisted sections.\n"
                            "\n"
                            "5.Students must register for a minimum of 4 courses. If a student fails to register for at least 4 courses, the administration will automatically allocate courses.\n"
                            "\n"
                            "Please ensure that you adhere to these terms and conditions to facilitate an organized and fair registration process.";


    bool Accept_butt = false;
    bool AcceptTerms = false;
    bool Decline_butt = false;
    bool DeclineTerms = false;

    bool login_butt = false;
    bool sign_butt = false;
    bool user_id_active = false;
    bool password_active = false;
    char user_id[10] = "";
    char password[64] = "";

    bool signlog_butt = false;
    bool show_login_failed = false;
    bool show_signup_failed = false;
    bool show_Pwd_failed = false;
    bool HSC_failed = false;

    bool signup_butt = false;
    bool login_butt_1 = false;
    int result;


    bool PassBoxEditMode = false;
    char PassBoxText[128] = "";
    bool CNPassBoxEditMode = false;
    char CNPassBoxText[128] = "";
    bool NameBoxEditMode = false;
    char NameBoxText[128] = "";
    bool DeptBoxEditMode = false;
    char DeptBoxText[128] = " ;CSE;IT;EEE;ECE;MECH;CIVIL;CHEM;BME";
    int dropdownActive_dept = 0;
    int dept_count = 9;
    bool HSC_BOXEditMode = false;
    char HSC_BOXText[128] = "";
    bool EmailBoxEditMode = false;
    char EmailBoxText[128] = "";

    bool reg_button = false;

    bool reg_failed = false;


    bool MainPage = false;
    bool if_admin_control_allowed = false;
    bool if_admin_control_allowed_checked = false;
    bool add_butt = false;
    bool remove_butt = false;
    bool view_butt = false;
    bool logout_butt = false;
    bool exit_butt = false;
    bool add_fail = false;


    bool AddPage = false;
    int sem_records;
    Course sem_courses[10];
    Course choosen_course;
    bool mandatory_failed = false;
    int mandatory_records;
    Course mandatory_courses[10];
    bool mandatory_commands[10] = {false};
    bool mand_click = false;


    bool exit_add_button = false;

    bool section_alloted = false;
    bool waitlist_alloted = false;
    bool section_removed = false;
    bool waitlist_removed = false;

    bool remove_fail = false;
    bool pre_req_failed = false;

    bool SectionPage = false;
    Section section_details[5];
    int sec_records;
    bool faculty_coommands[5] = {false};


    bool allot_commands[5] = {false};
    bool waitlist_commands[5] = {false};

    FacultyInfo current_faculty;

    bool exit_section_button = false;


    bool show_fac_box = false;
    int fac_index;
    char fac_box_content[500];


    Rectangle bounds = {0, 0, screenWidth, screenHeight};
    Rectangle content = {0, 0, 2000, 2000};
    Vector2 scroll = {0, 0};
    Rectangle view = {0, 0, screenWidth, screenHeight};

    //time_start
    char endTimeInput[64] = {0};
    time_t endTime = LoadEndTimeFromFile();
    bool inputEndTime = (endTime != (time_t) -1);
    bool processEnded = false;
    bool show_invalid_end_time = false;
    bool blocked_by_time = false;
    //time_end

    bool RemovePage = false;

    char regis_courses[10][10];
    int regis_records;
    bool select_course_butt[10];
    bool remove_course_butt[10];
    int waitlist_records;
    char waitlist_courses[10][10];
    bool wait_list_remove_butt[10];

    bool remove_exit_button = false;

    int course_view_records = 0;
    int waitlist_view_records = 0;
    bool if_got_regis_course = false;
    bool if_got_waitlist_course = false;


    bool Remove_waitlist_Page = false;
    bool rem_waitlist_button = false;
    bool rem_waitlist_exit_button = false;


    bool ViewPage = false;
    StudentInfo current_student;
    bool if_got_current_student = false;
    bool view_exit_butt = false;
    bool view_fac_commands[10] = {false};
    Course reg_courses[30];
    bool reg_courses_reterive = false;
    bool waitlist_view_read = false;
    int current_slot;
    bool slot_founded = false;
    bool checkd_slot_status = false;
    bool slot_status = false;


    bool AdminPage = false;
    bool slot_control_butt = false;

    char admin_dept_boxes[128] = " ;CSE;IT;EEE;ECE;MECH;CIVIL;CHEM;BME";
    int admin_dropdownActive_dept = 0;
    bool dept_dropdown_editmode = false;
    bool reg_dept_got = false;
    bool reg_sem_got = false;
    bool dept_got = false;
    bool sem_got = false;

    char admin_sem_boxes[20] = " ;1;2;3;4;5;6;7;8";
    int admin_dropdownActive_sem = 0;
    bool sem_dropdown_editmode = false;
    bool Allow_butt_commands[10] = {false};
    bool Block_butt_commands[10] = {false};

    bool reg_stats_butt = false;
    bool admin_exit_butt = false;
    bool admin_logout_butt = false;
    bool SlotPage = false;

    int allowed_slots[4];
    bool RegStatsPage = false;

    char stats_check_box1[64] = " ;Department wise;Semester wise";
    int stats1_dropdownActive = 0;
    bool stats1_dropdown_editmode = false;
    int stats1_count = 2;
    char stats_check_box2[64] = " ;Registered students;Total students";
    int stats2_dropdownActive = 0;
    bool stats2_dropdown_editmode = false;
    int stats2_count = 2;

    bool slot_exit_butt = false;
    bool reg_exit_butt = false;

    bool AdminLoginPage = false;
    bool admin_user_id_active = false;
    bool admin_password_active = false;
    char admin_user_id[64] = "";
    char admin_password[64] = "";
    bool admin_login_butt = false;
    bool show_adminlogin_failed = false;
    bool admin_back_butt = false;
    bool AdminLogin = false;

    char pre_requisitre_course[10][10];
    int pre_requisitre_records;
    char show_in_prereq_box[500];





    Image logo = LoadImage("databases\\LOGO.png");


    SetWindowIcon(logo);

    SetWindowState(FLAG_WINDOW_RESIZABLE);


    GuiSetStyle(DEFAULT, TEXT_SIZE, 40);

    char temp_user_id[64] = "";
    char temp_password[64] = "";

    GuiSetStyle(DEFAULT, TEXT_SIZE, 40);
    GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
    Font times_new_bold = LoadFont("databases\\Times New Roman\\times new roman bold.ttf");
    SetTextureFilter(times_new_bold.texture, TEXTURE_FILTER_TRILINEAR);

    GuiSetFont(times_new_bold);


    Texture2D logoTexture = LoadTextureFromImage(logo);
    UnloadImage(logo);


    int newgen_id;
    char new_id[10];

    SetTargetFPS(60);


    int newWidth = 200;
    int newHeight = 180;
    Vector2 position_logo = (Vector2) {0.0f, 0.0f};
    int x = 50;
    int y = 50;


    char running[200];
    float running_position = (float) screenWidth;
    int running_text_width;
    Course demand_course;



    while (!WindowShouldClose()) {

        ClearBackground(RAYWHITE);


        if (inputEndTime) {
            time_t currentTime = time(NULL);
            if (difftime(endTime, currentTime) <= 0) {
                processEnded = true;
                if (!blocked_by_time) {
                    block_slot("slot1");
                    block_slot("slot2");
                    block_slot("slot3");
                    block_slot("slot4");
                    allot_all_students();
                    blocked_by_time = true;
                    if_admin_control_allowed_checked = false;
                }
            }
        }

        running_position -= 4.0f;

        if (running_position < -running_text_width) {
            running_position = (float) screenWidth;
        }


        if (Login_page) {
            BeginDrawing();

            // Update active states
            if (user_id_active && IsKeyPressed(KEY_ENTER)) {
                user_id_active = false;
                password_active = true;
            } else if (password_active && IsKeyPressed(KEY_ENTER)) {
                password_active = false;
            }

            DrawRectangle(0, 0, screenWidth, 290, MY_BLUE);
            Rectangle sourcelogoRect_1 = {0.0f, 0.0f, (float) logoTexture.width, (float) logoTexture.height};
            Rectangle destlogoRect_1 = {(float) x, (float) y, (float) newWidth, (float) newHeight};
            DrawTexturePro(logoTexture, sourcelogoRect_1, destlogoRect_1, position_logo, 0.0f, WHITE);
            //DrawTextEx(times_new_bold,"SRS-University - Course Registration System", (Vector2){(screenWidth / 20) + 85, screenHeight / 8}, 90,1.0,BLUE);

            GuiSetStyle(DEFAULT, TEXT_SIZE, 80);
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));

            GuiLabel((Rectangle) {screenWidth * 0.15, screenHeight * 0.085, 2000, 100},
                     "SRS UNIVERSITY - LOGIN PAGE");
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(WHITE));
            GuiLabel((Rectangle) {screenWidth * 0.15 - 2, screenHeight * 0.085, 2000, 100},
                     "SRS UNIVERSITY - LOGIN PAGE");
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
            GuiSetStyle(DEFAULT, TEXT_SIZE, 40);


            GuiLabel((Rectangle) {screenWidth / 4, screenHeight / 2 + 250, 350, 50}, "Are you an Admin? ");
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(MY_BLUE));
            AdminLogin = GuiLabelButton((Rectangle) {screenWidth / 4 + 325, screenHeight / 2 + 250, 250, 50},
                                        "Login Here");
            GuiSetStyle(DEFAULT, TEXT_SIZE, 40);
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));

            //DrawText("SRS-University - Course Registration System", (screenWidth / 80) + 5, screenHeight / 8, 80,
            //       BLUE);

            // User ID
            float login_ypos = screenHeight * 0.4;
            GuiLabel((Rectangle) {(screenWidth * 0.25), login_ypos, MeasureText("Enter your User ID:", 40), 60},
                     "Enter your User ID:");
            //DrawText("Enter your Student ID:", (screenWidth / 4), (screenHeight / 2) - 100, 30, BLACK);
            if (GuiTextBox(
                    (Rectangle) {(screenWidth / 4) + MeasureText("Enter your User ID:", 40), login_ypos, 300, 60},
                    user_id, 64,
                    user_id_active)) {
                user_id_active = true;
                password_active = false;
            }

            // Password
            GuiLabel((Rectangle) {(screenWidth * 0.25), login_ypos + 70, MeasureText("Enter your Password:", 40), 60},
                     "Enter your Password:");

            if (GuiTextBox(
                    (Rectangle) {(screenWidth * 0.25) + MeasureText("Enter your User ID:", 40), login_ypos + 70, 300,
                                 60}, password, 64,
                    password_active)) {
                user_id_active = false;
                password_active = true;
            }

            // Login Button
            login_butt = GuiButton((Rectangle) {(screenWidth / 4) + 190, (screenHeight / 2) + 60, 300, 60}, "Login");

            //DrawText("Don't have an account?", (screenWidth / 4), (screenHeight / 2) + 190, 30, BLACK);
            GuiLabel((Rectangle) {(screenWidth / 4), (screenHeight / 2) + 183, 400, 50}, "Don't have an account?");
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(MY_BLUE));
            signlog_butt = GuiLabelButton((Rectangle) {(screenWidth / 4) + 380, (screenHeight / 2) + 180, 160, 50},
                                          "Sign Up");
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));

            if (signlog_butt) {
                Login_page = false;
                Sign_up_page = true;
                show_login_failed = false;
                strcpy(user_id, "");
                strcpy(password, "");
            }
            if (login_butt) {
                if (check_credentials(atoi(user_id), password)) {
                    if (!if_present_in_terms(user_id)){
                    Terms_page = true;
                    Login_page = false;}
                    else{
                        MainPage = true;
                        Login_page = false;
                    }
                } else {
                    show_login_failed = true;
                }
            }
            if (AdminLogin) {
                Login_page = false;
                AdminLoginPage = true;
            }
            if (show_login_failed) {
                GuiEnable();
                GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(RED));
                int result = GuiMessageBox((Rectangle) {screenWidth / 2 - 200, screenHeight / 2 - 150, 400, 200},
                                           "Login Failed",
                                           "Please check your credentials", (const char[]) {"OK"});

                GuiSetStyle(DEFAULT, TEXT_SIZE, 40);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
                strcpy(user_id, "");
                strcpy(password, "");
                GuiDisable();
                if (result >= 0) {
                    show_login_failed = false;
                    GuiEnable();
                }

            }

            EndDrawing();

        }
        else if (Terms_page){
            BeginDrawing();

            GuiScrollPanel(bounds, "", content, &scroll, &view);

            DrawRectangle(0, 0 + scroll.y, screenWidth, 150, MY_BLUE);
            GuiSetStyle(DEFAULT, TEXT_SIZE, 80);
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(WHITE));
            GuiLabel((Rectangle) {screenWidth / 2 - MeasureText("TERMS AND CONDITIONS",80)/2 , 30 + scroll.y,
                                  MeasureText("TERMS AND CONDITIONS",80), 150},
                     "TERMS AND CONDITIONS");
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
            GuiSetStyle(DEFAULT, TEXT_SIZE, 40);

            DrawMultiLineTextWrapped(termsText, (Rectangle) {10,160 , screenWidth , screenHeight }, 25, BLACK, times_new_bold,scroll.y);
            Accept_butt = GuiButton((Rectangle) {screenWidth / 2 - 200, screenHeight + 170 + scroll.y , 150, 50}, "Accept");
            Decline_butt = GuiButton((Rectangle) {screenWidth / 2 + 50, screenHeight + 170 + scroll.y, 150, 50}, "Decline");

            if(Decline_butt){
                Login_page = true;
                Terms_page = false;
            }
            if (Accept_butt){

                MainPage = true;
                Terms_page = false;
                write_student_to_terms(user_id);
                scroll.y = 0;

            }





            EndDrawing();
        }

        else if (Sign_up_page) {
            BeginDrawing();
            if (user_id_active && IsKeyPressed(KEY_ENTER)) {
                user_id_active = false;
                password_active = true;
            } else if (password_active && IsKeyPressed(KEY_ENTER)) {
                password_active = false;
            }
            DrawRectangle(0, 0, screenWidth, 290, MY_BLUE);
            Rectangle sourcelogoRect_1 = {0.0f, 0.0f, (float) logoTexture.width, (float) logoTexture.height};
            Rectangle destlogoRect_1 = {(float) x, (float) y, (float) newWidth, (float) newHeight};
            DrawTexturePro(logoTexture, sourcelogoRect_1, destlogoRect_1, position_logo, 0.0f, WHITE);
            //DrawTextEx(times_new_bold,"SRS-University - Course Registration System", (Vector2){(screenWidth / 20) + 85, screenHeight / 8}, 90,1.0,BLUE);

            GuiSetStyle(DEFAULT, TEXT_SIZE, 80);
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(WHITE));
            GuiLabel((Rectangle) {screenWidth / 20 + 190, screenHeight / 8 - 40, 2000, 100},
                     "SRS UNIVERSITY - REGISTRATION PAGE");
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
            GuiSetStyle(DEFAULT, TEXT_SIZE, 40);
            // User ID

            //DrawText("Enter your Temporary student ID:", (screenWidth / 4), (screenHeight / 2) - 100, 30, BLACK);
            GuiLabel((Rectangle) {(screenWidth / 4), (screenHeight / 2) - 115, 600, 60},
                     "Enter your Temporary student ID:");
            if (GuiTextBox((Rectangle) {(screenWidth / 4) + 550, (screenHeight / 2) - 115, 300, 60}, temp_user_id, 64,
                           user_id_active)) {
                user_id_active = true;
                password_active = false;
            }

            // Password
            //DrawText("Enter your Temporary Password:", (screenWidth / 4), (screenHeight / 2) - 20, 30, BLACK);
            GuiLabel((Rectangle) {(screenWidth / 4), (screenHeight / 2) - 35, 600, 60},
                     "Enter your Temporary Password:");
            if (GuiTextBox((Rectangle) {(screenWidth / 4) + 550, (screenHeight / 2) - 35, 300, 60}, temp_password, 64,
                           password_active)) {
                user_id_active = false;
                password_active = true;
            }

            // signup Button

            sign_butt = GuiButton((Rectangle) {(screenWidth / 4) + 275, (screenHeight / 2) + 60, 300, 60}, "Sign Up");



            //DrawText("Already have an account?", (screenWidth / 4), (screenHeight / 2) + 190, 30, BLACK);
            GuiLabel((Rectangle) {(screenWidth / 4), (screenHeight / 2) + 183, 400, 50}, "Already have an account?");

            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLUE));

            if (GuiLabelButton((Rectangle) {(screenWidth / 4) + 420, (screenHeight / 2) + 180, 160, 50}, "Login")) {
                Login_page = true;
                Sign_up_page = false;
                show_signup_failed = false;
                strcpy(temp_user_id, "");
                strcpy(temp_password, "");
            }
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));

            if (sign_butt) {
                if (check_temp(atoi(temp_user_id), temp_password)) {
                    Sign_up_page = false;
                    Reg_page = true;
                    newgen_id = gen_new_id();
                } else {
                    show_signup_failed = true;
                }
            }
            if (show_signup_failed) {

                GuiEnable();
                GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(RED));

                result = GuiMessageBox((Rectangle) {screenWidth / 2 - 180, screenHeight / 2 - 150, 400, 200},
                                       "Sign Up Failed",
                                       "Please check your credentials", (const char[]) {"OK"});

                GuiSetStyle(DEFAULT, TEXT_SIZE, 40);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
                strcpy(temp_user_id, "");
                strcpy(temp_password, "");
                GuiDisable();
                if (result >= 0) {
                    show_signup_failed = false;
                    GuiEnable();
                }

            }
            EndDrawing();
        }
        else if (Reg_page) {
            reg_failed = true;
            BeginDrawing();
            GuiScrollPanel(bounds, "", content, &scroll, &view);

            DrawRectangle(0, 0 + scroll.y, screenWidth, 290, MY_BLUE);
            Rectangle sourcelogoRect_1 = {0.0f, 0.0f, (float) logoTexture.width, (float) logoTexture.height};
            Rectangle destlogoRect_1 = {(float) x, (float) y, (float) newWidth, (float) newHeight};
            DrawTexturePro(logoTexture, sourcelogoRect_1, destlogoRect_1, position_logo, 0.0f, WHITE);
            //DrawTextEx(times_new_bold,"SRS-University - Course Registration System", (Vector2){(screenWidth / 20) + 85, screenHeight / 8}, 90,1.0,BLUE);

            GuiSetStyle(DEFAULT, TEXT_SIZE, 80);
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(WHITE));
            GuiLabel((Rectangle) {screenWidth / 20 + 190, screenHeight / 8 - 40 + scroll.y, 2000, 100},
                     "SRS UNIVERSITY - REGISTRATION PAGE");
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
            GuiSetStyle(DEFAULT, TEXT_SIZE, 40);

            itoa(newgen_id, new_id, 10);
            GuiDrawRectangle((Rectangle) {440, 390 + scroll.y, 820, 52}, 2, BLACK, MY_BLUE);
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(WHITE));
            GuiLabel((Rectangle) {445, 400 + scroll.y, 1100, 24}, "This is Your Newly Generated student id:");
            GuiLabel((Rectangle) {1100, 400 + scroll.y, 120, 24}, new_id);

            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));


            GuiLabel((Rectangle) {446, 460 + 20 + scroll.y, 800, 24}, "Create a password");
            if (GuiTextBox((Rectangle) {980, 450 + 20 + scroll.y, 450, 50}, PassBoxText, 128, PassBoxEditMode))
                PassBoxEditMode = !PassBoxEditMode;

            GuiLabel((Rectangle) {446, 520 + 20 + scroll.y, 800, 24}, "Rewrite your password");
            if (GuiTextBox((Rectangle) {980, 510 + 20 + scroll.y, 450, 50}, CNPassBoxText, 128,
                           CNPassBoxEditMode))
                CNPassBoxEditMode = !CNPassBoxEditMode;

            GuiLabel((Rectangle) {446, 580 + 20 + scroll.y, 850, 24}, "Enter your Name");
            if (GuiTextBox((Rectangle) {980, 570 + 20 + scroll.y, 450, 50}, NameBoxText, 128, NameBoxEditMode))
                NameBoxEditMode = !NameBoxEditMode;

            GuiLabel((Rectangle) {448, 640 + 20 + scroll.y, 800, 24}, "Enter your Department");
            //if (GuiTextBox((Rectangle) {980, 530 + 20, 450, 50}, DeptBoxText, 128, DeptBoxEditMode))

            bool drop = GuiDropdownBox((Rectangle) {980, 630 + 20 + scroll.y, 450, 50}, DeptBoxText,
                                       &dropdownActive_dept,
                                       DeptBoxEditMode);
            if (drop) { DeptBoxEditMode = !DeptBoxEditMode; }

            GuiLabel((Rectangle) {448, 700 + 20 + scroll.y, 800, 24}, "Enter your HSC percentage ");
            GuiLabel((Rectangle) {448, 765 + 20 + scroll.y, 800, 24}, "Enter your Email ID ");
            if (!DeptBoxEditMode) {
                if (GuiTextBox((Rectangle) {980, 690 + 20 + scroll.y, 450, 50}, HSC_BOXText, 128, HSC_BOXEditMode))
                    HSC_BOXEditMode = !HSC_BOXEditMode;

                if (GuiTextBox((Rectangle) {980, 755 + 20 + scroll.y, 450, 50}, EmailBoxText, 128, EmailBoxEditMode))
                    EmailBoxEditMode = !EmailBoxEditMode;
            }


            reg_button = GuiButton((Rectangle) {600, 760 + 128 + scroll.y, 250, 50}, "REGISTER");
            if (reg_button) {
                if (atof(HSC_BOXText) > 100 || atof(HSC_BOXText) < 0) {
                    HSC_failed = true;
                } else if (strcmp(PassBoxText, CNPassBoxText) == 0 && strcmp(PassBoxText, "") != 0 &&
                           strcmp(CNPassBoxText, "") != 0 && strcmp(NameBoxText, "") != 0 && dropdownActive_dept != 0 &&
                           strcmp(HSC_BOXText, "") != 0) {
                    add_new_details(newgen_id, NameBoxText,
                                    (char *) TextSplit(DeptBoxText, ';', &dept_count)[dropdownActive_dept],
                                    atof(HSC_BOXText), EmailBoxText);

                    add_to_login_db(newgen_id, PassBoxText);
                    remove_temp_detail(atoi(temp_user_id));
                    Reg_page = false;
                    Login_page = true;
                    scroll.y = 0;
                    strcpy(temp_user_id, "");
                    strcpy(temp_password, "");
                    strcpy(PassBoxText, "");
                    strcpy(CNPassBoxText, "");
                    strcpy(NameBoxText, "");
                    strcpy(HSC_BOXText, "");
                    strcpy(EmailBoxText, "");
                    reg_failed = false;
                    dropdownActive_dept = 0;
                    DeptBoxEditMode = false;


                } else {
                    show_Pwd_failed = true;
                }
            }
            if (show_Pwd_failed) {
                GuiEnable();
                GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(RED));

                int result = GuiMessageBox((Rectangle) {screenWidth / 2 - 200, screenHeight / 2 - 100, 400, 200},
                                           "Registration Failed",
                                           "Passwords do not match", (const char[]) {"OK"});

                GuiSetStyle(DEFAULT, TEXT_SIZE, 40);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
                strcpy(PassBoxText, "");
                strcpy(CNPassBoxText, "");
                GuiDisable();
                if (result >= 0) {
                    show_Pwd_failed = false;
                    GuiEnable();
                }
            }
            if (HSC_failed) {
                GuiEnable();
                GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(RED));

                int result = GuiMessageBox((Rectangle) {screenWidth / 2 - 200, screenHeight / 2 - 100, 400, 200},
                                           "Registration Failed",
                                           "Please enter a valid HSC percentage", (const char[]) {"OK"});

                GuiSetStyle(DEFAULT, TEXT_SIZE, 40);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
                strcpy(HSC_BOXText, "");
                GuiDisable();
                if (result >= 0) {
                    HSC_failed = false;
                    GuiEnable();
                }
            }


            EndDrawing();
        }
        else if (MainPage) {

            BeginDrawing();
            GuiScrollPanel(bounds, "", content, &scroll, &view);
            reg_courses_reterive = false;
            if_got_regis_course = false;
            if_got_waitlist_course = false;
            waitlist_view_read = false;
            DrawRectangle(0, 0 + scroll.y, screenWidth, 290, MY_BLUE);
            {
                Rectangle sourcelogoRect_1 = {0.0f, 0.0f, (float) logoTexture.width, (float) logoTexture.height};
                Rectangle destlogoRect_1 = {(float) x - 40, (float) y + scroll.y, (float) newWidth, (float) newHeight};
                DrawTexturePro(logoTexture, sourcelogoRect_1, destlogoRect_1, position_logo, 0.0f, WHITE);
            }

            if (!if_got_current_student) {
                current_student = get_current_student(atoi(user_id));
                if_got_current_student = true;
            }

            demand_course = get_max_reg_course(current_student.Department, current_student.Semester);

            strcpy(running, "Check out ");
            strcat(running, demand_course.Course_Name);
            strcat(running, " (");
            strcat(running, demand_course.Course_code);
            strcat(running,
                   ") .      This Course is on fire!!         Limited Seats Only Available!!          Register Soon!! \0");

            running_text_width = MeasureText(running, 30);


            GuiDrawRectangle((Rectangle) {0, 290.8 + scroll.y, screenWidth, 40}, 1, BLACK,
                             (Color) {255, 249, 196, 225});
            GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
            GuiLabel((Rectangle) {running_position, 290 + scroll.y, running_text_width, 40}, running);
            GuiSetStyle(DEFAULT, TEXT_SIZE, 40);

            GuiSetStyle(DEFAULT, TEXT_SIZE, 70);
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(WHITE));
            GuiLabel((Rectangle) {screenWidth / 20 + 140, screenHeight / 8 - 40 + scroll.y, 2000, 100},
                     "SRS UNIVERSITY - COURSE REGISTRATION SYSTEM");
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
            GuiSetStyle(DEFAULT, TEXT_SIZE, 40);
            if (!if_admin_control_allowed_checked) {
                if_admin_control_allowed = check_admin_control(atoi(user_id));
                if_admin_control_allowed_checked = true;
            }


            TimeDifference diff = GetTimeDifference(endTime);

            // Draw

            if (processEnded) {
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(RED));
                GuiLabel((Rectangle) {screenWidth / 2 - 100, screenHeight / 2 - 100 + scroll.y, 500, 50},
                         "Time's up!");
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
            } else {
                char timeLeft[128];
                snprintf(timeLeft, sizeof(timeLeft),
                         "Time left for Course Registration: %d days %d hours %d minutes %d seconds",
                         diff.days, diff.hours, diff.minutes, diff.seconds);
                //DrawText(timeLeft, 50, 50, 20, DARKGRAY);
                GuiDrawRectangle((Rectangle) {screenWidth / 4 - 85, screenHeight / 2 - 100 - 3 + scroll.y, 1130, 56},
                                 1, BLACK, (Color) {202, 87, 255, 225});
                GuiLabel((Rectangle) {screenWidth / 4 - 80, screenHeight / 2 - 100 + scroll.y, 1120, 50}, timeLeft);

            }


            if (if_admin_control_allowed) {
                add_butt = GuiButton((Rectangle) {screenWidth / 2 - 465, screenHeight / 2 + scroll.y, 450, 50},
                                     "ADD COURSE");
                remove_butt = GuiButton(
                        (Rectangle) {screenWidth / 2 + 15, screenHeight / 2 + scroll.y, 450, 50},
                        "REMOVE COURSE");
            } else {
                GuiSetStyle(DEFAULT, TEXT_SIZE, 60);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(RED));
                GuiLabel((Rectangle) {screenWidth / 2 - 325, screenHeight / 2 + scroll.y, 1000, 50},
                         "Registration Not Available!");
                GuiSetStyle(DEFAULT, TEXT_SIZE, 40);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
            }
            view_butt = GuiButton((Rectangle) {screenWidth / 2 - 465, screenHeight / 2 + 100 + scroll.y, 450, 50},
                                  " VIEW DETAILS ");

            rem_waitlist_button = GuiButton(
                    (Rectangle) {screenWidth / 2 + 15, screenHeight / 2 + 100 + scroll.y, 450, 50},
                    "REMOVE WAITLIST");
            logout_butt = GuiButton((Rectangle) {screenWidth / 2 - 465, screenHeight / 2 + 200 + scroll.y, 450, 50},
                                    "LOGOUT");
            exit_butt = GuiButton((Rectangle) {screenWidth / 2 + 15, screenHeight / 2 + 200 + scroll.y, 450, 50},
                                  "EXIT");


            if (exit_butt) {
                break;
            }
            if (logout_butt) {
                Login_page = true;
                strcpy(user_id, "");
                strcpy(password, "");
                MainPage = false;
                if_admin_control_allowed_checked = false;
                if_got_current_student = false;
            }
            if (add_butt) {
                if (add_check_eligibilty(atoi(user_id))) {
                    MainPage = false;
                    AddPage = true;
                    scroll.y = 0;
                } else { add_fail = true; }

            }
            if (add_fail) {
                GuiEnable();
                GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(RED));

                int result = GuiMessageBox(
                        (Rectangle) {screenWidth / 2 - 200, screenHeight / 2 - 100 + scroll.y, 400, 200},
                        "Add Failed",
                        "You have already registered for 6 courses", (const char[]) {"OK"});

                GuiSetStyle(DEFAULT, TEXT_SIZE, 40);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
                GuiDisable();
                if (result >= 0) {
                    add_fail = false;
                    GuiEnable();
                }

            }


            if (remove_butt) {

                    MainPage = false;
                    RemovePage = true;
                    scroll.y = 0;

            }
            if (remove_fail) {
                GuiEnable();
                GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(RED));

                int result = GuiMessageBox(
                        (Rectangle) {screenWidth / 2 - 200, screenHeight / 2 - 100 + scroll.y, 400, 200},
                        "Remove Failed",
                        "You must register alteast  5 courses \n\n for removing courses",
                        (const char[]) {"OK"});

                GuiSetStyle(DEFAULT, TEXT_SIZE, 40);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
                GuiDisable();
                if (result >= 0) {
                    remove_fail = false;
                    GuiEnable();
                }
            }
            if (view_butt) {
                MainPage = false;
                ViewPage = true;
                scroll.y = 0;
            }
            if (rem_waitlist_button) {
                MainPage = false;
                Remove_waitlist_Page = true;
                scroll.y = 0;
            }


            EndDrawing();


        }
        else if (AddPage) {
            BeginDrawing();
            GuiScrollPanel(bounds, "", content, &scroll, &view);
            //DrawText("ADD COURSE", (screenWidth / 80) + 5 + scroll.x, screenHeight / 8 - 75 + scroll.y, 80, BLUE);
            DrawRectangle(0, 0 + scroll.y, screenWidth, 290, MY_BLUE);
            GuiSetStyle(DEFAULT, TEXT_SIZE, 80);
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(WHITE));
            GuiLabel((Rectangle) {screenWidth / 20 + 190, screenHeight / 8 - 20 + scroll.y, 2000, 100},
                     "SRS UNIVERSITY - ADD COURSE PAGE");
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
            GuiSetStyle(DEFAULT, TEXT_SIZE, 40);


            int pos_y_non_mand = screenWidth/2 ;
            mandatory_records = not_registered_mandatory(current_student, mandatory_courses);
            if(mandatory_records >0) {
                GuiSetStyle(DEFAULT, TEXT_SIZE, 60);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(MY_BLUE));
                GuiLabel((Rectangle) {screenWidth / 2 - MeasureText("MANDATORY COURSES", 60)/2, screenHeight / 4 + 100 + scroll.y, MeasureText("MANDATORY COURSES", 60), 200},
                         "MANDATORY COURSES");
                GuiSetStyle(DEFAULT, TEXT_SIZE, 40);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
                Labels_for_sem_courses(mandatory_courses, mandatory_records, 100 + scroll.x,
                                       screenHeight / 4 + 330 + scroll.y,
                                       mandatory_commands);
            }
            else{
                GuiSetStyle(DEFAULT, TEXT_SIZE, 60);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(GREEN));
                GuiLabel((Rectangle) {screenWidth / 8 , screenHeight / 2 - 100 + scroll.y, MeasureText("You have already registered for all the mandatory courses!",50), 200},
                         "You have already registered for all the mandatory courses!");
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
                pos_y_non_mand = screenWidth/2 - 100;
                GuiSetStyle(DEFAULT, TEXT_SIZE, 40);
            }
            GuiSetStyle(DEFAULT, TEXT_SIZE, 60);
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(MY_BLUE));

            GuiLabel((Rectangle) {screenWidth / 2 - MeasureText("AVAILABLE COURSES FOR CHOOSING", 60)/2,   pos_y_non_mand-250+ scroll.y, MeasureText("AVAILABLE COURSES FOR CHOOSING", 60), 200},
                     "AVAILABLE COURSES FOR CHOOSING");
            GuiSetStyle(DEFAULT, TEXT_SIZE, 40);
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));

            sem_records = retrieve_non_mandatory_non_registered_courses(atoi(user_id), sem_courses);
            Labels_for_sem_courses(sem_courses, sem_records, 100 + scroll.x, pos_y_non_mand + scroll.y,
                                   select_course_butt);
            exit_add_button = GuiButton(
                    (Rectangle) {screenWidth / 2 + 680, screenHeight / 8 + 200 + scroll.y, 225, 50},
                    "<< Back");
            for (int i = 0; i < sem_records; i++) {
                if (select_course_butt[i] == true) {

                    choosen_course = sem_courses[i];

                    if(if_student_registered_mandatory(current_student)) {
                        if (pre_requisites(&choosen_course, atoi(user_id))) {
                            AddPage = false;
                            scroll.y = 0;
                            SectionPage = true;
                        } else { pre_req_failed = true; }
                    }
                    else { mandatory_failed = true; }


                }
            }
            for (int i = 0; i < mandatory_records; i++) {
                if (mandatory_commands[i] == true) {
                    choosen_course = mandatory_courses[i];
                    mand_click = true;
                    if_got_current_student = false;
                    scroll.y = 0;
                }
            }
            if (mand_click) {
                GuiEnable();
                GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(RED));
                int result_mand = GuiMessageBox((Rectangle) {screenWidth / 2 - 200, screenHeight / 2 - 100, MeasureText(
                                                        "You cannot Change or Remove Section once you have been allotted.", 20), 400},
                                           "Mandatory Course",
                                           "You cannot Change or Remove Section once you have been allotted.\n\n"
                                           "So make sure to choose the right section",
                                           (const char[]) {"Back;Proceed"});
                GuiSetStyle(DEFAULT, TEXT_SIZE, 40);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
                GuiDisable();

                if (result_mand >= 0 && result_mand != 2) {

                    mand_click = false;
                    GuiEnable();}
                else if (result_mand == 2) {

                    AddPage = false;
                    SectionPage = true;
                    mand_click = false;
                    scroll.y = 0;
                    GuiEnable();

                }
            }


            if (pre_req_failed) {
                GuiEnable();
                GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(RED));

                pre_requisitre_records = split_string(pre_requisitre_course, choosen_course.pre_requisite, "|");

                strcpy(show_in_prereq_box, "You do not meet the pre-requisites for the courses :\n\n ");
                for (int i = 0; i < pre_requisitre_records; i++) {
                    strcat(show_in_prereq_box, pre_requisitre_course[i]);
                    strcat(show_in_prereq_box, "\n\n");
                }


                int result = GuiMessageBox((Rectangle) {screenWidth / 2 - 200, screenHeight / 2 - 100, 200 +
                                                                                                       MeasureText(
                                                                                                               "You do not meet the pre-requisites for the courses :",
                                                                                                               20),
                                                        pre_requisitre_records * 20 + 300},
                                           "Pre-requisites Failed",
                                           show_in_prereq_box, (const char[]) {"OK"});

                GuiSetStyle(DEFAULT, TEXT_SIZE, 40);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
                GuiDisable();
                if (result >= 0) {
                    pre_req_failed = false;
                    GuiEnable();
                }
            }
            if(mandatory_failed){
                GuiEnable();
                GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(RED));

                int result = GuiMessageBox((Rectangle) {screenWidth / 2 - 200, screenHeight / 2 - 100, MeasureText("You have not registered for the mandatory courses",20), 200},
                                           "Mandatory Course Failed",
                                           "You have not registered for the mandatory courses", (const char[]) {"OK"});

                GuiSetStyle(DEFAULT, TEXT_SIZE, 40);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
                GuiDisable();
                if (result >= 0) {
                    mandatory_failed = false;
                    GuiEnable();
                }
            }




            if (exit_add_button) {
                MainPage = true;
                AddPage = false;
                if_got_current_student = false;
                scroll.y = 0;


            }


            EndDrawing();

        }
        else if (SectionPage) {
            BeginDrawing();
            GuiScrollPanel(bounds, "", content, &scroll, &view);

            DrawRectangle(0, 0 + scroll.y, screenWidth, 290, MY_BLUE);
            GuiSetStyle(DEFAULT, TEXT_SIZE, 80);
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(WHITE));
            GuiLabel((Rectangle) {screenWidth / 20 + 190, screenHeight / 8 - 20 + scroll.y, 2000, 100},
                     "SRS UNIVERSITY - SECTION PAGE");
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
            GuiSetStyle(DEFAULT, TEXT_SIZE, 40);

            sec_records = retrieve_section(choosen_course, section_details);
            exit_section_button = GuiButton(
                    (Rectangle) {screenWidth / 2 + 680, screenHeight / 8 + 200 + scroll.y, 225, 50},
                    "<< Back");

            Labels_for_section(section_details, sec_records, 100 + scroll.x,
                               screenHeight / 4 + 260 + scroll.y, faculty_coommands, allot_commands, waitlist_commands,
                               atoi(user_id));
            if (exit_section_button) {
                AddPage = true;
                SectionPage = false;
                show_fac_box = false;
                if_got_current_student = false;
                scroll.y = 0;

            }
            for (int i = 0; i < sec_records; i++) {
                if (faculty_coommands[i] == true) {
                    show_fac_box = true;
                    fac_index = i;

                }
            }
            for (int i = 0; i < sec_records; i++) {
                if (allot_commands[i] == true) {
                    allot_section(atoi(user_id), section_details[i].Section_code, choosen_course.Course_code);
                    section_alloted = true;
                }
            }
            if (section_alloted) {
                GuiEnable();
                GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(GREEN));

                int result = GuiMessageBox((Rectangle) {screenWidth / 2 - 500, screenHeight / 2 - 100, 400, 200},
                                           "Section Status",
                                           "Section has been Alloted Successfully",
                                           (const char[]) {"OK"});

                GuiSetStyle(DEFAULT, TEXT_SIZE, 40);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
                GuiDisable();
                if (result >= 0) {
                    SectionPage = false;
                    GuiEnable();
                    show_fac_box = false;
                    section_alloted = false;
                    MainPage = true;
                    if_got_current_student = false;
                    scroll.y = 0;

                }
            }


            for (int i = 0; i < sec_records; i++) {
                if (waitlist_commands[i] == true) {
                    allot_waitlist(atoi(user_id), choosen_course.Course_code, section_details[i].Section_code);
                    waitlist_alloted = true;

                }
            }
            if (waitlist_alloted) {
                GuiEnable();
                GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(GREEN));

                int result = GuiMessageBox((Rectangle) {screenWidth / 2 - 200, screenHeight / 2 - 100, 400, 200},
                                           "Waitlist Status",
                                           "Waitlist Section has been Alloted Successfully!", (const char[]) {"OK"});

                GuiSetStyle(DEFAULT, TEXT_SIZE, 40);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
                GuiDisable();
                if (result >= 0) {
                    MainPage = true;
                    SectionPage = false;
                    show_fac_box = false;
                    waitlist_alloted = false;
                    scroll.y = 0;
                    GuiEnable();
                }
            }


            if (show_fac_box) {

                current_faculty = get_fac_detials(section_details[fac_index].Faculty_code);

                strcat(fac_box_content, "            Name:  ");
                strcat(fac_box_content, current_faculty.faculty_name);
                strcat(fac_box_content, "                \n\n\nDesignation:  ");
                strcat(fac_box_content, current_faculty.designation);
                strcat(fac_box_content, "               \n\n\n Mail_id: ");
                strcat(fac_box_content, current_faculty.email_id);


                GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
                int result = GuiMessageBox(
                        (Rectangle) {screenWidth / 2 - 250, screenHeight / 2 - 100 + scroll.y, 750, 400},
                        "Faculty Details",
                        fac_box_content, (const char[]) {"OK"});

                if (result >= 0) { show_fac_box = false; }
                strcpy(fac_box_content, "");
            }
            for (int i = 0; i < sec_records; i++) {
                faculty_coommands[i] = false;
                allot_commands[i] = false;
                waitlist_commands[i] = false;
                if_got_current_student = false;

            }


            EndDrawing();


        }
        else if (RemovePage) {
            BeginDrawing();
            GuiScrollPanel(bounds, "", content, &scroll, &view);

            DrawRectangle(0, 0 + scroll.y, screenWidth, 290, MY_BLUE);
            GuiSetStyle(DEFAULT, TEXT_SIZE, 80);
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(WHITE));
            GuiLabel((Rectangle) {screenWidth / 20 + 100, screenHeight / 8 - 20 + scroll.y, 2000, 100},
                     "SRS UNIVERSITY - REMOVE COURSE PAGE");
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
            GuiSetStyle(DEFAULT, TEXT_SIZE, 40);


            regis_records = retrieve_non_mandatory_regcourses(atoi(user_id), regis_courses);
            if(regis_records > 0){
            Labels_for_courses(regis_courses, regis_records, 100 + scroll.x, screenHeight / 4 + 260 + scroll.y,
                               remove_course_butt);
            }
            else{
                GuiLabel((Rectangle) {screenWidth / 2 - 350, screenHeight / 2 + scroll.y, 700, 60},
                         "No Removable Courses Enrolled!");
                GuiSetStyle(DEFAULT, TEXT_SIZE, 40);
            }


            remove_exit_button = GuiButton(
                    (Rectangle) {screenWidth / 2 + 680, screenHeight / 8 + 200 + scroll.y, 225, 50},
                    "<< Back");


            for (int i = 0; i < regis_records; i++) {

                if (remove_course_butt[i] == true) {

                    remove_courses(atoi(user_id), regis_courses[i]);

                    section_removed = true;

                }
            }
            if (section_removed) {
                GuiEnable();
                GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(GREEN));

                int result = GuiMessageBox(
                        (Rectangle) {screenWidth / 2 - 200, screenHeight / 2 - 100 + scroll.y, 400, 200},
                        "Section Status",
                        "Section has been Removed Successfully!", (const char[]) {"OK"});

                GuiSetStyle(DEFAULT, TEXT_SIZE, 40);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
                GuiDisable();
                if (result >= 0) {
                    MainPage = true;
                    RemovePage = false;
                    section_removed = false;
                    if_got_current_student = false;
                    scroll.y = 0;
                    GuiEnable();
                }
            }
            EndDrawing();
            if (remove_exit_button) {
                MainPage = true;
                RemovePage = false;
                scroll.y = 0;
            }


        }
        else if (Remove_waitlist_Page)
        {


            BeginDrawing();
            GuiScrollPanel(bounds, "", content, &scroll, &view);

            DrawRectangle(0, 0 + scroll.y, screenWidth, 290, MY_BLUE);
            GuiSetStyle(DEFAULT, TEXT_SIZE, 80);
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(WHITE));
            GuiLabel((Rectangle) {screenWidth / 20 + 100, screenHeight / 8 - 20 + scroll.y, 2000, 100},
                     "SRS UNIVERSITY - REMOVE WAITLIST PAGE");
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
            GuiSetStyle(DEFAULT, TEXT_SIZE, 40);
            waitlist_records = retrieve_waitlist_sections(atoi(user_id), waitlist_courses);
            if (waitlist_records > 0) {
                //DrawText("REMOVE WAITLIST SECTIONS", (screenWidth / 80) + 5 + scroll.x,screenHeight / 4 + 50 + 450 + scroll.y, 80, BLUE);

                Labels_for_waitlist_sections(waitlist_courses, waitlist_records, 100 + scroll.x,
                                             screenHeight / 4 + 200 + scroll.y, wait_list_remove_butt);
                for (int i = 0; i < waitlist_records; i++) {
                    if (wait_list_remove_butt[i] == true) {
                        remove_from_waitlist(waitlist_courses[i], atoi(user_id));
                        waitlist_removed = true;
                    }
                }


            } else {
                GuiLabel((Rectangle) {screenWidth / 2 - 350, screenHeight / 2 + scroll.y, 700, 60},
                         "No Waitlist Sections Enrolled!");
                GuiSetStyle(DEFAULT, TEXT_SIZE, 40);

            }
            rem_waitlist_exit_button = GuiButton(
                    (Rectangle) {screenWidth / 2 + 680, screenHeight / 8 + 200 + scroll.y, 225, 50},
                    "<< Back");

            if (waitlist_removed) {
                GuiEnable();
                GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(GREEN));

                int result_1 = GuiMessageBox((Rectangle) {screenWidth / 2 - 200, screenHeight / 2 - 100, 400, 200},
                                             "Waitlist Status",
                                             "Waitlist Section has been Removed Successfully!", (const char[]) {"OK"});

                GuiSetStyle(DEFAULT, TEXT_SIZE, 40);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
                GuiDisable();
                if (result_1 >= 0) {
                    MainPage = true;
                    Remove_waitlist_Page = false;
                    waitlist_removed = false;
                    if_got_current_student = false;
                    scroll.y = 0;
                    GuiEnable();
                }
            }
            if (rem_waitlist_exit_button) {
                MainPage = true;
                Remove_waitlist_Page = false;
                scroll.y = 0;
            }

            EndDrawing();
        }
        else if (ViewPage) {
            BeginDrawing();
            GuiScrollPanel(bounds, "", content, &scroll, &view);


            //regis_records = retrieve_courses(345679, regis_courses);
            if (!if_got_current_student) {
                current_student = get_current_student(atoi(user_id));
                if_got_current_student = true;
            }

            char current_student_id[10];
            char current_semester[10];
            sprintf(current_semester, "%d", current_student.Semester);
            sprintf(current_student_id, "%d", current_student.student_id);


            GuiSetStyle(DEFAULT, TEXT_SIZE, 40);
            if (!slot_founded) {
                current_slot = find_which_slot(atoi(user_id));
                slot_founded = true;
            }

            if (!checkd_slot_status) {
                slot_status = if_slot_on(current_student.student_id, current_student.Department,
                                         current_student.Semester);
                checkd_slot_status = true;
            }
            if (slot_status) {
                GuiDrawRectangle((Rectangle) {0, screenHeight / 2 - 145 + scroll.y, screenWidth - 12, 60}, 1, BLACK,
                                 (Color) {122, 255, 120, 225});
                GuiLabel((Rectangle) {screenWidth / 2 + 50 + scroll.x, screenHeight / 2 - 140 + scroll.y, 400, 50},
                         "Slot Status : OPEN");
            } else {
                GuiDrawRectangle((Rectangle) {0, screenHeight / 2 - 145 + scroll.y, screenWidth - 12, 60}, 1, BLACK,
                                 RED);

                GuiLabel((Rectangle) {screenWidth / 2 + 50 + scroll.x, screenHeight / 2 - 140 + scroll.y, 400, 50},
                         "Slot Status : CLOSED");
            }
            if (current_slot == 1) {
                GuiLabel((Rectangle) {screenWidth / 4 + 50 + scroll.x, screenHeight / 2 - 140 + scroll.y, 400, 50},
                         "You are in Slot 1");
            } else if (current_slot == 2) {
                GuiLabel((Rectangle) {screenWidth / 4 + 50 + scroll.x, screenHeight / 2 - 140 + scroll.y, 400, 50},
                         "You are in Slot 2");
            } else if (current_slot == 3) {
                GuiLabel((Rectangle) {screenWidth / 4 + 50 + scroll.x, screenHeight / 2 - 140 + scroll.y, 400, 50},
                         "You are in Slot 3");
            } else if (current_slot == 4) {
                GuiLabel((Rectangle) {screenWidth / 4 + 50 + scroll.x, screenHeight / 2 - 140 + scroll.y, 400, 50},
                         "You are in Slot 4");
            }


            GuiDrawRectangle((Rectangle) {0, screenHeight / 2 - 90 + scroll.y, screenWidth - 12, 180}, 1, BLACK,
                             (Color) {202, 87, 255, 225});
            GuiLabel((Rectangle) {(screenWidth / 80) + 50 + scroll.x, screenHeight / 2 - 70 + scroll.y, 100, 50},
                     "Name: ");
            GuiLabel(
                    (Rectangle) {(screenWidth / 80) + 50 + 300 + scroll.x, screenHeight / 2 - 70 + scroll.y, 300, 50},
                    current_student.name);
            GuiLabel((Rectangle) {(screenWidth / 80) + 50 + scroll.x, screenHeight / 2 + scroll.y, 200, 50},
                     "Student ID: ");
            GuiLabel((Rectangle) {(screenWidth / 80) + 50 + 300 + scroll.x, screenHeight / 2 + scroll.y, 150, 50},
                     current_student_id);
            GuiLabel((Rectangle) {(screenWidth / 80) + 1180 + scroll.x, screenHeight / 2 - 70 + scroll.y, 250, 50},
                     "Department: ");
            GuiLabel((Rectangle) {(screenWidth / 80) + 1500 + scroll.x, screenHeight / 2 - 70 + scroll.y, 150, 50},
                     current_student.Department);
            GuiLabel((Rectangle) {(screenWidth / 80) + 1180 + scroll.x, screenHeight / 2 + scroll.y, 250, 50},
                     "Semester: ");
            GuiLabel((Rectangle) {(screenWidth / 80) + 1500 + scroll.x, screenHeight / 2 + scroll.y, 150, 50},
                     current_semester);


            DrawRectangle(0, 0 + scroll.y, screenWidth, 290, MY_BLUE);
            GuiSetStyle(DEFAULT, TEXT_SIZE, 80);
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(WHITE));
            GuiLabel((Rectangle) {screenWidth / 20 + 300, screenHeight / 8 - 20 + scroll.y, 2000, 100},
                     "REGISTRATION SUMMARY");
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
            GuiSetStyle(DEFAULT, TEXT_SIZE, 40);

            view_exit_butt = GuiButton(
                    (Rectangle) {screenWidth / 2 + 680, screenHeight / 8 + 175 + scroll.y, 225, 50},
                    "<< Back");
            if (!if_got_regis_course) {
                course_view_records = retrieve_courses(atoi(user_id), regis_courses);

                if_got_regis_course = true;
            }
            if (course_view_records > 0) {

                Labels_for_reg_courses_view(reg_courses, &reg_courses_reterive, regis_courses, course_view_records,
                                            50 + scroll.x,
                                            screenHeight / 2 + 200 + scroll.y, view_fac_commands,
                                            atoi(user_id));

            }
            else {
                GuiSetStyle(DEFAULT, TEXT_SIZE, 52);
                GuiLabel((Rectangle) {screenWidth / 2 - 350, screenHeight / 2 + 300 + scroll.y, 700, 60},
                         "No Registered Courses Available");
                GuiSetStyle(DEFAULT, TEXT_SIZE, 40);

            }
            if (!if_got_waitlist_course) {
                waitlist_view_records = retrieve_waitlist_sections(atoi(user_id), waitlist_courses);
                if_got_waitlist_course = true;
            }
            if (waitlist_view_records > 0) {
                GuiSetStyle(DEFAULT, TEXT_SIZE, 60);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(MY_BLUE));
                GuiLabel((Rectangle) {screenWidth / 2 - 400 + scroll.x, screenHeight / 2 + 600 + scroll.y, 1000, 60},
                         "WAITLIST  SUMMARY");
                GuiSetStyle(DEFAULT, TEXT_SIZE, 40);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));

                Labels_for_waitlist_sections_view(&waitlist_view_read, waitlist_courses, waitlist_view_records,
                                                  150 + scroll.x,
                                                  screenHeight / 2 + 800 + scroll.y, atoi(user_id));
            }

            for (int i = 0; i < course_view_records; i++) {
                if (view_fac_commands[i] == true) {
                    show_fac_box = true;
                    fac_index = i;
                }
            }
            if (show_fac_box) {
                Section current_section = reg_sec_from_course_code(atoi(user_id), regis_courses[fac_index]);
                current_faculty = get_fac_detials(current_section.Faculty_code);
                strcat(fac_box_content, "Name:  ");
                strcat(fac_box_content, current_faculty.faculty_name);
                strcat(fac_box_content, "     \n\nDesignation:  ");
                strcat(fac_box_content, current_faculty.designation);
                strcat(fac_box_content, "    \n\nMail_id:  ");
                strcat(fac_box_content, current_faculty.email_id);

                GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
                int result = GuiMessageBox(
                        (Rectangle) {screenWidth / 2 - 400, screenHeight / 2 + 150 + scroll.y, 750, 400},
                        "Faculty Details",
                        fac_box_content, (const char[]) {"OK"});
                if (result >= 0) show_fac_box = false;
                strcpy(fac_box_content, "");
            }


            if (view_exit_butt) {
                MainPage = true;
                ViewPage = false;
                show_fac_box = false;
                reg_courses_reterive = false;
                if_got_regis_course = false;
                if_got_waitlist_course = false;
                waitlist_view_read = false;
                slot_founded = false;
                checkd_slot_status = false;
                scroll.y = 0;

            }
            EndDrawing();
        }
        else if (AdminLoginPage) {
            BeginDrawing();

            // Update active states


            if (admin_user_id_active && IsKeyPressed(KEY_ENTER)) {
                admin_user_id_active = false;
                admin_password_active = true;
            } else if (admin_password_active && IsKeyPressed(KEY_ENTER)) {
                admin_password_active = false;
            }


            DrawRectangle(0, 0, screenWidth, 290, MY_BLUE);
            Rectangle sourcelogoRect_1 = {0.0f, 0.0f, (float) logoTexture.width, (float) logoTexture.height};
            Rectangle destlogoRect_1 = {(float) x, (float) y, (float) newWidth, (float) newHeight};
            DrawTexturePro(logoTexture, sourcelogoRect_1, destlogoRect_1, position_logo, 0.0f, WHITE);

            GuiSetStyle(DEFAULT, TEXT_SIZE, 80);
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(WHITE));
            GuiLabel((Rectangle) {screenWidth / 20 + 190, screenHeight / 8 - 40, 2000, 100},
                     "SRS UNIVERSITY - ADMIN LOGIN");
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
            GuiSetStyle(DEFAULT, TEXT_SIZE, 40);




            admin_back_butt = GuiButton((Rectangle) {screenWidth / 2 + 680, screenHeight / 8 + 200, 225, 50},
                                        "<< Back");
            // User ID
            GuiLabel((Rectangle) {(screenWidth / 4), (screenHeight / 2) - 30, 380, 60}, "Enter your User ID:");

            if (GuiTextBox((Rectangle) {(screenWidth / 4) + 380, (screenHeight / 2) - 30, 300, 60}, admin_user_id,
                           64,
                           admin_user_id_active)) {
                admin_user_id_active = true;
                admin_password_active = false;
            }

            // Password
            GuiLabel((Rectangle) {(screenWidth / 4), (screenHeight / 2) + 50, 380, 60}, "Enter your Password:");

            if (GuiTextBox((Rectangle) {(screenWidth / 4) + 380, (screenHeight / 2) + 50, 300, 60}, admin_password,
                           64,
                           admin_password_active)) {
                admin_user_id_active = false;
                admin_password_active = true;
            }

            // Login Button
            admin_login_butt = GuiButton((Rectangle) {(screenWidth / 4) + 190, (screenHeight / 2) + 150, 300, 60},
                                         "Login");


            if (admin_login_butt) {
                if (check_admin_credentials(atoi(admin_user_id), admin_password)) {
                    AdminPage = true;
                    AdminLoginPage = false;
                } else {
                    show_adminlogin_failed = true;
                }
            }
            if (show_adminlogin_failed) {
                GuiEnable();
                GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(RED));

                int result = GuiMessageBox((Rectangle) {screenWidth / 2 - 200, screenHeight / 2 - 100, 400, 200},
                                           "Login Failed",
                                           "Please check your credentials", (const char[]) {"OK"});

                GuiSetStyle(DEFAULT, TEXT_SIZE, 40);
                GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
                strcpy(admin_user_id, "");
                strcpy(admin_password, "");
                GuiDisable();
                if (result >= 0) {
                    show_adminlogin_failed = false;
                    GuiEnable();
                }
            }
            if (admin_back_butt) {
                Login_page = true;
                AdminLoginPage = false;
                show_adminlogin_failed = false;
                strcpy(admin_user_id, "");
                strcpy(admin_password, "");
            }

            EndDrawing();


        }
        else if (AdminPage) {

            BeginDrawing();
            reg_dept_got = false;
            reg_sem_got = false;
            dept_got = false;
            sem_got = false;


            DrawRectangle(0, 0, screenWidth, 290, MY_BLUE);
            Rectangle sourcelogoRect_1 = {0.0f, 0.0f, (float) logoTexture.width, (float) logoTexture.height};
            Rectangle destlogoRect_1 = {(float) x, (float) y, (float) newWidth, (float) newHeight};
            DrawTexturePro(logoTexture, sourcelogoRect_1, destlogoRect_1, position_logo, 0.0f, WHITE);
            //DrawTextEx(times_new_bold,"SRS-University - Course Registration System", (Vector2){(screenWidth / 20) + 85, screenHeight / 8}, 90,1.0,BLUE);

            GuiSetStyle(DEFAULT, TEXT_SIZE, 80);
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(WHITE));
            GuiLabel((Rectangle) {screenWidth / 20 + 190, screenHeight / 8 - 40, 2000, 100},
                     "SRS UNIVERSITY - ADMIN CONTROL");
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
            GuiSetStyle(DEFAULT, TEXT_SIZE, 40);


            slot_control_butt = GuiButton((Rectangle) {screenWidth / 2 - 200, screenHeight / 2 - 100, 450, 50},
                                          "SLOT CONTROL");
            reg_stats_butt = GuiButton((Rectangle) {screenWidth / 2 - 200, screenHeight / 2, 450, 50},
                                       "REGISTRATION STATS");
            admin_logout_butt = GuiButton((Rectangle) {screenWidth / 2 - 200, screenHeight / 2 + 100, 450, 50},
                                          "LOGOUT");
            admin_exit_butt = GuiButton((Rectangle) {screenWidth / 2 - 200, screenHeight / 2 + 200, 450, 50}, "EXIT");
            if (admin_exit_butt) {
                break;
            }
            if (admin_logout_butt) {
                AdminLoginPage = true;
                strcpy(admin_user_id, "");
                strcpy(admin_password, "");
                AdminPage = false;
            }

            if (slot_control_butt) {
                SlotPage = true;
                AdminPage = false;
            }
            if (reg_stats_butt) {
                RegStatsPage = true;
                AdminPage = false;
            }
            EndDrawing();
        }
        else if (SlotPage) {
            BeginDrawing();

            GuiScrollPanel(bounds, "", content, &scroll, &view);

            DrawRectangle(0, 0 + scroll.y, screenWidth, 290, MY_BLUE);


            GuiSetStyle(DEFAULT, TEXT_SIZE, 95);
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(WHITE));
            GuiLabel((Rectangle) {screenWidth / 20 + 190, screenHeight / 8 - 40 + scroll.y, 2000, 100},
                     "SLOT CONTROL SYSTEM");
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
            GuiSetStyle(DEFAULT, TEXT_SIZE, 40);


            slot_exit_butt = GuiButton(
                    (Rectangle) {screenWidth / 2 + 680, screenHeight / 8 + 200 + scroll.y, 225, 50},
                    "<< Back");
            if (slot_exit_butt) {
                SlotPage = false;
                AdminPage = true;
            }
            GuiDrawRectangle((Rectangle) {screenWidth / 4 - 20, screenHeight / 4 + 200 + scroll.y, 250, 60}, 1, BLACK,
                             SKYBLUE);
            GuiLabel((Rectangle) {screenWidth / 4, screenHeight / 4 + scroll.y + 200, 250, 60}, "SLOTS");

            GuiDrawRectangle((Rectangle) {screenWidth / 4 + 250 - 20, screenHeight / 4 + scroll.y + 200, 600, 60}, 1,
                             BLACK, SKYBLUE);
            GuiLabel((Rectangle) {screenWidth / 4 + 250, screenHeight / 4 + scroll.y + 200, 600, 60},
                     "                    STATUS");


            GuiDrawRectangle((Rectangle) {screenWidth / 4 - 20, screenHeight / 4 + scroll.y + 60 + 200, 250, 60}, 1,
                             BLACK, WHITE);
            GuiLabel((Rectangle) {screenWidth / 4, screenHeight / 4 + scroll.y + 60 + 200, 250, 60}, "SLOT 1");

            GuiDrawRectangle((Rectangle) {screenWidth / 4 - 20, screenHeight / 4 + scroll.y + 120 + 200, 250, 60}, 1,
                             BLACK, WHITE);
            GuiLabel((Rectangle) {screenWidth / 4, screenHeight / 4 + scroll.y + 120 + 200, 250, 60}, "SLOT 2");

            GuiDrawRectangle((Rectangle) {screenWidth / 4 - 20, screenHeight / 4 + scroll.y + 180 + 200, 250, 60}, 1,
                             BLACK, WHITE);
            GuiLabel((Rectangle) {screenWidth / 4, screenHeight / 4 + scroll.y + 180 + 200, 250, 60}, "SLOT 3");

            GuiDrawRectangle((Rectangle) {screenWidth / 4 - 20, screenHeight / 4 + scroll.y + 240 + 200, 250, 60}, 1,
                             BLACK, WHITE);
            GuiLabel((Rectangle) {screenWidth / 4, screenHeight / 4 + scroll.y + 240 + 200, 250, 60}, "SLOT 4");
            int pos = 0;
            check_if_allowed(allowed_slots);

            for (int i = 0; i < 4; i++) {
                GuiDrawRectangle(
                        (Rectangle) {screenWidth / 4 + 250 - 20, screenHeight / 4 + scroll.y + 60 + pos + 200,
                                     600 / 2, 60}, 1, BLACK, WHITE);

                GuiDrawRectangle(
                        (Rectangle) {screenWidth / 4 + 250 - 20 + 300, screenHeight / 4 + scroll.y + 60 + pos + 200,
                                     600 / 2, 60}, 1, BLACK, WHITE);
                if (allowed_slots[i] == 0) {
                    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(GREEN));
                    Allow_butt_commands[i] = GuiButton((Rectangle) {screenWidth / 4 + 250 - 20 + 3,
                                                                    screenHeight / 4 + scroll.y + 60 + pos + 3 + 200,
                                                                    600 / 2 - 6, 60 - 6}, "ALLOW ");


                    GuiLabel((Rectangle) {screenWidth / 4 + 250 - 20 + 300 + 3,
                                          screenHeight / 4 + scroll.y + 60 + pos + 3 + 200, 600 / 2 - 6, 60 - 6},
                             "Blocked");
                    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(LIGHTGRAY));

                } else if (allowed_slots[i] == 1) {
                    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(RED));
                    Block_butt_commands[i] = GuiButton((Rectangle) {screenWidth / 4 + 250 - 20 + 300 + 3,
                                                                    screenHeight / 4 + scroll.y + 60 + pos + 3 + 200,
                                                                    600 / 2 - 6, 60 - 6}, "BLOCK");
                    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(LIGHTGRAY));
                    GuiLabel((Rectangle) {screenWidth / 4 + 250 - 20 + 3,
                                          screenHeight / 4 + scroll.y + 60 + pos + 3 + 200, 600 / 2 - 6, 60 - 6},
                             "Allowed");
                    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(LIGHTGRAY));

                }
                pos += 60;
            }

            for (int i = 0; i < 4; i++) {
                if (Allow_butt_commands[i] == true) {
                    if (i == 0) {
                        allow_slot("slot1");
                    } else if (i == 1) {
                        allow_slot("slot2");
                    } else if (i == 2) {
                        allow_slot("slot3");
                    } else if (i == 3) {
                        allow_slot("slot4");
                    }

                    break;


                }


            }

            for (int i = 0; i < 4; i++) {
                if (Block_butt_commands[i] == true) {
                    if (i == 0) {
                        block_slot("slot1");
                    } else if (i == 1) {
                        block_slot("slot2");
                    } else if (i == 2) {
                        block_slot("slot3");
                    } else if (i == 3) {
                        block_slot("slot4");
                    }

                    break;

                }

            }

            for (int j = 0; j < 4; j++) {
                Allow_butt_commands[j] = false;
                Block_butt_commands[j] = false;
            }


            if (!inputEndTime) {
                // Draw
                ClearBackground(RAYWHITE);
                GuiLabel((Rectangle) {screenWidth / 4 + 20, 3 * screenHeight / 4 + 20 + scroll.y, 1200, 50},
                         "Enter end time (YYYY-MM-DD HH:MM:SS)");
                GuiTextBox((Rectangle) {screenWidth / 2 - 350, 3 * screenHeight / 4 + 20 + 80 + scroll.y, 500, 50},
                           endTimeInput, 64, true);

                if (GuiButton(
                        (Rectangle) {screenWidth / 2 - 250, 3 * screenHeight / 4 + 20 + 150 + scroll.y, 300, 50},
                        "Submit")) {
                    endTime = ParseDateTime(endTimeInput);
                    if (endTime != (time_t) -1) {
                        inputEndTime = true;
                        SaveEndTimeToFile(endTime);
                    } else {
                        show_invalid_end_time = true;
                    }
                }
                if (show_invalid_end_time) {
                    GuiEnable();
                    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
                    GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(RED));
                    int result = GuiMessageBox(
                            (Rectangle) {screenWidth / 2 - 200, screenHeight / 2 - 100 + scroll.y, 400, 200},
                            "Input Error",
                            "Invalid Date and Time Format", (const char[]) {"OK"});

                    GuiSetStyle(DEFAULT, TEXT_SIZE, 40);
                    GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
                    GuiDisable();
                    if (result >= 0) {
                        show_invalid_end_time = false;
                        GuiEnable();
                    }

                }

            } else {
                time_t currentTime = time(NULL);
                if (difftime(endTime, currentTime) <= 0) {
                    processEnded = true;
                }

                TimeDifference diff = GetTimeDifference(endTime);

                // Draw

                if (processEnded) {
                    GuiLabel((Rectangle) {screenWidth / 4, 3 * screenHeight / 4 + 20 + scroll.y, 500, 50},
                             "Time's up!");


                } else {
                    char timeLeft[128];
                    snprintf(timeLeft, sizeof(timeLeft), "Time left: %d days %d hours %d minutes %d seconds",
                             diff.days, diff.hours, diff.minutes, diff.seconds);
                    //DrawText(timeLeft, 50, 50, 20, DARKGRAY);
                    GuiLabel((Rectangle) {screenWidth / 4, 3 * screenHeight / 4 + 20 + scroll.y, 1200, 50}, timeLeft);

                }
                if (GuiButton((Rectangle) {screenWidth / 4, 3 * screenHeight / 4 + 80 + scroll.y, 300, 50},
                              "Reset")) {
                    inputEndTime = false;
                    ResetEndTimeInFile();
                    endTime = (time_t) -1;
                    processEnded = false;
                    blocked_by_time = false;
                }


            }


            EndDrawing();


        }
        else if (RegStatsPage) {
            BeginDrawing();
            GuiScrollPanel(bounds, "", content, &scroll, &view);


            DrawRectangle(0, 0 + scroll.y, screenWidth, 290, MY_BLUE);


            GuiSetStyle(DEFAULT, TEXT_SIZE, 95);
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(WHITE));
            GuiLabel((Rectangle) {screenWidth / 20 + 190, screenHeight / 8 - 40 + scroll.y, 2000, 100},
                     "REGISTRATION STATISTICS");
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
            GuiSetStyle(DEFAULT, TEXT_SIZE, 40);


            reg_exit_butt = GuiButton((Rectangle) {screenWidth / 2 + 680, screenHeight / 8 + 200 + scroll.y, 225, 50},
                                      "<< Back");
            if (GuiDropdownBox((Rectangle) {screenWidth / 4 - 50, screenHeight / 2 + 50 + scroll.y, 450, 50},
                               stats_check_box1, &stats1_dropdownActive, stats1_dropdown_editmode))
                stats1_dropdown_editmode = !stats1_dropdown_editmode;
            if (GuiDropdownBox((Rectangle) {screenWidth / 2, screenHeight / 2 + 50 + scroll.y, 450, 50},
                               stats_check_box2, &stats2_dropdownActive, stats2_dropdown_editmode))
                stats2_dropdown_editmode = !stats2_dropdown_editmode;
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
            GuiLabel((Rectangle) {screenWidth / 4 + 250, screenHeight / 2 - 50 + scroll.y, 500, 50},
                     "Select the type of statistics");
            GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));

            GuiLabel((Rectangle) {screenWidth / 2 - 65, screenHeight / 2 + 50 + scroll.y, 50, 50}, "VS");

            if (stats1_dropdownActive != 0 && stats2_dropdownActive != 0) {
                if (strcmp(TextSplit(stats_check_box1, ';', &stats1_count)[stats1_dropdownActive], "Department wise") ==
                    0 && strcmp(TextSplit(stats_check_box2, ';', &stats2_count)[stats2_dropdownActive],
                                "Registered students") == 0) {
                    reg_student_dept_wise_bar(&reg_dept_got, 400, 600,
                                              (Vector2) {screenWidth / 4, screenHeight / 2 + 330 + scroll.y});

                }
                if (strcmp(TextSplit(stats_check_box1, ';', &stats1_count)[stats1_dropdownActive], "Department wise") ==
                    0 &&
                    strcmp(TextSplit(stats_check_box2, ';', &stats2_count)[stats2_dropdownActive], "Total students") ==
                    0) {
                    dept_wise_bar(&dept_got, 400, 600,
                                  (Vector2) {screenWidth / 4, screenHeight / 2 + 330 + 50 + scroll.y});

                }
                if (strcmp(TextSplit(stats_check_box1, ';', &stats1_count)[stats1_dropdownActive], "Semester wise") ==
                    0 && strcmp(TextSplit(stats_check_box2, ';', &stats2_count)[stats2_dropdownActive],
                                "Registered students") == 0) {
                    reg_student_sem_wise_bar(&reg_sem_got, 400, 600,
                                             (Vector2) {screenWidth / 4, screenHeight / 2 + 330 + scroll.y});
                    // GuiLabel((Rectangle){screenWidth/4,screenHeight/2+150+scroll.y,200,50},"SEMESTER");
                }
                if (strcmp(TextSplit(stats_check_box1, ';', &stats1_count)[stats1_dropdownActive], "Semester wise") ==
                    0 &&
                    strcmp(TextSplit(stats_check_box2, ';', &stats2_count)[stats2_dropdownActive], "Total students") ==
                    0) {
                    sem_wise_bar(&sem_got, 400, 600,
                                 (Vector2) {screenWidth / 4, screenHeight / 2 + 50 + 330 + scroll.y});
                    //GuiLabel((Rectangle){screenWidth/4,screenHeight/2+50+150+scroll.y,200,50},"SEMESTER");
                }

            }


            if (reg_exit_butt) {
                RegStatsPage = false;
                AdminPage = true;
                reg_dept_got = false;
                reg_sem_got = false;
                dept_got = false;
                sem_got = false;
            }
            EndDrawing();
        }

    }


    CloseWindow();

    UnloadFont(times_new_bold);
    UnloadTexture(logoTexture); // Unload texture from GPU memory

    if (reg_failed) {
        decrement_new_id();

    }
    return 0;
}


void ShowSplashScreen() {
    // Initialization of the splash screen window
    const int splashScreenWidth = 450;
    const int splashScreenHeight = 350;

    SetConfigFlags(FLAG_WINDOW_UNDECORATED);

    InitWindow(splashScreenWidth, splashScreenHeight, "Splash Screen");


    Image logo = LoadImage("databases\\LOGO.png");
    Texture2D logoTexture = LoadTextureFromImage(logo);
    UnloadImage(logo);

    float splashTime = 0.0f;


    int newWidth = 450;
    int newHeight = 350;
    Vector2 position_logo = (Vector2) {0.0f, 0.0f};
    int x = 0;
    int y = 0;

    // Splash screen loop
    while (splashTime < SPLASH_TIME && !WindowShouldClose()) {
        // Update
        splashTime += GetFrameTime();

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);


        Rectangle sourcelogoRect_1 = {0.0f, 0.0f, (float) logoTexture.width, (float) logoTexture.height};
        Rectangle destlogoRect_1 = {(float) x, (float) y, (float) newWidth, (float) newHeight};
        DrawTexturePro(logoTexture, sourcelogoRect_1, destlogoRect_1, position_logo, 0.0f, WHITE);
        //
        // Draw splash screen (centered logo)

        EndDrawing();
    }

    // De-Initialization
    UnloadTexture(logoTexture); // Unload texture from GPU memory
// Unload the logo texture
    CloseWindow();
    ClearWindowState(FLAG_WINDOW_UNDECORATED);

}



void DrawMultiLineTextWrapped(const char *text, Rectangle rec, int lineSpacing, Color color, Font font,int scrollOffsetY)
{
    int lineHeight = font.baseSize + lineSpacing;
    Vector2 position = { rec.x, rec.y + scrollOffsetY  };

    const char *lineStart = text;
    const char *lineEnd = NULL;

    while (*lineStart)
    {
        lineEnd = lineStart;

        // Measure text and find line end within the rectangle width
        while (*lineEnd && *lineEnd != '\n' &&
               (MeasureTextEx(font, TextSubtext(lineStart, 0, lineEnd - lineStart + 1), font.baseSize, 1).x <= rec.width))
        {
            lineEnd++;
        }

        // Handle the case where a word is too long to fit within the rectangle width
        if (*lineEnd != '\n' && lineEnd != lineStart && *lineEnd != '\0')
        {
            // Move back to the previous word
            while (lineEnd > lineStart && *lineEnd != ' ') lineEnd--;
            // If no space is found, force break the word
            if (lineEnd == lineStart)
            {
                int charsThatFit = 0;
                for (int i = 0; lineStart[i] != '\0'; i++)
                {
                    if (MeasureTextEx(font, TextSubtext(lineStart, 0, i + 1), font.baseSize, 1).x > rec.width)
                        break;
                    charsThatFit = i + 1;
                }
                lineEnd = lineStart + charsThatFit;
            }
        }

        DrawTextEx(font, TextSubtext(lineStart, 0, lineEnd - lineStart), position, font.baseSize, 1, color);
        position.y += lineHeight;

        lineStart = (*lineEnd == '\n') ? lineEnd + 1 : lineEnd;
    }
}






















