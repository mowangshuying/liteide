qt_add_library(libucd
    include/libucd.h
    src/CharDistribution.cpp src/CharDistribution.h
    src/JpCntx.cpp src/JpCntx.h
    src/LangBulgarianModel.cpp
    src/LangCyrillicModel.cpp
    src/LangCzechModel.cpp
    src/LangFinnishModel.cpp
    src/LangFrenchModel.cpp
    src/LangGermanModel.cpp
    src/LangGreekModel.cpp
    src/LangHebrewModel.cpp
    src/LangHungarianModel.cpp
    src/LangPolishModel.cpp
    src/LangSpanishModel.cpp
    src/LangSwedishModel.cpp
    src/LangThaiModel.cpp
    src/LangTurkishModel.cpp
    src/nsBig5Prober.cpp src/nsBig5Prober.h
    src/nsCharSetProber.cpp src/nsCharSetProber.h
    src/nsCodingStateMachine.h
    src/nsDebug.h
    src/nsEUCJPProber.cpp src/nsEUCJPProber.h
    src/nsEUCKRProber.cpp src/nsEUCKRProber.h
    src/nsEUCTWProber.cpp src/nsEUCTWProber.h
    src/nsEscCharsetProber.cpp src/nsEscCharsetProber.h
    src/nsEscSM.cpp
    src/nsGB2312Prober.cpp src/nsGB2312Prober.h
    src/nsHebrewProber.cpp src/nsHebrewProber.h
    src/nsLatin1Prober.cpp src/nsLatin1Prober.h
    src/nsMBCSGroupProber.cpp src/nsMBCSGroupProber.h
    src/nsMBCSSM.cpp
    src/nsPkgInt.h
    src/nsSBCSGroupProber.cpp src/nsSBCSGroupProber.h
    src/nsSBCharSetProber.cpp src/nsSBCharSetProber.h
    src/nsSJISProber.cpp src/nsSJISProber.h
    src/nsUTF8Prober.cpp src/nsUTF8Prober.h
    src/nsUniversalDetector.cpp src/nsUniversalDetector.h
    src/nscore.h
    src/prmem.h
    src/ucdapi.cpp
)
target_include_directories(libucd PUBLIC
    ../../src/3rdparty
    ../../src/api
    ../../src/api/liteapi
    ../../src/utils
    include
)

target_compile_definitions(libucd PUBLIC
    IDE_LIBRARY_BASENAME=\\\"\\\"
    LITEAPP_LIBRARY
    QT_NO_CAST_TO_ASCII
)

target_link_libraries(libucd PUBLIC
    # Remove: L
    Qt::Core
    Qt::Gui
)

if(NOT MACOS)
    target_compile_definitions(libucd PUBLIC
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
    )
endif()

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(libucd PUBLIC
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if(win32-msvc_x_)
    target_compile_definitions(libucd PUBLIC
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CONFIG___contains___liteide_qtwebkit AND linux_x_)
    target_compile_definitions(libucd PUBLIC
        LITEIDE_QTWEBKIT
    )
endif()

if((NOT (linux_x_)) AND (NOT ((QT_VERSION_MAJOR GREATER 4))))
    target_compile_definitions(libucd PUBLIC
        LITEIDE_QTWEBKIT
    )
endif()

install(TARGETS libucd
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
