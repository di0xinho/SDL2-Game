#pragma once

#include <memory>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "State.hpp"
#include "GameData.hpp"
#include "GameConfig.hpp"
#include "PlayState.hpp"
#include <iostream>

class GameOverState : public State {
public:
    /// Konstruktor przyjmuj�cy informacj� o wygranej i ko�cowym wyniku oraz wska�nik na dane gry
    GameOverState(std::shared_ptr<GameData> data, bool win, int finalScore);
    ~GameOverState();

    void Init() override;
    void HandleInput() override;
    void Update(float deltaTime) override;
    void Draw(float deltaTime) override;

private:
    std::shared_ptr<GameData> data;
    bool win;
    int score;

    TTF_Font* font = nullptr;
    SDL_Texture* backgroundTexture = nullptr;
    Mix_Chunk* gameOverSound = nullptr;
    bool initialized = false;

    void loadAssets();
};