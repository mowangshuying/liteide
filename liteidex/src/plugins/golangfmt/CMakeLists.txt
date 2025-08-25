qt_add_plugin(golangfmt)
target_sources(golangfmt PRIVATE
    golangfmt.cpp golangfmt.h
    golangfmt_global.h
    golangfmtoption.cpp golangfmtoption.h golangfmtoption.ui
    golangfmtoptionfactory.cpp golangfmtoptionfactory.h
    golangfmtplugin.cpp golangfmtplugin.h
)
target_include_directories(golangfmt PRIVATE
    ../../../src/3rdparty
    ../../../src/api
    ../../../src/utils
)

target_compile_definitions(golangfmt PRIVATE
    GOLANGFMT_LIBRARY
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(golangfmt PRIVATE
    # Remove: L
    Qt::Core
    Qt::Gui
)


# Resources:
set(golangfmt_resource_files
    "images/gofmt.png"
)

qt_add_resources(golangfmt "golangfmt"
    PREFIX
        "/golangfmt"
    FILES
        ${golangfmt_resource_files}
)

if(NOT MACOS)
    target_compile_definitions(golangfmt PRIVATE
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(golangfmt PRIVATE
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(WIN32)
    target_link_libraries(golangfmt PRIVATE
        ole32
        shell32
        user32
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(golangfmt PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(golangfmt PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(golangfmt PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS golangfmt
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
