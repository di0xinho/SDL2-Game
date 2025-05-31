#pragma once
#include <SDL.h>
#include <vector>
#include "Animation.hpp"
#include "GameData.hpp"

class Coin {
public:
    Coin();
    void init(std::shared_ptr<GameData> data, const std::vector<const char*>& framePaths, SDL_FPoint pos);
    void update(float deltaTime);
    void render(SDL_Renderer* renderer, const SDL_Rect& camera);

    SDL_Rect getRect() const;
    bool isCollected() const;
    void collect();

private:
    Animation animation;
    SDL_FPoint position;
    SDL_FPoint size = { 20.0f, 20.0f };
    bool collected = false;
};
