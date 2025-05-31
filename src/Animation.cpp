#include "Animation.hpp"

Animation::Animation() {}

void Animation::addFrame(SDL_Texture* frame) {
    if (frame) {
        frames.push_back(frame);
    }
}

void Animation::setFrameDuration(float duration) {
    frameDuration = duration;
}

void Animation::update(float deltaTime) {
    if (frames.size() <= 1) return;

    timer += deltaTime;
    if (timer >= frameDuration) {
        timer -= frameDuration;
        currentFrameIndex = (currentFrameIndex + 1) % frames.size();
    }
}

SDL_Texture* Animation::getCurrentFrame() const {
    if (frames.empty()) return nullptr;
    return frames[currentFrameIndex];
}

void Animation::reset() {
    currentFrameIndex = 0;
    timer = 0.0f;
}
