#include "MoveRightCommand.hpp"

// Wykonuje komendê ruchu w prawo na przekazanym obiekcie gracza
void MoveRightCommand::Execute(Player& player) { player.MoveRight(); }