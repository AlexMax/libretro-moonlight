find_package(CURL REQUIRED)
find_package(EXPAT REQUIRED)
find_package(OpenSSL REQUIRED)

set(GAMESTREAM_SOURCES
    client.c
    discover.c
    http.c
    mkcert.c
    sps.c
    xml.c)

add_library(gamestream STATIC ${GAMESTREAM_SOURCES})
target_link_libraries(gamestream moonlight-common libcurl EXPAT OpenSSL::SSL)
