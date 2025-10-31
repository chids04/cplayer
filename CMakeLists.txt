cmake_minimum_required(VERSION 3.29)

project(cplayer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)
set(PYBIND11_FINDPYTHON ON)
set(SC_LIB_PATH "${CMAKE_SOURCE_DIR}/extern/sc-lib-fork")
set(PY_LIB_PATH "${CMAKE_SOURCE_DIR}/extern/python-libs") 
set(QT_QML_GENERATE_QMLLS_INI ON)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	set(VCPKG_TARGET_TRIPLET "x64-windows")

elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin") # macOS
	if(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
		set(VCPKG_TARGET_TRIPLET "arm64-osx")

	elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
		set(VCPKG_TARGET_TRIPLET "x64-osx")

	else()
		set(VCPKG_TARGET_TRIPLET "x64-osx")
	endif()

elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
   if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
	   set(VCPKG_TARGET_TRIPLET "x64-linux")
   else()
	   set(VCPKG_TARGET_TRIPLET "x64-linux")
   endif()
endif()



include("$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

find_package(Qt6 REQUIRED COMPONENTS Multimedia Quick Widgets Core)
find_package(ZLIB REQUIRED)
find_package(TagLib REQUIRED)
find_package(Python COMPONENTS Interpreter Development REQUIRED)


add_subdirectory(extern/RapidFuzz)
add_subdirectory(extern/pybind11)
add_subdirectory(cpp/types)
add_subdirectory(cpp/models)
add_subdirectory(cpp/playback)
add_subdirectory(cpp/image_providers)
add_subdirectory(cpp/background)
add_subdirectory(cpp/managers)

qt_standard_project_setup()
qt_policy(SET QTP0001 NEW)
qt_policy(SET QTP0004 NEW)

qt_add_executable(appcplayer
    cpp/main.cpp
    resources.qrc
)

qt_add_qml_module(appcplayer
    URI cplayer
    VERSION 1.0
	NO_CACHEGEN
    QML_FILES
	    qml/Main.qml

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
		qml/views/HomePage.qml
		qml/views/CSidebar.qml
        qml/views/Search.qml

	#QML Delegates
	QML_FILES
	    qml/delegates/SongDelegate.qml
		qml/delegates/FolderDelegate.qml
		qml/delegates/SongViewDelegate.qml
		qml/delegates/AlbumDelegate.qml

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
        qml/components/loading/RectangleLoader.qml
		qml/components/DlPopup.qml
		qml/components/AlbumInfo.qml



	# #Singleton
	# SOURCES
	#     cpp/globalsingleton.h
	# 	cpp/globalsingleton.cpp


	# #C++ Types
	# SOURCES
	#     cpp/types/song.h
	# 	cpp/types/song.cpp

	# 	cpp/types/album.h
	# 	cpp/types/album.cpp

	# 	cpp/types/folder.h
	# 	cpp/types/folder.cpp

	# 	cpp/types/playlist.h
	# 	cpp/types/playlist.cpp

    #     cpp/types/songdata.cpp
    #     cpp/types/songdata.h

	# #C++ Models
    # SOURCES

	# #C++ background tasks
	# SOURCES
	# 	cpp/background/musicscanner.h
	# 	cpp/background/musicscanner.cpp

    # #C++ Playback Control
    # SOURCES
    #     cpp/playback/mediaplayercontroller.h
    #     cpp/playback/mediaplayercontroller.cpp

    #     cpp/playback/nowplaying.h
    #     cpp/playback/nowplaying.cpp

    #     cpp/playback/queue.h
    #     cpp/playback/queue.cpp

	# 	cpp/playback/models/queuemodel.h
	# 	cpp/playback/models/queuemodel.cpp

	# 	cpp/playback/models/queuemodelfilter.h
	# 	cpp/playback/models/queuemodelfilter.cpp

	# 	cpp/playback/models/audiodevicemodel.h
	# 	cpp/playback/models/audiodevicemodel.cpp

    # #C++ Image Providers
    # SOURCES
    #     cpp/image_providers/playlistimageprovider.h
    #     cpp/image_providers/playlistimageprovider.cpp

	# 	cpp/image_providers/coverimgprovider.h
	# 	cpp/image_providers/coverimgprovider.cpp

    # #C++ QML Models
    # SOURCES
	#     cpp/models/album/albumfilterproxymodel.h
	# 	cpp/models/album/albumfilterproxymodel.cpp

	# 	cpp/models/album/albumlistmodel.h
	# 	cpp/models/album/albumlistmodel.cpp

	# 	cpp/models/album/albumsearchfilter.h
	# 	cpp/models/album/albumsearchfilter.cpp

	# 	cpp/models/song/songlistmodel.h
	# 	cpp/models/song/songlistmodel.cpp

	# 	cpp/models/song/songfilterproxymodel.h
	# 	cpp/models/song/songfilterproxymodel.cpp

	# 	cpp/models/playlist/playlistmodel.h
	# 	cpp/models/playlist/playlistmodel.cpp

	# 	cpp/models/playlist/playlistfilter.cpp
	# 	cpp/models/playlist/playlistfilter.h

	# 	cpp/models/folder/folderlistmodel.cpp
	# 	cpp/models/folder/folderlistmodel.h

	# #QML View Managers
    # SOURCES

	# 	cpp/managers/foldermanager.h
	# 	cpp/managers/foldermanager.cpp

	# 	cpp/managers/viewcontroller.h
	# 	cpp/managers/viewcontroller.cpp

	# 	cpp/managers/playlistmanager.h
	# 	cpp/managers/playlistmanager.cpp

	# 	cpp/managers/songmanager.h
	# 	cpp/managers/songmanager.cpp

	# 	cpp/managers/playbackmanager.h
	# 	cpp/managers/playbackmanager.cpp

    #     cpp/managers/downloadmanager.h
    #     cpp/managers/downloadmanager.cpp

    # #downloaders
    # SOURCES

    # cpp/downloaders/soundcloud/soundcloud.cpp
    # cpp/downloaders/soundcloud/soundcloud.h
    # cpp/downloaders/soundcloud/soundcloudmodel.h
    # cpp/downloaders/soundcloud/soundcloudmodel.cpp
    # cpp/downloaders/soundcloud/soundcloudsearchworker.h
	# cpp/downloaders/soundcloud/scplaylist.h
	# cpp/downloaders/soundcloud/scplaylist.cpp


)
if(WIN32)
    add_custom_target(kill_appcplayer
        COMMAND taskkill /IM appcplayer.exe /F || exit 0
        COMMENT "Killing previous instance of appcplayer.exe"
    )
else()  # Linux/macOS
    add_custom_target(kill_appcplayer
        COMMAND killall -9 appcplayer || true
        COMMENT "Killing previous instance of appcplayer"
    )
endif()

add_dependencies(appcplayer kill_appcplayer)


target_compile_definitions(appcplayer PRIVATE
    SC_LIB_PATH="${SC_LIB_PATH}"
	PY_LIB_PATH="${PY_LIB_PATH}"
    TAGLIB_STATIC
)

target_link_libraries(appcplayer
        PRIVATE Qt6::Quick Qt6::Multimedia Qt6::Widgets Qt6::Core
		rapidfuzz::rapidfuzz TagLib::tag pybind11::embed
		cplayer_types
    cplayer_models
    cplayer_playback
    cplayer_background
    cplayer_managers
    cplayer_image_providers
    )

# target_include_directories(appcplayer PRIVATE
# 		${CMAKE_CURRENT_SOURCE_DIR}/cpp
# 		${CMAKE_CURRENT_SOURCE_DIR}/cpp/types
# 		${CMAKE_CURRENT_SOURCE_DIR}/cpp/background
#         ${CMAKE_CURRENT_SOURCE_DIR}/cpp/downloaders
#         ${CMAKE_CURRENT_SOURCE_DIR}/cpp/downloaders/soundcloud
#         ${CMAKE_CURRENT_SOURCE_DIR}/cpp/cpp_models
# 		${CMAKE_CURRENT_SOURCE_DIR}/cpp/image_providers
# 		${CMAKE_CURRENT_SOURCE_DIR}/cpp/models
# 		${CMAKE_CURRENT_SOURCE_DIR}/cpp/models/song
# 		${CMAKE_CURRENT_SOURCE_DIR}/cpp/models/album
# 		${CMAKE_CURRENT_SOURCE_DIR}/cpp/models/playlist
# 		${CMAKE_CURRENT_SOURCE_DIR}/cpp/models/folder
# 		${CMAKE_CURRENT_SOURCE_DIR}/cpp/managers
# 		${CMAKE_CURRENT_SOURCE_DIR}/cpp/playback
# 		${CMAKE_CURRENT_SOURCE_DIR}/cpp/playback/models
# 		${CMAKE_CURRENT_SOURCE_DIR}/cpp/utility)


include(GNUInstallDirs)
install(TARGETS appcplayer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
