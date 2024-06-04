cmake_minimum_required(VERSION 3.16)

project(cplayer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.7 REQUIRED COMPONENTS Multimedia Quick Widgets Core)
# find_package(TagLib 2.0.1 REQUIRED)


if(WIN32)
        set(TAGLIB_ROOT "C:/pkg_mingw")

        find_path(TAGLIB_INCLUDE_DIR taglib/tag.h
                        PATHS ${TAGLIB_ROOT}/include)

        find_library(TAGLIB_LIBRARY NAMES tag taglib
                        PATHS ${TAGLIB_ROOT}/lib)
elseif(UNIX)
    find_package(ZLIB)
    find_package(TagLib)

endif()

qt_standard_project_setup()

qt_add_executable(appcplayer
    main.cpp
    resources.qrc
)

qt_add_qml_module(appcplayer
    URI cplayer
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES cpp/mediaplayercontroller.h cpp/mediaplayercontroller.cpp
        RESOURCES resources.qrc
        SOURCES cpp/mediaimageprovider.h cpp/mediaimageprovider.cpp
        QML_FILES qml/MediaSlider.qml
        QML_FILES qml/MainWindow.qml
        QML_FILES qml/Sidebar.qml
        QML_FILES qml/Songs.qml
        SOURCES cpp/song.h cpp/song.cpp
        SOURCES cpp/musiclibrary.h cpp/musiclibrary.cpp
        SOURCES cpp/songlistmodel.h cpp/songlistmodel.cpp
        SOURCES cpp/coverartholder.h cpp/coverartholder.cpp
        QML_FILES qml/Albums.qml
        SOURCES cpp/album.h cpp/album.cpp
        SOURCES cpp/albumholder.h cpp/albumholder.cpp
        SOURCES cpp/albumlistmodel.h cpp/albumlistmodel.cpp
        SOURCES cpp/viewcontroller.h cpp/viewcontroller.cpp
        SOURCES cpp/albumfilterproxymodel.h cpp/albumfilterproxymodel.cpp
        SOURCES cpp/albumsongsview.h cpp/albumsongsview.cpp
        SOURCES cpp/playlistmanager.h cpp/playlistmanager.cpp
        SOURCES cpp/playlist.h cpp/playlist.cpp
        QML_FILES qml/components/CButton.qml
        QML_FILES qml/Folders.qml
        QML_FILES qml/AlbumSongs.qml
        SOURCES  cpp/folderview.cpp cpp/folderview.h
        SOURCES cpp/musicscannerthread.cpp cpp/musicscannerthread.h
        SOURCES cpp/songholder.cpp cpp/songholder.h
        SOURCES cpp/songview.cpp cpp/songview.h
        SOURCES cpp/albumview.cpp cpp/albumview.h
)



# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appcplayer PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appcplayer
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(WIN32)
        target_link_directories(appcplayer PUBLIC ${TAGLIB_LIBRARY})
        #target_link_directories(appcplayer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/cpp/taglib/lib ${TAGLIB_LIBRARY})

        target_link_libraries(appcplayer
                PRIVATE Qt6::Quick Qt6::Multimedia Qt6::Widgets Qt6::Core ${TAGLIB_LIBRARY}
        )

        #target_include_directories(appcplayer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/cpp/taglib/include ${TAGLIB_INCLUDE_DIR})
        target_include_directories(appcplayer PRIVATE  ${TAGLIB_INCLUDE_DIR})
elseif(UNIX)
    #target_include_directories(appcplayer PRIVATE)
    target_link_libraries(appcplayer PRIVATE Qt6::Quick Qt6::Multimedia Qt6::Widgets Qt6::Core TagLib::tag)
endif()

include(GNUInstallDirs)
install(TARGETS appcplayer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
