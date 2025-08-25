qt_add_library(dlvclient
    dlvclient.cpp dlvclient.h
    dlvtypes.h
    varianthelper.cpp varianthelper.h
)
target_include_directories(dlvclient PUBLIC
    ../../../src/3rdparty
    ../../../src/api
    ../../../src/api/liteapi
    ../../../src/utils
)

target_compile_definitions(dlvclient PUBLIC
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(dlvclient PUBLIC
    # Remove: L
    Qt::Core
    Qt::Gui
    Qt::Network
)

if(NOT MACOS)
    target_compile_definitions(dlvclient PUBLIC
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(dlvclient PUBLIC
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(dlvclient PUBLIC
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(dlvclient PUBLIC
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(dlvclient PUBLIC
        LITEIDE_QTWEBKIT
    )
endif()

if(private-headers)
    target_compile_definitions(dlvclient PUBLIC
        USE_QT_PRIVATE_HEADERS
    )

    target_link_libraries(dlvclient PUBLIC
        Qt::CorePrivate
    )
endif()

if(QJSONRPC_LIBRARY_TYPE___contains___staticlib)
    target_compile_definitions(dlvclient PUBLIC
        QJSONRPC_STATIC
    )
endif()

if(NOT QJSONRPC_LIBRARY_TYPE___contains___staticlib)
    target_compile_definitions(dlvclient PUBLIC
        QJSONRPC_SHARED
    )
endif()

install(TARGETS dlvclient
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
