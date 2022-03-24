
project(priority_queue_test)
add_executable(${PROJECT_NAME} test.c

)
target_link_libraries(${PROJECT_NAME} priority_queue)

add_test(min_and_max ${PROJECT_NAME} min_and_max)