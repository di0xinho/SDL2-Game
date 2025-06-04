#pragma once
#include <SDL.h>
#include <vector>
#include "Animation.hpp"
#include "GameData.hpp"

/// Klasa reprezentuj�ca pojedyncz� monet� (obiekt do zebrania) w grze
class Coin {
public:
    /// Domy�lny konstruktor
    Coin();

    /// Inicjalizuje monet�: �aduje animacj�, ustawia pozycj� i powi�zanie z danymi gry
    void init(std::shared_ptr<GameData> data, const std::vector<const char*>& framePaths, SDL_FPoint pos);

    /// Aktualizuje logik� monety (np. animacj�)
    void update(float deltaTime);

    /// Renderuje monet� na ekranie, uwzgl�dniaj�c przesuni�cie kamery
    void render(SDL_Renderer* renderer, const SDL_Rect& camera);

    /// Zwraca prostok�t kolizyjny monety (do detekcji zbierania)
    SDL_Rect getRect() const;

    /// Sprawdza, czy moneta zosta�a zebrana
    bool isCollected() const;

    /// Oznacza monet� jako zebran�
    void collect();

private:
    Animation animation;      /// Animacja monety
    SDL_FPoint position;      /// Pozycja monety w �wiecie gry
    SDL_FPoint size = { 20.0f, 20.0f }; /// Rozmiar monety (domy�lnie 20x20 px)
    bool collected = false;   /// Czy moneta zosta�a zebrana?
};