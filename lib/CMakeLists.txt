# h264bitstream
set(H264_SRCIR "${CMAKE_CURRENT_SOURCE_DIR}/h264bitstream")
set(H264_SOURCES
    "${H264_SRCIR}/h264_nal.c"
    "${H264_SRCIR}/h264_sei.c"
    "${H264_SRCIR}/h264_stream.c")
add_library(h264bitstream STATIC ${H264_SOURCES})
target_include_directories(h264bitstream PUBLIC "${H264_SRCIR}")

# ENet Static Library
find_package(OpenSSL REQUIRED)
set(OPENSSL_USE_STATIC_LIBS TRUE)

set(ENET_SRCIR "${CMAKE_CURRENT_SOURCE_DIR}/moonlight-common-c/enet")
set(ENET_SOURCES
    "${ENET_SRCIR}/callbacks.c"
    "${ENET_SRCIR}/compress.c"
    "${ENET_SRCIR}/host.c"
    "${ENET_SRCIR}/list.c"
    "${ENET_SRCIR}/packet.c"
    "${ENET_SRCIR}/peer.c"
    "${ENET_SRCIR}/protocol.c"
    "${ENET_SRCIR}/unix.c"
    "${ENET_SRCIR}/vita.c"
    "${ENET_SRCIR}/win32.c")
add_library(enet STATIC ${ENET_SOURCES})
target_include_directories(enet PUBLIC "${ENET_SRCIR}/include")

# Reedsolomon
set(RS_SRCDIR "${CMAKE_CURRENT_SOURCE_DIR}/moonlight-common-c/reedsolomon")
add_library(reedsolomon STATIC "${RS_SRCDIR}/rs.c")
target_include_directories(reedsolomon PUBLIC "${RS_SRCDIR}")

# Moonlight
set(MOONLIGHT_SRCDIR "${CMAKE_CURRENT_SOURCE_DIR}/moonlight-common-c/src")
set(MOONLIGHT_SOURCES
    "${MOONLIGHT_SRCDIR}/AudioStream.c"
    "${MOONLIGHT_SRCDIR}/ByteBuffer.c"
    "${MOONLIGHT_SRCDIR}/Connection.c"
    "${MOONLIGHT_SRCDIR}/ControlStream.c"
    "${MOONLIGHT_SRCDIR}/FakeCallbacks.c"
    "${MOONLIGHT_SRCDIR}/InputStream.c"
    "${MOONLIGHT_SRCDIR}/LinkedBlockingQueue.c"
    "${MOONLIGHT_SRCDIR}/Misc.c"
    "${MOONLIGHT_SRCDIR}/Platform.c"
    "${MOONLIGHT_SRCDIR}/PlatformSockets.c"
    "${MOONLIGHT_SRCDIR}/RtpFecQueue.c"
    "${MOONLIGHT_SRCDIR}/RtpReorderQueue.c"
    "${MOONLIGHT_SRCDIR}/RtspConnection.c"
    "${MOONLIGHT_SRCDIR}/RtspParser.c"
    "${MOONLIGHT_SRCDIR}/SdpGenerator.c"
    "${MOONLIGHT_SRCDIR}/VideoDepacketizer.c"
    "${MOONLIGHT_SRCDIR}/VideoStream.c")
add_library(moonlight-common STATIC ${MOONLIGHT_SOURCES})
target_include_directories(moonlight-common PUBLIC "${MOONLIGHT_SRCDIR}")
target_link_libraries(moonlight-common enet reedsolomon OpenSSL::Crypto)
