add_subdirectory(libgamestream)

find_package(FFMPEG REQUIRED)

set(MOONLIGHT_SOURCES
    libretro.c
    video/ffmpeg.c)

add_library(moonlight_libretro SHARED ${MOONLIGHT_SOURCES})
target_link_libraries(moonlight_libretro moonlight-common)

# [AM] FIXME: Fix and then use imported target
#message("${FFMPEG_INCLUDE_DIRS}")
#message("${FFMPEG_LIBRARIES}")
target_compile_definitions(moonlight_libretro PUBLIC ${FFMPEG_INCLUDE_DIRS})
target_link_libraries(moonlight_libretro ${FFMPEG_LIBRARIES})
