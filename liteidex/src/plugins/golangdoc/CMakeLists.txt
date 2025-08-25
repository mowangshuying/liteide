qt_add_plugin(golangdoc)
target_sources(golangdoc PRIVATE
    findapiwidget.cpp findapiwidget.h
    finddocwidget.cpp finddocwidget.h
    golangdoc.cpp golangdoc.h
    golangdoc_global.h
    golangdocoption.cpp golangdocoption.h golangdocoption.ui
    golangdocoptionfactory.cpp golangdocoptionfactory.h
    golangdocplugin.cpp golangdocplugin.h
)
target_include_directories(golangdoc PRIVATE
    ../../api/docbrowserapi
    ../../../src/3rdparty
    ../../../src/api
    ../../../src/utils
)

target_compile_definitions(golangdoc PRIVATE
    GOLANGDOC_LIBRARY
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(golangdoc PRIVATE
    # Remove: L
    Qt::Core
    Qt::Gui
    Qt::Xml
)

if(NOT MACOS)
    target_compile_definitions(golangdoc PRIVATE
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(golangdoc PRIVATE
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(WIN32)
    target_link_libraries(golangdoc PRIVATE
        ole32
        shell32
        user32
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(golangdoc PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(golangdoc PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(golangdoc PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS golangdoc
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
