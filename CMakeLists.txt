cmake_minimum_required(VERSION 3.20)
project(snake C)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=[sanitizer_name] [additional_options] [-g] [-OX]")


find_package(SDL2 REQUIRED)
find_package(SDL2_gfx REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_GFX_INCLUDE_DIRS})
include_directories(${SDL2_TTF_INCLUDE_DIRS})


add_executable(snake lib/rendering.c debugmalloc.h main.c lib/rendering.h lib/Menu/button.c lib/Menu/button.h lib/Game/game.c lib/Game/game.h lib/Game/snake.h lib/Game/snake.c  lib/Menu/menu.c lib/Menu/menu.h lib/save_system.h lib/save_system.c)

target_link_libraries(snake ${SDL2_LIBRARIES} ${SDL2_GFX_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
file(COPY resources DESTINATION ./)
