cmake_minimum_required(VERSION 3.21)

project(FigmaQmlInterface VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt6 REQUIRED COMPONENTS Core Quick)
qt_standard_project_setup()
qt_add_library(${PROJECT_NAME} STATIC)

<<<<<<< Updated upstream
set(APP_QML_FILES "qml/Qml_server_address_onClick2_figma.qml"
   "qml/Button4_figma.qml"
   "qml/Subscribe1_figma.qml"
   "qml/Publish_figma.qml")
=======
set(APP_QML_FILES "qml/Publish4_figma.qml"
   "qml/Subscribe5_figma.qml"
   "qml/Qml_server_address_onClick10_figma.qml"
   "qml/Button12_figma.qml")
>>>>>>> Stashed changes
set(APP_IMAGE_FILES)

qt_add_qml_module(${PROJECT_NAME}
  URI ${PROJECT_NAME}
  VERSION 1.0
  SOURCES  FigmaQmlInterface.hpp
  QML_FILES FigmaQmlUi.qml ${APP_QML_FILES}
  RESOURCES ${APP_IMAGE_FILES}
  NO_PLUGIN
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Quick)

