#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>
#include "Animation.hpp"
#include "GameData.hpp"  
#include "Command.hpp"
#include "Weapon.hpp"
#include "GameConfig.hpp"
#include <cmath>

class Player {
public:
    Player();

    void init(std::shared_ptr<GameData> data);
    void setPosition(const SDL_FPoint& pos);
    SDL_FPoint getPosition() const;
    void moveBy(SDL_FPoint offset);

    void update(float deltaTime, const std::vector<SDL_Rect>& platforms, float groundY);
    void handleInput(const Uint8* keystates);
    void bindCommand(SDL_Scancode key, std::unique_ptr<Command> command);
    void render(SDL_Renderer* renderer, const SDL_Rect& camera);

    // Atak gracza
    void Attack();
    void Jump();
    void MoveLeft();
    void MoveRight();

    void tryThrowWeapon(std::shared_ptr<GameData> data, SDL_Texture* weaponTexture, std::vector<Weapon>& weaponList);
    void constrainToBounds(float minX, float maxX);

    // Ustawia dźwięk skoku
    void setJumpSound(Mix_Chunk* sound);
    // Ustawia dźwięk rzutu nożem
    void setKnifeThrowSound(Mix_Chunk* sound);
    // Zwraca dźwięku rzutu nożem
    Mix_Chunk* getKnifeThrowSound();

    SDL_Rect getRect() const;
    SDL_FPoint getVelocity() const;
    SDL_FPoint getSize() const;
    bool isOnGround() const;

    // Czy gracz może rzucić bronią (czy cooldown się skończy?)
    bool canShoot() const;
    // Resetuje cooldown rzutu bronią
    void resetWeaponCooldown();

    void startBlink(float duration);
    bool isBlinking() const;

private:
    SDL_FPoint position;
    SDL_FPoint velocity;
    SDL_FPoint size = { 50.0f, 50.0f };

    float speed = 200.0f;
    float jumpStrength = -500.0f;
    float gravity = 1000.0f;

    bool onGround = false;
    bool isMoving = false;

    // Migotanie (nieśmiertelność)
    bool blinking = false;
    float blinkTimer = 0.0f;
    float blinkDuration = 0.0f;
    float blinkFrequency = 12.0f;

    float weaponCooldown = 0.0f;       // Czas do końca cooldownu rzutu bronią
    const float weaponCooldownDuration = 0.5f; // Długość cooldownu rzutu bronią

    Animation idleAnim;
    Animation runAnim;
    Animation jumpAnim;
    Animation* currentAnim = nullptr;

    // Dźwięki skakania i rzucania nożem
    Mix_Chunk* jumpSound = nullptr;
    Mix_Chunk* knifeThrowSound = nullptr;

    std::unordered_map<SDL_Scancode, std::unique_ptr<Command>> commandMap;
};