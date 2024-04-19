cmake_minimum_required(VERSION 3.10)
project(saver)


set(SOURCE_LIB "${PROJECT_SOURCE_DIR}/saver.cpp")

add_library(saver SHARED ${SOURCE_LIB} ${coolApp_SOURCE_DIR}/include/saver.h)