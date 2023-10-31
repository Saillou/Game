cmake_minimum_required(VERSION 3.14)

project ("Game")
include(.cmake/config.cmake)

# Get sources
file(GLOB_RECURSE _config_list
    "./CMakeLists.txt"
)
file(GLOB_RECURSE _source_list 
    "${SOURCE_FOLDER}/*.c*"
    "${SOURCE_FOLDER}/*.h*"
)
file(GLOB_RECURSE _external_list
    "${EXTERNAL_FOLDER}/*.c*"
    "${EXTERNAL_FOLDER}/*.h*"
)

# Create visual studio filters following folders
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${_config_list})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${_source_list})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${_external_list})

# Create executable compile recipe
add_executable (${TARGET_NAME}
    ${_config_list}
    ${_source_list}
    ${_external_list}
)

# Set solution properties
set_target_properties(${TARGET_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_PATH}"
    VS_STARTUP_PROJECT "Game"
)