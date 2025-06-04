#include "InputManager.hpp"

// Konstruktor — inicjuje mapy i pozycjê myszy
InputManager::InputManager() {}
InputManager::~InputManager() {}

/// Aktualizuje stan wejœcia (klawiatura/mysz) na podstawie pojedynczego zdarzenia SDL
void InputManager::update(const SDL_Event& event) {
    // Resetuj "pressed" na pocz¹tku ka¿dej pêtli obs³ugi zdarzeñ!
    // (Wywo³uj update(event) dla ka¿dego eventu z pêtli SDL_PollEvent)

    // Klawiatura
    if (event.type == SDL_KEYDOWN && !event.key.repeat) {
        keyPressed[event.key.keysym.scancode] = true;
        keyDown[event.key.keysym.scancode] = true;
    }
    if (event.type == SDL_KEYUP) {
        keyDown[event.key.keysym.scancode] = false;
        keyPressed[event.key.keysym.scancode] = false;
    }

    // Mysz
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        mouseButtonPressed[event.button.button] = true;
        mouseButtonDown[event.button.button] = true;
    }
    if (event.type == SDL_MOUSEBUTTONUP) {
        mouseButtonDown[event.button.button] = false;
        mouseButtonPressed[event.button.button] = false;
    }
    if (event.type == SDL_MOUSEMOTION) {
        mousePos.x = event.motion.x;
        mousePos.y = event.motion.y;
    }
}

/// Sprawdza czy dany klawisz (podany jako SDL_Scancode) zosta³ wciœniêty w tej klatce
bool InputManager::isKeyPressed(SDL_Scancode key) const {
    return keyPressed[key];
}

/// Sprawdza czy dany klawisz jest ca³y czas wciœniêty (przechowywany stan)
bool InputManager::isKeyDown(SDL_Scancode key) const {
    return keyDown[key];
}

/// Sprawdza czy dany przycisk myszy zosta³ klikniêty w tej klatce
bool InputManager::isMouseButtonPressed(Uint8 button) const {
    return mouseButtonPressed[button];
}

/// Zwraca aktualn¹ pozycjê myszy na ekranie
SDL_Point InputManager::getMousePosition() const {
    return mousePos;
}

/// Sprawdza czy klikniêto w dany prostok¹t (np. przycisk UI)
bool InputManager::isRectClicked(const SDL_Rect& rect, Uint8 button) const {
    if (!isMouseButtonPressed(button))
        return false;
    return SDL_PointInRect(&mousePos, &rect);
}