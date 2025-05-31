#pragma once
#include <SDL.h>
#include <vector>

class Animation {
public:
    Animation();
    void addFrame(SDL_Texture* frame);
    void setFrameDuration(float duration); // czas trwania jednej klatki
    void update(float deltaTime);
    SDL_Texture* getCurrentFrame() const;
    void reset();

private:
    std::vector<SDL_Texture*> frames;
    float frameDuration = 0.1f; // domy�lnie 100 ms na klatk�
    float timer = 0.0f;
    size_t currentFrameIndex = 0;
};
