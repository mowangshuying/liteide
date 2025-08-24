qt_add_plugin(imageeditor)
target_sources(imageeditor PRIVATE
    imageeditor.cpp imageeditor.h
    imageeditor_global.h
    imageeditorfactory.cpp imageeditorfactory.h
    imageeditorfile.cpp imageeditorfile.h
    imageeditorplugin.cpp imageeditorplugin.h
    imageeditorwidget.cpp imageeditorwidget.h
)
target_include_directories(imageeditor PRIVATE
    ../../src/3rdparty
    ../../src/api
    ../../src/utils
)

target_compile_definitions(imageeditor PRIVATE
    IDE_LIBRARY_BASENAME=\\\"\\\"
    IMAGEEDITOR_LIBRARY
    LITEAPP_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(imageeditor PRIVATE
    # Remove: L
    Qt::Core
    Qt::Gui
)


# Resources:
set(imageeditor_resource_files
    "images/fitview.png"
    "images/nextframe.png"
    "images/pause.png"
    "images/play.png"
    "images/prevframe.png"
    "images/resetsize.png"
    "images/zoomin.png"
    "images/zoomout.png"
)

qt_add_resources(imageeditor "imageeditor"
    PREFIX
        "/imageeditor"
    FILES
        ${imageeditor_resource_files}
)

if(NOT QT.svg.name_ISEMPTY)
    target_link_libraries(imageeditor PRIVATE
        Qt::Svg
    )
endif()

if(NOT (NOT QT.svg.name_ISEMPTY))
    target_compile_definitions(imageeditor PRIVATE
        QT_NO_SVG
    )
endif()

if(NOT MACOS)
    target_compile_definitions(imageeditor PRIVATE
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(imageeditor PRIVATE
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(imageeditor PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(imageeditor PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(imageeditor PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS imageeditor
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
