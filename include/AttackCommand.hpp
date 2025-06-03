#pragma once

#include "Command.hpp"
#include "Player.hpp"
#include <vector>
#include "Weapon.hpp"
#include "GameData.hpp"

/// Klasa reprezentuj�ca polecenie ataku dla gracza (wzorzec Command)
class AttackCommand : public Command {
public:
    /// Konstruktor przyjmuj�cy tekstur� broni oraz referencj� do wektora broni
    AttackCommand(SDL_Texture* weaponTexture, std::vector<Weapon>& weapons)
        : weaponTexture(weaponTexture), weapons(weapons) {
    }
    /// Wykonuje komend� ataku na przekazanym obiekcie Player
    void Execute(Player& player) override;
private:
    SDL_Texture* weaponTexture;      // Wska�nik na tekstur� broni
    std::vector<Weapon>& weapons;    // Referencja do wektora aktywnych broni
    std::shared_ptr<GameData> _data; // Dane gry
};