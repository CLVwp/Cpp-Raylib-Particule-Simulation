cmake_minimum_required(VERSION 3.28)
project(Template-CCP-Raylib-App)

set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(Template-CCP-Raylib-App ${SOURCES}
        src/TCRA.cpp
        src/TCRA.hpp
        src/config/config.cpp
        src/state/State.hpp
        src/raygui_impl.cpp)

include_directories(rsc/raylib-5.0_win64_mingw-w64/include)

target_link_libraries(Template-CCP-Raylib-App
        ${CMAKE_SOURCE_DIR}/rsc/raylib-5.0_win64_mingw-w64/lib/libraylib.a
        -lwinmm
        -lgdi32
)

if(MINGW)
    target_link_libraries(Template-CCP-Raylib-App
            -static-libgcc
            -static-libstdc++
            -static
    )
endif()