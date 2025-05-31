#pragma once

#include <memory>
#include <stack>
#include "State.hpp"

/// Alias na unikalny wskaŸnik do stanu gry
typedef std::unique_ptr<State> StateRef;

/// Klasa odpowiedzialna za zarz¹dzanie stosami stanów gry
/// Pozwala dodawaæ, usuwaæ, zamieniaæ i aktywowaæ stany gry (np. menu, stan rozgrywki, pauza)
class StateMachine
{
public:
    /// Konstruktor.
    StateMachine() {}

    /// Destruktor.
    ~StateMachine() {}

    /// Dodaje nowy stan do stosu stanów
    void AddState(StateRef newState, bool isReplacing = true);

    /// Usuwa bie¿¹cy stan z wierzchu stosu
    void RemoveState();

    /// Przetwarza oczekuj¹ce zmiany stanów (dodanie/usuniêcie) - wywo³ywane na pocz¹tku ka¿dej pêtli gry
    void ProcessStateChanges();

    /// Zwraca wskaŸnik do aktywnego stanu gry (najwy¿ej na stosie)
    StateRef& GetActiveState();

    /// Czyœci ca³y stos stanów
    void Clear();

private:
    /// Stos przechowuj¹cy unikalne wskaŸniki do stanów gry
    std::stack<StateRef> _states;

    /// WskaŸnik na nowy stan oczekuj¹cy na dodanie
    StateRef _newState;

    /// Flaga oznaczaj¹ca usuwanie stanu
    bool _isRemoving = false;

    /// Flagi kontroluj¹ce dodawanie i zamianê stanu
    bool _isAdding = false, _isReplacing = false;
};