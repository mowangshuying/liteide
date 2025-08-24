cmake_minimum_required(VERSION 3.16)
project(golangtool VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set up AUTOMOC and some sensible defaults for runtime execution
# When using Qt 6.3, you can replace the code block below with
# qt_standard_project_setup()
set(CMAKE_AUTOMOC ON)
include(GNUInstallDirs)
set(CMAKE_AUTOUIC ON)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui)
find_package(Qt${QT_VERSION_MAJOR} OPTIONAL_COMPONENTS PrintSupport Widgets)

qt_add_plugin(golangtool)
target_sources(golangtool PRIVATE
    ../filebrowser/createdirdialog.cpp ../filebrowser/createdirdialog.h ../filebrowser/createdirdialog.ui
    ../filebrowser/createfiledialog.cpp ../filebrowser/createfiledialog.h ../filebrowser/createfiledialog.ui
    golangtool_global.h
    golangtoolplugin.cpp golangtoolplugin.h
    gopathbrowser.cpp gopathbrowser.h
    gopathmodel.cpp gopathmodel.h
    gopathproject.cpp gopathproject.h
    gopathprojectfactor.cpp gopathprojectfactor.h
    importgopathdialog.cpp importgopathdialog.h importgopathdialog.ui
)
target_include_directories(golangtool PRIVATE
    ../../src/3rdparty
    ../../src/api
    ../../src/utils
)

target_compile_definitions(golangtool PRIVATE
    GOLANGTOOL_LIBRARY
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(golangtool PRIVATE
    # Remove: L
    Qt::Core
    Qt::Gui
)


# Resources:
set(golangtool_resource_files
    "images/dir.png"
    "images/diropen.png"
    "images/gopath.png"
    "images/synceditor.png"
    "images/syncproject.png"
)

qt_add_resources(golangtool "golangtool"
    PREFIX
        "/"
    FILES
        ${golangtool_resource_files}
)

if(NOT MACOS)
    target_compile_definitions(golangtool PRIVATE
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(golangtool PRIVATE
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(golangtool PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(golangtool PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(golangtool PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS golangtool
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
