cmake_minimum_required(VERSION 3.10)
project(notepad)


set(SOURCE_LIB "${PROJECT_SOURCE_DIR}/notepad.cpp")

add_library(notepad STATIC ${SOURCE_LIB} ${coolApp_SOURCE_DIR}/include/notepad.h)