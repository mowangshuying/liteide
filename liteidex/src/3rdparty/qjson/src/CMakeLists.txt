qt_add_library(json
    json_parser.cc json_parser.hh
    json_scanner.cpp json_scanner.h
    location.hh
    parser.cpp parser.h parser_p.h
    parserrunnable.cpp parserrunnable.h
    position.hh
    qjson_debug.h
    qjson_export.h
    qobjecthelper.cpp qobjecthelper.h
    serializer.cpp serializer.h
    serializerrunnable.cpp serializerrunnable.h
    stack.hh
)
target_include_directories(json PUBLIC
    ../../../src/3rdparty
    ../../../src/api
    ../../../src/api/liteapi
    ../../../src/utils
)

target_compile_definitions(json PUBLIC
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(json PUBLIC
    # Remove: L
    Qt::Core
    Qt::Gui
)

if(NOT MACOS)
    target_compile_definitions(json PUBLIC
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(json PUBLIC
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(json PUBLIC
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(json PUBLIC
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(json PUBLIC
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS json
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
