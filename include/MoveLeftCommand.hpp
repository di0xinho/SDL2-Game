#pragma once

#include "Command.hpp"
#include "Player.hpp"

/// Komenda odpowiadaj�ca za ruch gracza w lewo
class MoveLeftCommand : public Command {
public:
    /// Wykonuje komend� ruchu w lewo na przekazanym obiekcie gracza
    void Execute(Player& player) override;
};