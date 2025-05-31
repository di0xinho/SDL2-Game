#pragma once

#include <SDL.h>
#include "GameData.hpp"
#include "GameConfig.hpp"
#include <cmath>

class Trophy {
public:
    Trophy();

    void init(std::shared_ptr<GameData> data);
    void setPosition(float x, float y);
    void update(float deltaTime);
    void render(SDL_Renderer* renderer, const SDL_Rect& camera);
    SDL_Rect getRect() const;
    SDL_FPoint getSize() const;

private:
    SDL_Texture* texture = nullptr;
    SDL_FPoint basePosition;
    SDL_FPoint currentPosition;
    SDL_FPoint size = { 200.0f, 200.0f };
    float oscillationTime = 0.0f;
};
