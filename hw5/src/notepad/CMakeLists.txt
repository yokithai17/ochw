cmake_minimum_required(VERSION 3.10)
project(notepad)


set(SOURCE_LIB "${PROJECT_SOURCE_DIR}/notepad.cpp")

add_library(notepad SHARED ${SOURCE_LIB} ${Win32SampleApp_SOURCE_DIR}/include/notepad.h)