# cpp/background/CMakeLists.txt
qt_add_library(cplayer_background STATIC
    musicscanner.cpp
)

qt_policy(SET QTP0001 NEW)
qt_policy(SET QTP0004 NEW)
qt_policy(SET QTP0005 NEW)

set_target_properties(cplayer_background PROPERTIES
    AUTOMOC ON
)

target_include_directories(cplayer_background PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}

)

target_link_libraries(cplayer_background PUBLIC
    cplayer_types
    cplayer_image_providers
    Qt6::Core
    TagLib::tag
)
