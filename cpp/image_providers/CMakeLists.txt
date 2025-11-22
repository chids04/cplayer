# cpp/image_providers/CMakeLists.txt
qt_add_library(cplayer_image_providers STATIC
    playlistimageprovider.cpp
    coverimgprovider.cpp
)

set_target_properties(cplayer_image_providers PROPERTIES
    AUTOMOC ON
)

qt_policy(SET QTP0001 NEW)
qt_policy(SET QTP0004 NEW)
qt_policy(SET QTP0005 NEW)

target_include_directories(cplayer_image_providers PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(cplayer_image_providers PUBLIC
    cplayer_types
    Qt6::Core
    Qt6::Quick
)
