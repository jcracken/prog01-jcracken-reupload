cmake_minimum_required(VERSION 2.8.11)
project(basic_sdl)

find_package(SDL2)

set(basic_sdl_sources
  main.cpp 
)

include_directories (${SDL2_INCLUDE_DIRS})
add_executable (${PROJECT_NAME} ${basic_sdl_sources})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

