qt_add_plugin(golangpackage)
target_sources(golangpackage PRIVATE
    filepathmodel.cpp filepathmodel.h
    golangpackage_global.h
    golangpackageoption.cpp golangpackageoption.h golangpackageoption.ui
    golangpackageoptionfactory.cpp golangpackageoptionfactory.h
    golangpackageplugin.cpp golangpackageplugin.h
    gotool.cpp gotool.h
    packagebrowser.cpp packagebrowser.h
    packageproject.cpp packageproject.h
    packageprojectfactory.cpp packageprojectfactory.h
    packagetree.cpp packagetree.h
)
target_include_directories(golangpackage PRIVATE
    ../../src/3rdparty
    ../../src/api
    ../../src/utils
)

target_compile_definitions(golangpackage PRIVATE
    GOLANGPACKAGE_LIBRARY
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(golangpackage PRIVATE
    # Remove: L
    Qt::Core
    Qt::Gui
)

if(NOT MACOS)
    target_compile_definitions(golangpackage PRIVATE
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(golangpackage PRIVATE
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(WIN32)
    target_link_libraries(golangpackage PRIVATE
        ole32
        shell32
        user32
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(golangpackage PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(golangpackage PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(golangpackage PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS golangpackage
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
