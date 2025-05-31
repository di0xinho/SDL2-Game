#pragma once
#include <SDL.h>
#include <vector>
#include "Animation.hpp"
#include "GameData.hpp"

class Enemy {
public:
    Enemy();

    void init(std::shared_ptr<GameData> data, const std::vector<const char*>& framePaths, SDL_FPoint pos, float range);
    void update(float deltaTime);
    void render(SDL_Renderer* renderer, const SDL_Rect& camera);

    SDL_Rect getRect() const;

    void setHitSound(Mix_Chunk* sound);
    void Hit();
    void Kill();
    bool IsAlive() const;

private:
    Animation animation;
    SDL_FPoint position;
    SDL_FPoint size = { 50.0f, 50.0f };
    float speed = 50.0f;
    float minX = 0.0f;
    float maxX = 0.0f;
    int direction = 1;

    Mix_Chunk* ouchSound = nullptr;

    int health = 3;
    float hitTimer = 0.0f;
    float hitDuration = 0.2f;
    bool alive = true;
};
