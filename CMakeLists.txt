cmake_minimum_required(VERSION 3.16...3.26)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/common/bootstrap.cmake" NO_POLICY_SCOPE)

project(${_name} VERSION ${_version})

option(ENABLE_FRONTEND_API "Use obs-frontend-api for UI functionality" OFF)
option(ENABLE_QT "Use Qt functionality" OFF)

include(compilerconfig)
include(defaults)
include(helpers)

add_library(${CMAKE_PROJECT_NAME} MODULE)

find_package(libobs REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE OBS::libobs)

if(ENABLE_FRONTEND_API)
  find_package(obs-frontend-api REQUIRED)
  target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE OBS::obs-frontend-api)
endif()

if(ENABLE_QT)
  find_package(Qt6 COMPONENTS Widgets Core)
  target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets)
  target_compile_options(
    ${CMAKE_PROJECT_NAME} PRIVATE $<$<C_COMPILER_ID:Clang,AppleClang>:-Wno-quoted-include-in-framework-header
                                  -Wno-comma>)
  set_target_properties(
    ${CMAKE_PROJECT_NAME}
    PROPERTIES AUTOMOC ON
               AUTOUIC ON
               AUTORCC ON)
endif()

target_sources(
        ${CMAKE_PROJECT_NAME} PRIVATE
        src/plugin-main.c
        src/audio-device-enum.c
        src/audio-device-enum.h
        src/mac-audio.c
        src/mac-display-capture.m
        src/mac-sck-audio-capture.m
        src/mac-sck-common.h
        src/mac-sck-common.m
        src/mac-sck-video-capture.m
        src/mac-window-capture.m
        src/plugin-main.c
        src/window-utils.h
        src/window-utils.m
)

target_link_libraries(
        ${CMAKE_PROJECT_NAME}
        PRIVATE OBS::libobs
        "$<LINK_LIBRARY:FRAMEWORK,AudioUnit.framework>"
        "$<LINK_LIBRARY:FRAMEWORK,Cocoa.framework>"
        "$<LINK_LIBRARY:FRAMEWORK,CoreAudio.framework>"
        "$<LINK_LIBRARY:FRAMEWORK,CoreFoundation.framework>"
        "$<LINK_LIBRARY:FRAMEWORK,CoreMedia.framework>"
        "$<LINK_LIBRARY:FRAMEWORK,CoreVideo.framework>"
        "$<LINK_LIBRARY:FRAMEWORK,IOSurface.framework>"
        "$<LINK_LIBRARY:WEAK_FRAMEWORK,ScreenCaptureKit.framework>")

set_target_properties_plugin(${CMAKE_PROJECT_NAME} PROPERTIES OUTPUT_NAME ${_name})
