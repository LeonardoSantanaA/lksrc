cmake_minimum_required(VERSION 3.7)
project(LkSouls)


set(CMAKE_CXX_STANDARD 17)

# Search all files in src and thirdpart/TinyXML directories
file(GLOB_RECURSE SOURCES
    ${CMAKE_SOURCE_DIR}/src/*h
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/thirdpart/TinyXML/*.cpp
)

# Include directories
include_directories(glad/include/)
include_directories(${CMAKE_SOURCE_DIR}/src/header)
include_directories(${CMAKE_SOURCE_DIR}/thirdpart/TinyXML/includes)

# add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Add compiler errors/warnings flags
#target_compile_options(${PROJECT_NAME} PRIVATE $<$<C_COMPILER_ID:MSVC>:/W4 /WX>)
#target_compile_options(${PROJECT_NAME} PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -Werror>)


list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2/)

# Find and link SDL2
find_package(SDL2 REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

# Find and link SDL2_Image
find_package(SDL2_image REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_IMAGE_LIBRARIES})

# Find and link SDL2_TTF
find_package(SDL2_ttf REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_TTF_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_TTF_LIBRARIES})

# Find and link SDL2_Mixer
find_package(SDL2_mixer REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_MIXER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_MIXER_LIBRARIES})

message(STATUS "SDL2_INCLUDE_DIRS: ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2_TTF_INCLUDE_DIRS: ${SDL2_TTF_INCLUDE_DIRS}")
message(STATUS "SDL2_IMAGE_INCLUDE_DIRS: ${SDL2_IMAGE_INCLUDE_DIRS}")
message(STATUS "SDL2_MIXER_INCLUDE_DIRS: ${SDL2_MIXER_INCLUDE_DIRS}")

message(STATUS "SDL2_LIBRARIES: ${SDL2_LIBRARY}")
message(STATUS "SDL2_TTF_LIBRARIES: ${SDL2_TTF_LIBRARIES}")
message(STATUS "SDL2_IMAGE_LIBRARIES: ${SDL2_IMAGE_LIBRARIES}")
message(STATUS "SDL2_MIXER_LIBRARIES: ${SDL2_MIXER_LIBRARIES}")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "RELEASE BUILD, TURN OFF WINDOWS TERMINAL")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()