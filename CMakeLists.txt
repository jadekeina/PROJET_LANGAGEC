cmake_minimum_required(VERSION 3.29)
project(PROJET_CSDL C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)



include_directories("C:/SDL2_ttf-devel-2.20.2-mingw/SDL2_ttf-2.20.2/x86_64-w64-mingw32/include")
link_directories("C:/SDL2_ttf-devel-2.20.2-mingw/SDL2_ttf-2.20.2/x86_64-w64-mingw32/lib")


set (SDL2_PATH "C:/SDL2-devel-2.30.10-mingw/SDL2-2.30.10/x86_64-w64-mingw32")

find_package(SDL2_ttf REQUIRED)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARIES})



add_executable(PROJET_CSDL src/main.c
        src/tasks.c)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})

