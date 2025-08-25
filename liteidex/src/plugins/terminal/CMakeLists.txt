qt_add_plugin(terminal)
target_sources(terminal PRIVATE
    terminal.cpp terminal.h
    terminal_global.h
    terminaloption.cpp terminaloption.h terminaloption.ui
    terminaloptionfactory.cpp terminaloptionfactory.h
    terminalplugin.cpp terminalplugin.h
)
target_include_directories(terminal PRIVATE
    ../../../src/3rdparty
    ../../../src/api
    ../../../src/utils
)

target_compile_definitions(terminal PRIVATE
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    QT_NO_CAST_TO_ASCII
    TERMINAL_LIBRARY
)

target_link_libraries(terminal PRIVATE
    # Remove: L
    Qt::Core
    Qt::Gui
)

if(WIN32)
    target_link_libraries(terminal PRIVATE
        Qt::Network
    )
endif()

if(NOT MACOS)
    target_compile_definitions(terminal PRIVATE
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(terminal PRIVATE
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(terminal PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(terminal PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(terminal PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS terminal
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
