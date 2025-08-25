qt_add_plugin(golangedit)
target_sources(golangedit PRIVATE
    goaddtagsdialog.cpp goaddtagsdialog.h goaddtagsdialog.ui
    golangedit.cpp golangedit.h
    golangedit_global.h
    golangeditoption.cpp golangeditoption.h golangeditoption.ui
    golangeditoptionfactory.cpp golangeditoptionfactory.h
    golangeditplugin.cpp golangeditplugin.h
    golangfilesearch.cpp golangfilesearch.h
    golanghighlighter.cpp golanghighlighter.h
    golanghighlighterfactory.cpp golanghighlighterfactory.h
    golangtextlexer.cpp golangtextlexer.h
    goplsfilesearch.cpp goplsfilesearch.h
    goremovetagsdialog.cpp goremovetagsdialog.h goremovetagsdialog.ui
)
target_include_directories(golangedit PRIVATE
    ../../../src/3rdparty
    ../../../src/api
    ../../../src/utils
)

target_compile_definitions(golangedit PRIVATE
    GOLANGEDIT_LIBRARY
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(golangedit PRIVATE
    # Remove: L
    Qt::Core
    Qt::Gui
)

if(NOT MACOS)
    target_compile_definitions(golangedit PRIVATE
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(golangedit PRIVATE
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(WIN32)
    target_link_libraries(golangedit PRIVATE
        ole32
        shell32
        user32
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(golangedit PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(golangedit PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(golangedit PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS golangedit
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
