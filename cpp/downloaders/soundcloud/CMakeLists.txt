qt_add_library(cplayer_soundcloud STATIC
    scplaylist.cpp
    soundcloud.cpp
    soundcloudmodel.cpp
)

set_target_properties(cplayer_soundcloud PROPERTIES
    AUTOMOC ON
)

qt_policy(SET QTP0001 NEW)
qt_policy(SET QTP0004 NEW)
qt_policy(SET QTP0005 NEW)

qt_add_qml_module(cplayer_soundcloud
    URI cpp.downloaders.soundcloud
    VERSION 1.0
    SOURCES
    scplaylist.h
    soundcloud.h
    soundcloudmodel.h
    scplaylist.cpp
    soundcloud.cpp
    soundcloudmodel.cpp
    soundcloudsearchworker.h
)


target_include_directories(cplayer_soundcloud PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(cplayer_soundcloud PRIVATE
     Qt6::Core
     Qt6::Quick
     pybind11::embed
)
