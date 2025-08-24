qt_add_executable(liteapp WIN32 MACOSX_BUNDLE
    aboutdialog.cpp aboutdialog.h aboutdialog.ui
    actionmanager.cpp actionmanager.h
    cdrv.h
    editormanager.cpp editormanager.h
    filemanager.cpp filemanager.h
    folderproject.cpp folderproject.h
    folderprojectfactory.cpp folderprojectfactory.h
    goproxy.cpp goproxy.h
    htmlwidgetmanager.cpp htmlwidgetmanager.h
    idletimer.cpp idletimer.h
    liteapp.cpp liteapp.h
    liteapp_global.h
    liteappoption.cpp liteappoption.h liteappoption.ui
    liteappoptionfactory.cpp liteappoptionfactory.h
    main.cpp
    mainwindow.cpp mainwindow.h
    mimetypemanager.cpp mimetypemanager.h
    multifolderwindow.cpp multifolderwindow.h
    newfiledialog.cpp newfiledialog.h newfiledialog.ui
    openeditorswidget.cpp openeditorswidget.h
    optionmanager.cpp optionmanager.h
    optionsbrowser.cpp optionsbrowser.h
    optionswidget.ui
    outputoption.cpp outputoption.h outputoption.ui
    pluginmanager.cpp pluginmanager.h
    pluginsdialog.cpp pluginsdialog.h pluginsdialog.ui
    projectmanager.cpp projectmanager.h
    recentmanager.cpp recentmanager.h
    rotationtoolbutton.cpp rotationtoolbutton.h
    sidewindowstyle.cpp sidewindowstyle.h
    splitfolderwindow.cpp splitfolderwindow.h
    splitwindowstyle.cpp splitwindowstyle.h
    textbrowserhtmlwidget.cpp textbrowserhtmlwidget.h
    tooldockwidget.cpp tooldockwidget.h
    toolmainwindow.cpp toolmainwindow.h
    toolwindowmanager.cpp toolwindowmanager.h
    windowstyle.h
)
target_include_directories(liteapp PRIVATE
    src/3rdparty
    src/api
    src/utils
)

target_compile_definitions(liteapp PRIVATE
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(liteapp PRIVATE
    # Remove: L
    Qt::Core
    Qt::Gui
)


# Resources:
set(liteapp_resource_files
    "images/addpage.png"
    "images/backward.png"
    "images/cleanoutput.png"
    "images/close.png"
    "images/closefile.png"
    "images/closepage.png"
    "images/closeproject.png"
    "images/closetab.png"
    "images/config.png"
    "images/copy.png"
    "images/cut.png"
    "images/darkclosebutton.png"
    "images/editclear.png"
    "images/fileitem.png"
    "images/filter.png"
    "images/folderitem.png"
    "images/forward.png"
    "images/godoc.png"
    "images/gopath.png"
    "images/gopher.png"
    "images/hideoutput.png"
    "images/hidesidebar.png"
    "images/hidetool.png"
    "images/home.png"
    "images/listpage.png"
    "images/liteide-logo128.png"
    "images/liteide-logo64.png"
    "images/liteide128.png"
    "images/liteide16.png"
    "images/liteide24.png"
    "images/liteide32.png"
    "images/liteide48.png"
    "images/liteide64.png"
    "images/lock.png"
    "images/logo/dui.png"
    "images/logo/gen.png"
    "images/logo/kan.png"
    "images/logo/kun.png"
    "images/logo/li.png"
    "images/logo/qian.png"
    "images/logo/space.png"
    "images/logo/xun.png"
    "images/logo/zhen.png"
    "images/movemenu.png"
    "images/new.png"
    "images/openfile.png"
    "images/openfolder.png"
    "images/openproject.png"
    "images/options.png"
    "images/paste.png"
    "images/projectitem.png"
    "images/redo.png"
    "images/reload.png"
    "images/save.png"
    "images/saveall.png"
    "images/saveproject.png"
    "images/setup.png"
    "images/sync.png"
    "images/undo.png"
    "images/unlock.png"
)

qt_add_resources(liteapp "liteapp"
    PREFIX
        "/"
    FILES
        ${liteapp_resource_files}
)

if(MACOS)
    target_sources(liteapp PUBLIC
        macsupport.h macsupport.mm
    )

    target_link_libraries(liteapp PRIVATE
        "-framework AppKit"
        Qt::Xml
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(liteapp PRIVATE
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(NOT MACOS)
    target_compile_definitions(liteapp PRIVATE
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if(WIN32)
    target_link_libraries(liteapp PRIVATE
        ole32
        shell32
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(liteapp PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(liteapp PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(liteapp PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS liteapp
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Consider using qt_generate_deploy_app_script() for app deployment if
# the project can use Qt 6.3. In that case rerun qmake2cmake with
# --min-qt-version=6.3.
