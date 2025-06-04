#pragma once
#include <SDL.h>
#include <vector>
#include "Animation.hpp"
#include "GameData.hpp"

/// Klasa reprezentuj¹ca pojedyncz¹ monetê (obiekt do zebrania) w grze
class Coin {
public:
    /// Domyœlny konstruktor
    Coin();

    /// Inicjalizuje monetê: ³aduje animacjê, ustawia pozycjê i powi¹zanie z danymi gry
    void init(std::shared_ptr<GameData> data, const std::vector<const char*>& framePaths, SDL_FPoint pos);

    /// Aktualizuje logikê monety (np. animacjê)
    void update(float deltaTime);

    /// Renderuje monetê na ekranie, uwzglêdniaj¹c przesuniêcie kamery
    void render(SDL_Renderer* renderer, const SDL_Rect& camera);

    /// Zwraca prostok¹t kolizyjny monety (do detekcji zbierania)
    SDL_Rect getRect() const;

    /// Sprawdza, czy moneta zosta³a zebrana
    bool isCollected() const;

    /// Oznacza monetê jako zebran¹
    void collect();

private:
    Animation animation;      /// Animacja monety
    SDL_FPoint position;      /// Pozycja monety w œwiecie gry
    SDL_FPoint size = { 20.0f, 20.0f }; /// Rozmiar monety (domyœlnie 20x20 px)
    bool collected = false;   /// Czy moneta zosta³a zebrana?
};