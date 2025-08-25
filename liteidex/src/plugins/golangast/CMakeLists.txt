qt_add_plugin(golangast)
target_sources(golangast PRIVATE
    astwidget.cpp astwidget.h
    golangast.cpp golangast.h
    golangast_global.h
    golangasticon.cpp golangasticon.h
    golangastitem.h
    golangastoption.cpp golangastoption.h golangastoption.ui
    golangastoptionfactory.cpp golangastoptionfactory.h
    golangastplugin.cpp golangastplugin.h
    golangsymbol.cpp golangsymbol.h
)
target_include_directories(golangast PRIVATE
    ../../../src/3rdparty
    ../../../src/api
    ../../../src/utils
)

target_compile_definitions(golangast PRIVATE
    GOLANGAST_LIBRARY
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(golangast PRIVATE
    # Remove: L
    Qt::Core
    Qt::Gui
)


# Resources:
set(golangast_resource_files
    "images/const.png"
    "images/const_p.png"
    "images/consts.png"
    "images/file.png"
    "images/func.png"
    "images/func_p.png"
    "images/funcs.png"
    "images/gofile.png"
    "images/import.png"
    "images/imports.png"
    "images/interface.png"
    "images/interface_p.png"
    "images/makefile.png"
    "images/package.png"
    "images/project.png"
    "images/struct.png"
    "images/struct_p.png"
    "images/todo.png"
    "images/todos.png"
    "images/type.png"
    "images/type_factor.png"
    "images/type_factor_p.png"
    "images/type_method.png"
    "images/type_method_p.png"
    "images/type_p.png"
    "images/type_var.png"
    "images/type_var_p.png"
    "images/var.png"
    "images/var_p.png"
    "images/vars.png"
)

qt_add_resources(golangast "golangast"
    PREFIX
        "/golangast"
    FILES
        ${golangast_resource_files}
)

if(NOT MACOS)
    target_compile_definitions(golangast PRIVATE
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(golangast PRIVATE
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(golangast PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(golangast PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(golangast PRIVATE
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS golangast
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
