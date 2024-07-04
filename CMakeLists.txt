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

    #QML Views
    QML_FILES
        qml/Songs.qml
        qml/Albums.qml
        qml/AlbumSongs.qml
        qml/Folders.qml
        qml/MainWindow.qml
        qml/Playlists.qml
        qml/PlaylistSongs.qml

    #QML Components
    QML_FILES
        qml/MediaSlider.qml
        qml/Sidebar.qml
        qml/components/CButton.qml
        qml/components/SongDelegate.qml
        qml/components/ErrorPopup.qml
        qml/components/SongContextMenu.qml

    #C++ Models
    SOURCES
        cpp/cpp_models/include/album.h
        cpp/cpp_models/include/coverartholder.h
        cpp/cpp_models/include/musicscannerthread.h
        cpp/cpp_models/include/playlist.h
        cpp/cpp_models/include/song.h
        cpp/cpp_models/include/folder.h

        cpp/cpp_models/src/album.cpp
        cpp/cpp_models/src/coverartholder.cpp
        cpp/cpp_models/src/musicscannerthread.cpp
        cpp/cpp_models/src/playlist.cpp
        cpp/cpp_models/src/song.cpp
        cpp/cpp_models/src/folder.cpp

    #C++ Playback Control
    SOURCES
        cpp/playback/include/mediaplayercontroller.h
        cpp/playback/include/nowplaying.h

        cpp/playback/src/mediaplayercontroller.cpp
        cpp/playback/src/nowplaying.cpp

    #C++ Image Providers
    SOURCES
        cpp/image_providers/include/mediaimageprovider.h
        cpp/image_providers/src/mediaimageprovider.cpp

    #C++ QML Models
    SOURCES
        cpp/qml_models/include/albumfilterproxymodel.h
        cpp/qml_models/include/albumlistmodel.h
        cpp/qml_models/include/songlistmodel.h
        cpp/qml_models/include/folderlistmodel.h
        cpp/qml_models/include/playlistmodel.h
        cpp/qml_models/include/playlistsongsmodel.h
        cpp/views/include/playlistview.h


        cpp/qml_models/src/albumfilterproxymodel.cpp
        cpp/qml_models/src/albumlistmodel.cpp
        cpp/qml_models/src/songlistmodel.cpp
        cpp/qml_models/src/folderlistmodel.cpp
        cpp/qml_models/src/playlistmodel.cpp
        cpp/qml_models/src/playlistsongsmodel.cpp
        cpp/views/src/playlistview.cpp


    #C++ QML View Controllers
    SOURCES
        cpp/views/include/albumsongsview.h
        cpp/views/include/albumview.h
        cpp/views/include/folderview.h
        cpp/views/include/songview.h
        cpp/views/include/viewcontroller.h

        cpp/views/src/albumsongsview.cpp
        cpp/views/src/albumview.cpp
        cpp/views/src/folderview.cpp
        cpp/views/src/songview.cpp
        cpp/views/src/viewcontroller.cpp
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
    target_include_directories(appcplayer PRIVATE
        ${TAGLIB_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/cpp/cpp_models/include
        ${CMAKE_CURRENT_SOURCE_DIR}/cpp/image_providers/include
        ${CMAKE_CURRENT_SOURCE_DIR}/cpp/qml_models/include
        ${CMAKE_CURRENT_SOURCE_DIR}/cpp/views/include
        ${CMAKE_CURRENT_SOURCE_DIR}/cpp/playback/include)


elseif(UNIX)
    #target_include_directories(appcplayer PRIVATE)
    target_link_libraries(appcplayer PRIVATE Qt6::Quick Qt6::Multimedia Qt6::Widgets Qt6::Core TagLib::tag)

    target_include_directories(appcplayer PRIVATE
        ${TAGLIB_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/cpp/cpp_models/include
        ${CMAKE_CURRENT_SOURCE_DIR}/cpp/image_providers/include
        ${CMAKE_CURRENT_SOURCE_DIR}/cpp/qml_models/include
        ${CMAKE_CURRENT_SOURCE_DIR}/cpp/views/include
        ${CMAKE_CURRENT_SOURCE_DIR}/cpp/playback/include)

endif()

include(GNUInstallDirs)
install(TARGETS appcplayer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
