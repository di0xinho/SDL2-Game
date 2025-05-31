#include "AttackCommand.hpp"

// Wykonuje komendê ataku na podanym graczu
void AttackCommand::Execute(Player& player) {
    player.Attack();
}