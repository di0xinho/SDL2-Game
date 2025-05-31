#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class HUD {
public:
    HUD(SDL_Renderer* renderer, TTF_Font* font);

    void updateScore(int score);
    void updateLives(int lives);
    void render(int screenWidth);

private:
    SDL_Renderer* renderer;
    TTF_Font* font;

    int currentScore = 0;
    int currentLives = 3;
};
