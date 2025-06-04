#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

/// Klasa odpowiedzialna za wyœwietlanie interfejsu gracza (HUD) — wyniku i liczby ¿yæ
class HUD {
public:
    /// Konstruktor HUD — przyjmuje renderer oraz czcionkê do wyœwietlania tekstu
    HUD(SDL_Renderer* renderer, TTF_Font* font);

    /// Aktualizuje wyœwietlany wynik gracza
    void updateScore(int score);

    /// Aktualizuje wyœwietlan¹ liczbê ¿yæ gracza
    void updateLives(int lives);

    /// Renderuje HUD na ekranie (wynik, liczba ¿yæ)
    void render(int screenWidth);

private:
    SDL_Renderer* renderer; /// WskaŸnik do renderer'a SDL
    TTF_Font* font;         /// WskaŸnik do czcionki TTF

    int currentScore = 0;   /// Aktualny wynik gracza
    int currentLives = 3;   /// Aktualna liczba ¿yæ gracza
};