cmake_minimum_required(VERSION 2.8.11)
project(sdl_demo)

if(MSVC)
    # Sets the compilation flags to report warnings through Level 4. We used to use "-Wall" until
    # the MSVC compiler started freaking out all the time about secure scanf, etc.
    set( CMAKE_CXX_FLAGS "-W4" )
    set(CMAKE_DEBUG_POSTFIX "d")
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
    add_definitions(-D_CRT_NONSTDC_NO_DEPRECATE)
else()
    # adds debug information for all other OSs
    add_definitions(-Wall -g -std=c++11)
endif()

add_definitions(-D_CMAKE_PREFIX_PATH=${source_files})

find_package(SDL2)

set(source_files
  main.cpp 
)

include_directories (${SDL2_INCLUDE_DIRS})
add_executable (${PROJECT_NAME} ${source_files})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

