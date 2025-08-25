qt_add_plugin(webkithtmlwidget)
target_sources(webkithtmlwidget PRIVATE
    webkitbrowser.cpp webkitbrowser.h
    webkithtmlwidget_global.h
    webkithtmlwidgetplugin.cpp webkithtmlwidgetplugin.h
    webviewhtmlwidget.cpp webviewhtmlwidget.h
)
target_include_directories(webkithtmlwidget PRIVATE
    ../../../src/3rdparty
    ../../../src/api
    ../../../src/utils
)

target_compile_definitions(webkithtmlwidget PRIVATE
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    QT_NO_CAST_TO_ASCII
    WEBKITHTMLWIDGET_LIBRARY
)

target_link_libraries(webkithtmlwidget PRIVATE
    # Remove: L
    Qt::Core
    Qt::Gui
)

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(webkithtmlwidget PRIVATE
        Qt::PrintSupport
        Qt::WebKitWidgets
        Qt::Widgets
    )
endif()

if(NOT ((QT_VERSION_MAJOR GREATER 4)))
    target_link_libraries(webkithtmlwidget PRIVATE
        Qt::Network
        webkit
    )
endif()

if(NOT MACOS)
    target_compile_definitions(webkithtmlwidget PRIVATE
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(webkithtmlwidget PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(webkithtmlwidget PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(webkithtmlwidget PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS webkithtmlwidget
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
