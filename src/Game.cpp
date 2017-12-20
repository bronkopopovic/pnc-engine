#include "Game.h"

void BRO::Game::setResMultiplier(int multiplier) {
    resMultiplier = multiplier;
    resMultiplierF = resMultiplier;
}

void BRO::Game::mapCursor(BRO::Game &game) {
    mappedCursor.x = currentCursor->sprite.getPosition().x - game.currentRoom->mask.left;
    mappedCursor.y = currentCursor->sprite.getPosition().y - game.currentRoom->mask.top;
}

void BRO::Game::playerSwitcher(BRO::Game &game) {
    // check if some other action was already performed by the click
    if (! game.clicked){
        clickCounter = 0;
        game.currentRoom->idlePlayers.clear();
        for (int i = 0; i < currentHud->playerIcons.size(); i++){
            if (currentHud->playerIcons[i]->sprite.getGlobalBounds().contains(mappedCursor)){
                clickCounter++;
                game.clicked = true;
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
}