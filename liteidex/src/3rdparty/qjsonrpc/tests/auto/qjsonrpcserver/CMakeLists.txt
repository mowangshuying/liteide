qt_add_executable(tst_qjsonrpcserver WIN32
    testservices.cpp testservices.h
    tst_qjsonrpcserver.cpp
)
target_include_directories(tst_qjsonrpcserver PRIVATE
    ../../../tests/common
    /json
)

target_link_libraries(tst_qjsonrpcserver PRIVATE
    # Remove: L../../../src
    # Remove: gui
    Qt::Core
    Qt::Network
    Qt::Test
)

if(private-headers)
    target_compile_definitions(tst_qjsonrpcserver PRIVATE
        USE_QT_PRIVATE_HEADERS
    )

    target_link_libraries(tst_qjsonrpcserver PRIVATE
        Qt::CorePrivate
    )
endif()

if(QJSONRPC_LIBRARY_TYPE___contains___staticlib)
    target_compile_definitions(tst_qjsonrpcserver PRIVATE
        QJSONRPC_STATIC
    )
endif()

if(NOT QJSONRPC_LIBRARY_TYPE___contains___staticlib)
    target_compile_definitions(tst_qjsonrpcserver PRIVATE
        QJSONRPC_SHARED
    )
endif()

install(TARGETS tst_qjsonrpcserver
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Consider using qt_generate_deploy_app_script() for app deployment if
# the project can use Qt 6.3. In that case rerun qmake2cmake with
# --min-qt-version=6.3.
