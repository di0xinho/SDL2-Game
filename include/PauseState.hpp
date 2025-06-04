#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "State.hpp"
#include "GameData.hpp"
#include "GameConfig.hpp"
#include <memory>
#include <iostream>

/// Klasa reprezentuj�ca ekran pauzy gry.
/// Obs�uguje wy�wietlanie informacji o pauzie, obs�ug� wej�cia oraz odpowiednie wstrzymanie logiki gry.
class PauseState : public State {
public:
    /// Konstruktor przyjmuj�cy wska�nik do wsp�dzielonych danych gry
    PauseState(std::shared_ptr<GameData> data);

    /// Destruktor � zwalnia za�adowane zasoby powi�zane z ekranem pauzy
    ~PauseState();

    /// Inicjalizuje stan pauzy (np. �aduje czcionk�, przygotowuje napisy)
    void Init() override;

    /// Obs�uguje wej�cie od u�ytkownika (np. wznowienie gry, powr�t do menu)
    void HandleInput() override;

    /// Aktualizuje logik� stanu pauzy (mo�liwe animacje lub efekty)
    void Update(float deltaTime) override;

    /// Renderuje ekran pauzy na ekranie gry
    void Draw(float deltaTime) override;

private:
    std::shared_ptr<GameData> data;   /// Wska�nik do wsp�dzielonych danych gry

    TTF_Font* font = nullptr;         /// Czcionka do wy�wietlania komunikat�w o pauzie
    SDL_Color titleColor = { 255, 255, 255 }; /// Kolor tytu�u ("Pauza")
    SDL_Color infoColor = { 150, 150, 150 }; /// Kolor dodatkowych informacji (np. "Naci�nij Esc aby wr�ci�")
    bool initialized = false;         /// Czy stan pauzy zosta� zainicjalizowany?

    /// Pomocnicza funkcja do inicjalizacji czcionki
    void initFont();
};