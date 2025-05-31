#include "StateMachine.hpp"

/// Dodaje nowy stan do maszyny stanów
/// Jeœli flaga isReplacing = true, obecny stan zostaje usuniêty
/// Jeœli flaga isReplacing = false, obecny stan jest pauzowany
void StateMachine::AddState(StateRef newState, bool isReplacing)
{
	this->_isAdding = true;
	this->_isReplacing = isReplacing;
	this->_newState = std::move(newState);
}

/// Oznacza obecny stan do usuniêcia podczas najbli¿szego ProcessStateChanges()
void StateMachine::RemoveState()
{
	this->_isRemoving = true;
}

/// Przetwarza oczekuj¹ce zmiany w stosie stanów
/// Usuwa lub dodaje stany, aktywuje Init()/pause()/resume() w zale¿noœci od sytuacji
void StateMachine::ProcessStateChanges()
{
	// Obs³uga usuwania stanu
	if (this->_isRemoving && !this->_states.empty())
	{
		this->_states.pop();

		// Jeœli jest jeszcze jakiœ stan, wznów go
		if (!this->_states.empty())
		{
			this->_states.top()->resume();
		}

		this->_isRemoving = false;
	}

	// Obs³uga dodawania nowego stanu
	if (this->_isAdding)
	{
		if (!this->_states.empty())
		{
			if (this->_isReplacing)
			{
				this->_states.pop();
			}
			else
			{
				this->_states.top()->pause();
			}
		}

		this->_states.push(std::move(this->_newState));
		this->_states.top()->Init();
		this->_isAdding = false;
	}
}

/// Zwraca referencjê do aktualnie aktywnego stanu gry (na górze stosu)
StateRef& StateMachine::GetActiveState()
{
	return this->_states.top();
}

/// Czyœci ca³y stos stanów oraz resetuje flagi kontrolne
void StateMachine::Clear()
{
	while (!_states.empty())
	{
		_states.pop();
	}
	_isAdding = false;
	_isRemoving = false;
	_isReplacing = false;
}