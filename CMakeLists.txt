cmake_minimum_required(VERSION 3.11)
        project(Homework)

        # Are we in the wrong directory?
        if (CMAKE_SOURCE_DIR MATCHES "[Hh][Ww]([0-9])$"
           AND NOT PROJECT_NAME MATCHES "${CMAKE_MATCH_1}$")
            message(FATAL_ERROR "Building ${PROJECT_NAME} in ${CMAKE_SOURCE_DIR}")
        endif()

        # Using -Wall is required:
        add_compile_options(-Wall)

        # These compile flags are highly recommended, but not required:
        add_compile_options(-Wextra -Wpedantic)

        # Optional super-strict mode:
        add_compile_options(-fmessage-length=80 -fno-diagnostics-show-option
            -fstack-protector-all -g -O3 -std=c++17 -Walloc-zero -Walloca
            -Wctor-dtor-privacy -Wduplicated-cond -Wduplicated-branches
            -Werror -Wextra-semi -Wfatal-errors -Winit-self -Wlogical-op
            -Wold-style-cast -Wshadow -Wunused-const-variable=1
            -Wzero-as-null-pointer-constant)

        # add_compile_options must be BEFORE add_executable.
        add_library(hw5 Event.cc Schedule.cc translate.cc)
        # Create the executable from the source file main.cc:
        add_executable(test test.cc)
        target_link_libraries(test hw5)

        # Create a tar file every time:
        add_custom_target(hw5.tar ALL COMMAND tar cf hw5.tar Event.cc Event.h Schedule.cc Schedule.h translate.cc test.cc CMakeLists.txt)
