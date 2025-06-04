#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

/// Klasa odpowiedzialna za wy�wietlanie interfejsu gracza (HUD) � wyniku i liczby �y�
class HUD {
public:
    /// Konstruktor HUD � przyjmuje renderer oraz czcionk� do wy�wietlania tekstu
    HUD(SDL_Renderer* renderer, TTF_Font* font);

    /// Aktualizuje wy�wietlany wynik gracza
    void updateScore(int score);

    /// Aktualizuje wy�wietlan� liczb� �y� gracza
    void updateLives(int lives);

    /// Renderuje HUD na ekranie (wynik, liczba �y�)
    void render(int screenWidth);

private:
    SDL_Renderer* renderer; /// Wska�nik do renderer'a SDL
    TTF_Font* font;         /// Wska�nik do czcionki TTF

    int currentScore = 0;   /// Aktualny wynik gracza
    int currentLives = 3;   /// Aktualna liczba �y� gracza
};