#include "Game.h"

void BRO::Game::setResMultiplier(int multiplier) {
    resMultiplier = multiplier;
    resMultiplierF = resMultiplier;
}

void BRO::Game::playerSwitcher(BRO::Game &game, BRO::Hud &hud) {
    game.currentRoom->idlePlayers.clear();
    for (int i = 0; i < hud.playerIcons.size(); i++){
        if (hud.playerIcons[i]->iconPoly.getGlobalBounds().contains(currentCursor->sprite.getPosition())){
            hud.playerIcons[i]->setActive(true);
            game.currentRoom->currentPlayer = hud.playerIcons[i]->linkedPlayer;
        } else {
            game.currentRoom->idlePlayers.push_back(hud.playerIcons[i]->linkedPlayer);
            hud.playerIcons[i]->setActive(false);
        }
    }
}