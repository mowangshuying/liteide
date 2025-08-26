qt_add_plugin(fakevimedit)
target_sources(fakevimedit PRIVATE
    ../../3rdparty/fakevim/fakevim/fakevimactions.cpp ../../3rdparty/fakevim/fakevim/fakevimactions.h
    ../../3rdparty/fakevim/fakevim/fakevimhandler.cpp ../../3rdparty/fakevim/fakevim/fakevimhandler.h
    ../../3rdparty/fakevim/fakevim/utils/hostosinfo.h
    ../../3rdparty/fakevim/fakevim/utils/qtcassert.cpp
    fakevimedit.cpp fakevimedit.h
    fakevimedit_global.h
    fakevimeditoption.cpp fakevimeditoption.h fakevimeditoption.ui
    fakevimeditoptionfactory.cpp fakevimeditoptionfactory.h
    fakevimeditplugin.cpp fakevimeditplugin.h
)
target_include_directories(fakevimedit PRIVATE
    ../../3rdparty/fakevim/fakevim
    ../../3rdparty/fakevim/fakevim/utils
    ../../../src/3rdparty
    ../../../src/api
    ../../../src/utils
)

target_compile_definitions(fakevimedit PRIVATE
    FAKEVIMEDIT_LIBRARY
    FAKEVIM_STANDALONE
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(fakevimedit PRIVATE
    # Remove: L
    Qt::Core
    Qt::Gui
    Qt::Core5Compat
)

if(NOT MACOS)
    target_compile_definitions(fakevimedit PRIVATE
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(fakevimedit PRIVATE
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(fakevimedit PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(fakevimedit PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(fakevimedit PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS fakevimedit
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
