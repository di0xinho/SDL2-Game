#include "MoveRightCommand.hpp"

// Wykonuje komend� ruchu w prawo na przekazanym obiekcie gracza
void MoveRightCommand::Execute(Player& player) { player.MoveRight(); }