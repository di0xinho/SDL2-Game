#include "Weapon.hpp"

/// Konstruktor domy�lny broni 
Weapon::Weapon() {}

/// Inicjalizuje bro�
void Weapon::init(std::shared_ptr<GameData> data, SDL_Texture* texture, SDL_FPoint startPos) {
    this->texture = texture;
    this->position = startPos;
    this->angle = 0.0f;
    this->lifetime = 5.0f;
    this->alive = true;
}

/// Aktualizuje pozycj�, obr�t i �ywotno�� broni
void Weapon::update(float deltaTime) {
    if (!alive) return;

    position.x += velocity.x * deltaTime;
    angle += 1.0f;

    lifetime -= deltaTime;
    if (lifetime <= 0.0f) {
        alive = false;
    }
}

/// Renderuje bro� na ekranie (z obrotem i przesuni�ciem kamery)
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

/// Zwraca prostok�t kolizyjny broni
SDL_Rect Weapon::getRect() const {
    return {
        static_cast<int>(position.x),
        static_cast<int>(position.y),
        static_cast<int>(size.x),
        static_cast<int>(size.y)
    };
}

/// Zwraca, czy bro� jest aktywna (czy jest "�ywa")
bool Weapon::isAlive() const {
    return alive;
}

/// Sprawdza kolizj� broni z danym prostok�tem (np. wrogiem)
bool Weapon::checkCollision(const SDL_Rect& other) {
    SDL_Rect rect = getRect();
    return SDL_HasIntersection(&rect, &other);
}

/// Oznacza bro� jako zniszczon� (nieaktywna) - potem w trakcie rozgrywki b�dzie usuwana
void Weapon::Kill() {
    alive = false;
}