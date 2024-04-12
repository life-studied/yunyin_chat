cmake_minimum_required(VERSION 3.5)

project(yunyin_chat
    VERSION 0.1
    DESCRIPTION "A chat application using Qt"
    HOMEPAGE_URL "https://github.com/life-studied/yunyin_chat"
    LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# default build type is Debug
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
if (CMAKE_BUILD_TYPE MATCHES "(Debug)|(Release)")
    message("Current build type: ${CMAKE_BUILD_TYPE}")
else()
    message("Set default buile type to Debug.")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# check complier
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    message("Current compile is GCC")
else()
    # message(FATAL_ERROR "Current compile is ${CMAKE_CXX_COMPILER_ID}, not support")
endif()

set(RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools Network)

set(RESOURCE_FILES ./res/res.qrc)

set(GLOBAL_FILES
        global.h
        global.cpp)

set(HELPER_FILES
        Singleton/Singleton.h)

set(NETWORK_FILES
        Network/HttpMgr.h
        Network/HttpMgr.cpp)

set(LOGIN_FILES
        Widgets/Login/logindialog.h
        Widgets/Login/logindialog.cpp
        Widgets/Login/logindialog.ui)

set(REGISTER_FILES
        Widgets/Register/registerdialog.h
        Widgets/Register/registerdialog.cpp
        Widgets/Register/registerdialog.ui)

set(STYLE_FILES
        Widgets/Style/style_helper.h)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ${GLOBAL_FILES}
        ${NETWORK_FILES}
        ${HELPER_FILES}
        ${LOGIN_FILES}
        ${REGISTER_FILES}
        ${STYLE_FILES}
        ${RESOURCE_FILES}             # resources
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(yunyin_chat
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(yunyin_chat PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)

set_target_properties(yunyin_chat PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(yunyin_chat)
endif()
