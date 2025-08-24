qt_add_plugin(litedebug)
target_sources(litedebug PRIVATE
    debugmanager.cpp debugmanager.h
    debugwidget.cpp debugwidget.h
    litedebug.cpp litedebug.h
    litedebug_global.h
    litedebugoption.cpp litedebugoption.h litedebugoption.ui
    litedebugoptionfactory.cpp litedebugoptionfactory.h
    litedebugplugin.cpp litedebugplugin.h
    selectexternaldialog.cpp selectexternaldialog.h selectexternaldialog.ui
)
target_include_directories(litedebug PRIVATE
    ../../src/3rdparty
    ../../src/api
    ../../src/utils
)

target_compile_definitions(litedebug PRIVATE
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    LITEDEBUG_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(litedebug PRIVATE
    # Remove: L
    Qt::Core
    Qt::Gui
)


# Resources:
set(litedebug_resource_files
    "images/breakmark.png"
    "images/continue.png"
    "images/insertbreak.png"
    "images/linemark.png"
    "images/runtoline.png"
    "images/showline.png"
    "images/startdebug.png"
    "images/stepinto.png"
    "images/stepout.png"
    "images/stepover.png"
    "images/stopdebug.png"
)

qt_add_resources(litedebug "litedebug"
    PREFIX
        "/litedebug"
    FILES
        ${litedebug_resource_files}
)

if(NOT MACOS)
    target_compile_definitions(litedebug PRIVATE
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(litedebug PRIVATE
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(WIN32)
    target_link_libraries(litedebug PRIVATE
        ole32
        shell32
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(litedebug PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(litedebug PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(litedebug PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS litedebug
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
