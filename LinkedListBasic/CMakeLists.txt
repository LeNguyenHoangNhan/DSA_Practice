cmake_minimum_required(VERSION 3.15)

add_executable(LinkedListBasic_question1 question1.cpp)
target_link_libraries(
    LinkedListBasic_question1
    PRIVATE project_options
            project_warnings)

add_executable(LinkedListBasic_question2 question2.cpp)
target_link_libraries(
    LinkedListBasic_question2
    PRIVATE project_options
            project_warnings)

add_executable(LinkedListBasic_question3 question3.cpp)
target_link_libraries(
    LinkedListBasic_question3
    PRIVATE project_options
            project_warnings)

add_executable(LinkedListBasic_question4 question4.cpp)
target_link_libraries(
    LinkedListBasic_question4
    PRIVATE project_options
            project_warnings)

add_executable(LinkedListBasic_question5 question5.cpp)
target_link_libraries(
    LinkedListBasic_question5
    PRIVATE project_options
            project_warnings)
