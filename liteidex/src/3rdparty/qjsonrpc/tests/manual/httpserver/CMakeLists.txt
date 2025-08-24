cmake_minimum_required(VERSION 3.16)
project(httpserver VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set up AUTOMOC and some sensible defaults for runtime execution
# When using Qt 6.3, you can replace the code block below with
# qt_standard_project_setup()
set(CMAKE_AUTOMOC ON)
include(GNUInstallDirs)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network Test)
find_package(Qt${QT_VERSION_MAJOR})

qt_add_executable(httpserver WIN32
    httpserver.cpp
    testservice.cpp testservice.h
)
target_include_directories(httpserver PRIVATE
    ../../../tests/common
    /json
)

target_link_libraries(httpserver PRIVATE
    # Remove: L../../../src
    # Remove: gui
    Qt::Core
    Qt::Network
    Qt::Test
)

if(private-headers)
    target_compile_definitions(httpserver PRIVATE
        USE_QT_PRIVATE_HEADERS
    )

    target_link_libraries(httpserver PRIVATE
        Qt::CorePrivate
    )
endif()

if(QJSONRPC_LIBRARY_TYPE___contains___staticlib)
    target_compile_definitions(httpserver PRIVATE
        QJSONRPC_STATIC
    )
endif()

if(NOT QJSONRPC_LIBRARY_TYPE___contains___staticlib)
    target_compile_definitions(httpserver PRIVATE
        QJSONRPC_SHARED
    )
endif()

install(TARGETS httpserver
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Consider using qt_generate_deploy_app_script() for app deployment if
# the project can use Qt 6.3. In that case rerun qmake2cmake with
# --min-qt-version=6.3.
