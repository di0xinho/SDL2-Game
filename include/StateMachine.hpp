#pragma once

#include <memory>
#include <stack>
#include "State.hpp"

/// Alias na unikalny wska�nik do stanu gry
typedef std::unique_ptr<State> StateRef;

/// Klasa odpowiedzialna za zarz�dzanie stosami stan�w gry
/// Pozwala dodawa�, usuwa�, zamienia� i aktywowa� stany gry (np. menu, stan rozgrywki, pauza)
class StateMachine
{
public:
    /// Konstruktor.
    StateMachine() {}

    /// Destruktor.
    ~StateMachine() {}

    /// Dodaje nowy stan do stosu stan�w
    void AddState(StateRef newState, bool isReplacing = true);

    /// Usuwa bie��cy stan z wierzchu stosu
    void RemoveState();

    /// Przetwarza oczekuj�ce zmiany stan�w (dodanie/usuni�cie) - wywo�ywane na pocz�tku ka�dej p�tli gry
    void ProcessStateChanges();

    /// Zwraca wska�nik do aktywnego stanu gry (najwy�ej na stosie)
    StateRef& GetActiveState();

    /// Czy�ci ca�y stos stan�w
    void Clear();

private:
    /// Stos przechowuj�cy unikalne wska�niki do stan�w gry
    std::stack<StateRef> _states;

    /// Wska�nik na nowy stan oczekuj�cy na dodanie
    StateRef _newState;

    /// Flaga oznaczaj�ca usuwanie stanu
    bool _isRemoving = false;

    /// Flagi kontroluj�ce dodawanie i zamian� stanu
    bool _isAdding = false, _isReplacing = false;
};