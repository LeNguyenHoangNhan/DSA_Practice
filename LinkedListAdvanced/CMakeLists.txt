cmake_minimum_required(VERSION 3.15)

add_executable(LinkedListAdvanced_question1 question1.cpp)
target_link_libraries(
    LinkedListAdvanced_question1
    PRIVATE project_options
            project_warnings)

add_executable(LinkedListAdvanced_question2 question2.cpp)
target_link_libraries(
    LinkedListAdvanced_question2
    PRIVATE project_options
            project_warnings)

add_executable(LinkedListAdvanced_question3 question3.cpp)
target_link_libraries(
    LinkedListAdvanced_question3
    PRIVATE project_options
            project_warnings)

add_executable(LinkedListAdvanced_question4 question4.cpp)
target_link_libraries(
    LinkedListAdvanced_question4
    PRIVATE project_options
            project_warnings)

add_executable(LinkedListAdvanced_question5 question5.cpp)
target_link_libraries(
    LinkedListAdvanced_question5
    PRIVATE project_options
            project_warnings)
