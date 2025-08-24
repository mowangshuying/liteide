cmake_minimum_required(VERSION 3.16)
project(api VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set up AUTOMOC and some sensible defaults for runtime execution
# When using Qt 6.3, you can replace the code block below with
# qt_standard_project_setup()
set(CMAKE_AUTOMOC ON)
include(GNUInstallDirs)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)


add_subdirectory(liteapi)
add_subdirectory(liteenvapi)
add_subdirectory(litefindapi)
add_subdirectory(litebuildapi)
add_subdirectory(liteeditorapi)
add_subdirectory(litedebugapi)
add_subdirectory(litettyapi)
add_subdirectory(docbrowserapi)
add_subdirectory(golangdocapi)
add_subdirectory(golangastapi)
add_subdirectory(quickopenapi)
add_subdirectory(terminalapi)
