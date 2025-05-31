#pragma once

#include <SDL.h>
#include "StateMachine.hpp"
#include "InputManager.hpp"
#include "AssetManager.hpp"
#include <memory>

/// Struktura przechowuj�ca wszystkie kluczowe komponenty gry
struct GameData
{
    StateMachine machine;                              /// Maszyna stan�w gry
    SDL_Renderer* renderer;
    std::shared_ptr<InputManager> inputManager;        /// Manager wej�cia
    std::shared_ptr<AssetManager> assetManager;        /// Manager zasob�w (tekstury, czcionki)
};