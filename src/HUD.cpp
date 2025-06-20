#include "HUD.hpp"

/// Konstruktor HUD-u � zapami�tuje renderer i czcionk� do wy�wietlania informacji
HUD::HUD(SDL_Renderer* renderer, TTF_Font* font)
    : renderer(renderer), font(font) {
}

/// Aktualizuje wy�wietlany wynik gracza
void HUD::updateScore(int score) {
    currentScore = score;
}

/// Aktualizuje wy�wietlan� liczb� �y� gracza
void HUD::updateLives(int lives) {
    currentLives = lives;
}

/// Renderuje HUD na ekranie (wynik i zdrowie gracza) w prawym g�rnym rogu
void HUD::render(int screenWidth) {
    SDL_Color white = { 255, 255, 255 };

    // Lives (zdrowie)
    std::string livesText = "Zdrowie: " + std::to_string(currentLives);
    SDL_Surface* livesSurface = TTF_RenderText_Blended(font, livesText.c_str(), white);
    SDL_Texture* livesTexture = SDL_CreateTextureFromSurface(renderer, livesSurface);
    SDL_Rect livesRect = {
        screenWidth - livesSurface->w - 10,
        10,
        livesSurface->w,
        livesSurface->h
    };
    SDL_RenderCopy(renderer, livesTexture, nullptr, &livesRect);
    SDL_FreeSurface(livesSurface);
    SDL_DestroyTexture(livesTexture);

    // Score (wynik)
    std::string scoreText = "Wynik: " + std::to_string(currentScore);
    SDL_Surface* scoreSurface = TTF_RenderText_Blended(font, scoreText.c_str(), white);
    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    SDL_Rect scoreRect = {
        screenWidth - scoreSurface->w - 10,
        20 + livesRect.h,
        scoreSurface->w,
        scoreSurface->h
    };
    SDL_RenderCopy(renderer, scoreTexture, nullptr, &scoreRect);
    SDL_FreeSurface(scoreSurface);
    SDL_DestroyTexture(scoreTexture);
}