set(MOONLIGHT_SOURCES)

add_library(moonlight_libretro SHARED)
target_link_libraries(moonlight_libretro moonlight-common-c)
