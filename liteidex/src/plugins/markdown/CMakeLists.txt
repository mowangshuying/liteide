qt_add_plugin(markdown)
target_sources(markdown PRIVATE
    htmlpreview.cpp htmlpreview.h
    markdown_global.h
    markdownbatchbrowser.cpp markdownbatchbrowser.h
    markdownbatchwidget.ui
    markdownedit.cpp markdownedit.h
    markdownplugin.cpp markdownplugin.h
)
target_include_directories(markdown PRIVATE
    ../../../src/3rdparty
    ../../../src/api
    ../../../src/utils
)

target_compile_definitions(markdown PRIVATE
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    MARKDOWN_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(markdown PRIVATE
    # Remove: L
    Qt::Core
    Qt::Gui
    Qt::Core5Compat
)


# Resources:
set(markdown_resource_files
    "css/textbrowser.css"
    "images/bold.png"
    "images/code.png"
    "images/config.png"
    "images/css.png"
    "images/h1.png"
    "images/h2.png"
    "images/h3.png"
    "images/h4.png"
    "images/h5.png"
    "images/h6.png"
    "images/hr.png"
    "images/image.png"
    "images/italic.png"
    "images/link.png"
    "images/ol.png"
    "images/quote.png"
    "images/syncscroll.png"
    "images/syncview.png"
    "images/ul.png"
)

qt_add_resources(markdown "markdown"
    PREFIX
        "/markdown"
    FILES
        ${markdown_resource_files}
)

if(NOT MACOS)
    target_compile_definitions(markdown PRIVATE
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(markdown PRIVATE
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(markdown PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(markdown PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(markdown PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS markdown
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
