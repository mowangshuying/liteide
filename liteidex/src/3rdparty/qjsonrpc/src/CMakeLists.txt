qt_add_library(qjsonrpc
    http-parser/http_parser.c http-parser/http_parser.h
    qjsonrpcabstractserver.cpp qjsonrpcabstractserver.h qjsonrpcabstractserver_p.h
    qjsonrpcglobal.h
    qjsonrpchttpclient.cpp qjsonrpchttpclient.h
    qjsonrpchttpserver.cpp qjsonrpchttpserver.h qjsonrpchttpserver_p.h
    qjsonrpclocalserver.cpp qjsonrpclocalserver.h
    qjsonrpcmessage.cpp qjsonrpcmessage.h
    qjsonrpcservice.cpp qjsonrpcservice.h qjsonrpcservice_p.h
    qjsonrpcserviceprovider.cpp qjsonrpcserviceprovider.h
    qjsonrpcservicereply.cpp qjsonrpcservicereply.h qjsonrpcservicereply_p.h
    qjsonrpcsocket.cpp qjsonrpcsocket.h qjsonrpcsocket_p.h
    qjsonrpctcpserver.cpp qjsonrpctcpserver.h
)
target_include_directories(qjsonrpc PUBLIC
    .
    ../../../src/3rdparty
    ../../../src/api
    ../../../src/api/liteapi
    ../../../src/utils
    http-parser
)

target_compile_definitions(qjsonrpc PUBLIC
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    QJSONRPC_BUILD
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(qjsonrpc PUBLIC
    # Remove: L
    Qt::Core
    Qt::Gui
    Qt::Network
    Qt::Core5Compat
)

if((QT_VERSION_MAJOR LESS 5))
    target_sources(qjsonrpc PUBLIC
        json/qjson.cpp
        json/qjsonarray.cpp
        json/qjsondocument.cpp
        json/qjsonobject.cpp
        json/qjsonparser.cpp
        json/qjsonvalue.cpp
        json/qjsonwriter.cpp
    )

    target_include_directories(qjsonrpc PUBLIC
        json
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(qjsonrpc PUBLIC
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(NOT MACOS)
    target_compile_definitions(qjsonrpc PUBLIC
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(qjsonrpc PUBLIC
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(qjsonrpc PUBLIC
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(qjsonrpc PUBLIC
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS qjsonrpc
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
