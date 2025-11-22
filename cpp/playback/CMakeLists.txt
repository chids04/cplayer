# cpp/playback/CMakeLists.txt

qt_add_library(cplayer_playback STATIC
    mediaplayercontroller.cpp
    nowplaying.cpp
    queue.cpp
    models/queuemodel.cpp
    models/queuemodelfilter.cpp
    models/audiodevicemodel.cpp
)

qt_policy(SET QTP0001 NEW)
qt_policy(SET QTP0004 NEW)
qt_policy(SET QTP0005 NEW)



set_target_properties(cplayer_playback PROPERTIES
    AUTOMOC ON
)

qt_add_qml_module(cplayer_playback
    URI cpp.playback
    VERSION 1.0
    SOURCES
        mediaplayercontroller.h mediaplayercontroller.cpp
        nowplaying.h nowplaying.cpp
        queue.h queue.cpp
        models/queuemodel.h models/queuemodel.cpp
        models/queuemodelfilter.h models/queuemodelfilter.cpp
        models/audiodevicemodel.h models/audiodevicemodel.cpp

    DEPENDENCIES TARGET cplayer_types
    DEPENDENCIES TARGET cplayer_models

)

target_include_directories(cplayer_playback PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/models
)

target_link_libraries(cplayer_playback PUBLIC
    cplayer_types
    Qt6::Core
    Qt6::Multimedia
    Qt6::Qml
)
