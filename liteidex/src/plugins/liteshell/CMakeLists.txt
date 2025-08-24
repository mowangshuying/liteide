cmake_minimum_required(VERSION 3.16)
project(liteshell VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set up AUTOMOC and some sensible defaults for runtime execution
# When using Qt 6.3, you can replace the code block below with
# qt_standard_project_setup()
set(CMAKE_AUTOMOC ON)
include(GNUInstallDirs)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui)
find_package(Qt${QT_VERSION_MAJOR} OPTIONAL_COMPONENTS PrintSupport Widgets)

qt_add_plugin(liteshell)
target_sources(liteshell PRIVATE
    liteshell_global.h
    liteshellplugin.cpp liteshellplugin.h
)
target_include_directories(liteshell PRIVATE
    ../../src/3rdparty
    ../../src/api
    ../../src/utils
)

target_compile_definitions(liteshell PRIVATE
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    LITESHELL_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(liteshell PRIVATE
    # Remove: L
    Qt::Core
    Qt::Gui
)

if(NOT MACOS)
    target_compile_definitions(liteshell PRIVATE
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(liteshell PRIVATE
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(liteshell PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(liteshell PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(liteshell PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS liteshell
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
