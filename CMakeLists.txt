cmake_minimum_required(VERSION 3.21)

project(qmottiapp LANGUAGES CXX)

include(FetchContent)

find_package(Qt6 CONFIG COMPONENTS Core Quick Network REQUIRED)

FetchContent_Declare(
    qmqtt
    GIT_REPOSITORY https://github.com/qt/qtmqtt.git
    GIT_TAG ${Qt6_VERSION}
)

FetchContent_MakeAvailable(qmqtt)
set(MQTT_INCLUDE
    "${CMAKE_BINARY_DIR}/include"
    "${CMAKE_BINARY_DIR}/include/QtMqtt")


set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 CONFIG COMPONENTS Core Quick Network REQUIRED)

# for FigmaQml
add_subdirectory(${CMAKE_SOURCE_DIR}/QMQTTI/Page_1/FigmaQmlInterface)

set(SOURCES
    qml/main.qml
    qml/Subscriptions.qml
    qml/Messages.qml
    src/main.cpp
    mqtti.cpp
    mqtti.h
    README.md
)

qt_add_executable(${PROJECT_NAME} ${SOURCES}
    qml.qrc)


    
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)

if (APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE ON)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    "QMQTTI/Page_1/FigmaQmlInterface" # for FigmaQML
    ${MQTT_INCLUDE}
)


target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Quick Qt6::Network
    # for FigmaQML
    FigmaQmlInterface
    Mqtt
)

add_subdirectory(test)


