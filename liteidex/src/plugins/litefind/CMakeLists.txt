qt_add_plugin(litefind)
target_sources(litefind PRIVATE
    filesearch.cpp filesearch.h
    filesearchmanager.cpp filesearchmanager.h
    findeditor.cpp findeditor.h
    litefind_global.h
    litefindplugin.cpp litefindplugin.h
    replacedocument.cpp replacedocument.h
)
target_include_directories(litefind PRIVATE
    ../../../src/3rdparty
    ../../../src/api
    ../../../src/utils
)

target_compile_definitions(litefind PRIVATE
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    LITEFIND_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(litefind PRIVATE
    # Remove: L
    Qt::Core
    Qt::Gui
)

if(NOT MACOS)
    target_compile_definitions(litefind PRIVATE
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(litefind PRIVATE
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(litefind PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(litefind PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(litefind PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS litefind
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
