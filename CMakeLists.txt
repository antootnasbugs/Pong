cmake_minimum_required(VERSION 3.5)
project(Pong)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(src)

file(GLOB SOURCES src/*.cpp)


add_executable(${PROJECT_NAME} ${SOURCES})

include_directories(/Users/antonino/Downloads/raylib-5.0_macos/include)
find_library(RAYLIB_LIB raylib HINTS /Users/antonino/Downloads/raylib-5.0_macos/lib)

target_link_libraries(${PROJECT_NAME} ${RAYLIB_LIB})

if(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/Info.plist
    )

    set(RESOURCE_FILES
        ${CMAKE_SOURCE_DIR}/resources/icon.icns
        ${CMAKE_SOURCE_DIR}/resources/coll_sound.wav
    )

    set_source_files_properties(${RESOURCE_FILES} PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources"
    )


     add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        $<TARGET_BUNDLE_DIR:${PROJECT_NAME}>/Contents/Resources
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/resources/icon.icns
        $<TARGET_BUNDLE_DIR:${PROJECT_NAME}>/Contents/Resources
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/resources/coll_sound.wav
        $<TARGET_BUNDLE_DIR:${PROJECT_NAME}>/Contents/Resources
    )

endif()
