#pragma once

#include "Command.hpp"
#include "Player.hpp"

/// Komenda odpowiadaj¹ca za ruch gracza w prawo
class MoveRightCommand : public Command {
public:
    /// Wykonuje komendê ruchu w prawo na przekazanym obiekcie gracza
    void Execute(Player& player) override;
};