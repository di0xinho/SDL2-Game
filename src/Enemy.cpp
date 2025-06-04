#include "Enemy.hpp"

/// Konstruktor domyœlny przeciwnika — inicjuje pustego wroga
Enemy::Enemy() {}

/// Inicjalizuje przeciwnika: ³aduje klatki animacji, ustawia pozycjê i zakres patrolowania
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

/// Aktualizuje animacjê i logikê ruchu przeciwnika (ruch lewo/prawo, efekt trafienia)
void Enemy::update(float deltaTime) {
    animation.update(deltaTime);

    // Aktualizacja timera trafienia (efekt "migania" po otrzymaniu obra¿eñ)
    if (hitTimer > 0.0f) {
        hitTimer -= deltaTime;
        if (hitTimer < 0.0f) hitTimer = 0.0f;
    }

    // Patrolowanie w zadanym zakresie
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

/// Renderuje przeciwnika na ekranie, z efektem trafienia (czerwony kolor po otrzymaniu obra¿eñ)
void Enemy::render(SDL_Renderer* renderer, const SDL_Rect& camera) {
    SDL_Texture* texture = animation.getCurrentFrame();

    SDL_Rect dstRect = {
        static_cast<int>(position.x) - camera.x,
        static_cast<int>(position.y) - camera.y,
        static_cast<int>(size.x),
        static_cast<int>(size.y)
    };

    if (hitTimer > 0.0f) {
        SDL_SetTextureColorMod(texture, 255, 50, 50); // Czerwony odcieñ po trafieniu
    }
    else {
        SDL_SetTextureColorMod(texture, 255, 255, 255); // Normalny kolor
    }

    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
}

/// Zwraca prostok¹t kolizyjny przeciwnika (do wykrywania kolizji z graczem lub broni¹)
SDL_Rect Enemy::getRect() const {
    return {
        static_cast<int>(position.x),
        static_cast<int>(position.y),
        static_cast<int>(size.x),
        static_cast<int>(size.y)
    };
}

/// Oznacza przeciwnika jako trafionego (zmniejsza ¿ycie, uruchamia efekt trafienia i dŸwiêk)
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

/// Oznacza przeciwnika jako martwego (wy³¹cza go z gry)
void Enemy::Kill() {
    alive = false;
}

/// Sprawdza, czy przeciwnik jest ¿ywy
bool Enemy::IsAlive() const {
    return alive;
}

/// Ustawia dŸwiêk trafienia przeciwnika
void Enemy::setHitSound(Mix_Chunk* sound) {
    ouchSound = sound;
}