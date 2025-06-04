#pragma once

#include <memory>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "State.hpp"
#include "GameData.hpp"
#include "GameConfig.hpp"
#include "PlayState.hpp"

/// Klasa reprezentuj¹ca g³ówne menu gry.
/// Obs³uguje wyœwietlanie t³a, przycisków oraz muzyki w tle.
/// Umo¿liwia przejœcie do rozgrywki po klikniêciu na ikonkê „Play”.
class MenuState : public State {
public:
    /// Konstruktor menu — przyjmuje wskaŸnik do wspólnych danych gry
    MenuState(std::shared_ptr<GameData> data);

    /// Destruktor — zwalnia za³adowane zasoby
    ~MenuState();

    /// Inicjalizuje stan menu (³adowanie zasobów, przygotowanie przycisków)
    void Init() override;

    /// Obs³uguje wejœcie od u¿ytkownika (np. klikniêcie w przycisk)
    void HandleInput() override;

    /// Aktualizuje logikê menu (np. efekty animacji przycisku)
    void Update(float deltaTime) override;

    /// Renderuje menu na ekranie (t³o, przyciski, teksty)
    void Draw(float deltaTime) override;

private:
    std::shared_ptr<GameData> data;        /// WskaŸnik do wspó³dzielonych danych gry

    SDL_Texture* backgroundTexture = nullptr;   /// Tekstura t³a menu
    SDL_Texture* playButtonTexture = nullptr;   /// Tekstura przycisku "Play"
    TTF_Font* font = nullptr;                   /// Czcionka u¿ywana w menu
    Mix_Music* menuMusic = nullptr;             /// Muzyka odtwarzana w menu

    SDL_Rect playButtonRect{};                  /// Prostok¹t okreœlaj¹cy pozycjê i rozmiar przycisku "Play"

    float buttonScale = 0.5f;                   /// Skala przycisku "Play"
    bool initialized = false;                   /// Czy stan menu zosta³ zainicjalizowany?
    const int fontSize = 32;                    /// Rozmiar czcionki w menu
};