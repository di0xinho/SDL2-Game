#pragma once

#include <SDL.h>

/// Klasa zarządzająca wejściem użytkownika (klawiatura, mysz) dla SDL2
class InputManager {
public:
    InputManager();
    ~InputManager();

    /// Musi być wołane na początku każdej pętli zdarzeń!
    void update(const SDL_Event& event);

    /// Sprawdza, czy dany klawisz został wciśnięty (tylko raz do momentu puszczenia)
    bool isKeyPressed(SDL_Scancode key) const;

    /// Sprawdza, czy dany klawisz jest aktualnie wciśnięty
    bool isKeyDown(SDL_Scancode key) const;

    /// Sprawdza, czy przycisk myszy został wciśnięty (tylko raz do momentu puszczenia)
    bool isMouseButtonPressed(Uint8 button) const;

    /// Zwraca pozycję kursora myszy względem okna gry
    SDL_Point getMousePosition() const;

    /// Sprawdza, czy dany prostokąt (SDL_Rect) został kliknięty wybranym przyciskiem myszy
    bool isRectClicked(const SDL_Rect& rect, Uint8 button) const;

private:
    // Tablice stanów klawiszy (pressed oraz down)
    bool keyPressed[SDL_NUM_SCANCODES] = { false };
    bool keyDown[SDL_NUM_SCANCODES] = { false };

    // Stan przycisków myszy
    bool mouseButtonPressed[8] = { false }; // SDL obsługuje do 8 przycisków myszy
    bool mouseButtonDown[8] = { false };

    SDL_Point mousePos = { 0, 0 };
};