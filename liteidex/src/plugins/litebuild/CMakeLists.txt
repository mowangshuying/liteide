qt_add_plugin(litebuild)
target_sources(litebuild PRIVATE
    build.cpp build.h
    buildconfigdialog.cpp buildconfigdialog.h buildconfigdialog.ui
    buildmanager.cpp buildmanager.h
    litebuild.cpp litebuild.h
    litebuild_global.h
    litebuildoption.cpp litebuildoption.h litebuildoption.ui
    litebuildoptionfactory.cpp litebuildoptionfactory.h
    litebuildplugin.cpp litebuildplugin.h
)
target_include_directories(litebuild PRIVATE
    ../../../src/3rdparty
    ../../../src/api
    ../../../src/utils
)

target_compile_definitions(litebuild PRIVATE
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    LITEBUILD_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(litebuild PRIVATE
    # Remove: L
    Qt::Core
    Qt::Gui
)


# Resources:
set(litebuild_resource_files
    "images/bk.png"
    "images/build.png"
    "images/buildall.png"
    "images/builddebug.png"
    "images/buildrun.png"
    "images/buildtest.png"
    "images/clean.png"
    "images/cleanall.png"
    "images/config.png"
    "images/cover.png"
    "images/debug.png"
    "images/doc.png"
    "images/download.png"
    "images/filebuild.png"
    "images/filerun.png"
    "images/filetest.png"
    "images/fmt.png"
    "images/get.png"
    "images/gopm.png"
    "images/graph.png"
    "images/install.png"
    "images/lint.png"
    "images/module.png"
    "images/rebuild.png"
    "images/reget.png"
    "images/run.png"
    "images/runterm.png"
    "images/stopaction.png"
    "images/test.png"
    "images/testbench.png"
    "images/testcover.png"
    "images/tidy.png"
    "images/update.png"
    "images/utils.png"
    "images/ver.png"
    "images/vet.png"
)

qt_add_resources(litebuild "litebuild"
    PREFIX
        "/litebuild"
    FILES
        ${litebuild_resource_files}
)

if(NOT MACOS)
    target_compile_definitions(litebuild PRIVATE
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(litebuild PRIVATE
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(WIN32)
    target_link_libraries(litebuild PRIVATE
        ole32
        shell32
        user32
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(litebuild PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(litebuild PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(litebuild PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS litebuild
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
