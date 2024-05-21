cmake_minimum_required(VERSION 3.10)
project(coolApp CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/lib)

set(MAIN_SOURCE WIN32 main.cpp)

add_executable(${PROJECT_NAME} ${MAIN_SOURCE})
set(libs notepad saver loader config)


target_link_libraries(${PROJECT_NAME} ${libs})

target_include_directories(${PROJECT_NAME} PRIVATE include)

include_directories(include)

add_subdirectory(src/notepad)
add_subdirectory(src/saver)
add_subdirectory(src/config)
add_subdirectory(src/loader)