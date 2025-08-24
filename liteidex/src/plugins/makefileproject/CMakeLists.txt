cmake_minimum_required(VERSION 3.16)
project(makefileproject VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set up AUTOMOC and some sensible defaults for runtime execution
# When using Qt 6.3, you can replace the code block below with
# qt_standard_project_setup()
set(CMAKE_AUTOMOC ON)
include(GNUInstallDirs)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui)
find_package(Qt${QT_VERSION_MAJOR} OPTIONAL_COMPONENTS PrintSupport Widgets)

qt_add_plugin(makefileproject)
target_sources(makefileproject PRIVATE
    makefilefile.cpp makefilefile.h
    makefilefilefactory.cpp makefilefilefactory.h
    makefileproject.cpp makefileproject.h
    makefileproject_global.h
    makefileprojectplugin.cpp makefileprojectplugin.h
)
target_include_directories(makefileproject PRIVATE
    ../../src/3rdparty
    ../../src/api
    ../../src/utils
)

target_compile_definitions(makefileproject PRIVATE
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    MAKEFILEPROJECT_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(makefileproject PRIVATE
    # Remove: L
    Qt::Core
    Qt::Gui
)

if(NOT MACOS)
    target_compile_definitions(makefileproject PRIVATE
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(makefileproject PRIVATE
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(WIN32)
    target_link_libraries(makefileproject PRIVATE
        ole32
        shell32
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(makefileproject PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(makefileproject PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(makefileproject PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS makefileproject
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
