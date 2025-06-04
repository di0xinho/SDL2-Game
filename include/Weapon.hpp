#pragma once
#include <SDL.h>
#include "GameData.hpp"
#include <memory>

/// Klasa reprezentuj�ca bro� rzucan� przez gracza 
class Weapon {
public:
    /// Domy�lny konstruktor
    Weapon();

    /// Inicjalizuje bro�: ustawia tekstur�, pozycj� startow� i resetuje w�a�ciwo�ci broni
    void init(std::shared_ptr<GameData> data, SDL_Texture* texture, SDL_FPoint startPos);

    /// Aktualizuje logik� broni (ruch, czas �ycia)
    void update(float deltaTime);

    /// Renderuje bro� na ekranie, uwzgl�dniaj�c przesuni�cie kamery
    void render(SDL_Renderer* renderer, const SDL_Rect& camera);

    /// Zwraca prostok�t kolizyjny broni (do detekcji trafie�)
    SDL_Rect getRect() const;

    /// Sprawdza, czy bro� nadal istnieje (nie wygas�a, nie zderzy�a si�)
    bool isAlive() const;

    /// Oznacza bro� jako zniszczon� (oznacza j� jako "martw�")
    void Kill();

    /// Sprawdza kolizj� broni z innym prostok�tem (np. przeciwnikiem)
    bool checkCollision(const SDL_Rect& other);

private:
    SDL_FPoint position{};                  /// Aktualna pozycja broni w �wiecie gry
    SDL_FPoint velocity{ 300.0f, 0.0f };    /// Pr�dko�� broni 
    float angle = 0.0f;                     /// K�t obrotu (np. do animacji lotu)
    float lifetime = 5.0f;                  /// Pozosta�y czas �ycia broni (sekundy)
    bool alive = true;                      /// Czy bro� jest aktywna?

    SDL_Texture* texture = nullptr;         /// Tekstura broni
    SDL_FPoint size{ 32.0f, 32.0f };        /// Rozmiar broni (domy�lnie 32x32 px)
};