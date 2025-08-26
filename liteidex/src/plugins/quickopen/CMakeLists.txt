qt_add_plugin(quickopen)
target_sources(quickopen PRIVATE
    quickopen_global.h
    quickopenaction.cpp quickopenaction.h
    quickopeneditor.cpp quickopeneditor.h
    quickopenfiles.cpp quickopenfiles.h
    quickopenfilesystem.cpp quickopenfilesystem.h
    quickopenfolder.cpp quickopenfolder.h
    quickopenhelp.cpp quickopenhelp.h
    quickopenlines.cpp quickopenlines.h
    quickopenmanager.cpp quickopenmanager.h
    quickopenmimetype.cpp quickopenmimetype.h
    quickopenoption.cpp quickopenoption.h quickopenoption.ui
    quickopenoptionfactory.cpp quickopenoptionfactory.h
    quickopenplugin.cpp quickopenplugin.h
    quickopenwidget.cpp quickopenwidget.h
)
target_include_directories(quickopen PRIVATE
    ../../../src/3rdparty
    ../../../src/api
    ../../../src/utils
)

target_compile_definitions(quickopen PRIVATE
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    QT_NO_CAST_TO_ASCII
    QUICKOPEN_LIBRARY
)

target_link_libraries(quickopen PRIVATE
    # Remove: L
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

if(NOT MACOS)
    target_compile_definitions(quickopen PRIVATE
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(quickopen PRIVATE
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(WIN32)
    target_link_libraries(quickopen PRIVATE
        ole32
        shell32
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(quickopen PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(quickopen PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(quickopen PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS quickopen
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
