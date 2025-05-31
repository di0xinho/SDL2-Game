#pragma once


#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "State.hpp"
#include "GameData.hpp"
#include "GameConfig.hpp"
#include <memory>
#include <iostream>


class PauseState : public State {
public:
    PauseState(std::shared_ptr<GameData> data);
    ~PauseState();

    void Init() override;
    void HandleInput() override;
    void Update(float deltaTime) override;
    void Draw(float deltaTime) override;

private:
    std::shared_ptr<GameData> data;

    TTF_Font* font = nullptr;
    SDL_Color titleColor = { 255, 255, 255 };
    SDL_Color infoColor = { 150, 150, 150 };
    bool initialized = false;

    void initFont();
};