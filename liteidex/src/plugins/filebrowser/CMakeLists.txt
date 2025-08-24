qt_add_plugin(filebrowser)
target_sources(filebrowser PRIVATE
    filebrowser.cpp filebrowser.h
    filebrowser_global.h
    filebrowseroption.cpp filebrowseroption.h filebrowseroption.ui
    filebrowseroptionfactory.cpp filebrowseroptionfactory.h
    filebrowserplugin.cpp filebrowserplugin.h
)
target_include_directories(filebrowser PRIVATE
    ../../src/3rdparty
    ../../src/api
    ../../src/utils
)

target_compile_definitions(filebrowser PRIVATE
    FILEBROWSER_LIBRARY
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(filebrowser PRIVATE
    # Remove: L
    Qt::Core
    Qt::Gui
)


# Resources:
set(filebrowser_resource_files
    "images/cdup.png"
    "images/reload.png"
    "images/sync.png"
)

qt_add_resources(filebrowser "filebrowser"
    PREFIX
        "/filebrowser"
    FILES
        ${filebrowser_resource_files}
)

if(NOT MACOS)
    target_compile_definitions(filebrowser PRIVATE
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(filebrowser PRIVATE
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(WIN32)
    target_link_libraries(filebrowser PRIVATE
        ole32
        shell32
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(filebrowser PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(filebrowser PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(filebrowser PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS filebrowser
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
