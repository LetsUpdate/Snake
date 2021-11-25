cmake_minimum_required(VERSION 3.20)
project(snake C)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=[sanitizer_name] [additional_options] [-g] [-OX]")

# Find SDL2, SDL2_image and SDL2_gfx libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_gfx REQUIRED)
find_package(SDL2_ttf REQUIRED)


add_executable(snake lib/rendering.c debugmalloc.h main.c lib/rendering.h lib/Menu/button.c lib/Menu/button.h lib/Game/game.c lib/Game/game.h lib/Game/snake.h lib/Game/snake.c lib/Menu/menu.c lib/Menu/menu.h lib/save_system.h lib/save_system.c)
# Link SDL2::Main, SDL2::Image and SDL2::GFX to our project
target_link_libraries(${PROJECT_NAME} SDL2::Main SDL2::Image SDL2::GFX SDL2::TTF)

file(COPY resources DESTINATION ./)
