cmake_minimum_required(VERSION 3.10)
project(loader)


set(SOURCE_LIB "${PROJECT_SOURCE_DIR}/loader.cpp")

add_library(loader SHARED ${SOURCE_LIB} ${coolApp_SOURCE_DIR}/include/loader.h)