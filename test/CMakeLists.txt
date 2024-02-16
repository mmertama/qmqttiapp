cmake_minimum_required(VERSION 3.21)
project(qmottitest LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Test Core Quick Network)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

qt_standard_project_setup()

enable_testing(true)

qt_add_executable(${PROJECT_NAME}
    qmottitest.hpp
    qmottitest.cpp
    )

target_include_directories(${PROJECT_NAME} PRIVATE .. .)
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Test
    $<FILTER: $<TARGET_OBJECTS:qmottiapp>,EXCLUDE,main\.cpp\.o>
    $<TARGET_PROPERTY:qmottiapp,LINK_LIBRARIES>
    )
