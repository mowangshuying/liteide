cmake_minimum_required(VERSION 3.16)
project(auto VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set up AUTOMOC and some sensible defaults for runtime execution
# When using Qt 6.3, you can replace the code block below with
# qt_standard_project_setup()
set(CMAKE_AUTOMOC ON)
include(GNUInstallDirs)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)


add_subdirectory(qjsonrpcmessage)
add_subdirectory(qjsonrpcsocket)
add_subdirectory(qjsonrpcserver)
add_subdirectory(qjsonrpcservice)
add_subdirectory(qjsonrpchttpclient)
add_subdirectory(qjsonrpchttpserver)
add_subdirectory(issue22)
if(((((QT_VERSION_MAJOR LESS 5)))))
    add_subdirectory(json)
endif()
if(((((QT_VERSION_MINOR GREATER 1)) AND ((QT_VERSION_MAJOR GREATER 4)))))
    add_subdirectory(qjsonrpcmetatype)
endif()
