# cpp/types/CMakeLists.txt

qt_add_library(cplayer_types STATIC
    song.cpp
    album.cpp
    folder.cpp
    playlist.cpp
    songdata.cpp
)

set_target_properties(cplayer_types PROPERTIES
    AUTOMOC ON
)

qt_policy(SET QTP0001 NEW)

qt_add_qml_module(cplayer_types
    URI cplayer.types
    VERSION 1.0
    SOURCES
        song.h song.cpp
        album.h album.cpp
        folder.h folder.cpp
        playlist.h playlist.cpp
        songdata.h songdata.cpp
)

target_include_directories(cplayer_types PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(cplayer_types PUBLIC
    Qt6::Core
    Qt6::Qml
    Qt6::Gui
)