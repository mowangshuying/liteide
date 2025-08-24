qt_add_library(qtc_searchresult
    searchresultcolor.h
    searchresultitem.h
    searchresulttreeitemdelegate.cpp searchresulttreeitemdelegate.h
    searchresulttreeitemroles.h
    searchresulttreeitems.cpp searchresulttreeitems.h
    searchresulttreemodel.cpp searchresulttreemodel.h
    searchresulttreeview.cpp searchresulttreeview.h
    searchresultwidget.cpp searchresultwidget.h
)
target_include_directories(qtc_searchresult PUBLIC
    ../../src/3rdparty
    ../../src/api
    ../../src/api/liteapi
    ../../src/utils
)

target_compile_definitions(qtc_searchresult PUBLIC
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(qtc_searchresult PUBLIC
    # Remove: L
    Qt::Core
    Qt::Gui
)

if(NOT MACOS)
    target_compile_definitions(qtc_searchresult PUBLIC
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(qtc_searchresult PUBLIC
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(qtc_searchresult PUBLIC
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(qtc_searchresult PUBLIC
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(qtc_searchresult PUBLIC
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS qtc_searchresult
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
