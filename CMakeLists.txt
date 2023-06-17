cmake_minimum_required(VERSION 3.5)

project(Thunder VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Xml Widgets OpenGL REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Xml Widgets OpenGL REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainWin.cpp
        mainWin.h
        modelManager.h
        modelManager.cpp
#        modelViewer.h
#        modelViewer.cpp
        interface.cpp
        interface.h
        logSys.h
        logSys.cpp
        treeWidgetManager.cpp
        treeWidgetManager.h
        mainwindow.ui
        icons.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Thunder
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Thunder APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Thunder SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Thunder
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Thunder PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Xml Qt${QT_VERSION_MAJOR}::OpenGL)

set_target_properties(Thunder PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Thunder)
endif()
