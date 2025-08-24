qt_add_executable(liteide WIN32 MACOSX_BUNDLE
    main.cpp
)
target_compile_definitions(liteide PRIVATE
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(liteide PRIVATE
    # Remove: L
    Qt::Core
    Qt::Gui
)

if(MACOS)
    target_link_libraries(liteide PRIVATE
        # Remove: L${CMAKE_CURRENT_SOURCE_DIR}/liteide/bin/LiteIDE.app/Contents/MacOS
        Qt::Xml
    )
endif()

if(NOT MACOS)
    target_compile_definitions(liteide PRIVATE
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )

    target_link_libraries(liteide PRIVATE
        # Remove: L${CMAKE_CURRENT_SOURCE_DIR}/liteide/bin
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(liteide PRIVATE
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(liteide PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(liteide PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(liteide PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS liteide
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Consider using qt_generate_deploy_app_script() for app deployment if
# the project can use Qt 6.3. In that case rerun qmake2cmake with
# --min-qt-version=6.3.
