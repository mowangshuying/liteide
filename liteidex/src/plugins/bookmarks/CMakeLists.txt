qt_add_plugin(bookmarks)
target_sources(bookmarks PRIVATE
    bookmarkmanager.cpp bookmarkmanager.h
    bookmarkmodel.cpp bookmarkmodel.h
    bookmarks_global.h
    bookmarksplugin.cpp bookmarksplugin.h
)
target_include_directories(bookmarks PRIVATE
    ../../src/3rdparty
    ../../src/api
    ../../src/utils
)

target_compile_definitions(bookmarks PRIVATE
    BOOKMARKS_LIBRARY
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(bookmarks PRIVATE
    # Remove: L
    Qt::Core
    Qt::Gui
)


# Resources:
set(bookmarks_resource_files
    "images/bookmark16.png"
    "images/bookmark32.png"
)

qt_add_resources(bookmarks "bookmarks"
    PREFIX
        "/bookmarks"
    FILES
        ${bookmarks_resource_files}
)

if(NOT MACOS)
    target_compile_definitions(bookmarks PRIVATE
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(bookmarks PRIVATE
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(bookmarks PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(bookmarks PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(bookmarks PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS bookmarks
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
