qt_add_executable(tcpserver WIN32
    tcpserver.cpp
    testservice.cpp testservice.h
)
target_include_directories(tcpserver PRIVATE
    ../../../tests/common
    /json
)

target_link_libraries(tcpserver PRIVATE
    # Remove: L../../../src
    # Remove: gui
    Qt::Core
    Qt::Network
    Qt::Test
)

if(private-headers)
    target_compile_definitions(tcpserver PRIVATE
        USE_QT_PRIVATE_HEADERS
    )

    target_link_libraries(tcpserver PRIVATE
        Qt::CorePrivate
    )
endif()

if(QJSONRPC_LIBRARY_TYPE___contains___staticlib)
    target_compile_definitions(tcpserver PRIVATE
        QJSONRPC_STATIC
    )
endif()

if(NOT QJSONRPC_LIBRARY_TYPE___contains___staticlib)
    target_compile_definitions(tcpserver PRIVATE
        QJSONRPC_SHARED
    )
endif()

install(TARGETS tcpserver
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Consider using qt_generate_deploy_app_script() for app deployment if
# the project can use Qt 6.3. In that case rerun qmake2cmake with
# --min-qt-version=6.3.
