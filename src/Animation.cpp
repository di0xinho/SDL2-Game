#include "Animation.hpp"

/// Konstruktor domy�lny animacji � inicjuje pust� animacj�
Animation::Animation() {}

/// Dodaje pojedyncz� klatk� (tekstur�) do animacji
void Animation::addFrame(SDL_Texture* frame) {
    if (frame) {
        frames.push_back(frame);
    }
}

/// Ustawia czas trwania jednej klatki animacji
void Animation::setFrameDuration(float duration) {
    frameDuration = duration;
}

/// Aktualizuje animacj� � przechodzi do nast�pnej klatki po up�ywie odpowiedniego czasu
void Animation::update(float deltaTime) {
    // Je�li animacja ma 0 lub 1 klatk�, nie aktualizuj
    if (frames.size() <= 1) return;

    timer += deltaTime;
    if (timer >= frameDuration) {
        timer -= frameDuration;
        currentFrameIndex = (currentFrameIndex + 1) % frames.size();
    }
}

/// Zwraca wska�nik do aktualnej klatki (tekstury) animacji
SDL_Texture* Animation::getCurrentFrame() const {
    if (frames.empty()) return nullptr;
    return frames[currentFrameIndex];
}

/// Resetuje animacj� do pierwszej klatki i zeruje timer
void Animation::reset() {
    currentFrameIndex = 0;
    timer = 0.0f;
}