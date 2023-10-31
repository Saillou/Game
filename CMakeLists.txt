cmake_minimum_required(VERSION 3.14)

project ("Game")
include(.cmake/config.cmake)

add_executable (${TARGET_NAME}
    ${SOURCE_FOLDER}/main.cpp
)

set_target_properties(${TARGET_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_PATH}"
)