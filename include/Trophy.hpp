#pragma once

#include <SDL.h>
#include "GameData.hpp"
#include "GameConfig.hpp"
#include <cmath>
#include <memory>

/// Klasa reprezentuj¹ca trofeum (cel poziomu) — koñcowy punkt do osi¹gniêcia przez gracza
class Trophy {
public:
    /// Domyœlny konstruktor
    Trophy();

    /// Inicjalizuje trofeum (³aduje teksturê, ustawia pozycjê bazow¹)
    void init(std::shared_ptr<GameData> data);

    /// Ustawia pozycjê bazow¹ trofeum
    void setPosition(float x, float y);

    /// Aktualizuje logikê trofeum (np. efekt unoszenia siê)
    void update(float deltaTime);

    /// Renderuje trofeum na ekranie, uwzglêdniaj¹c przesuniêcie kamery
    void render(SDL_Renderer* renderer, const SDL_Rect& camera);

    /// Zwraca prostok¹t kolizyjny trofeum (do detekcji dotarcia gracza)
    SDL_Rect getRect() const;

    /// Zwraca rozmiar trofeum
    SDL_FPoint getSize() const;

private:
    SDL_Texture* texture = nullptr;        /// Tekstura trofeum
    SDL_FPoint basePosition;               /// Bazowa pozycja trofeum (punkt odniesienia dla oscylacji)
    SDL_FPoint currentPosition;            /// Aktualna pozycja trofeum (uwzglêdniaj¹ca animacjê unoszenia)
    SDL_FPoint size = { 200.0f, 200.0f };  /// Rozmiar trofeum (domyœlnie 200x200 px)
    float oscillationTime = 0.0f;          /// Timer animacji unoszenia (oscylacji)
};