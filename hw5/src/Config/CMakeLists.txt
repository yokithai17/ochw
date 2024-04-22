cmake_minimum_required(VERSION 3.10)
project(config)


set(SOURCE_LIB "${PROJECT_SOURCE_DIR}/config.cpp")

add_library(config SHARED ${SOURCE_LIB} ${coolApp_SOURCE_DIR}/include/config.h)