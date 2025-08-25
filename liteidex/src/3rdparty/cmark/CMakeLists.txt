qt_add_library(cmark
    libcmark.cpp libcmark.h
    src/blocks.c
    src/buffer.c src/buffer.h
    src/chunk.h
    src/cmark.c src/cmark.h
    src/cmark_ctype.c src/cmark_ctype.h
    src/commonmark.c
    src/houdini.h
    src/houdini_href_e.c
    src/houdini_html_e.c
    src/houdini_html_u.c
    src/html.c
    src/inlines.c src/inlines.h
    src/iterator.c src/iterator.h
    src/latex.c
    src/man.c
    src/node.c src/node.h
    src/parser.h
    src/references.c src/references.h
    src/render.c src/render.h
    src/scanners.c src/scanners.h
    src/utf8.c src/utf8.h
    src/xml.c
)
target_include_directories(cmark PUBLIC
    .
    ../../src/3rdparty
    ../../src/api
    ../../src/api/liteapi
    ../../src/utils
)

target_compile_definitions(cmark PUBLIC
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    QT_DEPRECATED_WARNINGS
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(cmark PUBLIC
    # Remove: L
    Qt::Core
    Qt::Gui
)

if(NOT MACOS)
    target_compile_definitions(cmark PUBLIC
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(cmark PUBLIC
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(cmark PUBLIC
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(cmark PUBLIC
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(cmark PUBLIC
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS cmark
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
