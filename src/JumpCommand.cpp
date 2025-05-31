#include "JumpCommand.hpp"

// Wykonuje komendê skoku na przekazanym obiekcie gracza
void JumpCommand::Execute(Player& player) {
    player.Jump();
}