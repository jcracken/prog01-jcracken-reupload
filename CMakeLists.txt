cmake_minimum_required(VERSION 2.8.11)
project(sdl_demo)

find_package(SDL2)

set(source_files
  main.cpp 
)

include_directories (${SDL2_INCLUDE_DIRS})
add_executable (${PROJECT_NAME} ${source_files})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

