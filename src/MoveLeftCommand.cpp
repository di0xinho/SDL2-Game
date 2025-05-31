#include "MoveLeftCommand.hpp"

// Wykonuje komendê ruchu w lewo na przekazanym obiekcie gracza
void MoveLeftCommand::Execute(Player& player) { player.MoveLeft(); }