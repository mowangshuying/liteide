qt_add_library(qtctexteditor
    autocompleter.cpp autocompleter.h
    basetextblockselection.cpp basetextblockselection.h
    basetextdocumentlayout.cpp basetextdocumentlayout.h
    colorscheme.cpp colorscheme.h
    generichighlighter/context.cpp generichighlighter/context.h
    generichighlighter/dynamicrule.cpp generichighlighter/dynamicrule.h
    generichighlighter/highlightdefinition.cpp generichighlighter/highlightdefinition.h
    generichighlighter/highlightdefinitionhandler.cpp generichighlighter/highlightdefinitionhandler.h
    generichighlighter/highlightdefinitionmetadata.cpp generichighlighter/highlightdefinitionmetadata.h
    generichighlighter/highlighter.cpp generichighlighter/highlighter.h
    generichighlighter/highlighterexception.h
    generichighlighter/includerulesinstruction.cpp generichighlighter/includerulesinstruction.h
    generichighlighter/itemdata.cpp generichighlighter/itemdata.h
    generichighlighter/keywordlist.cpp generichighlighter/keywordlist.h
    generichighlighter/manager2.cpp generichighlighter/manager2.h
    generichighlighter/progressdata.cpp generichighlighter/progressdata.h
    generichighlighter/reuse.h
    generichighlighter/rule.cpp generichighlighter/rule.h
    generichighlighter/specificrules.cpp generichighlighter/specificrules.h
    itexteditor.cpp itexteditor.h
    katehighlighter.cpp katehighlighter.h
    syntaxhighlighter.cpp syntaxhighlighter.h
    tabsettings.cpp tabsettings.h
    texteditor_global.h
)
target_include_directories(qtctexteditor PUBLIC
    .
    ../../../src/3rdparty
    ../../../src/api
    ../../../src/api/liteapi
    ../../../src/utils
)

target_compile_definitions(qtctexteditor PUBLIC
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    QT_NO_CAST_TO_ASCII
    TEXTEDITOR_LIBRARY
)

target_link_libraries(qtctexteditor PUBLIC
    # Remove: L
    Qt::Core
    Qt::Gui
    Qt::Core5Compat
    Qt::Xml
)

if(NOT MACOS)
    target_compile_definitions(qtctexteditor PUBLIC
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(qtctexteditor PUBLIC
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(qtctexteditor PUBLIC
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(qtctexteditor PUBLIC
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(qtctexteditor PUBLIC
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS qtctexteditor
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
