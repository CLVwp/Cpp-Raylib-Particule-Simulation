cmake_minimum_required(VERSION 3.28)
project(Beta)

set(CMAKE_CXX_STANDARD 23)

add_executable(${PROJECT_NAME} ${SOURCES}
        src/main.cpp
        src/TCRA.cpp
        src/TCRA.hpp
        src/raygui_impl.cpp

        src/config/config.cpp
        src/config/config.hpp

        src/state/State.hpp
        src/state/particule_render_test.cpp
        src/state/particule_render_test.hpp

        src/state/MainMenuState.cpp
        src/state/MainMenuState.hpp)


include_directories(rsc/raylib-5.0_win64_mingw-w64/include)

target_link_libraries(${PROJECT_NAME}
        ${CMAKE_SOURCE_DIR}/rsc/raylib-5.0_win64_mingw-w64/lib/libraylib.a
        -lwinmm
        -lgdi32
)

if(MINGW)
    target_link_libraries(${PROJECT_NAME}
            -static-libgcc
            -static-libstdc++
            -static
    )
endif()