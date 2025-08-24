qt_add_library(ptyqt
    core/iptyprocess.h
    core/ptyqt.cpp core/ptyqt.h
)
target_include_directories(ptyqt PUBLIC
    ../../src/3rdparty
    ../../src/api
    ../../src/api/liteapi
    ../../src/utils
)

target_compile_definitions(ptyqt PUBLIC
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(ptyqt PUBLIC
    # Remove: L
    Qt::Core
    Qt::Gui
)

if(WIN32)
    target_sources(ptyqt PUBLIC
        core/winpty.h
        core/winpty_constants.h
    )

    target_link_libraries(ptyqt PUBLIC
        Qt::Network
    )
endif()

if(win32-g++)
    target_sources(ptyqt PUBLIC
        core/winptyprocess.cpp core/winptyprocess.h
    )
endif()

if(win32-msvc_x_)
    target_sources(ptyqt PUBLIC
        core/conptyprocess.cpp core/conptyprocess.h
    )

    target_compile_definitions(ptyqt PUBLIC
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(UNIX)
    target_sources(ptyqt PUBLIC
        core/unixptyprocess.cpp core/unixptyprocess.h
    )
endif()

if(NOT MACOS)
    target_compile_definitions(ptyqt PUBLIC
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(ptyqt PUBLIC
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(ptyqt PUBLIC
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(ptyqt PUBLIC
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS ptyqt
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
