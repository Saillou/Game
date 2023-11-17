# Setup project
cmake_minimum_required(VERSION 3.12)

project("Game")
include(.cmake/config.cmake)

# Get sources ..
file(GLOB_RECURSE _cmake_list    CONFIGURE_DEPENDS "${CMAKE_FOLDER}/*.cmake" "./CMakeLists.txt")
file(GLOB_RECURSE _source_list   CONFIGURE_DEPENDS "${SOURCE_FOLDER}/*.c*"   "${SOURCE_FOLDER}/*.h*")
file(GLOB_RECURSE _resource_list CONFIGURE_DEPENDS "${RESOURCES_FOLDER}/*")
file(GLOB_RECURSE _external_list CONFIGURE_DEPENDS "${EXTERNAL_FOLDER}/*.c*" "${EXTERNAL_FOLDER}/*.h*")

# .. and create visual studio filters (following folders tree)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${_cmake_list})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${_source_list})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${_resource_list})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${_external_list})

# Create compilation list
add_executable(${TARGET_NAME}
    ${_cmake_list}
    ${_source_list}
    ${_resource_list}
    ${_external_list}
)

# Set solution properties
set_target_properties(${TARGET_NAME} PROPERTIES 
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_FOLDER}
    VS_STARTUP_PROJECT ${TARGET_NAME}
)

# Set search directory for headers
target_include_directories(${TARGET_NAME} PRIVATE 
    "${RESOURCES_FOLDER}/"
    "${EXTERNAL_FOLDER}/glm/"
    "${EXTERNAL_FOLDER}/glad/include/"
    "${EXTERNAL_FOLDER}/GLFW/include/"
    "${EXTERNAL_FOLDER}/freetype/include/"
)

# Add libraries by path
target_link_libraries(${TARGET_NAME} 
    debug "${EXTERNAL_FOLDER}/glfw/bin/Debug/glfw3.lib"
    debug "${EXTERNAL_FOLDER}/freetype/bin/Debug/freetype.lib"

    optimized "${EXTERNAL_FOLDER}/glfw/bin/Release/glfw3.lib"
    optimized "${EXTERNAL_FOLDER}/freetype/bin/Release/freetype.lib"
)