cmake_minimum_required(VERSION 3.20)
project(snake C)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=[sanitizer_name] [additional_options] [-g] [-OX]")

find_package(SDL2 REQUIRED)
find_package(SDL2_gfx REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_GFX_INCLUDE_DIRS})


add_executable(snake rendering/rendering.c debugmalloc.h main.c rendering/rendering.h rendering/button.c rendering/button.h rendering/Game/game.c rendering/Game/game.h rendering/Game/snake.c rendering/Game/snake.h rendering/menu.c rendering/menu.h)

target_link_libraries(snake ${SDL2_LIBRARIES} ${SDL2_GFX_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
