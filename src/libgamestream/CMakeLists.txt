find_package(CURL REQUIRED)
find_package(EXPAT REQUIRED)
find_package(OpenSSL REQUIRED)

set(GAMESTREAM_SOURCES
    client.c
    # discover.c # Not cross-platform
    http.c
    mkcert.c
    sps.c
    uuid.c
    xml.c)

add_library(gamestream STATIC ${GAMESTREAM_SOURCES})
target_include_directories(gamestream PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(gamestream moonlight-common h264bitstream CURL::libcurl EXPAT::EXPAT OpenSSL::SSL)
