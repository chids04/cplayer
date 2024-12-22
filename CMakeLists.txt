cmake_minimum_required(VERSION 3.16)

project(cplayer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.8 REQUIRED COMPONENTS Multimedia Quick Widgets Core)
# find_package(TagLib 2.0.1 REQUIRED)


if(WIN32)
    set(TAGLIB_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/xtras/taglib)

    find_path(TAGLIB_INCLUDE_DIR taglib/tag.h
        PATHS ${TAGLIB_ROOT}/include)

    find_library(TAGLIB_LIBRARY NAMES tag taglib
        PATHS ${TAGLIB_ROOT}/lib)

elseif(UNIX)
    find_package(ZLIB)
    find_package(TagLib)

endif()

add_subdirectory(3rdparty/RapidFuzz)


qt_standard_project_setup()
qt_policy(
        SET QTP0001 NEW
        SET QTP0004 NEW)

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
        qml/Settings.qml

    #QML Components
    QML_FILES
        qml/MediaSlider.qml
        qml/Sidebar.qml
        qml/components/CButton.qml
        qml/components/SongDelegate.qml
        qml/components/ErrorPopup.qml
        qml/components/SongContextMenu.qml
        qml/components/FolderDelegate.qml
        qml/components/FolderDelPopUp.qml
        qml/components/PlaylistContextMenu.qml
		qml/components/NowPlayingRect.qml

    #C++ Models
    SOURCES
        cpp/cpp_models/album.h
        cpp/cpp_models/album.cpp

        cpp/cpp_models/coverartholder.h
        cpp/cpp_models/coverartholder.cpp

        cpp/cpp_models/musicscannerthread.h
        cpp/cpp_models/musicscannerthread.cpp


        cpp/cpp_models/playlist.h
        cpp/cpp_models//playlist.cpp

        cpp/cpp_models/song.h
        cpp/cpp_models/song.cpp


        cpp/cpp_models/folder.h
        cpp/cpp_models/folder.cpp

        cpp/cpp_models/songaddthread.h
        cpp/cpp_models/songaddthread.cpp

    #C++ Playback Control
    SOURCES
        cpp/playback/mediaplayercontroller.h
        cpp/playback/mediaplayercontroller.cpp

        cpp/playback/nowplaying.h
        cpp/playback/nowplaying.cpp

        cpp/playback/queue.h
        cpp/playback/queue.cpp

		cpp/playback/queuemodel.h
		cpp/playback/queuemodel.cpp

    #C++ Image Providers
    SOURCES
        cpp/image_providers/mediaimageprovider.h
        cpp/image_providers/mediaimageprovider.cpp

        cpp/image_providers/playlistimageprovider.h
        cpp/image_providers/playlistimageprovider.cpp

    #C++ QML Models
    SOURCES
        cpp/qml_models/albumfilterproxymodel.h
        cpp/qml_models/albumfilterproxymodel.cpp

        cpp/qml_models/albumlistmodel.h
        cpp/qml_models/albumlistmodel.cpp

        cpp/qml_models/songlistmodel.h
        cpp/qml_models/songlistmodel.cpp

        cpp/qml_models/folderlistmodel.h
        cpp/qml_models/folderlistmodel.cpp

        cpp/qml_models/playlistmodel.h
        cpp/qml_models/playlistmodel.cpp

        cpp/qml_models/playlistsongsmodel.h
        cpp/qml_models/playlistsongsmodel.cpp

        cpp/qml_models/songfilterproxymodel.h
        cpp/qml_models/songfilterproxymodel.cpp

        cpp/qml_models/albumsearchfilter.h
        cpp/qml_models/albumsearchfilter.cpp

        cpp/qml_models/modelhandler.h
        cpp/qml_models/modelhandler.cpp

        cpp/qml_models/musichandler.h
        cpp/qml_models/musichandler.cpp

        cpp/qml_models/playlistfilter.cpp
        cpp/qml_models/playlistfilter.h

		cpp/qml_models/audiodevicemodel.h
		cpp/qml_models/audiodevicemodel.cpp

    #C++ QML View Controllers
    SOURCES
        cpp/views/albumsongsview.h
        cpp/views/albumview.h
        cpp/views/folderview.h
        cpp/views/songview.h
        cpp/views/viewcontroller.h

        cpp/views/albumsongsview.cpp
        cpp/views/albumview.cpp
        cpp/views/folderview.cpp
        cpp/views/songview.cpp
        cpp/views/viewcontroller.cpp

        cpp/views/playlistsongsview.cpp
        cpp/views/playlistsongsview.h

        cpp/views/playlistmanager.h
        cpp/views/playlistmanager.cpp

    #C++ utlities
    SOURCES
        cpp/utility/settingsmanager.cpp
        cpp/utility/settingsmanager.h

        cpp/utility/utilitysingleton.h
        cpp/utility/utilitysingleton.cpp
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
        rapidfuzz::rapidfuzz
    )

    #target_include_directories(appcplayer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/cpp/taglib/include ${TAGLIB_INCLUDE_DIR})
#    target_include_directories(appcplayer PRIVATE
#        ${TAGLIB_INCLUDE_DIR}
#        ${CMAKE_CURRENT_SOURCE_DIR}/cpp/cpp_models
#        ${CMAKE_CURRENT_SOURCE_DIR}/cpp/image_providers
#        ${CMAKE_CURRENT_SOURCE_DIR}/cpp/qml_models
#        ${CMAKE_CURRENT_SOURCE_DIR}/cpp/views
#        ${CMAKE_CURRENT_SOURCE_DIR}/cpp/playback
#        ${CMAKE_CURRENT_SOURCE_DIR}/cpp/utility)


elseif(UNIX)
    #target_include_directories(appcplayer PRIVATE)
    target_link_libraries(appcplayer
        PRIVATE Qt6::Quick Qt6::Multimedia Qt6::Widgets Qt6::Core TagLib::tag
        rapidfuzz::rapidfuzz
    )

#    target_include_directories(appcplayer PRIVATE
#        ${TAGLIB_INCLUDE_DIR}
#        ${CMAKE_CURRENT_SOURCE_DIR}/cpp/cpp_models/include
#        ${CMAKE_CURRENT_SOURCE_DIR}/cpp/image_providers/include
#        ${CMAKE_CURRENT_SOURCE_DIR}/cpp/qml_models/include
#        ${CMAKE_CURRENT_SOURCE_DIR}/cpp/views/include
#        ${CMAKE_CURRENT_SOURCE_DIR}/cpp/playback/include
#        ${CMAKE_CURRENT_SOURCE_DIR}/cpp/utility/include)

endif()

target_include_directories(appcplayer PRIVATE
        ${TAGLIB_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/cpp/cpp_models
        ${CMAKE_CURRENT_SOURCE_DIR}/cpp/image_providers
        ${CMAKE_CURRENT_SOURCE_DIR}/cpp/qml_models
        ${CMAKE_CURRENT_SOURCE_DIR}/cpp/views
        ${CMAKE_CURRENT_SOURCE_DIR}/cpp/playback
        ${CMAKE_CURRENT_SOURCE_DIR}/cpp/utility)


include(GNUInstallDirs)
install(TARGETS appcplayer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
