qt_add_library(libvterm
    include/vterm.h
    include/vterm_keycodes.h
    src/encoding.c
    src/keyboard.c
    src/mouse.c
    src/parser.c
    src/pen.c
    src/rect.h
    src/screen.c
    src/state.c
    src/unicode.c
    src/utf8.h
    src/vterm.c
    src/vterm_internal.h
)
target_include_directories(libvterm PUBLIC
    ../../src/3rdparty
    ../../src/api
    ../../src/api/liteapi
    ../../src/utils
    include
)

target_compile_definitions(libvterm PUBLIC
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(libvterm PUBLIC
    # Remove: L
    Qt::Core
    Qt::Gui
)

if(NOT MACOS)
    target_compile_definitions(libvterm PUBLIC
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(libvterm PUBLIC
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(libvterm PUBLIC
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(libvterm PUBLIC
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(libvterm PUBLIC
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS libvterm
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
