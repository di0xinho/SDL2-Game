#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <memory>
#include <vector>
#include "State.hpp"
#include "GameConfig.hpp"
#include "PauseState.hpp"
#include "GameOverState.hpp"
#include "GameData.hpp"
#include "Player.hpp"
#include "Coin.hpp"
#include "HUD.hpp"
#include "Enemy.hpp"
#include "Weapon.hpp"
#include "Trophy.hpp"
#include "JumpCommand.hpp"
#include "AttackCommand.hpp"
#include "MoveLeftCommand.hpp"
#include "MoveRightCommand.hpp"

/// G��wny stan rozgrywki.
/// Odpowiada za obs�ug� logiki gry, renderowanie �wiata, obs�ug� wej�cia oraz zarz�dzanie obiektami gry.
class PlayState : public State {
public:
    /// Konstruktor przyjmuj�cy wska�nik do wsp�lnych danych gry
    PlayState(std::shared_ptr<GameData> data);

    /// Inicjalizuje stan rozgrywki (�adowanie zasob�w, ustawianie obiekt�w, reset gry)
    void Init() override;

    /// Obs�uguje wej�cie od u�ytkownika (ruch, skok, pauza, atak)
    void HandleInput() override;

    /// Aktualizuje logik� gry (ruch, kolizje, animacje, post�p rozgrywki)
    void Update(float dt) override;

    /// Renderuje �wiat gry, obiekty, HUD oraz t�o
    void Draw(float dt) override;

private:
    std::shared_ptr<GameData> _data;           /// Wska�nik do wsp�dzielonych danych gry

    SDL_Texture* _backgroundTexture = nullptr; /// Tekstura t�a gry
    SDL_Texture* _landTexture = nullptr;       /// Tekstura platform/ziemi
    SDL_Texture* _weaponTexture = nullptr;     /// Tekstura broni do rzucania
    Mix_Music* gameMusic = nullptr;            /// Muzyka odtwarzana podczas gry

    Player _player;                            /// Obiekt gracza
    Trophy _trophy;                            /// Trofeum (cel poziomu)
    HUD hud{ nullptr, nullptr };               /// HUD wy�wietlaj�cy wynik i �ycie

    std::vector<SDL_Rect> _platforms;          /// Wektor prostok�t�w platform do kolizji
    std::vector<Coin> _coins;                  /// Wektor monet do zebrania
    std::vector<Enemy> _enemies;               /// Wektor przeciwnik�w
    std::vector<Weapon> _weapons;              /// Wektor aktywnych broni na planszy

    SDL_Rect _camera;                          /// Aktualny widok kamery

    TTF_Font* robotoFont;                      /// Czcionka do HUD/menu

    int _score = 0;                            /// Aktualny wynik gracza
    int _lives = 3;                            /// Liczba �y� gracza
    const float groundY = 450.0f;              /// Poziom linii ziemi w grze (y)
};