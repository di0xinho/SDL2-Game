#pragma once

#include <memory>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "State.hpp"
#include "GameData.hpp"
#include "GameConfig.hpp"
#include "PlayState.hpp"

/// Klasa reprezentuj�ca g��wne menu gry.
/// Obs�uguje wy�wietlanie t�a, przycisk�w oraz muzyki w tle.
/// Umo�liwia przej�cie do rozgrywki po klikni�ciu na ikonk� �Play�.
class MenuState : public State {
public:
    /// Konstruktor menu � przyjmuje wska�nik do wsp�lnych danych gry
    MenuState(std::shared_ptr<GameData> data);

    /// Destruktor � zwalnia za�adowane zasoby
    ~MenuState();

    /// Inicjalizuje stan menu (�adowanie zasob�w, przygotowanie przycisk�w)
    void Init() override;

    /// Obs�uguje wej�cie od u�ytkownika (np. klikni�cie w przycisk)
    void HandleInput() override;

    /// Aktualizuje logik� menu (np. efekty animacji przycisku)
    void Update(float deltaTime) override;

    /// Renderuje menu na ekranie (t�o, przyciski, teksty)
    void Draw(float deltaTime) override;

private:
    std::shared_ptr<GameData> data;        /// Wska�nik do wsp�dzielonych danych gry

    SDL_Texture* backgroundTexture = nullptr;   /// Tekstura t�a menu
    SDL_Texture* playButtonTexture = nullptr;   /// Tekstura przycisku "Play"
    TTF_Font* font = nullptr;                   /// Czcionka u�ywana w menu
    Mix_Music* menuMusic = nullptr;             /// Muzyka odtwarzana w menu

    SDL_Rect playButtonRect{};                  /// Prostok�t okre�laj�cy pozycj� i rozmiar przycisku "Play"

    float buttonScale = 0.5f;                   /// Skala przycisku "Play"
    bool initialized = false;                   /// Czy stan menu zosta� zainicjalizowany?
    const int fontSize = 32;                    /// Rozmiar czcionki w menu
};