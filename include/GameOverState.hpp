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

/// Klasa reprezentuj�ca ekran ko�ca gry (Game Over / Wygrana)
/// Odpowiada za wy�wietlanie informacji o wyniku, komunikat�w oraz obs�ug� wej�cia po zako�czeniu gry.
class GameOverState : public State {
public:
    /// Konstruktor przyjmuj�cy informacj� o wygranej i ko�cowym wyniku oraz wska�nik na dane gry
    GameOverState(std::shared_ptr<GameData> data, bool win, int finalScore);

    /// Destruktor - zwalnia zasoby ekranu GameOver
    ~GameOverState();

    /// Inicjalizuje stan (np. �aduje zasoby, ustawia teksty)
    void Init() override;

    /// Obs�uguje wej�cie od u�ytkownika (np. powr�t do menu, restart)
    void HandleInput() override;

    /// Aktualizuje logik� stanu (tu zwykle niewiele si� dzieje)
    void Update(float deltaTime) override;

    /// Rysuje ekran Game Over na ekranie
    void Draw(float deltaTime) override;

private:
    std::shared_ptr<GameData> data;   /// Wska�nik do wsp�dzielonych danych gry (tekstury, renderer itp.)
    bool win;                         /// Czy gracz wygra�?
    int score;                        /// Ko�cowy wynik gracza

    TTF_Font* font = nullptr;         /// Czcionka do wy�wietlania tekstu
    SDL_Texture* backgroundTexture = nullptr; /// Tekstura t�a ekranu Game Over
    Mix_Chunk* gameOverSound = nullptr;       /// D�wi�k odtwarzany przy Game Over
    bool initialized = false;         /// Czy stan zosta� poprawnie zainicjalizowany?

    /// Pomocnicza funkcja do �adowania zasob�w (czcionki, tekstur, d�wi�k�w)
    void loadAssets();
};