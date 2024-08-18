cmake_minimum_required(VERSION 3.27)
project(Game_LTNC)

set(CMAKE_CXX_STANDARD 17)

#set(SDL2_INCLUDE_DIR "D:/UET/SDL/include")
#SET(SDL2_LIB_DIR "D:/UET/SDL/lib/x86")

#set(SDL_Image_INCLUDE_DIR "D:/UET/SDL_image/include")
#SET(SDL_Image_LIB_DIR "D:/UET/SDL_image/lib/x86")

SET(SDL2_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL/include)
SET(SDL2_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL/lib/x86)

SET(SDL_Image_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL_image/include)
SET(SDL_Image_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL_image/lib/x86)

SET(SDL_TTF_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL_ttf/include)
SET(SDL_TTF_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL_ttf/lib/x86)

SET(SDL_MIXER_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL_mixer/include)
SET(SDL_MIXER_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL_mixer/lib/x86)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

include_directories(${SDL_Image_INCLUDE_DIR})
link_directories(${SDL_Image_LIB_DIR})

include_directories(${SDL_TTF_INCLUDE_DIR})
link_directories(${SDL_TTF_LIB_DIR})

include_directories(${SDL_MIXER_INCLUDE_DIR})
link_directories(${SDL_MIXER_LIB_DIR})

add_executable(Game_LTNC src/main.cpp
        src/gameObject.cpp
        src/header/gameObject.h
        src/map.cpp
        src/header/map.h
        src/header/utils.h
        src/utils.cpp
        src/character.cpp
        src/header/character.h
        src/timer.cpp
        src/header/timer.h
        src/threat.cpp
        src/header/threat.h
        src/item.cpp
        src/header/item.h
        src/Explosion.cpp
        src/text.cpp
        src/header/text.h
        src/header/Image.h
        src/Button.cpp
        src/header/Button.h
)

target_link_libraries(Game_LTNC SDL2main SDL2 SDL2_image SDL2_ttf SDL2_mixer)
