# FindFFMPEG
# --------
# Finds FFmpeg libraries
#
# This module will first look for the required library versions on the system.
# If they are not found, it will fall back to downloading and building kodi's own version
#
# --------
# FFMPEG_PATH - use external ffmpeg not found in system paths
#               usage: -DFFMPEG_PATH=/path/to/ffmpeg_install_prefix
#
# WITH_FFMPEG - use external ffmpeg not found in system paths
#               WARNING: this option is for developers as it will _disable ffmpeg version checks_!
#               Consider using FFMPEG_PATH instead, which _does_ check library versions
#               usage: -DWITH_FFMPEG=/path/to/ffmpeg_install_prefix
#
# --------
# This module will define the following variables:
#
# FFMPEG_FOUND - system has FFmpeg
# FFMPEG_INCLUDE_DIRS - FFmpeg include directory
# FFMPEG_LIBRARIES - FFmpeg libraries
# FFMPEG_LDFLAGS - linker flags
#
# and the following imported targets::
#
# ffmpeg  - The FFmpeg libraries
# --------
#

# external FFMPEG
if(NOT ENABLE_INTERNAL_FFMPEG OR KODI_DEPENDSBUILD)
  if(FFMPEG_PATH)
    list(APPEND CMAKE_PREFIX_PATH ${FFMPEG_PATH})
  endif()

  include(FindPkgConfig)
  if(PKG_CONFIG_FOUND)
    pkg_check_modules(PC_FFMPEG libavcodec libavfilter libavformat libavutil libswscale libswresample libpostproc)
    string(REGEX REPLACE "framework;" "framework " PC_FFMPEG_LDFLAGS "${PC_FFMPEG_LDFLAGS}")
  endif()

  find_path(FFMPEG_INCLUDE_DIRS libavcodec/avcodec.h libavfilter/avfilter.h libavformat/avformat.h
                                libavutil/avutil.h libswscale/swscale.h libpostproc/postprocess.h
            PATH_SUFFIXES ffmpeg
            PATHS ${PC_FFMPEG_INCLUDE_DIRS}
            NO_DEFAULT_PATH)
  find_path(FFMPEG_INCLUDE_DIRS libavcodec/avcodec.h libavfilter/avfilter.h libavformat/avformat.h
                                libavutil/avutil.h libswscale/swscale.h libpostproc/postprocess.h)

  find_library(FFMPEG_LIBAVCODEC
               NAMES avcodec libavcodec
               PATH_SUFFIXES ffmpeg/libavcodec
               PATHS ${PC_FFMPEG_libavcodec_LIBDIR}
               NO_DEFAULT_PATH)
  find_library(FFMPEG_LIBAVCODEC NAMES avcodec libavcodec PATH_SUFFIXES ffmpeg/libavcodec)

  find_library(FFMPEG_LIBAVFILTER
               NAMES avfilter libavfilter
               PATH_SUFFIXES ffmpeg/libavfilter
               PATHS ${PC_FFMPEG_libavfilter_LIBDIR}
               NO_DEFAULT_PATH)
  find_library(FFMPEG_LIBAVFILTER NAMES avfilter libavfilter PATH_SUFFIXES ffmpeg/libavfilter)

  find_library(FFMPEG_LIBAVFORMAT
               NAMES avformat libavformat
               PATH_SUFFIXES ffmpeg/libavformat
               PATHS ${PC_FFMPEG_libavformat_LIBDIR}
               NO_DEFAULT_PATH)
  find_library(FFMPEG_LIBAVFORMAT NAMES avformat libavformat PATH_SUFFIXES ffmpeg/libavformat)

  find_library(FFMPEG_LIBAVUTIL
               NAMES avutil libavutil
               PATH_SUFFIXES ffmpeg/libavutil
               PATHS ${PC_FFMPEG_libavutil_LIBDIR}
               NO_DEFAULT_PATH)
  find_library(FFMPEG_LIBAVUTIL NAMES avutil libavutil PATH_SUFFIXES ffmpeg/libavutil)

  find_library(FFMPEG_LIBSWSCALE
               NAMES swscale libswscale
               PATH_SUFFIXES ffmpeg/libswscale
               PATHS ${PC_FFMPEG_libswscale_LIBDIR}
               NO_DEFAULT_PATH)
  find_library(FFMPEG_LIBSWSCALE NAMES swscale libswscale PATH_SUFFIXES ffmpeg/libswscale)

  find_library(FFMPEG_LIBSWRESAMPLE
               NAMES swresample libswresample
               PATH_SUFFIXES ffmpeg/libswresample
               PATHS ${PC_FFMPEG_libswresample_LIBDIR}
               NO_DEFAULT_PATH)
  find_library(FFMPEG_LIBSWRESAMPLE NAMES NAMES swresample libswresample PATH_SUFFIXES ffmpeg/libswresample)

  find_library(FFMPEG_LIBPOSTPROC
               NAMES postproc libpostproc
               PATH_SUFFIXES ffmpeg/libpostproc
               PATHS ${PC_FFMPEG_libpostproc_LIBDIR}
               NO_DEFAULT_PATH)
  find_library(FFMPEG_LIBPOSTPROC NAMES postproc libpostproc PATH_SUFFIXES ffmpeg/libpostproc)

  if((PC_FFMPEG_FOUND
      AND PC_FFMPEG_libavcodec_VERSION
      AND PC_FFMPEG_libavfilter_VERSION
      AND PC_FFMPEG_libavformat_VERSION
      AND PC_FFMPEG_libavutil_VERSION
      AND PC_FFMPEG_libswscale_VERSION
      AND PC_FFMPEG_libswresample_VERSION
      AND PC_FFMPEG_libpostproc_VERSION)
     OR WIN32)
    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(FFMPEG
                                      REQUIRED_VARS FFMPEG_INCLUDE_DIRS
                                                    FFMPEG_LIBAVCODEC
                                                    FFMPEG_LIBAVFILTER
                                                    FFMPEG_LIBAVFORMAT
                                                    FFMPEG_LIBAVUTIL
                                                    FFMPEG_LIBSWSCALE
                                                    FFMPEG_LIBSWRESAMPLE
                                                    FFMPEG_LIBPOSTPROC
                                      FAIL_MESSAGE "FFmpeg not found, please consider using -DENABLE_INTERNAL_FFMPEG=ON")

  else()
    message(STATUS "FFmpeg not found, falling back to internal build")
    unset(FFMPEG_INCLUDE_DIRS)
    unset(FFMPEG_INCLUDE_DIRS CACHE)
    unset(FFMPEG_LIBRARIES)
    unset(FFMPEG_LIBRARIES CACHE)
  endif()

  if(FFMPEG_FOUND)
    set(FFMPEG_LDFLAGS ${PC_FFMPEG_LDFLAGS} CACHE STRING "ffmpeg linker flags")

    # check if ffmpeg libs are statically linked
    set(FFMPEG_LIB_TYPE SHARED)
    foreach(_fflib IN LISTS FFMPEG_LIBRARIES)
      if(${_fflib} MATCHES ".+\.a$" AND PC_FFMPEG_STATIC_LDFLAGS)
        set(FFMPEG_LDFLAGS ${PC_FFMPEG_STATIC_LDFLAGS} CACHE STRING "ffmpeg linker flags" FORCE)
        set(FFMPEG_LIB_TYPE STATIC)
        break()
      endif()
    endforeach()

    set(FFMPEG_LIBRARIES ${FFMPEG_LIBAVCODEC} ${FFMPEG_LIBAVFILTER}
                         ${FFMPEG_LIBAVFORMAT} ${FFMPEG_LIBAVUTIL}
                         ${FFMPEG_LIBSWSCALE} ${FFMPEG_LIBSWRESAMPLE}
                         ${FFMPEG_LIBPOSTPROC} ${FFMPEG_LDFLAGS})

    if(NOT TARGET ffmpeg)
    # [AM] Doesn't work (LIBRARIES isn't filled out)
    add_library(ffmpeg ${FFMPEG_LIB_TYPE} IMPORTED)
      set_target_properties(ffmpeg PROPERTIES
                                   FOLDER "External Projects"
                                   IMPORTED_LOCATION "${FFMPEG_LIBRARIES}"
                                   INTERFACE_INCLUDE_DIRECTORIES "${FFMPEG_INCLUDE_DIRS}"
                                   INTERFACE_LINK_LIBRARIES "${FFMPEG_LDFLAGS}")
    endif()
  endif()
endif()

mark_as_advanced(FFMPEG_INCLUDE_DIRS FFMPEG_LIBRARIES FFMPEG_LDFLAGS FFMPEG_FOUND)
