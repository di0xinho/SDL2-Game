#pragma once

#include "Command.hpp"
#include "Player.hpp"
#include <vector>
#include "Weapon.hpp"
#include "GameData.hpp"

/// Klasa reprezentuj¹ca polecenie ataku dla gracza (wzorzec Command)
class AttackCommand : public Command {
public:
    /// Konstruktor przyjmuj¹cy teksturê broni oraz referencjê do wektora broni
    AttackCommand(SDL_Texture* weaponTexture, std::vector<Weapon>& weapons)
        : weaponTexture(weaponTexture), weapons(weapons) {
    }
    /// Wykonuje komendê ataku na przekazanym obiekcie Player
    void Execute(Player& player) override;
private:
    SDL_Texture* weaponTexture;      // WskaŸnik na teksturê broni
    std::vector<Weapon>& weapons;    // Referencja do wektora aktywnych broni
    std::shared_ptr<GameData> _data; // Dane gry
};