#pragma once

#include <memory>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "State.hpp"
#include "GameData.hpp"
#include "GameConfig.hpp"
#include "PlayState.hpp"
#include <iostream>

/// Klasa reprezentuj¹ca ekran koñca gry (Game Over / Wygrana)
/// Odpowiada za wyœwietlanie informacji o wyniku, komunikatów oraz obs³ugê wejœcia po zakoñczeniu gry.
class GameOverState : public State {
public:
    /// Konstruktor przyjmuj¹cy informacjê o wygranej i koñcowym wyniku oraz wskaŸnik na dane gry
    GameOverState(std::shared_ptr<GameData> data, bool win, int finalScore);

    /// Destruktor - zwalnia zasoby ekranu GameOver
    ~GameOverState();

    /// Inicjalizuje stan (np. ³aduje zasoby, ustawia teksty)
    void Init() override;

    /// Obs³uguje wejœcie od u¿ytkownika (np. powrót do menu, restart)
    void HandleInput() override;

    /// Aktualizuje logikê stanu (tu zwykle niewiele siê dzieje)
    void Update(float deltaTime) override;

    /// Rysuje ekran Game Over na ekranie
    void Draw(float deltaTime) override;

private:
    std::shared_ptr<GameData> data;   /// WskaŸnik do wspó³dzielonych danych gry (tekstury, renderer itp.)
    bool win;                         /// Czy gracz wygra³?
    int score;                        /// Koñcowy wynik gracza

    TTF_Font* font = nullptr;         /// Czcionka do wyœwietlania tekstu
    SDL_Texture* backgroundTexture = nullptr; /// Tekstura t³a ekranu Game Over
    Mix_Chunk* gameOverSound = nullptr;       /// DŸwiêk odtwarzany przy Game Over
    bool initialized = false;         /// Czy stan zosta³ poprawnie zainicjalizowany?

    /// Pomocnicza funkcja do ³adowania zasobów (czcionki, tekstur, dŸwiêków)
    void loadAssets();
};