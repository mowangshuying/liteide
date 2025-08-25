qt_add_plugin(dlvdebugger)
target_sources(dlvdebugger PRIVATE
    dlvdebugger.cpp dlvdebugger.h
    dlvdebugger_global.h
    dlvdebuggeroption.cpp dlvdebuggeroption.h dlvdebuggeroption.ui
    dlvdebuggeroptionfactory.cpp dlvdebuggeroptionfactory.h
    dlvdebuggerplugin.cpp dlvdebuggerplugin.h
)
target_include_directories(dlvdebugger PRIVATE
    ../../../src/3rdparty
    ../../../src/api
    ../../../src/utils
)

target_compile_definitions(dlvdebugger PRIVATE
    GDBDEBUGER_LIBRARY
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(dlvdebugger PRIVATE
    # Remove: L
    Qt::Core
    Qt::Gui
)

if(CONFIG___contains___liteide_use_dlvclient)
    target_sources(dlvdebugger PUBLIC
        dlvrpcdebugger.cpp dlvrpcdebugger.h
    )

    target_compile_definitions(dlvdebugger PRIVATE
        USE_DLVCLIENT
    )

    target_link_libraries(dlvdebugger PRIVATE
        Qt::Network
    )
endif()

if(CONFIG___contains___liteide_use_dlvclient AND private-headers)
    target_compile_definitions(dlvdebugger PRIVATE
        USE_QT_PRIVATE_HEADERS
    )

    target_link_libraries(dlvdebugger PRIVATE
        Qt::CorePrivate
    )
endif()

if(CONFIG___contains___liteide_use_dlvclient AND QJSONRPC_LIBRARY_TYPE___contains___staticlib)
    target_compile_definitions(dlvdebugger PRIVATE
        QJSONRPC_STATIC
    )
endif()

if(CONFIG___contains___liteide_use_dlvclient AND NOT QJSONRPC_LIBRARY_TYPE___contains___staticlib)
    target_compile_definitions(dlvdebugger PRIVATE
        QJSONRPC_SHARED
    )
endif()

if(NOT MACOS)
    target_compile_definitions(dlvdebugger PRIVATE
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(dlvdebugger PRIVATE
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(WIN32)
    target_link_libraries(dlvdebugger PRIVATE
        ole32
        shell32
        user32
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(dlvdebugger PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(dlvdebugger PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(dlvdebugger PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS dlvdebugger
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
