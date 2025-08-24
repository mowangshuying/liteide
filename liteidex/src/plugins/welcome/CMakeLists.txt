qt_add_plugin(welcome)
target_sources(welcome PRIVATE
    litedoc.cpp litedoc.h
    welcome_global.h
    welcomebrowser.cpp welcomebrowser.h
    welcomeplugin.cpp welcomeplugin.h
)
target_include_directories(welcome PRIVATE
    ../../api/docbrowserapi
    ../../src/3rdparty
    ../../src/api
    ../../src/utils
)

target_compile_definitions(welcome PRIVATE
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    QT_NO_CAST_TO_ASCII
    WELCOME_LIBRARY
)

target_link_libraries(welcome PRIVATE
    # Remove: L
    Qt::Core
    Qt::Gui
    Qt::Xml
)

if(NOT MACOS)
    target_compile_definitions(welcome PRIVATE
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(welcome PRIVATE
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(welcome PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(welcome PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(welcome PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS welcome
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
