#include "AttackCommand.hpp"

// Wykonuje komend� ataku na podanym graczu
void AttackCommand::Execute(Player& player) {
    player.Attack();
}