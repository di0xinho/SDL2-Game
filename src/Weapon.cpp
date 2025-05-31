#include "Weapon.hpp"

Weapon::Weapon() {}

void Weapon::init(std::shared_ptr<GameData> data, SDL_Texture* texture, SDL_FPoint startPos) {
    this->texture = texture;
    this->position = startPos;
    this->angle = 0.0f;
    this->lifetime = 5.0f;
    this->alive = true;
}

void Weapon::update(float deltaTime) {
    if (!alive) return;

    position.x += velocity.x * deltaTime;
    angle += 1.0f;

    lifetime -= deltaTime;
    if (lifetime <= 0.0f) {
        alive = false;
    }
}

void Weapon::render(SDL_Renderer* renderer, const SDL_Rect& camera) {
    if (!alive || !texture) return;

    SDL_Rect dstRect = {
        static_cast<int>(position.x) - camera.x,
        static_cast<int>(position.y) - camera.y,
        static_cast<int>(size.x),
        static_cast<int>(size.y)
    };

    SDL_RenderCopyEx(renderer, texture, nullptr, &dstRect, angle, nullptr, SDL_FLIP_NONE);
}

SDL_Rect Weapon::getRect() const {
    return {
        static_cast<int>(position.x),
        static_cast<int>(position.y),
        static_cast<int>(size.x),
        static_cast<int>(size.y)
    };
}

bool Weapon::isAlive() const {
    return alive;
}

bool Weapon::checkCollision(const SDL_Rect& other) {
    return SDL_HasIntersection(&getRect(), &other);
}

void Weapon::Kill() {
    alive = false;
}
