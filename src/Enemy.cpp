#include "Enemy.hpp"

Enemy::Enemy() {}

void Enemy::init(std::shared_ptr<GameData> data, const std::vector<const char*>& framePaths, SDL_FPoint pos, float range) {
    for (size_t i = 0; i < framePaths.size(); ++i) {
        std::string key = "enemy_frame_" + std::to_string(i);
        SDL_Texture* frame = data->assetManager->loadTexture(key, framePaths[i]);
        animation.addFrame(frame);
    }
    animation.setFrameDuration(0.2f);
    position = pos;
    minX = pos.x - range;
    maxX = pos.x + range;
}

void Enemy::update(float deltaTime) {
    animation.update(deltaTime);

    if (hitTimer > 0.0f) {
        hitTimer -= deltaTime;
        if (hitTimer < 0.0f) hitTimer = 0.0f;
    }

    position.x += direction * speed * deltaTime;

    if (position.x < minX) {
        position.x = minX;
        direction = 1;
    }
    else if (position.x > maxX) {
        position.x = maxX;
        direction = -1;
    }
}

void Enemy::render(SDL_Renderer* renderer, const SDL_Rect& camera) {
    SDL_Texture* texture = animation.getCurrentFrame();

    SDL_Rect dstRect = {
        static_cast<int>(position.x) - camera.x,
        static_cast<int>(position.y) - camera.y,
        static_cast<int>(size.x),
        static_cast<int>(size.y)
    };

    if (hitTimer > 0.0f) {
        SDL_SetTextureColorMod(texture, 255, 50, 50);
    }
    else {
        SDL_SetTextureColorMod(texture, 255, 255, 255);
    }

    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
}

SDL_Rect Enemy::getRect() const {
    return {
        static_cast<int>(position.x),
        static_cast<int>(position.y),
        static_cast<int>(size.x),
        static_cast<int>(size.y)
    };
}

void Enemy::Hit() {
    if (!alive) return;

    health--;

    if (ouchSound) {
        Mix_PlayChannel(-1, ouchSound, 0);
    }

    hitTimer = hitDuration;

    if (health <= 0) {
        Kill();
    }
}

void Enemy::Kill() {
    alive = false;
}

bool Enemy::IsAlive() const {
    return alive;
}

void Enemy::setHitSound(Mix_Chunk* sound) {
    ouchSound = sound;
}
