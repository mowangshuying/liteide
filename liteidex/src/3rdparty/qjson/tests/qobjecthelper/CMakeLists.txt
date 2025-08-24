cmake_minimum_required(VERSION 3.16)
project(qobjecthelper VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set up AUTOMOC and some sensible defaults for runtime execution
# When using Qt 6.3, you can replace the code block below with
# qt_standard_project_setup()
set(CMAKE_AUTOMOC ON)
include(GNUInstallDirs)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui)

qt_add_executable(qobjecthelper WIN32 MACOSX_BUNDLE
    person.cpp person.h
    testqobjecthelper.cpp
)
target_include_directories(qobjecthelper PRIVATE
    .
    ../../include
)

target_compile_definitions(qobjecthelper PRIVATE
    QMAKE_BUILD
)

target_link_libraries(qobjecthelper PRIVATE
    Qt::Core
    Qt::Gui
)

if(WIN32)
    target_link_libraries(qobjecthelper PRIVATE
        # Remove: L../../lib
        qjson0
    )
endif()

if(MACOS)
    target_link_libraries(qobjecthelper PRIVATE
        "-framework qjson"
    )
endif()

if(UNIX AND NOT MACOS)
    target_link_libraries(qobjecthelper PRIVATE
        # Remove: L../../lib
        qjson
    )
endif()

install(TARGETS qobjecthelper
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Consider using qt_generate_deploy_app_script() for app deployment if
# the project can use Qt 6.3. In that case rerun qmake2cmake with
# --min-qt-version=6.3.
