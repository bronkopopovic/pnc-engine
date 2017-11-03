#include "Game.h"

void BRO::Game::setResMultiplier(int multiplier) {
    resMultiplier = multiplier;
    resMultiplierF = resMultiplier;
}

void BRO::Game::playerSwitcher() {
    hitCounter = 0;
    currentRoom->idlePlayers.clear();
    for (int i = 0; i < currentHud->playerIcons.size(); i++){
        if (currentHud->playerIcons[i]->iconPoly.getGlobalBounds().contains(currentCursor->sprite.getPosition())){
            hitCounter++;
        }
    }
    for (int i = 0; i < currentHud->playerIcons.size(); i++){
        if (currentHud->playerIcons[i]->iconPoly.getGlobalBounds().contains(currentCursor->sprite.getPosition()) ||
                (!(currentHud->playerIcons[i]->iconPoly.getGlobalBounds().contains(currentCursor->sprite.getPosition())) &&
                 currentHud->playerIcons[i]->isActive && hitCounter == 0))
        {
            currentHud->playerIcons[i]->setActive(true);
            currentPlayer = currentHud->playerIcons[i]->linkedPlayer;
        } else {
            currentRoom->idlePlayers.push_back(currentHud->playerIcons[i]->linkedPlayer);
            currentHud->playerIcons[i]->setActive(false);
        }
    }
}