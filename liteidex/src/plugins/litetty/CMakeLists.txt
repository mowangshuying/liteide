qt_add_plugin(litetty)
target_sources(litetty PRIVATE
    litetty.cpp litetty.h
    litetty_global.h
    litettyplugin.cpp litettyplugin.h
)
target_include_directories(litetty PRIVATE
    ../../../src/3rdparty
    ../../../src/api
    ../../../src/utils
)

target_compile_definitions(litetty PRIVATE
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    LITETTY_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(litetty PRIVATE
    # Remove: L
    Qt::Core
    Qt::Gui
    Qt::Network
    liteapi
    litettyapi
)

if(WIN32)
    target_sources(litetty PUBLIC
        sockettty.cpp sockettty.h
    )
endif()

if(UNIX)
    target_sources(litetty PUBLIC
        fifotty.cpp fifotty.h
        sockettty.cpp sockettty.h
    )
endif()

if(NOT MACOS)
    target_compile_definitions(litetty PRIVATE
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(litetty PRIVATE
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(litetty PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(litetty PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(litetty PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS litetty
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
