qt_add_plugin(liteenv)
target_sources(liteenv PRIVATE
    envmanager.cpp envmanager.h
    goenvmanager.cpp goenvmanager.h
    liteenv_global.h
    liteenvoption.cpp liteenvoption.h liteenvoption.ui
    liteenvoptionfactory.cpp liteenvoptionfactory.h
    liteenvplugin.cpp liteenvplugin.h
)
target_include_directories(liteenv PRIVATE
    ../../src/3rdparty
    ../../src/api
    ../../src/utils
)

target_compile_definitions(liteenv PRIVATE
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    LITEENV_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(liteenv PRIVATE
    # Remove: L
    Qt::Core
    Qt::Gui
)


# Resources:
set(liteenv_resource_files
    "images/reload.png"
    "images/setenv.png"
)

qt_add_resources(liteenv "liteenv"
    PREFIX
        "/liteenv"
    FILES
        ${liteenv_resource_files}
)

if(NOT MACOS)
    target_compile_definitions(liteenv PRIVATE
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(liteenv PRIVATE
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(WIN32)
    target_link_libraries(liteenv PRIVATE
        ole32
        shell32
        user32
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(liteenv PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(liteenv PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(liteenv PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS liteenv
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
