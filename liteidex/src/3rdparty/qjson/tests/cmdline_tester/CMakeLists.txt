qt_add_executable(cmdline_tester WIN32 MACOSX_BUNDLE
    cmdline_tester.cpp
    cmdlineparser.cpp
)
target_include_directories(cmdline_tester PRIVATE
    .
    ../../include
)

target_link_libraries(cmdline_tester PRIVATE
    Qt::Core
    Qt::Gui
)

if(WIN32)
    target_link_libraries(cmdline_tester PRIVATE
        # Remove: L../../lib
        qjson0
    )
endif()

if(MACOS)
    target_link_libraries(cmdline_tester PRIVATE
        "-framework qjson"
    )
endif()

if(UNIX AND NOT MACOS)
    target_link_libraries(cmdline_tester PRIVATE
        # Remove: L../../lib
        qjson
    )
endif()

install(TARGETS cmdline_tester
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Consider using qt_generate_deploy_app_script() for app deployment if
# the project can use Qt 6.3. In that case rerun qmake2cmake with
# --min-qt-version=6.3.
