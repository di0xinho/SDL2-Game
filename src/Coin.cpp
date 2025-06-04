#include "Coin.hpp"

/// Konstruktor domyœlny monety — inicjuje pust¹ monetê
Coin::Coin() {}

/// Inicjalizuje monetê: ³aduje klatki animacji, ustawia pozycjê
void Coin::init(std::shared_ptr<GameData> data, const std::vector<const char*>& framePaths, SDL_FPoint pos) {
    for (size_t i = 0; i < framePaths.size(); ++i) {
        std::string key = "coin_frame_" + std::to_string(i);
        SDL_Texture* frame = data->assetManager->loadTexture(key, framePaths[i]);
        animation.addFrame(frame);
    }
    animation.setFrameDuration(0.06f);
    position = pos;
}

/// Aktualizuje animacjê monety tylko jeœli nie zosta³a zebrana
void Coin::update(float deltaTime) {
    if (!collected) animation.update(deltaTime);
}

/// Renderuje monetê na ekranie (jeœli nie zosta³a zebrana)
void Coin::render(SDL_Renderer* renderer, const SDL_Rect& camera) {
    if (collected) return;
    SDL_Rect dstRect = {
        static_cast<int>(position.x) - camera.x,
        static_cast<int>(position.y) - camera.y,
        static_cast<int>(size.x),
        static_cast<int>(size.y)
    };
    SDL_RenderCopy(renderer, animation.getCurrentFrame(), nullptr, &dstRect);
}

/// Zwraca prostok¹t kolizyjny monety (do wykrywania zebrania)
SDL_Rect Coin::getRect() const {
    return {
        static_cast<int>(position.x),
        static_cast<int>(position.y),
        static_cast<int>(size.x),
        static_cast<int>(size.y)
    };
}

/// Sprawdza, czy moneta zosta³a zebrana
bool Coin::isCollected() const {
    return collected;
}

/// Oznacza monetê jako zebran¹ (ukrywa j¹ i blokuje aktualizacjê animacji)
void Coin::collect() {
    collected = true;
}