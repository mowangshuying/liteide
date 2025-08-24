qt_add_executable(tst_qjsonrpcsocket WIN32
    ../../../tests/common/signalspy.h
    tst_qjsonrpcsocket.cpp
)
target_include_directories(tst_qjsonrpcsocket PRIVATE
    ../../../tests/common
    /json
)

target_link_libraries(tst_qjsonrpcsocket PRIVATE
    # Remove: L../../../src
    # Remove: gui
    Qt::Core
    Qt::Network
    Qt::Test
)


# Resources:
set(tst_qjsonrpcsocket_resource_files
    "testwire.json"
)

qt_add_resources(tst_qjsonrpcsocket "tst_qjsonrpcsocket"
    PREFIX
        "/"
    FILES
        ${tst_qjsonrpcsocket_resource_files}
)

if(private-headers)
    target_compile_definitions(tst_qjsonrpcsocket PRIVATE
        USE_QT_PRIVATE_HEADERS
    )

    target_link_libraries(tst_qjsonrpcsocket PRIVATE
        Qt::CorePrivate
    )
endif()

if(QJSONRPC_LIBRARY_TYPE___contains___staticlib)
    target_compile_definitions(tst_qjsonrpcsocket PRIVATE
        QJSONRPC_STATIC
    )
endif()

if(NOT QJSONRPC_LIBRARY_TYPE___contains___staticlib)
    target_compile_definitions(tst_qjsonrpcsocket PRIVATE
        QJSONRPC_SHARED
    )
endif()

install(TARGETS tst_qjsonrpcsocket
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Consider using qt_generate_deploy_app_script() for app deployment if
# the project can use Qt 6.3. In that case rerun qmake2cmake with
# --min-qt-version=6.3.
