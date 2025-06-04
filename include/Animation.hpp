#pragma once

#include <SDL.h>
#include <vector>

/// Klasa obs�uguj�ca animacje sprite'�w opart� na wektorze wska�nik�w do tekstur SDL
class Animation {
public:
    /// Domy�lny konstruktor
    Animation();

    /// Dodaje now� klatk� animacji
    void addFrame(SDL_Texture* frame);

    /// Ustawia czas trwania pojedynczej klatki animacji (w sekundach)
    void setFrameDuration(float duration);

    /// Aktualizuje animacj� o zadany czas (deltaTime)
    void update(float deltaTime);

    /// Zwraca wska�nik do aktualnej klatki animacji
    SDL_Texture* getCurrentFrame() const;

    /// Resetuje animacj� do pierwszej klatki
    void reset();

private:
    std::vector<SDL_Texture*> frames; /// Wektor wska�nik�w do klatek animacji
    float frameDuration = 0.1f;       /// Czas trwania jednej klatki animacji (w sekundach), domy�lnie 0.1s
    float timer = 0.0f;               /// Licznik czasu od poprzedniej zmiany klatki
    size_t currentFrameIndex = 0;     /// Indeks aktualnej klatki animacji
};