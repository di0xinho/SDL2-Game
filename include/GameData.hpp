#pragma once

#include <SDL.h>
#include "StateMachine.hpp"
#include "InputManager.hpp"
#include "AssetManager.hpp"
#include <memory>

/// Struktura przechowuj¹ca wszystkie kluczowe komponenty gry
struct GameData
{
    StateMachine machine;                              /// Maszyna stanów gry
    SDL_Renderer* renderer;
    std::shared_ptr<InputManager> inputManager;        /// Manager wejœcia
    std::shared_ptr<AssetManager> assetManager;        /// Manager zasobów (tekstury, czcionki)
};