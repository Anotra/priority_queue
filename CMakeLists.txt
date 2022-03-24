cmake_minimum_required(VERSION 3.13)

project(priority_queue)
add_library(${PROJECT_NAME} STATIC)
target_sources(${PROJECT_NAME} PRIVATE priority_queue.c)
target_include_directories(${PROJECT_NAME} PUBLIC ./)

enable_testing()
add_subdirectory(test)