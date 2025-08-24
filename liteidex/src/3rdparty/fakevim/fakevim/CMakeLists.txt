qt_add_library(fakevim
    fakevimactions.cpp fakevimactions.h
    fakevimhandler.cpp fakevimhandler.h
    utils/hostosinfo.h
    utils/qtcassert.cpp
)
target_include_directories(fakevim PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../../../src/3rdparty
    ../../../src/api
    ../../../src/api/liteapi
    ../../../src/utils
    utils
)

target_compile_definitions(fakevim PUBLIC
    FAKEVIM_STANDALONE
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(fakevim PUBLIC
    # Remove: L
    Qt::Core
    Qt::Gui
)

if(NOT MACOS)
    target_compile_definitions(fakevim PUBLIC
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(fakevim PUBLIC
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(fakevim PUBLIC
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(fakevim PUBLIC
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(fakevim PUBLIC
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS fakevim
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
