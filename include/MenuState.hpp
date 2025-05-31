#pragma once

#include <memory>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "State.hpp"
#include "GameData.hpp"
#include "GameConfig.hpp"
#include "PlayState.hpp"

class MenuState : public State {
public:
    MenuState(std::shared_ptr<GameData> data);
    ~MenuState();

    void Init() override;
    void HandleInput() override;
    void Update(float deltaTime) override;
    void Draw(float deltaTime) override;

private:
    std::shared_ptr<GameData> data;

    SDL_Texture* backgroundTexture = nullptr;
    SDL_Texture* playButtonTexture = nullptr;
    TTF_Font* font = nullptr;
    Mix_Music* menuMusic = nullptr;

    SDL_Rect playButtonRect{};

    float buttonScale = 0.5f;
    bool initialized = false;
    const int fontSize = 32;
};