cmake_minimum_required(VERSION 3.28)
project(Course_Registration_System C)

set(CMAKE_C_STANDARD 11)

# Add this line
find_package(CURL REQUIRED)

find_package(libcurl-simple-https CONFIG REQUIRED)
find_package(raylib CONFIG REQUIRED)
add_executable(Course_Registration_System
        all_includes_and_macros.h
        main.c
        trial.c
        file_functions.c
        file_functions.h
        "login signup.c"
        "login signup.h"
        modifying_functions.c
        modifying_functions.h
        Structure_definitions.c
        add_module.c
        add_module.h
        remove_module.c
        slot.c
        view_module.c
        view_module.h
        slot.h
        mail.c
        mail.h
)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,54777216")

target_link_libraries(Course_Registration_System PRIVATE libcurl-simple-https PRIVATE raylib)
