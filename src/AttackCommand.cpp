#include "AttackCommand.hpp"

// Wykonuje komendê ataku - rzut no¿em, jeœli mo¿liwe
void AttackCommand::Execute(Player& player) {
    // Jeœli gracz mo¿e rzuciæ broni¹ (nie trwa cooldown)
    if (player.canShoot()) {
        // Rzuæ broni¹ (np. no¿em)
        player.tryThrowWeapon(_data, weaponTexture, weapons);

        // Odtwórz dŸwiêk rzutu no¿em, jeœli jest ustawiony
        if (auto sound = player.getKnifeThrowSound()) {
            Mix_PlayChannel(-1, sound, 0);
        }
    }
}