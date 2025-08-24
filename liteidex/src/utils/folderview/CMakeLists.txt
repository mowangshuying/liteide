qt_add_library(folderview
    abstractmultiproxymodel.cpp abstractmultiproxymodel.h abstractmultiproxymodel_p.h
    basefolderview.cpp
    basefoldeview.h
    dirsortfilterproxymodel.cpp dirsortfilterproxymodel.h
    filesystemmodelex.cpp filesystemmodelex.h
    folderdialog.cpp folderdialog.h
    folderlistmodel.cpp folderlistmodel.h
    folderlistview.cpp folderlistview.h
    folderview.cpp folderview.h
    multifoldermodel.cpp multifoldermodel.h
    multifolderview.cpp multifolderview.h
    multiindexmodel.cpp multiindexmodel.h multiindexmodel_p.h
)
target_include_directories(folderview PUBLIC
    ../../src/3rdparty
    ../../src/api
    ../../src/api/liteapi
    ../../src/utils
)

target_compile_definitions(folderview PUBLIC
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(folderview PUBLIC
    # Remove: L
    Qt::Core
    Qt::Gui
)

if(NOT MACOS)
    target_compile_definitions(folderview PUBLIC
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(folderview PUBLIC
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(folderview PUBLIC
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(folderview PUBLIC
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(folderview PUBLIC
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS folderview
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
