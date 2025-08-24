qt_add_library(terminalapi
    terminalapi.h
)
target_include_directories(terminalapi PUBLIC
    ../../src/api
)

target_compile_definitions(terminalapi PUBLIC
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(terminalapi PUBLIC
    # Remove: L
    Qt::Core
    Qt::Gui
)

if(NOT MACOS)
    target_compile_definitions(terminalapi PUBLIC
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(terminalapi PUBLIC
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(terminalapi PUBLIC
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(terminalapi PUBLIC
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(terminalapi PUBLIC
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS terminalapi
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
