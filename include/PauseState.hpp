#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "State.hpp"
#include "GameData.hpp"
#include "GameConfig.hpp"
#include <memory>
#include <iostream>

/// Klasa reprezentuj¹ca ekran pauzy gry.
/// Obs³uguje wyœwietlanie informacji o pauzie, obs³ugê wejœcia oraz odpowiednie wstrzymanie logiki gry.
class PauseState : public State {
public:
    /// Konstruktor przyjmuj¹cy wskaŸnik do wspó³dzielonych danych gry
    PauseState(std::shared_ptr<GameData> data);

    /// Destruktor — zwalnia za³adowane zasoby powi¹zane z ekranem pauzy
    ~PauseState();

    /// Inicjalizuje stan pauzy (np. ³aduje czcionkê, przygotowuje napisy)
    void Init() override;

    /// Obs³uguje wejœcie od u¿ytkownika (np. wznowienie gry, powrót do menu)
    void HandleInput() override;

    /// Aktualizuje logikê stanu pauzy (mo¿liwe animacje lub efekty)
    void Update(float deltaTime) override;

    /// Renderuje ekran pauzy na ekranie gry
    void Draw(float deltaTime) override;

private:
    std::shared_ptr<GameData> data;   /// WskaŸnik do wspó³dzielonych danych gry

    TTF_Font* font = nullptr;         /// Czcionka do wyœwietlania komunikatów o pauzie
    SDL_Color titleColor = { 255, 255, 255 }; /// Kolor tytu³u ("Pauza")
    SDL_Color infoColor = { 150, 150, 150 }; /// Kolor dodatkowych informacji (np. "Naciœnij Esc aby wróciæ")
    bool initialized = false;         /// Czy stan pauzy zosta³ zainicjalizowany?

    /// Pomocnicza funkcja do inicjalizacji czcionki
    void initFont();
};