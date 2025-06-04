#pragma once
#include <SDL.h>
#include <vector>
#include "Animation.hpp"
#include "GameData.hpp"

/// Klasa reprezentuj¹ca przeciwnika poruszaj¹cego siê w okreœlonym zakresie (patroluj¹cego)
class Enemy {
public:
    /// Domyœlny konstruktor
    Enemy();

    /// Inicjalizuje przeciwnika: ³aduje animacjê, ustawia pozycjê i zakres ruchu
    void init(std::shared_ptr<GameData> data, const std::vector<const char*>& framePaths, SDL_FPoint pos, float range);

    /// Aktualizuje logikê przeciwnika (ruch, animacja, stan po otrzymaniu obra¿eñ)
    void update(float deltaTime);

    /// Renderuje przeciwnika na ekranie, uwzglêdniaj¹c przesuniêcie kamery
    void render(SDL_Renderer* renderer, const SDL_Rect& camera);

    /// Zwraca prostok¹t kolizyjny przeciwnika (do detekcji kolizji)
    SDL_Rect getRect() const;

    /// Ustawia dŸwiêk odtwarzany po otrzymaniu ciosu
    /// @param sound - wskaŸnik do dŸwiêku SDL_Mixer
    void setHitSound(Mix_Chunk* sound);

    /// Zdarzenie: przeciwnik otrzyma³ cios (zmniejsza zdrowie, odtwarza dŸwiêk)
    void Hit();

    /// Zdarzenie: przeciwnik zosta³ zabity (ustawia alive = false)
    void Kill();

    /// Sprawdza, czy przeciwnik ¿yje
    bool IsAlive() const;

private:
    Animation animation;         /// Animacja przeciwnika
    SDL_FPoint position;         /// Pozycja przeciwnika w œwiecie gry
    SDL_FPoint size = { 50.0f, 50.0f }; /// Rozmiar przeciwnika (domyœlnie 50x50 px)
    float speed = 50.0f;         /// Prêdkoœæ poruszania siê przeciwnika (px/s)
    float minX = 0.0f;           /// Lewy kraniec patrolu
    float maxX = 0.0f;           /// Prawy kraniec patrolu
    int direction = 1;           /// Kierunek ruchu: 1 - w prawo, -1 - w lewo

    Mix_Chunk* ouchSound = nullptr; /// DŸwiêk odtwarzany przy otrzymaniu ciosu

    int health = 3;              /// Liczba punktów ¿ycia
    float hitTimer = 0.0f;       /// Timer nieœmiertelnoœci po otrzymaniu ciosu (sekundy)
    float hitDuration = 0.2f;    /// Czas trwania nieœmiertelnoœci po ciosie (sekundy)
    bool alive = true;           /// Czy przeciwnik ¿yje?
};