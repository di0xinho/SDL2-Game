#include "JumpCommand.hpp"

// Wykonuje komend� skoku na przekazanym obiekcie gracza
void JumpCommand::Execute(Player& player) {
    player.Jump();
}