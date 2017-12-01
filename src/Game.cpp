#include "Game.h"

void BRO::Game::setResMultiplier(int multiplier) {
    resMultiplier = multiplier;
    resMultiplierF = resMultiplier;
}

void BRO::Game::playerSwitcher(BRO::Game &game) {
    clickCounter = 0;
    game.currentRoom->idlePlayers.clear();
    mappedCursor.x = currentCursor->sprite.getPosition().x - game.currentRoom->mask.left;
    mappedCursor.y = currentCursor->sprite.getPosition().y - game.currentRoom->mask.top;
    for (int i = 0; i < currentHud->playerIcons.size(); i++){
        if (currentHud->playerIcons[i]->sprite.getGlobalBounds().contains(mappedCursor)){
            clickCounter++;
        }
    }
    for (int i = 0; i < currentHud->playerIcons.size(); i++){
        if (currentHud->playerIcons[i]->sprite.getGlobalBounds().contains(mappedCursor) ||
                (!(currentHud->playerIcons[i]->sprite.getGlobalBounds().contains(mappedCursor)) &&
                 currentHud->playerIcons[i]->isActive && clickCounter == 0)){
            currentHud->playerIcons[i]->setActive(true);
            game.currentRoom->currentPlayer = currentHud->playerIcons[i]->linkedPlayer;
        } else {
            game.currentRoom->idlePlayers.push_back(currentHud->playerIcons[i]->linkedPlayer);
            currentHud->playerIcons[i]->setActive(false);
        }
    }
}