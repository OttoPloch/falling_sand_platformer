cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(app
src/main.cpp
src/game.cpp
src/window_preset.cpp
src/get_random_number.cpp
src/world.cpp
src/grid.cpp
src/cell.cpp
src/cell_manager.cpp
src/cell_preset.cpp
src/behavior.cpp
src/behaviors/falling_behavior.cpp
src/behaviors/settling_behavior.cpp
src/behaviors/flowing_behavior.cpp
src/behaviors/heavy_behavior.cpp
src/behaviors/spreading_behavior.cpp
src/behaviors/flaming_behavior.cpp
src/behaviors/flammable_behavior.cpp
src/behaviors/static_behavior.cpp
src/behaviors/burning_behavior.cpp
src/behaviors/cooling_behavior.cpp
)
target_compile_features(app PRIVATE cxx_std_17)
target_link_libraries(app PRIVATE SFML::Graphics)
