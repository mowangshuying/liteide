qt_add_plugin(golangcode)
target_sources(golangcode PRIVATE
    ../liteeditor/faketooltip.cpp ../liteeditor/faketooltip.h
    golangcode.cpp golangcode.h
    golangcode_global.h
    golangcodeoption.cpp golangcodeoption.h golangcodeoption.ui
    golangcodeoptionfactory.cpp golangcodeoptionfactory.h
    golangcodeplugin.cpp golangcodeplugin.h
)
target_include_directories(golangcode PRIVATE
    ../../src/3rdparty
    ../../src/api
    ../../src/utils
)

target_compile_definitions(golangcode PRIVATE
    GOLANGCODE_LIBRARY
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(golangcode PRIVATE
    # Remove: L
    Qt::Core
    Qt::Gui
)

if(NOT MACOS)
    target_compile_definitions(golangcode PRIVATE
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(golangcode PRIVATE
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(WIN32)
    target_link_libraries(golangcode PRIVATE
        ole32
        shell32
        user32
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(golangcode PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(golangcode PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(golangcode PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS golangcode
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
