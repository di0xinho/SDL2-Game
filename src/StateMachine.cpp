#include "StateMachine.hpp"

/// Dodaje nowy stan do maszyny stan�w
/// Je�li flaga isReplacing = true, obecny stan zostaje usuni�ty
/// Je�li flaga isReplacing = false, obecny stan jest pauzowany
void StateMachine::AddState(StateRef newState, bool isReplacing)
{
	this->_isAdding = true;
	this->_isReplacing = isReplacing;
	this->_newState = std::move(newState);
}

/// Oznacza obecny stan do usuni�cia podczas najbli�szego ProcessStateChanges()
void StateMachine::RemoveState()
{
	this->_isRemoving = true;
}

/// Przetwarza oczekuj�ce zmiany w stosie stan�w
/// Usuwa lub dodaje stany, aktywuje Init()/pause()/resume() w zale�no�ci od sytuacji
void StateMachine::ProcessStateChanges()
{
	// Obs�uga usuwania stanu
	if (this->_isRemoving && !this->_states.empty())
	{
		this->_states.pop();

		// Je�li jest jeszcze jaki� stan, wzn�w go
		if (!this->_states.empty())
		{
			this->_states.top()->resume();
		}

		this->_isRemoving = false;
	}

	// Obs�uga dodawania nowego stanu
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

/// Zwraca referencj� do aktualnie aktywnego stanu gry (na g�rze stosu)
StateRef& StateMachine::GetActiveState()
{
	return this->_states.top();
}

/// Czy�ci ca�y stos stan�w oraz resetuje flagi kontrolne
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