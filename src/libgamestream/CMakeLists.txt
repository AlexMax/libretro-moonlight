find_package(CURL REQUIRED)
find_package(EXPAT REQUIRED)
find_package(OpenSSL REQUIRED)

set(GAMESTREAM_SOURCES
    client.c
    uuid.c)

    # client.c
    # discover.c
    # http.c
    # mkcert.c
    # sps.c
    # uuid.c
    # xml.c

add_library(gamestream STATIC ${GAMESTREAM_SOURCES})
target_link_libraries(gamestream moonlight-common libcurl EXPAT OpenSSL::SSL)

add_executable(gamestream-test test.c)
target_link_libraries(gamestream-test gamestream)
