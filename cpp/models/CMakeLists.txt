# cpp/models/CMakeLists.txt
qt_add_library(cplayer_models STATIC
    # Song models
    song/songlistmodel.cpp
    song/songfilterproxymodel.cpp
    
    # Album models
    album/albumlistmodel.cpp
    album/albumfilterproxymodel.cpp
    album/albumsearchfilter.cpp
    
    # Playlist models
    playlist/playlistmodel.cpp
    playlist/playlistfilter.cpp
    
    # Folder models
    folder/folderlistmodel.cpp
)

set_target_properties(cplayer_models PROPERTIES
    AUTOMOC ON
)

qt_policy(SET QTP0001 NEW)

qt_add_qml_module(cplayer_models
    URI cplayer.models
    VERSION 1.0
    SOURCES
        # Song models
        song/songlistmodel.h song/songlistmodel.cpp
        song/songfilterproxymodel.h song/songfilterproxymodel.cpp
        
        # Album models
        album/albumlistmodel.h album/albumlistmodel.cpp
        album/albumfilterproxymodel.h album/albumfilterproxymodel.cpp
        album/albumsearchfilter.h album/albumsearchfilter.cpp
        
        # Playlist models
        playlist/playlistmodel.h playlist/playlistmodel.cpp
        playlist/playlistfilter.h playlist/playlistfilter.cpp
        
        # Folder models
        folder/folderlistmodel.h folder/folderlistmodel.cpp

        DEPENDENCIES TARGET cplayer_types
)

target_include_directories(cplayer_models PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/song
    ${CMAKE_CURRENT_SOURCE_DIR}/album
    ${CMAKE_CURRENT_SOURCE_DIR}/playlist
    ${CMAKE_CURRENT_SOURCE_DIR}/folder
)

target_link_libraries(cplayer_models PUBLIC
    cplayer_types
    cplayer_managers
    cplayer_playback
    Qt6::Core
    Qt6::Qml
    rapidfuzz::rapidfuzz
)