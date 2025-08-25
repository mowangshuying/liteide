qt_add_plugin(liteeditor)
target_sources(liteeditor PRIVATE
    codecompleter.cpp codecompleter.h
    editorapimanager.cpp editorapimanager.h
    faketooltip.cpp faketooltip.h
    functiontooltip.cpp functiontooltip.h
    highlightermanager.cpp highlightermanager.h
    katehighlighterfactory.cpp katehighlighterfactory.h
    katetextlexer.cpp katetextlexer.h
    litecompleter.cpp litecompleter.h
    liteeditor.cpp liteeditor.h
    liteeditor_global.h
    liteeditorfile.cpp liteeditorfile.h
    liteeditorfilefactory.cpp liteeditorfilefactory.h
    liteeditormark.cpp liteeditormark.h
    liteeditoroption.cpp liteeditoroption.h liteeditoroption.ui
    liteeditoroptionfactory.cpp liteeditoroptionfactory.h
    liteeditorplugin.cpp liteeditorplugin.h
    liteeditorwidget.cpp liteeditorwidget.h
    liteeditorwidgetbase.cpp liteeditorwidgetbase.h
    litewordcompleter.cpp litewordcompleter.h
    snippetapi.cpp snippetapi.h
    wordapi.cpp wordapi.h
)
target_include_directories(liteeditor PRIVATE
    ../../../src/3rdparty
    ../../../src/api
    ../../../src/utils
)

target_compile_definitions(liteeditor PRIVATE
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    LITEEDITOR_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(liteeditor PRIVATE
    # Remove: L
    Qt::Core
    Qt::Gui
    Qt::Xml
)


# Resources:
set(liteeditor_resource_files
    "images/copy.png"
    "images/cut.png"
    "images/exporthtml.png"
    "images/exportpdf.png"
    "images/fileprint.png"
    "images/fileprintpreview.png"
    "images/findword.png"
    "images/func.png"
    "images/goto.png"
    "images/keyword.png"
    "images/lock.png"
    "images/paste.png"
    "images/redo.png"
    "images/snippet.png"
    "images/undo.png"
    "images/unlock.png"
)

qt_add_resources(liteeditor "liteeditor"
    PREFIX
        "/liteeditor"
    FILES
        ${liteeditor_resource_files}
)

if(NOT MACOS)
    target_compile_definitions(liteeditor PRIVATE
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(liteeditor PRIVATE
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(liteeditor PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(liteeditor PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(liteeditor PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS liteeditor
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
