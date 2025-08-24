qt_add_library(fileutil
    fileutil.cpp fileutil.h
    findfilesthread.cpp findfilesthread.h
)
target_include_directories(fileutil PUBLIC
    ../../src/3rdparty
    ../../src/api
    ../../src/api/liteapi
    ../../src/utils
)

target_compile_definitions(fileutil PUBLIC
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(fileutil PUBLIC
    # Remove: L
    Qt::Core
    Qt::Gui
)

if(MACOS)
    target_sources(fileutil PUBLIC
        fileutil_mac.mm
    )
endif()

if(NOT MACOS)
    target_compile_definitions(fileutil PUBLIC
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(fileutil PUBLIC
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(fileutil PUBLIC
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(fileutil PUBLIC
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(fileutil PUBLIC
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS fileutil
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
