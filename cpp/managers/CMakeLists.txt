# cpp/managers/CMakeLists.txt
qt_add_library(cplayer_managers STATIC
    foldermanager.cpp
    viewcontroller.cpp
    playlistmanager.cpp
    songmanager.cpp
    playbackmanager.cpp
    downloadmanager.cpp
)

set_target_properties(cplayer_managers PROPERTIES
    AUTOMOC ON
)

qt_policy(SET QTP0001 NEW)
qt_policy(SET QTP0004 NEW)
qt_policy(SET QTP0005 NEW)

qt_add_qml_module(cplayer_managers
    URI cpp.managers
    VERSION 1.0
    SOURCES
        foldermanager.h foldermanager.cpp
        viewcontroller.h viewcontroller.cpp
        playlistmanager.h playlistmanager.cpp
        songmanager.h songmanager.cpp
        playbackmanager.h playbackmanager.cpp
        downloadmanager.h downloadmanager.cpp
)

target_include_directories(cplayer_managers PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(cplayer_managers PUBLIC
    cplayer_models
    cplayer_playback
    cplayer_types
    Qt6::Core
    Qt6::Qml
)
