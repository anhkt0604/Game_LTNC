cmake_minimum_required(VERSION 3.27)
project(Game_LTNC)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(Game_LTNC main.cpp)

target_link_libraries(Game_LTNC ${SDL2_LIBRARIES})