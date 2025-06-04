#pragma once
#include "Command.hpp"
#include "Player.hpp"

/// Komenda odpowiadaj�ca za wykonanie skoku przez gracza (wzorzec Command)
class JumpCommand : public Command {
public:
    /// Wykonuje akcj� skoku na przekazanym graczu
    void Execute(Player& player) override;
};