cmake_minimum_required(VERSION 3.16)
project(tst_qjsonrpchttpserver VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set up AUTOMOC and some sensible defaults for runtime execution
# When using Qt 6.3, you can replace the code block below with
# qt_standard_project_setup()
set(CMAKE_AUTOMOC ON)
include(GNUInstallDirs)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network Test)
find_package(Qt${QT_VERSION_MAJOR})

qt_add_executable(tst_qjsonrpchttpserver WIN32
    ../../../tests/common/signalspy.h
    tst_qjsonrpchttpserver.cpp
)
target_include_directories(tst_qjsonrpchttpserver PRIVATE
    ../../../tests/common
    /json
)

target_link_libraries(tst_qjsonrpchttpserver PRIVATE
    # Remove: L../../../src
    # Remove: gui
    Qt::Core
    Qt::Network
    Qt::Test
)


# Resources:
set(certificates_resource_files
    "certs/aspiriniks.ca.crt"
    "certs/fake-login.live.com.key"
    "certs/fake-login.live.com.pem"
    "certs/fluke.cert"
    "certs/fluke.key"
    "certs/qt-test-server-cacert.pem"
)

qt_add_resources(tst_qjsonrpchttpserver "certificates"
    PREFIX
        "/"
    FILES
        ${certificates_resource_files}
)

if(private-headers)
    target_compile_definitions(tst_qjsonrpchttpserver PRIVATE
        USE_QT_PRIVATE_HEADERS
    )

    target_link_libraries(tst_qjsonrpchttpserver PRIVATE
        Qt::CorePrivate
    )
endif()

if(QJSONRPC_LIBRARY_TYPE___contains___staticlib)
    target_compile_definitions(tst_qjsonrpchttpserver PRIVATE
        QJSONRPC_STATIC
    )
endif()

if(NOT QJSONRPC_LIBRARY_TYPE___contains___staticlib)
    target_compile_definitions(tst_qjsonrpchttpserver PRIVATE
        QJSONRPC_SHARED
    )
endif()

install(TARGETS tst_qjsonrpchttpserver
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Consider using qt_generate_deploy_app_script() for app deployment if
# the project can use Qt 6.3. In that case rerun qmake2cmake with
# --min-qt-version=6.3.
