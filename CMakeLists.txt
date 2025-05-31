cmake_minimum_required(VERSION 3.28)
project(SDL2_Game LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

# Pobranie SDL2
FetchContent_Declare(SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.30.10 
    GIT_SHALLOW ON
    SYSTEM
)

# Pobranie SDL2_image
FetchContent_Declare(SDL2_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG release-2.8.4 
    GIT_SHALLOW ON
    SYSTEM
)

# Pobranie SDL2_ttf
FetchContent_Declare(SDL2_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG release-2.24.0
    GIT_SHALLOW ON
    SYSTEM
)

# Pobranie SDL2_mixer
FetchContent_Declare(SDL2_mixer
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
    GIT_TAG release-2.8.0
    GIT_SHALLOW ON
    SYSTEM
)

FetchContent_MakeAvailable(SDL2 SDL2_image SDL2_ttf SDL2_mixer)

# Dodanie wsparcia dla OpenGL
find_package(OpenGL REQUIRED)

add_executable(main "src/main.cpp" "src/StateMachine.cpp" "src/MenuState.cpp" "src/AssetManager.cpp" "src/InputManager.cpp" "src/PauseState.cpp" "src/GameOverState.cpp" "src/PlayState.cpp" "src/Animation.cpp" "src/Player.cpp" "src/Coin.cpp" "src/HUD.cpp" "src/Enemy.cpp" "src/Weapon.cpp" "src/Trophy.cpp")

target_compile_features(main PRIVATE cxx_std_17)

# Linkowanie bibliotek
target_link_libraries(main
    PRIVATE
        SDL2::SDL2
        SDL2::SDL2main
        SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf
        SDL2_mixer::SDL2_mixer
        OpenGL::GL
)

# Nagłówki
target_include_directories(main PRIVATE include)
