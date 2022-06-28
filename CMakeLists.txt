cmake_minimum_required(VERSION 3.15.1)

project (student_repository CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(enums INTERFACE)
target_include_directories(enums INTERFACE enums)

add_executable(student_repository
        src/main.cpp
        src/Student/Student.cpp
        src/Database/RAM_DB.cpp
        )

target_include_directories(student_repository PUBLIC src/Database src/Student)
#target_include_directories(student_repository src/Student)

target_link_libraries(student_repository enums)
