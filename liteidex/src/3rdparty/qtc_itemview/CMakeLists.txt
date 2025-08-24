qt_add_library(qtc_itemview
    itemviews.cpp itemviews.h
    opendocumentstreeview.cpp opendocumentstreeview.h
    proxymodel.cpp proxymodel.h
)
target_include_directories(qtc_itemview PUBLIC
    ../../src/3rdparty
    ../../src/api
    ../../src/api/liteapi
    ../../src/utils
)

target_compile_definitions(qtc_itemview PUBLIC
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(qtc_itemview PUBLIC
    # Remove: L
    Qt::Core
    Qt::Gui
)


# Resources:
set(qtc_itemview_resource_files
    "images/closebutton.png"
    "images/darkclosebutton.png"
)

qt_add_resources(qtc_itemview "qtc_itemview"
    PREFIX
        "/"
    FILES
        ${qtc_itemview_resource_files}
)

if(NOT MACOS)
    target_compile_definitions(qtc_itemview PUBLIC
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(qtc_itemview PUBLIC
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(qtc_itemview PUBLIC
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(qtc_itemview PUBLIC
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(qtc_itemview PUBLIC
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS qtc_itemview
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
