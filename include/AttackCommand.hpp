#pragma once

#include "Command.hpp"
#include "Player.hpp"

/// Klasa reprezentuj¹ca polecenie ataku dla gracza (wzorzec Command)
class AttackCommand : public Command {
public:
    /// Wykonuje komendê ataku na przekazanym obiekcie Player
    void Execute(Player& player) override;
};