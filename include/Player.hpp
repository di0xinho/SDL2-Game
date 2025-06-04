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
#include <memory>
#include <unordered_map>

/// Klasa reprezentująca gracza — obsługuje ruch, animacje, wejście, atak, rzucanie bronią oraz kolizje
class Player {
public:
    /// Domyślny konstruktor
    Player();

    /// Inicjalizuje gracza (ładuje animacje, resetuje pozycję itp.)
    void init(std::shared_ptr<GameData> data);

    /// Ustawia pozycję gracza
    void setPosition(const SDL_FPoint& pos);

    /// Zwraca aktualną pozycję gracza
    SDL_FPoint getPosition() const;

    /// Przesuwa gracza o zadany wektor
    void moveBy(SDL_FPoint offset);

    /// Aktualizuje logikę gracza (ruch, animacje, kolizje)
    void update(float deltaTime, const std::vector<SDL_Rect>& platforms, float groundY);

    /// Obsługuje wejście z klawiatury (ruch, skok, atak, rzuty)
    void handleInput(const Uint8* keystates);

    /// Powiązuje komendę (wzorzec Command) z konkretnym klawiszem
    void bindCommand(SDL_Scancode key, std::unique_ptr<Command> command);

    /// Renderuje gracza na ekranie, uwzględniając przesunięcie kamery
    void render(SDL_Renderer* renderer, const SDL_Rect& camera);

    // Akcje gracza 

    /// Skok gracza
    void Jump();

    /// Ruch w lewo
    void MoveLeft();

    /// Ruch w prawo
    void MoveRight();

    /// Próba rzutu bronią (np. nożem)
    void tryThrowWeapon(std::shared_ptr<GameData> data, SDL_Texture* weaponTexture, std::vector<Weapon>& weaponList);

    /// Ogranicza pozycję gracza do podanego zakresu na osi X
    void constrainToBounds(float minX, float maxX);

    /// Ustawia dźwięk skoku
    void setJumpSound(Mix_Chunk* sound);

    /// Ustawia dźwięk rzutu nożem
    void setKnifeThrowSound(Mix_Chunk* sound);

    /// Zwraca wskaźnik do dźwięku rzutu nożem
    Mix_Chunk* getKnifeThrowSound();

    /// Zwraca prostokąt kolizyjny gracza
    SDL_Rect getRect() const;

    /// Zwraca aktualną prędkość gracza
    SDL_FPoint getVelocity() const;

    /// Zwraca rozmiar gracza
    SDL_FPoint getSize() const;

    /// Sprawdza, czy gracz stoi na ziemi
    bool isOnGround() const;

    /// Czy gracz może rzucić bronią (czy cooldown się skończył?)
    bool canShoot() const;

    /// Resetuje cooldown rzutu bronią
    void resetWeaponCooldown();

    /// Rozpoczyna efekt migotania gracza (np. po otrzymaniu obrażeń)
    void startBlink(float duration);

    /// Sprawdza, czy efekt migotania jest aktywny
    bool isBlinking() const;

private:
    SDL_FPoint position;                         /// Pozycja gracza w świecie gry
    SDL_FPoint velocity;                         /// Prędkość gracza
    SDL_FPoint size = { 50.0f, 50.0f };          /// Rozmiar gracza (domyślnie 50x50 px)

    float speed = 200.0f;                        /// Prędkość poruszania się (px/s)
    float jumpStrength = -500.0f;                /// Siła skoku (ujemna dla ruchu w górę)
    float gravity = 1000.0f;                     /// Przyspieszenie grawitacyjne

    bool onGround = false;                       /// Czy gracz jest na ziemi?
    bool isMoving = false;                       /// Czy gracz się porusza?

    // Migotanie (nieśmiertelność) 
    bool blinking = false;                       /// Czy efekt migotania jest aktywny?
    float blinkTimer = 0.0f;                     /// Timer efektu migotania
    float blinkDuration = 0.0f;                  /// Czas trwania migotania
    float blinkFrequency = 12.0f;                /// Częstotliwość migotania (ile razy na sekundę)

    float weaponCooldown = 0.0f;                 /// Pozostały czas cooldownu rzutu bronią (sekundy)
    const float weaponCooldownDuration = 0.5f;   /// Długość cooldownu rzutu bronią (sekundy)

    Animation idleAnim;                          /// Animacja bezczynności gracza
    Animation runAnim;                           /// Animacja biegu gracza
    Animation jumpAnim;                          /// Animacja skoku gracza
    Animation* currentAnim = nullptr;            /// Aktualnie odtwarzana animacja

    // Dźwięki 
    Mix_Chunk* jumpSound = nullptr;              /// Dźwięk skoku
    Mix_Chunk* knifeThrowSound = nullptr;        /// Dźwięk rzutu nożem

    std::unordered_map<SDL_Scancode, std::unique_ptr<Command>> commandMap; /// Mapowanie klawiszy na komendy (wzorzec Command)
};