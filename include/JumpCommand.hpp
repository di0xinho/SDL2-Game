#pragma once
#include "Command.hpp"
#include "Player.hpp"

class JumpCommand : public Command {
public:
    void Execute(Player& player) override;
};
