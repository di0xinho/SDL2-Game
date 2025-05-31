#include "Trophy.hpp"

Trophy::Trophy() {
    basePosition = { 0.0f, 0.0f };
    currentPosition = { 0.0f, 0.0f };
}

void Trophy::init(std::shared_ptr<GameData> data) {
    texture = data->assetManager->getTexture("trophy");
}

void Trophy::setPosition(float x, float y) {
    basePosition = { x, y };
    currentPosition = basePosition;
}

void Trophy::update(float deltaTime) {
    oscillationTime += deltaTime;
    currentPosition.y = basePosition.y + std::sin(oscillationTime * 2.0f) * 5.0f;
}

void Trophy::render(SDL_Renderer* renderer, const SDL_Rect& camera) {
    SDL_Rect dstRect = {
        static_cast<int>(currentPosition.x) - camera.x,
        static_cast<int>(currentPosition.y) - camera.y,
        static_cast<int>(size.x),
        static_cast<int>(size.y)
    };
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
}

SDL_Rect Trophy::getRect() const {
    return {
        static_cast<int>(currentPosition.x),
        static_cast<int>(currentPosition.y),
        static_cast<int>(size.x),
        static_cast<int>(size.y)
    };
}

SDL_FPoint Trophy::getSize() const {
    return size;
}
