cmake_minimum_required(VERSION 3.16)

project(cplayer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.8 REQUIRED COMPONENTS Multimedia Quick Widgets Core)


if(WIN32)
     # set(TAGLIB_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/xtras/taglib)

     # find_path(TAGLIB_INCLUDE_DIR taglib/tag.h
     #     PATHS ${TAGLIB_ROOT}/include)

     # find_library(TAGLIB_LIBRARY NAMES tag taglib
     #      PATHS ${TAGLIB_ROOT}/lib)
    set(TagLib_DIR "C:\\pkg_static\\lib\\cmake\\taglib")
    include($ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
    find_package(ZLIB)
    find_package(TagLib)

elseif(UNIX)
    find_package(ZLIB)
    find_package(TagLib)

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
	    qml/views/Songs.qml
		qml/views/Albums.qml
		qml/views/AlbumSongs.qml
		qml/views/Folders.qml
		qml/views/MainWindow.qml
		qml/views/Playlists.qml
		qml/views/PlaylistSongs.qml
		qml/views/Settings.qml
		qml/views/Sidebar.qml

	#QML Delegates
	QML_FILES
	    qml/delegates/SongDelegate.qml
		qml/delegates/FolderDelegate.qml
		qml/delegates/SongViewDelegate.qml

		#QML Components
    QML_FILES
	    qml/components/MediaSlider.qml
        qml/components/CButton.qml
        qml/components/ErrorPopup.qml
        qml/components/SongContextMenu.qml
        qml/components/FolderDelPopUp.qml
        qml/components/PlaylistContextMenu.qml
		qml/components/NowPlayingRect.qml
		qml/components/MsgPopup.qml
		qml/components/AudioDevicesPopup.qml
		qml/components/EditPlaylist.qml
		qml/components/EditSong.qml



	#Singleton
	SOURCES
	    cpp/globalsingleton.h
		cpp/globalsingleton.cpp


	#C++ Types
	SOURCES
	    cpp/types/song.h
		cpp/types/song.cpp

		cpp/types/album.h
		cpp/types/album.cpp

		cpp/types/folder.h
		cpp/types/folder.cpp

		cpp/types/playlist.h
		cpp/types/playlist.cpp

        cpp/types/songdata.cpp
        cpp/types/songdata.h

	#C++ Models
    SOURCES

	#C++ background tasks
	SOURCES
		cpp/background/musicscanner.h
		cpp/background/musicscanner.cpp

    #C++ Playback Control
    SOURCES
        cpp/playback/mediaplayercontroller.h
        cpp/playback/mediaplayercontroller.cpp

        cpp/playback/nowplaying.h
        cpp/playback/nowplaying.cpp

        cpp/playback/queue.h
        cpp/playback/queue.cpp

		cpp/playback/models/queuemodel.h
		cpp/playback/models/queuemodel.cpp

		cpp/playback/models/queuemodelfilter.h
		cpp/playback/models/queuemodelfilter.cpp

		cpp/playback/models/audiodevicemodel.h
		cpp/playback/models/audiodevicemodel.cpp

    #C++ Image Providers
    SOURCES
        cpp/image_providers/playlistimageprovider.h
        cpp/image_providers/playlistimageprovider.cpp

		cpp/image_providers/coverimgprovider.h
		cpp/image_providers/coverimgprovider.cpp

    #C++ QML Models
    SOURCES
	    cpp/models/album/albumfilterproxymodel.h
		cpp/models/album/albumfilterproxymodel.cpp

		cpp/models/album/albumlistmodel.h
		cpp/models/album/albumlistmodel.cpp

		cpp/models/album/albumsearchfilter.h
		cpp/models/album/albumsearchfilter.cpp

		cpp/models/song/songlistmodel.h
		cpp/models/song/songlistmodel.cpp

		cpp/models/song/songfilterproxymodel.h
		cpp/models/song/songfilterproxymodel.cpp

		cpp/models/playlist/playlistmodel.h
		cpp/models/playlist/playlistmodel.cpp

		cpp/models/playlist/playlistfilter.cpp
		cpp/models/playlist/playlistfilter.h

	#QML View Managers
    SOURCES

		cpp/managers/foldermanager.h
		cpp/managers/foldermanager.cpp

		cpp/managers/viewcontroller.h
		cpp/managers/viewcontroller.cpp

		cpp/managers/playlistmanager.h
		cpp/managers/playlistmanager.cpp

		cpp/models/folder/folderlistmodel.h
		cpp/models/folder/folderlistmodel.cpp

		cpp/managers/songmanager.h
		cpp/managers/songmanager.cpp

		cpp/managers/playbackmanager.h
		cpp/managers/playbackmanager.cpp

    #C++ utlities
    SOURCES

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

    target_compile_definitions(appcplayer PRIVATE TAGLIB_STATIC)
    target_link_libraries(appcplayer
        PRIVATE Qt6::Quick Qt6::Multimedia Qt6::Widgets Qt6::Core TagLib::tag
        rapidfuzz::rapidfuzz
    )

elseif(UNIX)
    target_link_libraries(appcplayer
        PRIVATE Qt6::Quick Qt6::Multimedia Qt6::Widgets Qt6::Core TagLib::tag
        rapidfuzz::rapidfuzz
    )

endif()

target_include_directories(appcplayer PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/cpp
		${CMAKE_CURRENT_SOURCE_DIR}/cpp/types
		${CMAKE_CURRENT_SOURCE_DIR}/cpp/background
		${CMAKE_CURRENT_SOURCE_DIR}/cpp/cpp_models
		${CMAKE_CURRENT_SOURCE_DIR}/cpp/image_providers
		${CMAKE_CURRENT_SOURCE_DIR}/cpp/models
		${CMAKE_CURRENT_SOURCE_DIR}/cpp/models/song
		${CMAKE_CURRENT_SOURCE_DIR}/cpp/models/album
		${CMAKE_CURRENT_SOURCE_DIR}/cpp/models/playlist
		${CMAKE_CURRENT_SOURCE_DIR}/cpp/managers
		${CMAKE_CURRENT_SOURCE_DIR}/cpp/managers/models
		${CMAKE_CURRENT_SOURCE_DIR}/cpp/playback
		${CMAKE_CURRENT_SOURCE_DIR}/cpp/playback/models
		${CMAKE_CURRENT_SOURCE_DIR}/cpp/utility)


include(GNUInstallDirs)
install(TARGETS appcplayer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
