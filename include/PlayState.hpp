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

/// G³ówny stan rozgrywki.
/// Odpowiada za obs³ugê logiki gry, renderowanie œwiata, obs³ugê wejœcia oraz zarz¹dzanie obiektami gry.
class PlayState : public State {
public:
    /// Konstruktor przyjmuj¹cy wskaŸnik do wspólnych danych gry
    PlayState(std::shared_ptr<GameData> data);

    /// Inicjalizuje stan rozgrywki (³adowanie zasobów, ustawianie obiektów, reset gry)
    void Init() override;

    /// Obs³uguje wejœcie od u¿ytkownika (ruch, skok, pauza, atak)
    void HandleInput() override;

    /// Aktualizuje logikê gry (ruch, kolizje, animacje, postêp rozgrywki)
    void Update(float dt) override;

    /// Renderuje œwiat gry, obiekty, HUD oraz t³o
    void Draw(float dt) override;

private:
    std::shared_ptr<GameData> _data;           /// WskaŸnik do wspó³dzielonych danych gry

    SDL_Texture* _backgroundTexture = nullptr; /// Tekstura t³a gry
    SDL_Texture* _landTexture = nullptr;       /// Tekstura platform/ziemi
    SDL_Texture* _weaponTexture = nullptr;     /// Tekstura broni do rzucania
    Mix_Music* gameMusic = nullptr;            /// Muzyka odtwarzana podczas gry

    Player _player;                            /// Obiekt gracza
    Trophy _trophy;                            /// Trofeum (cel poziomu)
    HUD hud{ nullptr, nullptr };               /// HUD wyœwietlaj¹cy wynik i ¿ycie

    std::vector<SDL_Rect> _platforms;          /// Wektor prostok¹tów platform do kolizji
    std::vector<Coin> _coins;                  /// Wektor monet do zebrania
    std::vector<Enemy> _enemies;               /// Wektor przeciwników
    std::vector<Weapon> _weapons;              /// Wektor aktywnych broni na planszy

    SDL_Rect _camera;                          /// Aktualny widok kamery

    TTF_Font* robotoFont;                      /// Czcionka do HUD/menu

    int _score = 0;                            /// Aktualny wynik gracza
    int _lives = 3;                            /// Liczba ¿yæ gracza
    const float groundY = 450.0f;              /// Poziom linii ziemi w grze (y)
};