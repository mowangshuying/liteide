qt_add_plugin(golangpresent)
target_sources(golangpresent PRIVATE
    exportdialog.cpp exportdialog.h exportdialog.ui
    golangpresent_global.h
    golangpresentedit.cpp golangpresentedit.h
    golangpresentplugin.cpp golangpresentplugin.h
)
target_include_directories(golangpresent PRIVATE
    ../../../src/3rdparty
    ../../../src/api
    ../../../src/utils
)

target_compile_definitions(golangpresent PRIVATE
    GOLANGPRESENT_LIBRARY
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(golangpresent PRIVATE
    # Remove: L
    Qt::Core
    Qt::Gui
)


# Resources:
set(golangpresent_resource_files
    "images/bold.png"
    "images/bullets.png"
    "images/code.png"
    "images/config.png"
    "images/exporthtml.png"
    "images/exportpdf.png"
    "images/image.png"
    "images/italic.png"
    "images/link.png"
    "images/quote.png"
    "images/s1.png"
    "images/s2.png"
    "images/s3.png"
    "images/verify.png"
)

qt_add_resources(golangpresent "golangpresent"
    PREFIX
        "/golangpresent"
    FILES
        ${golangpresent_resource_files}
)

if(NOT MACOS)
    target_compile_definitions(golangpresent PRIVATE
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(golangpresent PRIVATE
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(WIN32)
    target_link_libraries(golangpresent PRIVATE
        ole32
        shell32
        user32
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(golangpresent PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(golangpresent PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(golangpresent PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS golangpresent
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
