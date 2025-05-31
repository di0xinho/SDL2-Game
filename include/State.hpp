#pragma once

/// Klasa bazowa reprezentuj�ca stan gry 
/// Pozwala na definiowanie w�asnych stan�w przez dziedziczenie
class State
{
public:
    /// Wirtualny destruktor
    virtual ~State() {}

    /// Metoda wywo�ywana podczas inicjalizacji stanu (np. pod �adowanie zasob�w)
    virtual void Init() = 0;

    /// Obs�uga wej�cia u�ytkownika (np. klawiatura, mysz)
    virtual void HandleInput() = 0;

    /// Aktualizacja logiki stanu
    virtual void Update(float dt) = 0;

    /// Rysowanie stanu na ekranie
    virtual void Draw(float dt) = 0;

    /// Opcjonalna metoda pauzuj�ca stan 
    virtual void pause() {}

    /// Opcjonalna metoda wznawiaj�ca stan 
    virtual void resume() {}
};