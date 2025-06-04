#pragma once
#include "Command.hpp"
#include "Player.hpp"

/// Komenda odpowiadaj¹ca za wykonanie skoku przez gracza (wzorzec Command)
class JumpCommand : public Command {
public:
    /// Wykonuje akcjê skoku na przekazanym graczu
    void Execute(Player& player) override;
};