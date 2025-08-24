cmake_minimum_required(VERSION 3.16)
project(manual VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set up AUTOMOC and some sensible defaults for runtime execution
# When using Qt 6.3, you can replace the code block below with
# qt_standard_project_setup()
set(CMAKE_AUTOMOC ON)
include(GNUInstallDirs)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network Test)
find_package(Qt${QT_VERSION_MAJOR})


add_subdirectory(localserver)
add_subdirectory(localclient)
add_subdirectory(tcpserver)
add_subdirectory(tcpclient)
add_subdirectory(qjsonrpc)
add_subdirectory(httpclient)
add_subdirectory(httpserver)
add_subdirectory(benchmark)
if((((NOT ((QT_VERSION_MAJOR GREATER 4)))) OR ((TARGET Qt::Script) AND ((QT_VERSION_MAJOR GREATER 4)))))
    add_subdirectory(console)
endif()
