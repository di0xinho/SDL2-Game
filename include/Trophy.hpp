#pragma once

#include <SDL.h>
#include "GameData.hpp"
#include "GameConfig.hpp"
#include <cmath>
#include <memory>

/// Klasa reprezentuj�ca trofeum (cel poziomu) � ko�cowy punkt do osi�gni�cia przez gracza
class Trophy {
public:
    /// Domy�lny konstruktor
    Trophy();

    /// Inicjalizuje trofeum (�aduje tekstur�, ustawia pozycj� bazow�)
    void init(std::shared_ptr<GameData> data);

    /// Ustawia pozycj� bazow� trofeum
    void setPosition(float x, float y);

    /// Aktualizuje logik� trofeum (np. efekt unoszenia si�)
    void update(float deltaTime);

    /// Renderuje trofeum na ekranie, uwzgl�dniaj�c przesuni�cie kamery
    void render(SDL_Renderer* renderer, const SDL_Rect& camera);

    /// Zwraca prostok�t kolizyjny trofeum (do detekcji dotarcia gracza)
    SDL_Rect getRect() const;

    /// Zwraca rozmiar trofeum
    SDL_FPoint getSize() const;

private:
    SDL_Texture* texture = nullptr;        /// Tekstura trofeum
    SDL_FPoint basePosition;               /// Bazowa pozycja trofeum (punkt odniesienia dla oscylacji)
    SDL_FPoint currentPosition;            /// Aktualna pozycja trofeum (uwzgl�dniaj�ca animacj� unoszenia)
    SDL_FPoint size = { 200.0f, 200.0f };  /// Rozmiar trofeum (domy�lnie 200x200 px)
    float oscillationTime = 0.0f;          /// Timer animacji unoszenia (oscylacji)
};