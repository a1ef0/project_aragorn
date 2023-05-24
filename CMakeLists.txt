cmake_minimum_required(VERSION 3.5)

project(project_aragorn LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(project_aragorn main.cpp
    EASY1/easy1.h
    EASY1/easy1.cpp
    MD5/md5.h
    MD5/md5.cpp)
target_include_directories(project_aragorn PUBLIC EASY1/ MD5/)

install(TARGETS project_aragorn
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
