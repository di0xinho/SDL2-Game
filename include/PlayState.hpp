#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <memory>
#include <vector>
#include "State.hpp"
#include "GameData.hpp"
#include "Player.hpp"
#include "Coin.hpp"
#include "HUD.hpp"
#include "Enemy.hpp"
#include "Weapon.hpp"
#include "Trophy.hpp"



/// G³ówny stan rozgrywki
class PlayState : public State {
public:
    PlayState(std::shared_ptr<GameData> data);

    void Init() override;
    void HandleInput() override;
    void Update(float dt) override;
    void Draw(float dt) override;

private:
    std::shared_ptr<GameData> _data;

    SDL_Texture* _backgroundTexture = nullptr;
    SDL_Texture* _landTexture = nullptr;
    SDL_Texture* _weaponTexture = nullptr;
    Mix_Music* gameMusic = nullptr;

    Player _player;
    Trophy _trophy;
    HUD hud{ nullptr, nullptr };

    std::vector<SDL_Rect> _platforms;
    std::vector<Coin> _coins;
    std::vector<Enemy> _enemies;
    std::vector<Weapon> _weapons;
    
    SDL_Rect _camera;

    TTF_Font* robotoFont;

    int _score = 0;
    int _lives = 3;
    const float groundY = 450.0f; // linia ziemi
};
