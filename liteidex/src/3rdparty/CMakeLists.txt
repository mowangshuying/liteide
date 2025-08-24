cmake_minimum_required(VERSION 3.16)
project(3rdparty VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set up AUTOMOC and some sensible defaults for runtime execution
# When using Qt 6.3, you can replace the code block below with
# qt_standard_project_setup()
set(CMAKE_AUTOMOC ON)
include(GNUInstallDirs)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)


add_subdirectory(treemodelcompleter)
add_subdirectory(qtc_texteditor)
add_subdirectory(qtc_gdbmi)
add_subdirectory(qtc_editutil)
add_subdirectory(qtc_searchresult)
add_subdirectory(qtc_itemview)
add_subdirectory(qt_browser)
add_subdirectory(qjson)
add_subdirectory(elidedlabel)
add_subdirectory(cplusplus)
add_subdirectory(fakevim)
add_subdirectory(diff_match_patch)
add_subdirectory(qjsonrpc)
add_subdirectory(libucd)
add_subdirectory(cmark)
add_subdirectory(libvterm)
add_subdirectory(ptyqt)
