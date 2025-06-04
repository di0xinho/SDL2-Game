#include "Trophy.hpp"

/// Konstruktor — ustawia domyœlne pozycje trofeum na (0,0)
Trophy::Trophy() {
    basePosition = { 0.0f, 0.0f };
    currentPosition = { 0.0f, 0.0f };
}

/// Inicjalizuje trofeum — pobiera teksturê z assetManagera
void Trophy::init(std::shared_ptr<GameData> data) {
    texture = data->assetManager->getTexture("trophy");
}

/// Ustawia bazow¹ i aktualn¹ pozycjê trofeum
void Trophy::setPosition(float x, float y) {
    basePosition = { x, y };
    currentPosition = basePosition;
}

/// Aktualizuje pozycjê trofeum (oscylacja góra-dó³ dla efektu animacji)
void Trophy::update(float deltaTime) {
    oscillationTime += deltaTime;
    currentPosition.y = basePosition.y + std::sin(oscillationTime * 2.0f) * 5.0f;
}

/// Renderuje trofeum na ekranie (z uwzglêdnieniem kamery)
void Trophy::render(SDL_Renderer* renderer, const SDL_Rect& camera) {
    SDL_Rect dstRect = {
        static_cast<int>(currentPosition.x) - camera.x,
        static_cast<int>(currentPosition.y) - camera.y,
        static_cast<int>(size.x),
        static_cast<int>(size.y)
    };
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
}

/// Zwraca prostok¹t kolizyjny trofeum (do wykrywania zebrania przez gracza)
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