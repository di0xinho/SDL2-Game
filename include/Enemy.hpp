#pragma once
#include <SDL.h>
#include <vector>
#include "Animation.hpp"
#include "GameData.hpp"

/// Klasa reprezentuj�ca przeciwnika poruszaj�cego si� w okre�lonym zakresie (patroluj�cego)
class Enemy {
public:
    /// Domy�lny konstruktor
    Enemy();

    /// Inicjalizuje przeciwnika: �aduje animacj�, ustawia pozycj� i zakres ruchu
    void init(std::shared_ptr<GameData> data, const std::vector<const char*>& framePaths, SDL_FPoint pos, float range);

    /// Aktualizuje logik� przeciwnika (ruch, animacja, stan po otrzymaniu obra�e�)
    void update(float deltaTime);

    /// Renderuje przeciwnika na ekranie, uwzgl�dniaj�c przesuni�cie kamery
    void render(SDL_Renderer* renderer, const SDL_Rect& camera);

    /// Zwraca prostok�t kolizyjny przeciwnika (do detekcji kolizji)
    SDL_Rect getRect() const;

    /// Ustawia d�wi�k odtwarzany po otrzymaniu ciosu
    /// @param sound - wska�nik do d�wi�ku SDL_Mixer
    void setHitSound(Mix_Chunk* sound);

    /// Zdarzenie: przeciwnik otrzyma� cios (zmniejsza zdrowie, odtwarza d�wi�k)
    void Hit();

    /// Zdarzenie: przeciwnik zosta� zabity (ustawia alive = false)
    void Kill();

    /// Sprawdza, czy przeciwnik �yje
    bool IsAlive() const;

private:
    Animation animation;         /// Animacja przeciwnika
    SDL_FPoint position;         /// Pozycja przeciwnika w �wiecie gry
    SDL_FPoint size = { 50.0f, 50.0f }; /// Rozmiar przeciwnika (domy�lnie 50x50 px)
    float speed = 50.0f;         /// Pr�dko�� poruszania si� przeciwnika (px/s)
    float minX = 0.0f;           /// Lewy kraniec patrolu
    float maxX = 0.0f;           /// Prawy kraniec patrolu
    int direction = 1;           /// Kierunek ruchu: 1 - w prawo, -1 - w lewo

    Mix_Chunk* ouchSound = nullptr; /// D�wi�k odtwarzany przy otrzymaniu ciosu

    int health = 3;              /// Liczba punkt�w �ycia
    float hitTimer = 0.0f;       /// Timer nie�miertelno�ci po otrzymaniu ciosu (sekundy)
    float hitDuration = 0.2f;    /// Czas trwania nie�miertelno�ci po ciosie (sekundy)
    bool alive = true;           /// Czy przeciwnik �yje?
};