cmake_minimum_required(VERSION 3.16)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
set(ProjectId ${ParentProject}_${ProjectId})

project(${ProjectId})

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCE_FILES "*.h" "*.cpp")

add_executable(${ProjectId} ${SOURCE_FILES})