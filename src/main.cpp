#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <memory>
#include <iostream>
#include "GameData.hpp"
#include "MenuState.hpp"
#include "InputManager.hpp"
#include "AssetManager.hpp"
#include "GameConfig.hpp"

int main(int argc, char* argv[])
{
    // Inicjalizacja SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    if (TTF_Init() != 0)
    {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cerr << "Mix_OpenAudio Error: " << Mix_GetError() << std::endl;
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(GAME_TITLE,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN);

    if (!window)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        Mix_CloseAudio();
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer)
    {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        Mix_CloseAudio();
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Tworzenie wspó³dzielonych danych gry
    auto data = std::make_shared<GameData>();
    data->renderer = renderer;

    data->inputManager = std::make_shared<InputManager>();
    data->assetManager = std::make_shared<AssetManager>(renderer);

    // Dodanie pierwszego stanu do maszyny stanów
    data->machine.AddState(std::make_unique<MenuState>(data), true);

    bool isRunning = true;
    Uint32 lastTick = SDL_GetTicks();

    // G³ówna pêtla gry
    while (isRunning)
    {
        Uint32 currentTick = SDL_GetTicks();
        float dt = (currentTick - lastTick) / 1000.0f;
        lastTick = currentTick;

        data->machine.ProcessStateChanges();

        if (!data->machine.GetActiveState())
        {
            break; // Brak aktywnego stanu – koñczymy grê
        }

        // Obs³uga wejœcia, aktualizacja logiki i rysowanie
        data->machine.GetActiveState()->HandleInput();
        data->machine.GetActiveState()->Update(dt);
        data->machine.GetActiveState()->Draw(dt);
    }

    // Sprz¹tanie zasobów
    data->assetManager->clear();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}