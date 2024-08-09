# UniversityCourseRegistration

This repository includes the source code, input data, and documentation created for an undergraduate course project. While it may have some rough edges, the project details are provided below:

- **Project Title:** Software System for University Course Registration

- **Team Name:** B2_3

- **Team Members:** Ramcharan S,Sakthivel T,Saravanan E

This project consists of a application built in C that is designed to manage the course registration process for students.It handles the allocation of courses based on student details, course details, and section availability.

# Features

- **Seamless Course Management:** Easily add or remove courses.
- **Email Notifications:** Get timely updates on registration status.
- **Automatic Waitlist Allotment:** Seats are auto-assigned from waitlists.
- **Seat Allocation for Unregistered Students:** Automatic seat assignment.
- **Slot Allocation System:** Conflict-free course scheduling.
- **Data Visualizations for Admin:** Insights and reports for administrators.
- **Streaming High Demand Courses:** Real-time course availability updates.


# Getting Started
## Installation

- **Step 1** - To install raylib.h,raygui.h and curl.h,go to https://vcpkg.io/
- **Step 2** - Click Get started and select the Installation method for your respective IDE.
- **Step 3** - With the help of the tutorial, install Raylib,Raygui and Curl.
- **Step 4** - Add the installed library path to the include linker paths of your IDE.

## Running the executable

To start with the course registration application,

**Step 1:** 

Download the ZIP file for the course registration Software from the given drive link : 
https://drive.google.com/file/d/1aGoIEQbZllDWrB9w_LziWkhsTex0tkXU/view?usp=sharing

**Step 2:**

Extract all the files from the downloaded ZIP file.

**Step 3:**


The following files should exist in the database folder which is inside the Course_Registration_System:

- Login_db.csv(user_id,password)
- Temporary_creds.csv(user_id,password)
- Admin_login.csv(user_id,password)
- Course_details.csv(department,semester,course_code,course_name, elective,section_1,section_2,section_3,credits,prerequisites,  mandatory)
- Student_db.csv(student_id,name,department,semester,   hsc_percent,completed_courses,registered_courses,        registered_sections,waitlist_sections,cgpa,email_id,       admin_status) 
- Section_details.csv(section_code,faculty_code,seat_available, registered_students,waitlist_availability,waitlist_students)
- staff.csv(faculty_code,faculty_name,gender,designation,email_id)
- last_gen_stu_id.txt
- terms_accepted.txt
- block_time.txt
- endtime.txt
- block_time.txt
- Times New Roman
- LOGO.png


**Step 5:**

In the Course_Registration_System folder,  Course_Registration_System.exe file will be available.   
Open the exe file.

## Compilation

The C Application is built with the help of certain external libraries. Before compiling, one must ensure all these build-dependencies are satisfied. These dependencies include:

- **Raylib** and **libcurl** should be installed into the `Course_Registration_System` folder in the source code.
- **Raygui** should be installed globally on the system and its path should be included in the linker's path of the compiler.
- One can then compile the provided source files into the executable file.


- The source codes are also available in the given drive link: https://drive.google.com/drive/folders/1uhhd_8B4VKcjs3k5tgIksiTBHdHCmsQ1?usp=sharing

- Alternatively if you are using cmake, then the link for cmakelists.txt is given: https://drive.google.com/file/d/1go5l7zVuND-H4So5rveOFzbll23CjWsn/view?usp=sharing


**Remember:**

 To sign up, the student should enter the temporary credentials, which is available in the database folder "Temporary_creds.csv".


# Constraints Implemented

## Hard Constraints

• A student should be able to register in a particular course only if he/she has already completed all prerequisites for that course. 

• Each course can be offered by multiple faculty members.

• Every section will have a fixed strength. If the section fills up, further registration should not be allowed.

• A wait list (10% of the class strength) will be maintained in case the allotment is not possible in the first round. 

• If a student wants to add or drop any course after initial registration, it should be allowed only within the first two weeks after the semester starts. 

• Students from the waitlist can be allotted their choice subsequent to the processing of drop requests.

## Soft Constraints

• Students can choose a course only after enrolling themselves in the mandatory courses.

• The students are allocated into four different slots based on their CGPA and HSC %. The student can do the registration only if the slot allocated to them is open.
