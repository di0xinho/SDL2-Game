#include "MoveLeftCommand.hpp"

// Wykonuje komend� ruchu w lewo na przekazanym obiekcie gracza
void MoveLeftCommand::Execute(Player& player) { player.MoveLeft(); }