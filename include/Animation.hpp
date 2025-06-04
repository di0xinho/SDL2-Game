#pragma once

#include <SDL.h>
#include <vector>

/// Klasa obs³uguj¹ca animacje sprite'ów opart¹ na wektorze wskaŸników do tekstur SDL
class Animation {
public:
    /// Domyœlny konstruktor
    Animation();

    /// Dodaje now¹ klatkê animacji
    void addFrame(SDL_Texture* frame);

    /// Ustawia czas trwania pojedynczej klatki animacji (w sekundach)
    void setFrameDuration(float duration);

    /// Aktualizuje animacjê o zadany czas (deltaTime)
    void update(float deltaTime);

    /// Zwraca wskaŸnik do aktualnej klatki animacji
    SDL_Texture* getCurrentFrame() const;

    /// Resetuje animacjê do pierwszej klatki
    void reset();

private:
    std::vector<SDL_Texture*> frames; /// Wektor wskaŸników do klatek animacji
    float frameDuration = 0.1f;       /// Czas trwania jednej klatki animacji (w sekundach), domyœlnie 0.1s
    float timer = 0.0f;               /// Licznik czasu od poprzedniej zmiany klatki
    size_t currentFrameIndex = 0;     /// Indeks aktualnej klatki animacji
};