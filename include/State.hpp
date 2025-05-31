#pragma once

/// Klasa bazowa reprezentuj¹ca stan gry 
/// Pozwala na definiowanie w³asnych stanów przez dziedziczenie
class State
{
public:
    /// Wirtualny destruktor
    virtual ~State() {}

    /// Metoda wywo³ywana podczas inicjalizacji stanu (np. pod ³adowanie zasobów)
    virtual void Init() = 0;

    /// Obs³uga wejœcia u¿ytkownika (np. klawiatura, mysz)
    virtual void HandleInput() = 0;

    /// Aktualizacja logiki stanu
    virtual void Update(float dt) = 0;

    /// Rysowanie stanu na ekranie
    virtual void Draw(float dt) = 0;

    /// Opcjonalna metoda pauzuj¹ca stan 
    virtual void pause() {}

    /// Opcjonalna metoda wznawiaj¹ca stan 
    virtual void resume() {}
};