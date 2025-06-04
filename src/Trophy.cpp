#include "Trophy.hpp"

/// Konstruktor � ustawia domy�lne pozycje trofeum na (0,0)
Trophy::Trophy() {
    basePosition = { 0.0f, 0.0f };
    currentPosition = { 0.0f, 0.0f };
}

/// Inicjalizuje trofeum � pobiera tekstur� z assetManagera
void Trophy::init(std::shared_ptr<GameData> data) {
    texture = data->assetManager->getTexture("trophy");
}

/// Ustawia bazow� i aktualn� pozycj� trofeum
void Trophy::setPosition(float x, float y) {
    basePosition = { x, y };
    currentPosition = basePosition;
}

/// Aktualizuje pozycj� trofeum (oscylacja g�ra-d� dla efektu animacji)
void Trophy::update(float deltaTime) {
    oscillationTime += deltaTime;
    currentPosition.y = basePosition.y + std::sin(oscillationTime * 2.0f) * 5.0f;
}

/// Renderuje trofeum na ekranie (z uwzgl�dnieniem kamery)
void Trophy::render(SDL_Renderer* renderer, const SDL_Rect& camera) {
    SDL_Rect dstRect = {
        static_cast<int>(currentPosition.x) - camera.x,
        static_cast<int>(currentPosition.y) - camera.y,
        static_cast<int>(size.x),
        static_cast<int>(size.y)
    };
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
}

/// Zwraca prostok�t kolizyjny trofeum (do wykrywania zebrania przez gracza)
SDL_Rect Trophy::getRect() const {
    return {
        static_cast<int>(currentPosition.x),
        static_cast<int>(currentPosition.y),
        static_cast<int>(size.x),
        static_cast<int>(size.y)
    };
}

/// Zwraca rozmiar trofeum (jako SDL_FPoint)
SDL_FPoint Trophy::getSize() const {
    return size;
}