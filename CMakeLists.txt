cmake_minimum_required(VERSION 3.29)
project(PROJET_CSDL C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARIES})

set(CMAKE_PREFIX_PATH "C:/msys64/mingw64")


add_executable(PROJET_CSDL src/main.c
        src/tasks.c)

add_executable(main src/main.c src/tasks.c)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})

target_link_libraries(main mingw32 SDL2main SDL2 SDL2_ttf)
