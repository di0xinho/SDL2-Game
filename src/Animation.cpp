#include "Animation.hpp"

/// Konstruktor domyœlny animacji — inicjuje pust¹ animacjê
Animation::Animation() {}

/// Dodaje pojedyncz¹ klatkê (teksturê) do animacji
void Animation::addFrame(SDL_Texture* frame) {
    if (frame) {
        frames.push_back(frame);
    }
}

/// Ustawia czas trwania jednej klatki animacji
void Animation::setFrameDuration(float duration) {
    frameDuration = duration;
}

/// Aktualizuje animacjê — przechodzi do nastêpnej klatki po up³ywie odpowiedniego czasu
void Animation::update(float deltaTime) {
    // Jeœli animacja ma 0 lub 1 klatkê, nie aktualizuj
    if (frames.size() <= 1) return;

    timer += deltaTime;
    if (timer >= frameDuration) {
        timer -= frameDuration;
        currentFrameIndex = (currentFrameIndex + 1) % frames.size();
    }
}

/// Zwraca wskaŸnik do aktualnej klatki (tekstury) animacji
SDL_Texture* Animation::getCurrentFrame() const {
    if (frames.empty()) return nullptr;
    return frames[currentFrameIndex];
}

/// Resetuje animacjê do pierwszej klatki i zeruje timer
void Animation::reset() {
    currentFrameIndex = 0;
    timer = 0.0f;
}