cmake_minimum_required(VERSION 3.16)
project(utils VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set up AUTOMOC and some sensible defaults for runtime execution
# When using Qt 6.3, you can replace the code block below with
# qt_standard_project_setup()
set(CMAKE_AUTOMOC ON)
include(GNUInstallDirs)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)


add_subdirectory(fileutil)
add_subdirectory(mimetype)
add_subdirectory(extension)
add_subdirectory(textoutput)
add_subdirectory(symboltreeview)
add_subdirectory(modelproject)
add_subdirectory(processex)
add_subdirectory(colorstyle)
add_subdirectory(documentbrowser)
add_subdirectory(htmlutil)
add_subdirectory(golangapi)
add_subdirectory(filesystem)
add_subdirectory(editorutil)
add_subdirectory(folderview)
add_subdirectory(iconutil)
add_subdirectory(dlvclient)
add_subdirectory(navigate)
add_subdirectory(tabwidget)
add_subdirectory(vterm)
