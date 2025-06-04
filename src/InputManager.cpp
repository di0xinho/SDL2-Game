#include "InputManager.hpp"

// Konstruktor � inicjuje mapy i pozycj� myszy
InputManager::InputManager() {}
InputManager::~InputManager() {}

/// Aktualizuje stan wej�cia (klawiatura/mysz) na podstawie pojedynczego zdarzenia SDL
void InputManager::update(const SDL_Event& event) {
    // Resetuj "pressed" na pocz�tku ka�dej p�tli obs�ugi zdarze�!
    // (Wywo�uj update(event) dla ka�dego eventu z p�tli SDL_PollEvent)

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

/// Sprawdza czy dany klawisz (podany jako SDL_Scancode) zosta� wci�ni�ty w tej klatce
bool InputManager::isKeyPressed(SDL_Scancode key) const {
    return keyPressed[key];
}

/// Sprawdza czy dany klawisz jest ca�y czas wci�ni�ty (przechowywany stan)
bool InputManager::isKeyDown(SDL_Scancode key) const {
    return keyDown[key];
}

/// Sprawdza czy dany przycisk myszy zosta� klikni�ty w tej klatce
bool InputManager::isMouseButtonPressed(Uint8 button) const {
    return mouseButtonPressed[button];
}

/// Zwraca aktualn� pozycj� myszy na ekranie
SDL_Point InputManager::getMousePosition() const {
    return mousePos;
}

/// Sprawdza czy klikni�to w dany prostok�t (np. przycisk UI)
bool InputManager::isRectClicked(const SDL_Rect& rect, Uint8 button) const {
    if (!isMouseButtonPressed(button))
        return false;
    return SDL_PointInRect(&mousePos, &rect);
}