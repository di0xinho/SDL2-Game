#pragma once
#include <SDL.h>
#include "GameData.hpp"

class Weapon {
public:
    Weapon();

    void init(std::shared_ptr<GameData> data, SDL_Texture* texture, SDL_FPoint startPos);
    void update(float deltaTime);
    void render(SDL_Renderer* renderer, const SDL_Rect& camera);

    SDL_Rect getRect() const;
    bool isAlive() const;
    void Kill();
    bool checkCollision(const SDL_Rect& other);

private:
    SDL_FPoint position{};
    SDL_FPoint velocity{ 300.0f, 0.0f };
    float angle = 0.0f;
    float lifetime = 5.0f;
    bool alive = true;

    SDL_Texture* texture = nullptr;
    SDL_FPoint size{ 32.0f, 32.0f };
};
