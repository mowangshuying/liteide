qt_add_executable(liteide_ctrlc_stub MACOSX_BUNDLE
    liteide_ctrlc_stub.cpp
)
target_compile_definitions(liteide_ctrlc_stub PRIVATE
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(liteide_ctrlc_stub PRIVATE
    Qt::Core
    Qt::Gui
    shell32
    user32
)

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(liteide_ctrlc_stub PRIVATE
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(NOT MACOS)
    target_compile_definitions(liteide_ctrlc_stub PRIVATE
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(liteide_ctrlc_stub PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(liteide_ctrlc_stub PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(liteide_ctrlc_stub PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS liteide_ctrlc_stub
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Consider using qt_generate_deploy_app_script() for app deployment if
# the project can use Qt 6.3. In that case rerun qmake2cmake with
# --min-qt-version=6.3.
