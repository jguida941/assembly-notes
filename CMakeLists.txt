cmake_minimum_required(VERSION 3.30)
project(assembly_notes)

set(CMAKE_CXX_STANDARD 20)

add_executable(assembly_notes module-1/1-2-activity-cpp-to-assembly/src/assignment1_1.cpp)

add_executable(assignment2_1 module-2/2-1-activity-cpp-to-assembly-with-loops/src/assignment2_1.cpp)

# 2-2 Activity — one target per assembly block.
add_executable(assignment2_2_1 module-2/2-2-activity-assembly-to-cpp/src/assignment2_2_1.cpp)
add_executable(assignment2_2_2 module-2/2-2-activity-assembly-to-cpp/src/assignment2_2_2.cpp)
add_executable(assignment2_2_3 module-2/2-2-activity-assembly-to-cpp/src/assignment2_2_3.cpp)
