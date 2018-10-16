set(MOONLIGHT_SOURCES
    libretro.c)

add_library(moonlight_libretro SHARED ${MOONLIGHT_SOURCES})
target_link_libraries(moonlight_libretro moonlight-common)
